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
