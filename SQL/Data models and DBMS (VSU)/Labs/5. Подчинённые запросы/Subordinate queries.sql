-- 1. Вывести адреса объектов недвижимости, которые не были осмотрены покупателями (использовать NOT IN). --
    
    -- QUERY: --
    SELECT PROPERTY.City, PROPERTY.Street, PROPERTY.Flat
    FROM PROPERTY
    WHERE PROPERTY.Property_no NOT IN (SELECT VIEWING.Property_no FROM VIEWING);

-- 2. Вывести адреса объектов недвижимости, которые не были осмотрены покупателями (использовать NOT EXISTS). --


    SELECT PROPERTY.City, PROPERTY.Street, PROPERTY.Flat 
    FROM PROPERTY
    WHERE NOT EXISTS (SELECT City, Street, Flat  FROM VIEWING WHERE PROPERTY.Property_no = VIEWING.Property_no)

-- 3. Вывести адреса объектов недвижимости, которые не были осмотрены покупателями (не использовать NOT IN, NOT EXISTS). --
    -- QUERY: --


-- 4. Вывести список трехкомнатных квартир, цены которых не превышают средней цены двухкомнатной квартиры. --

    -- QUERY: --
    SELECT * FROM PROPERTY
    WHERE PROPERTY.Rooms = 3 and PROPERTY.Selling_Price < (SELECT AVG(PROPERTY.Selling_Price) FROM PROPERTY WHERE Rooms = 2)

-- 5. Вывести список адресов квартир в каждом городе, цены которых превышают среднюю цену квартир в этом городе. --

    -- QUERY: --
    SELECT PROPERTY.City, PROPERTY.Street, PROPERTY.Flat
    FROM PROPERTY
    WHERE PROPERTY.Selling_Price > (SELECT AVG(PROPERTY.Selling_Price) FROM Property WHERE PROPERTY.City = PROPERTY.City)

-- 6. Вывести список адресов квартир однокомнатных квартир в Витебске, цены которых выше цены любой двухкомнатной квартиры в Полоцке. --

-- 7. Вывести номера отделений, в которых средняя заработная плата сотрудников в два раза ниже заработной платы директора компании. --

    -- QUERY: -- 
    SELECT STAFF.Branch_no
    FROM STAFF
    WHERE STAFF.Position != 'директор' 
    GROUP BY STAFF.Branch_no 
    HAVING AVG(STAFF.Salary)*2  <= (SELECT STAFF.Salary FROM STAFF WHERE STAFF.Position = 'директор' AND STAFF.Branch_no = STAFF.Branch_no)

-- 8. Найти сотрудников (Staff_no, Fname), продавших максимальное количество объектов недвижимости в своем отделении, в течение последних трех месяцев. --

    -- !!! QUERY: -- 
    SELECT PROPERTY.Staff_no, STAFF.FName
    FROM PROPERTY
    JOIN STAFF ON STAFF.Staff_no = PROPERTY.Staff_no
    WHERE		
        (SELECT COUNT(*) FROM VIEWING
        JOIN PROPERTY ON VIEWING.Property_no = PROPERTY.Property_no
        WHERE PROPERTY.Property_no = PROPERTY.Property_no
        AND VIEWING.Comments = 'согласен'
        AND DATEDIFF(MONTH, VIEWING.Date_View, GETDATE()) < 3)
        = 
        (SELECT TOP 1 COUNT(*) FROM VIEWING
        JOIN PROPERTY ON VIEWING.Property_no = PROPERTY.Property_no
        WHERE PROPERTY.Branch_no = PROPERTY.Branch_no
        AND VIEWING.Comments = 'согласен'
        AND DATEDIFF(MONTH, VIEWING.Date_View, GETDATE()) < 3
        GROUP BY PROPERTY.Staff_no
        ORDER BY COUNT(*) DESC);

-- 9. Определить количество отделений, в которых средняя заработная плата в два раза ниже заработной платы директора компании. --

    -- QUERY: --
    SELECT COUNT(*) FROM
	(SELECT STAFF.Branch_no 
	FROM STAFF
	WHERE STAFF.Position != 'директор' 
	GROUP BY STAFF.Branch_no HAVING 2*AVG(STAFF.Salary) <=
		(SELECT STAFF.Salary 
		FROM STAFF
		WHERE STAFF.Position = 'директор' AND STAFF.Branch_no = STAFF.Branch_no)) AS Salary 


-- 10. Определить количество сотрудников компании заработная плата которых превышают среднюю заработную плату. --

    -- QUERY: --
    SELECT COUNT(*) 
    FROM STAFF 
    WHERE Salary > (SELECT AVG(Salary) FROM STAFF);


-- 11. Вывести данные сотрудников каждого отделения, заработная плата которых не превышает среднюю заработную плату и которые продали более двух квартир в течение последних шести месяцев. --

    --!!! QUERY: -- 
    SELECT STAFF.Staff_no, STAFF.FName, STAFF.LName
    FROM PROPERTY
    JOIN STAFF ON PROPERTY.Staff_no = STAFF.Staff_no 
    WHERE STAFF.Salary < (SELECT AVG(STAFF.Salary) FROM STAFF)
    AND (SELECT COUNT(*) FROM VIEWING
        JOIN PROPERTY ON VIEWING.Property_no = PROPERTY.Property_no
        WHERE VIEWING.Property_no = PROPERTY.Property_no
        AND Comments = 'согласен'
        AND DATEDIFF(MONTH, VIEWING.Date_View, GETDATE()) < 6) > 2;




