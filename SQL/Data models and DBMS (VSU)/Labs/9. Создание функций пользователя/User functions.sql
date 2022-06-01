--III.	Создайте пользовательские функции
USE DreamHome

-- 1. Cкалярную, возвращающую имя заданного сотрудника  в формате Фамилия И. 
--     С помощью функции создать запрос для вывода номеров телефонов сотрудников. 

	-- FUNCTION --

	CREATE FUNCTION FullName(@staff_no nchar(9))
	RETURNS nchar(30)
	AS BEGIN
	DECLARE @address nchar(30) = ((SELECT s.fname FROM staff s WHERE s.staff_no=@staff_no) + ' ' +
								SUBSTRING((SELECT s.lname FROM staff s WHERE s.staff_no=@staff_no),1,1)+'.')
	RETURN @address
	END
	GO


 	-- QUERY --

	SELECT dbo.FullName('BMO550260')

	--DROP FUNCTION dbo.FullName



-- 2. Скалярную,  для вывода адреса самой дешевой квартиры с заданным, как параметр, количеством комнат в заданном, как параметр, городе.
--     Вызвать функцию для определения адреса самой дешевой  однокомнатной квартиры в Витебске.

	-- FUNCTION --

	CREATE FUNCTION CheapestPropInCity( @City varchar(20),@Rooms tinyint)
	RETURNS varchar(30)
	AS BEGIN
	DECLARE 
		@address varchar(30),
		@MinPrice int = (SELECT MIN(selling_price) FROM property WHERE city=@City AND rooms=@Rooms)
		SET @address =@City + ', ' +
			(SELECT p.street FROM property p WHERE selling_price = @MinPrice AND rooms=@Rooms) + ' ' +
			(SELECT p.house FROM property p WHERE selling_price = @MinPrice AND rooms=@Rooms)
		RETURN @address
		END

	GO
	
	-- QUERY --

	SELECT dbo.CheapestPropInCity('Витебск',1)




-- 3. Cкалярную, для вычисления количества объектов, проданных отделением в заданном интервале времени. 
--     Вызвать функцию для определения количества объектов:
--      а) проданных одним из отделений за определенный период времени.
--      б) проданных каждым отделением за определенный период времени. 
--      в) рейтинг отделений по числу проданных объектов в заданном интервале времени.

	-- FUNCTION --

	CREATE FUNCTION NumberSelling(@branch_no smallint,@FromDate DATE,@ToDate DATE)
	RETURNS INT
	AS BEGIN
	 RETURN (SELECT COUNT(*)
				FROM viewing v 
				JOIN property p
				ON v.property_no=p.property_no
				JOIN branch b
				ON b.branch_no = p.branch_no
				WHERE comments LIKE 'согласен'
				AND v.date_view>=@FromDate 
				AND v.date_view<=@ToDate
				AND b.branch_no=@branch_no)
	END
	GO

 	-- QUERIES --

	--a) проданных одним из отделений за определенный период времени.
	SELECT dbo.NumberSelling(3,'2015-10-19','2022-10-19');

	--б) проданных каждым отделением за определенный период времени. 
	SELECT dbo.NumberSelling(branch_no,'2015-10-19','2022-10-19') FROM branch

	--в) рейтинг отделений по числу проданных объектов в заданном интервале времени.
	SELECT  dbo.NumberSelling(branch_no,'2015-10-19','2022-10-19') AS 'NumberSelling'
	FROM branch
	ORDER BY 'NumberSelling' DESC

	--DROP FUNCTION dbo.NumberSelling



-- 4. Табличную, возвращающую данные о среднем возрасте сотрудников отделения компании. 
--     Таблица должна включать номер отделения и средний возраст. С помощью функции создать запрос для вывода:
--      а) списка отделений, в которых средний возраст сотрудников превышает 50 лет,
--      б) количества отделений, в которых средний возраст сотрудников превышает 50 лет,
--      в) отделения с минимальным средним возрастом сотрудников.

	-- FUNCTION --

	CREATE FUNCTION AverageAge()
	RETURNS TABLE
	AS RETURN (SELECT s.branch_no, AVG(DATEDIFF(YEAR, s.dob, GETDATE())) AS 'Average age' FROM staff s GROUP BY s.branch_no)
	GO

 	-- QUERIES --

	--а) списка отделений, в которых средний возраст сотрудников превышает 50 лет
	SELECT * FROM AverageAge() a WHERE a.[Average age]>50

	--б) количества отделений, в которых средний возраст сотрудников превышает 50 лет
	SELECT COUNT(*) FROM AverageAge() a WHERE a.[Average age]>50

	--в) отделения с минимальным средним возрастом сотрудников.
	SELECT * FROM AverageAge() a WHERE a.[Average age] = (SELECT MIN(a.[Average age]) FROM AverageAge() a)



