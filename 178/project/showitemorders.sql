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
	



