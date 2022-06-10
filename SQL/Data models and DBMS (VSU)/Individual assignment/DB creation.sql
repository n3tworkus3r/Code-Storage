CREATE DATABASE Hotel
ON PRIMARY (NAME=Hotel,
FILENAME = 'D:\Projects\SQL\Hotel\Hotel.mdf',
Size=3Mb,
Maxsize=15Mb,
FileGrowth=1Mb)
Log On
(NAME=lTaxiStation,
FILENAME = 'D:\Projects\SQL\Hotel\Hotel.ldf',
Size=3Mb,
Maxsize=15Mb,
FileGrowth=1Mb)


-- II. TABLES CREATING
USE Hotel

CREATE TABLE HOTELS (
    hotel_id        smallint     NOT NULL PRIMARY KEY,
    hotel_name      varchar(20)  NOT NULL,
    city            varchar(20)  NOT NULL,
    hotel_address   varchar(50)  NOT NULL
);

CREATE TABLE ROOMS (
    room_id         smallint     NOT NULL PRIMARY KEY,
    hotel_id        smallint     NOT NULL,
    type            varchar(20)  NOT NULL,
    places          smallint     NOT NULL,
    price           float        NOT NULL,
    state           varchar(20)  NOT NULL 
);

CREATE TABLE CLIENTS (
    client_id          smallint     NOT NULL PRIMARY KEY,
    client_name        varchar(20)  NOT NULL,
    client_surname     varchar(20)  NOT NULL,
    client_middlename  varchar(20)  NOT NULL,
    client_address     varchar(20)  NOT NULL,
    client_doc_number  varchar(20)
);

CREATE TABLE REGISTRATIONS (
    client_id          smallint     NOT NULL,
    room_id            smallint     NOT NULL,
    arrival_date      date         NOT NULL,
    eviction_date      date         NOT NULL,
    archieve_id         smallint

    PRIMARY KEY(client_id, room_id),
);




ALTER TABLE ROOMS
    ADD CONSTRAINT FK_ROOMS_HOTELS FOREIGN KEY (hotel_id) REFERENCES HOTELS(hotel_id) 

ALTER TABLE ROOMS
    ADD CONSTRAINT FK_ROOMS_REGISTRATIONS FOREIGN KEY (room_id) REFERENCES REGISTRATIONS(room_id) 


ALTER TABLE CLIENTS
    ADD CONSTRAINT FK_CLIENTS_REGISTRATIONS FOREIGN KEY (client_id) REFERENCES REGISTRATIONS(client_id) 


ALTER TABLE REGISTRATIONS
    ADD CONSTRAINT FK_REGISTRATIONS_CLIENTS FOREIGN KEY (client_id) REFERENCES CLIENTS(client_id) 
    
ALTER TABLE REGISTRATIONS
    ADD CONSTRAINT FK_REGISTRATIONS_ROOMS FOREIGN KEY (room_id) REFERENCES ROOMS(room_id) 








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
