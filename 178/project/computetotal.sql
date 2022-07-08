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
