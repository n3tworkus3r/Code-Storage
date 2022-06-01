CREATE DATABASE Faculty
ON PRIMARY (NAME=Faculty,
FILENAME = 'D:\Projects\SQL\Faculty\Faculty.mdf',
Size=3Mb,
Maxsize=15Mb,
FileGrowth=1Mb)
Log On
(NAME=lTaxiStation,
FILENAME = 'D:\Projects\SQL\Faculty\Faculty.ldf',
Size=3Mb,
Maxsize=15Mb,
FileGrowth=1Mb)


-- II. TABLES CREATING
USE Faculty

CREATE TABLE SPECIALTY (
    specialty_id   smallint    NOT NULL PRIMARY KEY,
    specialty_name  varchar(20)  NOT NULL,
);

CREATE TABLE GROUPS (
    group_id       smallint    NOT NULL PRIMARY KEY,
    group_name      varchar(20)  NOT NULL,
    specialty_id   smallint    NOT NULL,
    CONSTRAINT FK_GROUP_SPECIALTY FOREIGN KEY(specialty_id) REFERENCES SPECIALTY ON UPDATE CASCADE,
);

CREATE TABLE STUDENTS (
    student_id         smallint     NOT NULL PRIMARY KEY,
    student_name       varchar(20)  NOT NULL,
    student_surname    varchar(20)  NOT NULL,
    student_middlename varchar(20)  NOT NULL,
    photo              varchar(20)  NOT NULL,
    group_id           smallint     NOT NULL,
    admittance         bit          NOT NULL,
    fellowship         money        NOT NULL,
    CONSTRAINT FK_STUDENTS_GROUP FOREIGN KEY(group_id) REFERENCES GROUPS ON UPDATE CASCADE,
);

CREATE TABLE TIMETABLE (
    group_id           smallint     NOT NULL,
    subject_id         smallint     NOT NULL,
    day                date         NOT NULL,
    classroom          varchar(20)  NOT NULL,
    teacher_id         smallint     NOT NULL
    PRIMARY KEY(group_id,subject_id),
    CONSTRAINT FK_TIMETABLE_GROUP FOREIGN KEY(group_id) REFERENCES GROUPS ON UPDATE CASCADE,
);

CREATE TABLE SUBJECTS (
    subject_id         smallint     NOT NULL PRIMARY KEY,
    subject_name       varchar(20)  NOT NULL,
    cathedra           varchar(20)  NOT NULL
);

CREATE TABLE TEACHERS (
    teacher_id          smallint     NOT NULL PRIMARY KEY,
    teacher_name        varchar(20)  NOT NULL,
    teacher_surname     varchar(20)  NOT NULL,
    teacher_middlename  varchar(20)  NOT NULL,
    cathedra            varchar(20)  NOT NULL,
    position            varchar(20)  NOT NULL,
);

CREATE TABLE TEACHER_SUBJECTS (
    teacher_id          smallint    NOT NULL,
    subject_id         smallint     NOT NULL,
    PRIMARY KEY(teacher_id,subject_id),
    CONSTRAINT FK_TEACHER_SUBJECTS_TEACHERS FOREIGN KEY(teacher_id) REFERENCES TEACHERS ON UPDATE CASCADE,
    CONSTRAINT FK_TEACHER_SUBJECTS_SUBJECTS FOREIGN KEY(subject_id) REFERENCES SUBJECTS ON UPDATE CASCADE
);


CREATE TABLE GRADES (
    student_id          smallint    NOT NULL,
    subject_id          smallint    NOT NULL,
    grade               int          NOT NULL,
    teacher_id          smallint    NOT NULL,
    day                 date         NOT NULL,
    type_of_control     varchar(20)  NOT NULL,
PRIMARY KEY(student_id,subject_id),
CONSTRAINT FK_GRADES_SUBJECTS FOREIGN KEY(subject_id) REFERENCES SUBJECTS ON UPDATE CASCADE,
CONSTRAINT FK_GRADES_STUDENTS FOREIGN KEY(student_id) REFERENCES STUDENTS ON UPDATE CASCADE,
CONSTRAINT FK_GRADES_TEACHER FOREIGN KEY(teacher_id) REFERENCES TEACHERS ON UPDATE CASCADE,
); 

--III. FILLING TABLES
-- TEACHERS
INSERT TEACHERS VALUES (1,'Пётр', 'Петров', 'Петрович', 'Геометрия', 'Доцент');
INSERT TEACHERS VALUES (2,'Иван', 'Михайлов', 'Петрович', 'Алгебра', 'Ассистент');
INSERT TEACHERS VALUES (3,'Никита', 'Степанов', 'Петрович', 'Русский язык', 'Профессор');
INSERT TEACHERS VALUES (4,'Семён', 'Беляев', 'Петрович', 'Геометрия', 'Доцент');
INSERT TEACHERS VALUES (5,'Никита', 'Кузьменьков', 'Владимирович', 'Геометрия', 'Ст.преподаватель');

--SPECIALTY
INSERT INTO SPECIALTY VALUES(100,'ПИ');
INSERT INTO SPECIALTY VALUES(101,'ПОИТ');
INSERT INTO SPECIALTY VALUES(102,'КБ');
INSERT INTO SPECIALTY VALUES(103,'ПМ');

--GROUP
INSERT INTO GROUPS VALUES (11, 'ПОКС',100);
INSERT INTO GROUPS VALUES (12, 'ПриМат',101);
INSERT INTO GROUPS VALUES (13, 'МатИнф',102);
INSERT INTO GROUPS VALUES (14, 'WEB',103);

--SUBJECTS
INSERT INTO SUBJECTS VALUES(1,'Анал.геом.','Геометрия');
INSERT INTO SUBJECTS VALUES(2,'Теория чисел','Алгебра');
INSERT INTO SUBJECTS VALUES(3,'Орфография','Русский язык');
INSERT INTO SUBJECTS VALUES(4,'Матимака','Алгебра');

--TIMETABLE
INSERT TIMETABLE VALUES(11,1,'2020-12-17','117a',3);
INSERT TIMETABLE VALUES(12,2,'2020-12-17','118a',2);
INSERT TIMETABLE VALUES(13,3,'2020-12-17','119a',1);
INSERT TIMETABLE VALUES(14,4,'2020-12-17','118a',4);

--STUDENTS
INSERT STUDENTS VALUES(101,'Иван', 'Степанов', 'Семенович', 'C:\photo1', 11, 1, 100);
INSERT STUDENTS VALUES(102,'Илья', 'Семенов', 'Семенович', 'C:\photo2', 13, 0, 140);
INSERT STUDENTS VALUES(103,'Семен', 'Михайлов', 'Семенович', 'C:\photo3', 11, 1, 150);
INSERT STUDENTS VALUES(104,'Виталий', 'Семенов', 'Семенович', 'C:\photo4', 12, 0, 100);
INSERT STUDENTS VALUES(105,'Семен', 'Семенов', 'Семенович', 'C:\photo5', 14, 1, 190);

--GRADES
INSERT INTO GRADES VALUES (101,1,10,1,'2020-12-17','Экзамен');
INSERT INTO GRADES VALUES (102,3,9,1,'2020-12-18','Зачёт');
INSERT INTO GRADES VALUES (103,1,8,1,'2020-12-19','Экзамен');
INSERT INTO GRADES VALUES (101,2,5,1,'2020-12-20','Зачёт');
INSERT INTO GRADES VALUES (101,4,3,2,'2020-12-20','Зачёт');
