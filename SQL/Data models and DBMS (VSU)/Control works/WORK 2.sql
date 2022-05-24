
-- 3
CREATE TRIGGER MARKCHECK
AFTER INSERT, UPDATE
AS
BEGIN









----- 2
CREATE FUNCTION AVGMARK( @Код_студента INT)
RETURNS REAL AS
RETURN (SELECT AVG(Оценка) FROM Оценки WHERE Оценки.Код_студента = @Код_студента)



SELECT Код_группы FROM Группы JOIN Студенты ON Группы.Код_группы = Студенты.Код_группы
WHERE Код_группы IN 
  (SELECT Код_группы 
  FROM Группы 
  JOIN Студенты ON Студенты.Код_группы = Группы.Код_группы 
  WHERE AVGMARK(Студенты.Код_студента) > 7
  GROUP BY Код_группы
  HAVING COUNT(Студенты.Код_студента) = COUNT(Студенты.Код_группы))
  GROUP BY Код_группы

