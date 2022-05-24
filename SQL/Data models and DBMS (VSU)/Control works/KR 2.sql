CREATE FUNCTION AVGMARK(@group_id INT)
RETURNS REAL AS
BEGIN
	DECLARE @avg_m REAL

	SELECT @avg_m = AVG(о.Оценка)
	FROM предметы п
	LEFT JOIN Оценки о ON о.Код_предмета = п.Код_предмета
	LEFT JOIN Студенты с ON с.Код_студента = о.Код_студента
	WHERE п.Название_предмета = @subject_name AND с.Код_группы = @group_id;

	RETURN @avg_m;
END;


-- 2
CREATE FUNCTION MARKS_NUMBER
(@Код_группы NVARCHAR(20))
RETURNS INT
AS
RETURN (SELECT COUNT(*) FROM Оценки WHERE Код_преподавателся = @Код_преподавателся AND Оценка > 4)

SELECT Код_преподавателся, Фамилия_преподавателя FROM Преподаватели WHERE dbo.MARKS_NUMBER(Код_преподавателся) > 10
SELECT Код_преподавателся, Фамилия_преподавателя, dbo.MARKS_NUMBER(Код_преподавателся) FROM Преподаватели ORDER BY dbo.MARKS_NUMBER(Код_преподавателся) DESC LIMIT 1



-- 3
CREATE FUNCTION STUDENTS_WITH_AVG_MARK_LOWER
(@Код_группы NVARCHAR(30), @Средний_балл REAL)
RETURNS TABLE
AS
RETURN (SELECT с.Код_студента, AVG(о.Оценка) FROM Студенты AS с 
		LEFT JOIN Оценки AS о ON с.Код_студента = о.Код_студента 
		WHERE с.Код_группы = @Код_группы 
        GROUP BY с.Код_студента 
		HAVING AVG(о.Оценка) < @Средний_балл)
		
SELECT * FROM Группы AS г 
WHERE (SELECT COUNT(*) FROM dbo.STUDENTS_WITH_AVG_MARK_LOWER(г.Код_группы, 6)) 
       = (SELECT COUNT(*) FROM Студенты AS с WHERE с.Код_группы = г.Код_группы)