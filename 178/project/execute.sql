
--add item query
exec additemorder ('1', '1', '12', '04-JUN-22', null, 3);
exec additemorder ('2', '1', '23', '04-JUN-22', null, 12);
exec additemorder ('3', '4', '45', '04-JUN-22', null, 3);
exec additemorder ('4', '6', '78', '04-JUN-22', null, 5);
--check for updated tables
select * from itemorder;
select * from comicbook;

--set ship date query
exec setshippingdate ('1', '06-JUN-22');
exec setshippingdate ('2', '06-JUN-22');
exec setshippingdate ('3', '04-JUN-22');
exec setshippingdate ('4', '06-JUN-22');

--check item order for update

select * from itemorder;


--order total
select computetotal('1') from dual;
update custom set ctype = 'r', joindate = '05-JUN-22', where custid = '12';
select computetotal('1') from dual;

select computetotal('2') from dual;
select computetotal('3') from dual;

select computetotal('4') from dual;
update custom set ctype = 'g', joindate = '05-JUN-22', where custid = '78';
select computetotal('4') from dual;

-- check update items and customer

select * from custom
select * from itemorder;

-- order details

exec showitemorder ('12', '04-JUN-22');
exec showitemorder ('45', '04-JUN-22');


