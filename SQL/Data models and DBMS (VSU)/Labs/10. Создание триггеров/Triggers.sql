--IV.  Создайте триггеры
use DreamHome

-- 1. Для удаления из таблиц PROPERTY и VIEWING объекта недвижимости, по которому заключается контракт. 
--     (Предварительно удалить связь  с таблицей CONTRACT)
--     Вывести сообщение о том, что сотрудник, отвечавший за объект, совершил сделку,повысить ему заработную плату на 5%.  
--     Проверьте работоспособность триггера.

	ALTER TABLE contract 
	DROP CONSTRAINT FK_contract_property_no_property_property_no;

	ALTER TABLE contract 
	DROP CONSTRAINT FK_contract_property_no_property_property_no;
	GO

	-- TRIGGER --

	CREATE TRIGGER SellingProperty  
	ON contract
	AFTER INSERT
	AS
	DECLARE @staff_no nchar(9) = (SELECT p.staff_no FROM property p WHERE property_no = 
														(SELECT property_no FROM inserted))
	IF EXISTS (SELECT * FROM property WHERE property_no= (SELECT property_no FROM inserted))  
	BEGIN
		DELETE FROM property WHERE property_NO= (SELECT property_no FROM inserted)
		DELETE FROM viewing WHERE property_NO= (SELECT property_no FROM inserted)
		PRINT('Сотрудник '+@staff_no+' продал квартиру')
		UPDATE staff SET salary=salary+0.05*salary WHERE staff_no=@staff_no
	END;  
	GO  

-- 2. Для вывода сообщения о превышении количества объектов собственности,  закрепленных за сотрудником.
--     При вводе нового объекта в таблицу PROPERTY (количество объектов не должно быть больше трех). 
--     Проверьте работоспособность триггера. 

	-- TRIGGER --

	CREATE TRIGGER Workload
	ON property
	AFTER INSERT
	AS
		DECLARE @staff_no nchar(9) =(SELECT staff_no FROM inserted)
		IF((SELECT COUNT(*) FROM property WHERE staff_no =@staff_no)>=3)
		BEGIN
		PRINT('Данный сотрудник отвечает уже более чем за 3 квартиры. Рекомендуется выбратьдругога сотрудника')
		--ROLLBACK;  
		END

-- 3. Для снижения заработной платы сотрудника на 5%, если квартира,
--     За которую он отвечает  осматривается  в третий раз,  в поле  Comments таблицы VIEWING вводится значение 
--     "не согласен"" и  если его зарплата превышает среднюю заработную плату отделения в котором он работает. 
--     Проверьте работоспособность триггера.

	-- TRIGGER --

	CREATE TRIGGER WhatsWrongWithYou
	ON viewing
	AFTER INSERT
	AS
	DECLARE @staff_no nchar(9) = (SELECT p.staff_no FROM inserted i JOIN property p ON p.property_no=i.property_no)

	DECLARE @numberTries int = (SELECT COUNT(*)
				FROM viewing 
				JOIN property 
				ON viewing.property_no=property.property_no
				WHERE comments LIKE 'не согласен' AND staff_no=@Staff_no);

	DECLARE @middleSalary int = 
		(
		SELECT AVG(salary) FROM staff WHERE branch_no =
			(
			SELECT branch_no FROM staff WHERE staff_no= @staff_no
			)
		)
	IF(@numberTries>=3 AND (SELECT salary FROM staff WHERE staff_no=@staff_no) > @middleSalary)
	BEGIN
		UPDATE staff 
		SET salary-=salary*0.05
	END

-- 4. Создать триггер, который при занесении данных в таблицу OWNER проверяет, 
--     есть ли у этого владельца объекты проданные ранее (содержатся в таблице CONTRACT) и выводит сообщение,
--     о дате заключения предыдущей сделки для этого владельца.  Проверьте работоспособность триггера.

	-- TRIGGER --

	CREATE TRIGGER CheckOwner
	ON owner
	AFTER INSERT
	AS
		SELECT c.date_contract
		FROM contract c 
		JOIN property p 
		ON c.property_no=p.property_no 
		WHERE p.owner_no=(SELECT owner_no FROM inserted) ---Qiestion: HOW CHECK TRIGGER (1)

	GO

-- 5. Для удаления данных о владельце недвижимости из таблицы OWNER,
--     при продаже принадлежащего ему объекта недвижимости в том случае, если у него нет других объектов.
--     Проверьте работоспособность триггера.

	-- TRIGGER --
	
	CREATE TRIGGER DeleteUselessOwner
	ON property
	AFTER DELETE
	AS
	 IF NOT EXISTS(SELECT * FROM property WHERE owner_no = (SELECT owner_no FROM deleted))
	BEGIN
		DELETE FROM owner WHERE owner_no =  (SELECT owner_no FROM deleted)
	END