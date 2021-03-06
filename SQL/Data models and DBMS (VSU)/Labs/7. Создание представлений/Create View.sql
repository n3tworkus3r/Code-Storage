-- C помощью SQL запроса создать представление, содержащее данные об агентах, отвечающих за продажу объектов. --
-- Представление должно включать номер отделения (Branch_no), номер работника (Staff_no) и сведения о количестве объектов,
-- за которые он отвечает. --

    -- QUERY: --
    CREATE VIEW STAFF_PROP (Branch_no, Staff_no, Properties)
    AS SELECT STAFF.Branch_no, STAFF.Staff_no, COUNT(*)
    FROM STAFF INNER JOIN PROPERTY ON STAFF.Staff_no=
    PROPERTY.Staff_no
    GROUP BY STAFF.Branch_no, STAFF.Staff_no;

    -- USING: --
    SELECT * FROM STAFF_PROP

    -- DELETE: -- 
    DROP VIEW STAFF_PROP


 -- 1.	Содержащее данные о средней заработной плате отделений компании. --
 -- Представление должно включать номер отделения (Branch_no) и среднюю заработную плату (Salary). --
 -- С помощью представления создать запрос, возвращающий номера  отделений с максимальной  и минимальной средней заработной платой. --

    -- VIEW: --
    CREATE VIEW STAFF_AVG_SALARY (Branch_no, Salary)
    AS SELECT STAFF.Branch_no, AVG(STAFF.Salary)
    FROM STAFF
    GROUP BY STAFF.Branch_no

    -- USING: --
    SELECT * FROM STAFF_AVG_SALARY

    -- QUERY --
    SELECT MAX(Salary) AS "MAX", MIN(Salary) AS "MIN" FROM STAFF_AVG_SALARY

    -- DELETE: -- 
    DROP VIEW STAFF_AVG_SALARY



-- 2.	Содержащее данные о количестве квартир, за который отвечает каждый сотрудник. --
-- Представление должно включать номер сотрудника (Staff_no) и количество квартир, за которые он отвечает. --
-- С помощью представления создать запрос, возвращающий фамилии сотрудников, отвечающих за 2 квартиры. --

    -- VIEW: --
    CREATE VIEW STAFF_PROPERTY (Staff_no, Properties)
    AS SELECT STAFF.Staff_no, COUNT(*)
    FROM STAFF INNER JOIN PROPERTY ON STAFF.Staff_no=PROPERTY.Staff_no
    GROUP BY STAFF.Staff_no;

    -- USING: --
    SELECT * FROM STAFF_PROPERTY

    -- QUERY --
    SELECT STAFF.FName FROM STAFF WHERE STAFF.Staff_no IN (SELECT Staff_no FROM [STAFF_PROPERTY] WHERE Properties= 2)

    -- DELETE: -- 
    DROP VIEW STAFF_PROPERTY

-- 3.	Содержащее сведения об общей площади и площади кухни каждой квартиры в таблице PROPERTY. --
-- Представление должно содержать поля Property_no, Общая площадь, Площадь кухни. --
-- С помощью представления вывести адреса  квартир, у которых площадь кухни не менее 12 метров. --

    -- VIEW: --
    CREATE VIEW PROP_AREA (Property_no, area, kitchen)
    AS
    SELECT Property_no, 
        (SELECT SUM(CAST( VALUE AS float)) FROM STRING_SPLIT(PROPERTY.the_area, '/')) as full_area,  
        CAST( right(CONVERT(nvarchar,the_area), charindex('/', REVERSE(CONVERT(nvarchar,the_area))) - 1) AS INT)
    FROM PROPERTY 




    -- USING: --
    SELECT * FROM PROPERTY_AREA

    -- QUERY --
    SELECT PROPERTY.Street, PROPERTY.House, PROPERTY.Flat FROM PROPERTY WHERE PROPERTY.Property_no IN (SELECT Property_no FROM PROP_AREA WHERE kitchen >= 12)

    -- DELETE: -- 
    DROP VIEW PROPERTY_AREA





--4.    Содержащее данные о квартирах, которые были осмотрены более 2 раз и у которых в поле comment таблицы Viewing записано «требует ремонта». 
--      С помощью представления создать запрос, возвращающий фамилии и номера телефонов владельцев этих квартир

CREATE VIEW BAD_PROP(Property_no, Owner_no)
AS
SELECT p.Property_no, p.Owner_no
FROM PROPERTY p
INNER JOIN VIEWING v ON p.Property_no = v.Property_no
WHERE v.Comments LIKE 'требует ремонта'
GROUP BY p.Property_no, p.Owner_no
HAVING count(v.Property_no) > 2

GO

SELECT o.Owner_no, o.FName, o.Otel_no
FROM BAD_PROP bp
LEFT JOIN OWNER o ON o.Owner_no = bp.Owner_no



-- КОНТРОЛЬНЫЕ ВОПРОСЫ --

-- 1.	Для чего используются представления?
--    Представление дает возможность пользователю работать только с теми данными,
--    которые ему нужны, кроме того, механизм представлений позволяет скрыть служебные, конфиденциальные данные.

-- 2.	Происходит ли изменение данных в представлении в случае внесения изменений базовые таблицы, на основе которых они созданы?
--    При изменении данных в таблице они автоматически изменяются и в представлении, что обеспечивает актуальное состояние данных. 

-- 3.	В чем заключается отличие горизонтальных и вертикальных представлений?

-- 4.	Можно ли создать представление на основании нескольких таблиц?

-- 5.	Перечислите ограничения на обновление данных в представлениях.
