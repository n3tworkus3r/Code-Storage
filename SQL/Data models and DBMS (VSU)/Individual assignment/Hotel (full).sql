use master
drop database Hotels
create database Hotels
go
use Hotels
go
create table HOTELS(
	id int primary key identity(1,1),
	hotel_name nvarchar(max),
	hotel_address nvarchar(max),
)
create table ROOMS(
	id int primary key identity(1,1),
	hotel_id int foreign key references HOTELS(id),
	room_num int check(10<=room_num and room_num<100),
	places_amount int,
	room_type nvarchar(64) check(room_type in('lux', 'regular')),
	daily_cost money check(100000<=daily_cost and daily_cost<500000),
	room_status nvarchar(64)
		check(room_status in('available','taken','booked'))
		default('available')
)
create table GUESTS(
	id int primary key identity(1,1),
	first_name nvarchar(128), 
	last_name nvarchar(128), 
	second_name nvarchar(128), 
	home_address nvarchar(max)
)
create table BOOKING_RECORDS(
	id int primary key identity(1,1),
	arrival_date date default(getdate()),
	leaving_date date default(getdate()),
	guest_id int foreign key references GUESTS(id),
	room_id int foreign key references ROOMS(id)
)
create table ARCHIVED_BOOKING_RECORDS(
	record_id int primary key identity(1,1),
	arrival_date date,
	leaving_date date,
	guest_id int foreign key references GUESTS(id),
	room_id int foreign key references ROOMS(id)
)
insert into HOTELS (hotel_name, hotel_address)
values ('Some hotel name', 'Some street')
insert into ROOMS (hotel_id, room_num, places_amount, room_type)
values (1, 87, 1, 'lux')
insert into GUESTS (first_name, last_name, second_name, home_address)
values ('some name', 'some last name', 'some second name', 'some address')
insert into BOOKING_RECORDS (guest_id, room_id)
values (1, 1)
go
create trigger init_price on ROOMS
after insert
as
	update ROOMS set daily_cost =
			(select places_amount from inserted)
			*
			(select iif(room_type = 'lux',100, 20) from inserted)
		where id = (select id from inserted)
go
create trigger room_booked on BOOKING_RECORDS
after insert
as
	update ROOMS set room_status =
		iif((select arrival_date from inserted) > getdate(),'booked',
			iif((select leaving_date from inserted) < getdate(),'available','taken')
		)
go
create procedure increace_price_if_all_rooms_taken
	@hotel_id int
as
	update ROOMS set daily_cost = daily_cost * 1.05
		where hotel_id = @hotel_id
go
create procedure get_available_single_placed_rooms
	@hotel_id int
as
	with hotel_rooms as
	(
		select * from ROOMS
			where hotel_id = @hotel_id
	)
	select * from hotel_rooms
		where places_amount = 1 and 
			id not in (
				select room_id from BOOKING_RECORDS
				where room_id in (select id from hotel_rooms)
					and dateadd(day, 1, getdate()) <= leaving_date
			)
	-- ??? print 'No single-placed rooms available'
go
create procedure book_room
	@guest_id int,
	@room_id int,
	@arrival_date date,
	@days_amount int
as
	insert into BOOKING_RECORDS (guest_id, room_id, arrival_date, leaving_date)
		values (@guest_id, @room_id, @arrival_date, dateadd(day, @days_amount, @arrival_date))
commit
go
create procedure archive_booking_records
as
begin
	begin transaction archiving_booking_records
	declare @records_to_archive table(id int)
	insert into @records_to_archive
		select id from BOOKING_RECORDS
			where dateadd(year, 1, leaving_date) > getdate()
	insert into ARCHIVED_BOOKING_RECORDS
		(guest_id, room_id, arrival_date, leaving_date)
		select guest_id, room_id, arrival_date, leaving_date
		from BOOKING_RECORDS
		where id in(select * from @records_to_archive)
	delete from BOOKING_RECORDS
		where id in(select * from @records_to_archive)
end
go
create view avaliable_rooms as
	select * from ROOMS
		where room_status = 'avaliable'
go
create view hotels_income as
	select hotel_id, sum(daily_cost*datediff(day, arrival_date, leaving_date)) from BOOKING_RECORDS
		join ROOMS on id=room_id
		where leaving_date > dateadd(month, -1, getdate())
		group by hotel_id

