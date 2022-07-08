Create Or Replace Trigger Acct_Cust_Trig
AFTER INSERT OR UPDATE ON Accounts_6
FOR EACH ROW	
BEGIN	
	If inserting then
		update totals_6
		set totalAmount = totalAmount + :new.amount
		where custno = :new.custno;	
		
		insert into totals_6 
select :new.custno, :new.amount from dual where not exists (select * from TOTALS_6 where custno= :new.custno);
END IF;
if updating then
	update totals_6
	set totalAmount = totalAmount + 		
	where custno = :new.custno;		
	end if; 
END;
/
Show Errors;

