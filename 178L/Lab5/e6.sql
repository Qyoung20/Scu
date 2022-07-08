Create or Replace FUNCTION getEmpSalary(p_name in VARCHAR)
Return NUMBER IS

/* Define the local variables you need.
You need a variable to hold the salary returned */

l_salary ace.salary%type;

BEGIN

/* Two things are missing from the below statement (hint: how
are you saving the result into l_salary?)*/
Select salary into l_salary from ace WhERE name = p_name;


return l_salary;
END;
/
show errors;
