###############################################################################
################################## ВАРИАНТ 12 #################################
###############################################################################

# 1. Вывести список групп, в которых нет среднего балла по предмету нижу 7.
# Для получения среднего балла по предмету в группе создать пользовательскую
# скалярную функцию.

CREATE FUNCTION GetAvgGradeIn(@given_group_id INT, @given_subject_id INT)
  RETURNS DOUBLE
  AS
  RETURN
  (
    SELECT AVG(grade) from GRADES
    WHERE subject_id = @given_subject_id
      and student_id in 
      (
        select student_id from STUDENTS
        where group_id = @given_group_id
      )
  )
  
GO

SELECT * FROM GROUPS WHERE 7 > dbo.GetAvgGradeIn(group_id, subject)


###############################################################################

# 2. Создать табличную пользовательскую функцию для вычисления минимального
# среднего балла, полученного студентом группы (код группы, минимальный средний балл)
# С помощью функциии создать следующие запросы:

   * Найти группы (название), в которых минимальный средний балл студента выше 6.
   * Вывести фамилии студентов, получивших минимальный средний балл в каждой группе
 

CREATE FUNCTION GetMinGradesByGroupIds()
  RETURNS TABLE
  AS RETURN
    SELECT group_id, 
      min(student_avg_grade.avg_grade) AS min_avg_grade
      FROM STUDENTS
    JOIN 
      (
        SELECT student_id, AVG(grade) as avg_grade
        FROM GRADES
        GROUP BY student_id
      ) AS student_avg_grade 
      ON student_avg_grade.student_id = STUDENTS.student_id
    GROUP BY group_id
GO

###############
#####  1) #####
###############

SELECT group_name from GROUPS
where group_id in 
(
  select group_id from dbo.GetMinGradesByGroupIds()
  where min_avg_grade > 6
)


###############
#####  2) #####
###############


WITH student_avg as 
(
  SELECT student_id, AVG(grade) AS avg_grade FROM GRADES
    GROUP BY student_id
),
student_group_avg as
(
  SELECT STUDENTS.student_surname, STUDENTS.group_id,
  student_avg.avg_grade from student_avg
  join STUDENTS on STUDENTS.student_id = student_avg.student_id
)
SELECT student_surname FROM student_group_avg
JOIN dbo.GetMinGradesByGroupIds() AS min_grades 
  ON min_grades.group_id = student_group_avg.group_id
WHERE student_group_avg.avg_grade = min_grades.min_avg_grade





###############################################################################

# 3. Создать триггер для ввода данных в таблицу Расписание с учётом того, что в таблице
# не должно быть предметов, отсутствующих в таблице Предметы и количество предметов,
# сдаваемых группой, не может быть больше 5.


CREATE TRIGGER UPDATE_TIMETABLE
ON TIMETABLE
AFTER INSERT
AS
  IF
  (
    NOT EXISTS (
      SELECT subject_id FROM SUBJECTS
      WHERE subject_id = (SELECT subject_id FROM inserted)
    )
    OR
    (
      SELECT COUNT(*) FROM TIMETABLE
      WHERE group_id = (SELECT group_id FROM inserted)
    ) > 5
  )
  BEGIN
    print('some err text')
  END

###############################################################################