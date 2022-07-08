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
