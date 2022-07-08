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
	if (l_ctype = 'r')
		l_shippingfee := 10.00;
	elseif (t_ctype = 'g')
		l_shippingfee := 00.00;
	end if;

--check num of books
	if (l_copies >= noitems)
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
	select ctype into t_ctype from custom where custid = cid;
	if (l_ctype = 'r')
		l_shippingfee := 10.00;
	elseif (add_ctype = 'g')
		l_shippingfee := 00.00;
	end if;
	insert into itemorder (orderid, custid, itemid, orderdate, noOfitems, shipdate, shippingfee)
			values (oid, cid, iid, odate, noitemsm, null, add_shippingfee);	
	end;
end;
\
show errors;

create or replace function computetotal (oid in itemorder.orderid%type)
return number is
	c_total storeitem.price%type;
	c_price storeitem.price%type;
	c_quantity itemorder.noOfitems%type;
	c_shippingfee itemorder.shippingfee%type;
	c_itemid itemorder.itemid%type;
	c_subtotal storeitem.price%type;
	c_tax storeitem.price%type;

begin
	select itemid into c_itemid from itemorder where orderid = oid;
	select price into c_price from storeitem where itemid = c_itemid;
	select noOfitems into c_quantity from itemorder where orderid = oid;
	select shippingfee into c_shippingfee from itemorder where orderid = oid;

	c_subtotal := c_price * c_quantity;
	--check if gold and total above 100 then discount
	if c_shipfee = 00.00 and c_subtotal >= 100.00 then
		c_subtotal := c_subtotal * 0.9;
	end if;
	
	c_tax := c_subtotal * 0.05;
	c_total := c_subtotal + c_tax + c_shippingfee;
	return c_total;
end;
/
show errors;

create or replace procedure setshippingdate( oid in itemorder.orderid%type, sdate in itemorder.shipdate%type)
is
	set_orderdate itemorder.orderdate%type;
begin
	--check if orderdate is after shipdate else incorect 
	select orderdate into set_orderdate from itemorder where orderid = oid;
	if (add_orderdate <= sdate) then
		update itemorder set shipdate = sdate where orderid = oid;
	else
		dbms_output.put_line('Invalid date');
	end if;
end;
/
show errors;

create or replace procedure showitemorder (cid in itemorder.custid%type, odate in itemorder.orderdate%type)
as
	s_custid custom.custid%type;
	s_name custom.name%type;
	s_phone custom.phone%type;
	s_address custom.address%type;
	
	s_orderid itemorder.orderid%type;
	s_itemid itemorder.itemid%type;
	s_title comicbook.title%type;
	s_size tshirt.ssize%type;
	s_price storeitem.price%type;
	s_orderdate itemorder.orderdate%type;
	s_shipdate itemorder.shippingdate%type;
	s_quantity itemorder.noofitems%type;

	s_subtotal storeitems.price%type;
	s_tax storeitems.price%type;
	s_shipfee storetiems.price%type;
	s_discount storeitems.price%type;
	s_ototal storeitems.price%type;
	s_gtotal storeitems.price%type := 00.00;

	cursor s_comic is select orderid, custid, itemid, title, price, orderdate, shipdate, noofitems, shippingfee from (itemorder join comicbook using(itemid)) join storeitem using(itemid) where custid = cid and orderdate >= odate order by custid;
cursor s_tshirt is selece orderid, custid, itemid, ssize, price, orderdate, shipdate, noofitems, shippingfee from (itemorder join tshirt using(itemid)) join storeitem using(itemid) where custid = cid and orderdate >= odate order by custid;

Begin
	select custid, name, phone, address into s_custid, s_name, s_phone, s_address from custom where custid = cid;
	dbms_output.put_line('Customer details:');
	dbms_output.put_line(' ' || s_custid || ', ' || 's_name' || ', ' || s_phone || ', ' || s_address );
	dbms_output.put_line('Comic book order(s): ');
	open s_comic;
	loop
		fetch s_comic into s_orderid, s_itemid, s_title, s_price, s_orderdate, s_shipdate, s_quantity, s_shipfee;
		exit when s_comic%notfound;
		s_subtotal := s_price * s_quantity;
		if s_shipfee = 00.00 and l_subtotal >= 100.00 then
			s_discount := 00.10;
		else
			s_discount := 00.00;
		end if;

		s_discount := s_discount *s_subtotal;
		s_subtotal := s_subtotal - s_discount;
		s_tax := s_subtotal * 00.05;
		s_ototal := s_subtotal + s_tax + s_shipfee;
		s_gtotal := s_gtotal + s_ototal;
		dbms_output.put_line('Order id: ' || s_orderId || ', Item id: ' || s_itemId || ', Comic: ' || s_title || ', Price of Item: ' || s_price || ', Order Date: ' || s_orderDate || ', Date Shipped : ' || s_shipDate || ', Number of Items: ' || s_quantity || ', Discount Applied: ' || s_discount || ', Shipping Fee: ' || s_shipFee || ', Taxes: ' || s_tax || ', Order Total: ' || s_orderTotal);		
	end loop;
	close s_comic;

	open s_tshirt;
	loop
		fetch s_tshirt into s_orderidm s_custid, s_itemid, s_size, s_price, s_orderdate, s_shipdate, s_quantity, s_shipfee;
		exit when s_tshirt%notfound;
		
		s_subtotal := s_price * s_quantity;
		if s_shipfee = 00.00 and s_subtotal >= 100.00 then
			s_discount = 00.10;
		else
			s_discount = 00.00;
		end if;

	s_discount := s_discount * s_subtotal;
	s_subtotal := s_subtotal - s_discount;
	s_tax := s_subtotal * 00.05;
	s_ototal := s_subtotal + s_tax + s_shipfee;
	s_gtotal := s_gtotal + s_ototal;
	dbms_outpud.put_line('Tshirt Order(s): ');
	dbms_output.put_line('Order id: ' || s_orderId || ', Item id: ' || s_itemId || ', Tshirt Size: ' || s_size || ', Price of Item: ' || s_price || ', Order Date: ' || s_orderDate || ', Date Shipped : ' || s_shipDate || ', Number of Items: ' || s_quantity || ', Discount Applied: ' || s_discount || ', Shipping Fee: ' || s_shipFee || ', Taxes: ' || s_tax || ', Order Total: ' || s_orderTotal);
	end loop;
	close s_tshirt;
	
	dbms_output.put_line('Grand Total: ' || s_gtotal);
end;
/
show errors;
	
create or replace trigger ctypeupdate
after update on custom
for each row
begin
	--check if cust is gold update fee to 0 else make 10
	if :new.ctype = 'g' then
		update itemorder set shippingfee = 00.00 where custid = :newcustid;
	else
		update itemorder set shippingfee = 10.00 where custid = :newcustid;
	end if;
end ctypeupdate;
/
show errors;








