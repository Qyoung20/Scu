create or replace procedure additemorder (oid in itemorder.orderid%type, iid in itemorder.orderid%type, cid in custom.custid%type, odate in itemorder.orderdate%type, sdate in itemorder.shipdate%type, noitems in intemorder.noOfitems%type)
is
	l_ctype custom.ctype%type;
	l_copies comicbook.copies%type;
	l_shippingfee itemorder.shippingfee%type;
	nobook exception;

BEGIN

	--put data in
	select copies into l_copies from comicbook where itemid = iid;
	select ctype into l_ctype from customer where custid = cid;
	--check and update ship fee for cust type
	if (l_ctype = 'r') then
		add_shippingfee := 10.00;
	elseif (add_ctype = 'g') then
		l_shippingfee := 00.00;
	end if;

--check num of books
	if (add_copies >= noitems) then
		insert into itemorder (orderid, custid, itemid, orderdate, noOfitems, shipdate, shippingfee)
			values (oid, cid, iid, odate, noitemsm, null, add_shippingfee);
		update comicbook set copies = l_copies - noitems where itemid = iid;
	else
		raise nobook;
	end if;

EXCEPTION
	when nobook then dbms_output.put_line('No more of this book in stock');
	when no_data_found then
	declare
		l_ctype custom.ctype%type;
		l_shippingdfee itemorder.shippingfee%type;
	begin
	select ctype into add_ctype from custom where custid = cid;
	if (l_ctype = 'r') then
		l_shippingfee := 10.00;
	elseif (l_ctype = 'g') then
		l_shippingfee := 00.00;
		end if;
			insert into itemorder (orderid, custid, itemid, orderdate, noOfitems, shipdate, shippingfee)
			values (oid, cid, iid, odate, noitemsm, null, add_shippingfee);	
	end;
end;
\
show errors;









