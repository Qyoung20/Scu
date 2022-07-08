Create or Replace Procedure assignJobTitlesAndSalaries
As
	type titlesList IS VARRAY(6) OF ace.title%type;
	type salaryList IS VARRAY(6) of ace.salary%type;
	v_titles titlesList;
	v_salaries salaryList;
Cursor Emp_cur IS
	Select * from ace;
	l_emprec Emp_cur%rowtype;
	l_title ace.title%type;
	l_salary ace.salary%type;
	l_randomnumber INTEGER := 1;

BEGIN
/* Titles are stored in the v_titles array  */
/* Salaries for each title are stored in the v_salaries array.
The salary of v_titles[0] title is at v_salaries[0].
*/
v_titles := titlesList('advisor', 'director', 'assistant', 'manager',
'supervisor', 'god');

v_salaries := salaryList(130000, 100000, 600000, 500000, 800000,'9999999');

/* use a for loop to iterate through the set  */
for l_emprec IN Emp_cur
LOOP
/* We get a random number between 1-5 both inclusive */
	l_randomnumber := dbms_random.value(1,6);
/* Get the title using the random value as the index into the
v_tiles array */
	l_title := v_titles(l_randomnumber);
/* Get the salary using the same random value as the index into
the v_salaries array */
	l_salary := v_salaries(l_randomnumber);
/* Update the employee title and salary using the l_title
and l_salary */
	update ace
	set title = l_title
	where name = l_emprec.name;
	update ace
	set salary = l_salary
	where name = l_emprec.name;

END LOOP;
commit;
END;
/
Show errors;
