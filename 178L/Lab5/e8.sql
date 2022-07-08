Create or Replace Function calcSalaryRaise( p_name in
ace.name%type, percentRaise IN NUMBER)
RETURN NUMBER
IS
	l_salary ace.salary%type;
	l_raise ace.salary%type;
	l_cnt Integer;
BEGIN
	-- Find the current salary of p_name from AlphaCoEMP table.
	Select salary into l_salary from ace
	where name = p_name;
	-- Calculate the raise amount
	l_raise := l_salary * (percentRaise/100);
	-- Check if the p_name is in Emp_Work table.
	-- If so, add a $1000 bonus to the
	-- raise amount
	Select count(*) into l_cnt from ew
	where name = p_name;
	if l_cnt >= 1 THEN
	l_raise := l_raise + 1000;
End IF;
/* return a value from the function */
	return l_raise;
END;
/
Show Errors;
