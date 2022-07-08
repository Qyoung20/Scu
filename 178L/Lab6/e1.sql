CREATE or REPLACE TRIGGER display_customer_trig
AFTER  INSERT on BankCust_6
FOR EACH ROW
BEGIN
DBMS_OUTPUT.PUT_LINE('From Trigger '||'Customer NO:
'||:new.custno||' Customer Name: '||:new.custname || 'City Name: ' ||:new.city );
END;
/
show errors;

