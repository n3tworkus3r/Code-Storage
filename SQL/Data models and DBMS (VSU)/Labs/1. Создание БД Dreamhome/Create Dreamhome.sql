-- TASK 1
CREATE DATABASE DreamHome
ON PRIMARY(
    NAME = DreamHome,
    FILENAME='D:\Repositories\SQL\Dreamhome\DreamHome.mdf',
    Size = 15Mb,
    MaxSize = 30Mb,
    FileGrowth = 1Mb
)
Log On(
    NAME = DreamHome2_log,
    FILENAME='D:\Repositories\SQL\Dreamhome\DreamHome.ldf',
    Size = 2Mb,
    MaxSize = 7Mb,
    FileGrowth = 1Mb
)

-- TASK 2
USE DreamHome
EXEC sp_addtype Postcode,  'char(6)', 'NULL'
EXEC sp_addtype member_no, 'smallint'

-- LAST TASKS

EXEC sp_addtype Phonenumber, 'char(17)', 'NOT NULL'
EXEC sp_addtype shortstring, 'varchar(20)'
