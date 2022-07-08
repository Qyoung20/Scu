Create Or Replace Trigger Acct_Cust_Trig
AFTER INSERT ON Accounts_6
FOR EACH ROW	
BEGIN	
/*If the custno is already in the Totals_6 table, the update will succeed */
	update totals_6
	set totalAmount = totalAmount + :new.amount
	where custno = :new.custno;	
		
/*If the custno is not in the Totals_6 table, we insert a row into
Totals_6 table. Complete the missing part in the subquery */
insert into totals_6 (select :new.custno, :new.amount from dual
	where not exists (select * from TOTALS_6 where custno= :new.custno ));							
END;
/
show errors;


