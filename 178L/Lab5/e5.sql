Create or Replace Procedure setEmpSalary(p_name in VARCHAR, low in
INTEGER, high in INTEGER)
As
l_salary ace.salary%TYPE;

BEGIN

l_salary:= ROUND(dbms_random.value(low,high));

UPDATE ace

SET salary = l_salary

WHERE name = p_name;

COMMIT;

END;
/
show errors;
