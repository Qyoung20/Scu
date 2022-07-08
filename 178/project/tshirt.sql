create table tshirt(
ssize varchar (1),
itemid varchar(2) primary key references storeitem(itemid)
);
