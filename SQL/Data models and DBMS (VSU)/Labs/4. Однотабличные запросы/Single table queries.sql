-- 1. Вывести список объектов недвижимости не закрепленных ни за одним сотрудником.
SELECT * FROM PROPERTY WHERE Staff_no IS NULL;
-- 2 Вывести адреса объектов недвижимости, которые   были осмотрены покупателями.
SELECT DISTINCT City, Street, House, Flat FROM PROPERTY 
INNER JOIN VIEWING ON VIEWING.Property_no = PROPERTY.Property_no;
-- 3 Вывести адреса объектов недвижимости, которые не  были осмотрены покупателями.
SELECT City, Street, House, Flat FROM PROPERTY
LEFT JOIN VIEWING
ON VIEWING.Property_no = PROPERTY.Property_no
WHERE VIEWING.Property_no IS NULL;
-- 4 Вывести данные  (фамилия, номер телефона) продавцов всех осмотренных покупате-лями объектов собственности, у которых (объектов) в поле COMMENT таблицы VIEWING установлено значение «требует ремонта».
SELECT LName, Otel_no FROM OWNER 
INNER JOIN PROPERTY
ON OWNER.Owner_no = PROPERTY.Owner_no
INNER JOIN VIEWING
ON PROPERTY.Property_no = VIEWING.Property_no 
WHERE Comments = 'требует ремонта';
-- 5 Вывести данные об объектах собственности (Property_no, адрес) об объектах соб-ственности, которые были зарегистрированы  в БД более трех месяцев назад и не бы-ли проданы.
SELECT PROPERTY.Property_no, City, Street, House, Flat FROM PROPERTY
LEFT JOIN VIEWING
ON PROPERTY.Property_no = VIEWING.Property_no
WHERE Date_registration <= DATEADD(MONTH, -3, GETDATE())
AND (Comments = 'не согласен' OR VIEWING.Property_no IS NULL OR Comments = 'требует ремонта')
-- 6 Вывести список трёхкомнатных квартир в Витебске,  расположенных на втором – четвертом этажах,  у которых площадь кухни не менее 10 метров и  цена которых не превышает 70000$.
SELECT * FROM PROPERTY
WHERE Rooms = 3 AND Floor_Num in (2, 4) AND City = 'Витебск' AND Selling_Price <= 70000 AND The_area LIKE '______[1-9]_'
-- 7 Вывести список сотрудников (Staff_no, Fname), продавших более одного объекта не-движимости.
SELECT STAFF.Staff_no, Fname FROM STAFF 
INNER JOIN 
PROPERTY ON STAFF.Staff_no = PROPERTY.Staff_no 
WHERE (SELECT COUNT(*) FROM VIEWING
WHERE PROPERTY.Property_no = VIEWING.Property_no AND Comments = 'согласен') > 1
-- 8 Найти номера отделений и фамилии служащих, однофамильцы которых работают в этом же отделении.
SELECT DISTINCT B1.Branch_no, S1.FName FROM BRANCH B1
INNER JOIN
STAFF S1 ON S1.Branch_no = B1.Branch_no 
INNER JOIN
(SELECT B2.Branch_no, S2.FName, S2.Staff_no FROM BRANCH B2 
INNER JOIN
STAFF S2 ON S2.Branch_no = B2.Branch_no) AS T2 ON B1.Branch_no = T2.Branch_no AND S1.FName = T2.FName AND S1.Staff_no <> T2.Staff_no