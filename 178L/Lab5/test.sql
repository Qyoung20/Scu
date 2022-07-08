Create or Replace Procedure setSalaries(low in INTEGER, high in INTEGER)
As
Cursor Emp_cur IS
Select * from ace;
-- Local variables
l_emprec Emp_cur%rowtype;
l_salary ace.salary%type;
BEGIN
for l_emprec IN Emp_cur
loop
l_salary := ROUND(dbms_random.value(low,high));
update ace
set salary = l_salary
where name = l_emprec.name;
END LOOP;
commit;
END;
/
show errors;

