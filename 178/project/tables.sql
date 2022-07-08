create table storeitem(
itemid varchar (14) primary key,
price number (6,2)
);

create table comicbook(
isbn varchar(13) unique not null,
title varchar(20),
publishdate date,
copies int check (copies >= 0),
itemid varchar(14) primary key references storeitem(itemid)
);

create table tshirt(
ssize varchar (1),
itemid varchar(2) primary key references storeitem(itemid)
);

create table custom(
ctype varchar (1),
custid varchar (2) primary key,
name varchar(30),
phone int not null unique,
address varchar(30),
joindate date,
constraint type_ck check (ctype = 'r' or ctype = 'g')
);

create table itemorder(
orderid varchar (10) primary key,
custid varchar (2) references custom(custid),
itemid varchar (14) references storeitem(itemid),
orderdate date,
noOfitems int,
shipdate date,
shippingfee number(4,2),
foreign key (itemid) references storeitem(itemid),
constraint order_ck check (shipdate >= orderdate)
);
