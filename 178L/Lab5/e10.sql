CREATE or REPLACE procedure saveCountByTitle
AS
type titlesList IS VARRAY(5) OF ace.title%type;

l_advisor_cnt integer := 0;

Cursor t is
	select unique title from ace;
	l_emprec t%rowtype;
	

BEGIN
delete from EmpStats;
for l_emprec in t
loop
l_advisor_cnt := countByTitle(l_emprec.title);

 -- Any previously loaded data is deleted
/* inserting count of employees with title, ‘advisor’.*/

insert into EmpStats values (l_emprec.title, l_advisor_cnt, SYSDATE);
end loop;
commit;
END;
/
Show errors;
