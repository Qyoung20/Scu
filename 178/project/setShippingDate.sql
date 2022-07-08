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
