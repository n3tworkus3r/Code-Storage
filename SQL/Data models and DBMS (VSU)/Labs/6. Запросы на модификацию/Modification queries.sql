-- 1. Снизить на 10% заработную плату сотрудников, которые не продали ни одной квартиры, и
-- заработная плата которых превышает среднюю заработную плату в своем отделении. --
    
    -- QUERY: --
    UPDATE STAFF
    SET Salary = Salary * 0.9
    WHERE Staff_no NOT IN 
        (SELECT p.Staff_no FROM VIEWING AS v
	    JOIN PROPERTY AS p ON v.Property_no = p.Property_no
	    WHERE Comments = 'согласен')
        AND Salary > 
        (SELECT AVG(s2.Salary) 
	    FROM STAFF AS s2
	    WHERE STAFF.Branch_no = s2.Branch_no);

-- 2. Уменьшить на 10% цены самых дорогих в своих отделениях квартир. --
   
    -- QUERY: --
	UPDATE PROPERTY
	SET Selling_Price = Selling_Price * 0.9
	WHERE Selling_Price >= ALL
	    (SELECT p1.Selling_Price 
		FROM PROPERTY AS p1
		WHERE PROPERTY.Branch_no= p1.Branch_no);

-- В локальную временную таблицу занести список сотрудников, которые не продали ни одной квартиры в течение последнего года. 
	
	-- QUERY: --
	SELECT * INTO #BadStaff FROM STAFF AS s
	WHERE s.Staff_no NOT IN 
	    (SELECT p1.Staff_no 
		FROM VIEWING AS v1 
		JOIN PROPERTY AS p1 ON v1.Property_no = p1.Property_no
		WHERE Comments = 'согласен'
		AND DATEDIFF(YEAR, date_view, GETDATE()) < 1);

-- 3. В локальную временную таблицу занести список сотрудников, которые не продали ни одной квартиры в течение последнего года. --


	-- QUERY: --
	SELECT * INTO #BadStaff FROM STAFF AS s
	WHERE s.Staff_no NOT IN 
	    (SELECT p1.Staff_no 
		FROM VIEWING AS v1 
		JOIN PROPERTY AS p1 ON v1.Property_no = p1.Property_no
		WHERE Comments = 'согласен'
		AND DATEDIFF(YEAR, date_view, GETDATE()) < 1);

-- 4. В таблицу BONUS (Staff_no, Amt) занести данные сотрудников, которые продали максимальное количество квартир (Amt). --
	
	-- QUERY: --
	CREATE TABLE BONUS(
	    Staff_no   NCHAR(9)   NOT NULL,
		Amt	       INT		  NOT NULL
	);

	INSERT INTO BONUS
		SELECT s.Staff_no,
	        (SELECT TOP 1 COUNT(p1.Staff_no) AS Quantity
	        FROM VIEWING AS v1
	        JOIN PROPERTY AS p1
	        ON v1.Property_no = p1.Property_no
	        WHERE v1.Comments = 'согласен'
	        GROUP BY p1.Staff_no
	        ORDER BY COUNT(p1.Staff_no) DESC) AS Quantity
		FROM STAFF AS s 
		JOIN PROPERTY AS p ON s.Staff_no = p.Staff_no
		WHERE s.Staff_no IN 
			(SELECT p2.Staff_no
			FROM VIEWING AS v2
			JOIN PROPERTY AS p2 ON v2.Property_no = p2.Property_no
			WHERE v2.Comments = 'согласен'
			GROUP BY p2.Staff_no
			HAVING COUNT(p2.Staff_no) = 
	            (SELECT TOP 1 COUNT(p3.Staff_no) AS Quantity
				FROM VIEWING AS v3
				JOIN PROPERTY AS p3 ON v3.Property_no = p3.Property_no
				WHERE v3.Comments = 'согласен'
				GROUP BY p3.Staff_no
				ORDER BY COUNT(p3.Staff_no) DESC));

-- 5. Таблица PROPERTY_1 служит для хранения данных о проданных объектах собственности (находятся в таблице CONTRACT). С помощью команды INSERT вставить данные об этих квартирах из таблицы PROPERTY в таблицу PROPERTY_1. --
	
	-- QUERY: --
	CREATE TABLE PROPERTY_1 (
	    Property_no          Member_no     NOT NULL,
	    Data_registration    date          NOT NULL,
	    Postcode             Postcode      NOT NULL,
	    City                 shortstring   NOT NULL,
	    Street               shortstring   NOT NULL,
	    House                shortstring   NOT NULL,
	    Flat                 smallint      NOT NULL,
	    Floor_Type           nchar(3)      NOT NULL,
	    Floor                tinyint       NOT NULL,
	    Rooms                tinyint       NOT NULL,
	    The_area             nvarchar(256) NOT NULL,
	    Balcony              nchar(3)      NOT NULL,
	    Ptel                 nchar(1)      NOT NULL DEFAULT N'Т',
	    Selling_Price        int           NOT NULL,
	    Branch_no            Member_no     NOT NULL,
	    Staff_no             nchar(9)      NULL,
	    Owner_no             Member_no     NOT NULL,      
	);

	INSERT INTO PROPERTY_1
	SELECT * FROM PROPERTY p
	WHERE p.Property_no IN (SELECT c.Property_no FROM CONTRACT AS c);


-- 6. Удалить из базы данных записи о проданных объектах недвижимости. --
	-- QUERY: --
	DELETE FROM PROPERTY
	WHERE Property_no IN 
	    (SELECT v.Property_no 
		FROM VIEWING AS v
		WHERE v.Comments = 'согласен') 
	OR Property_no IN (SELECT c.Property_no FROM CONTRACT AS c);