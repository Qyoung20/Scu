Select name, title, salary CURRENTSALARY, (salary +
trunc(calcSalaryRaise(name,2))) NEWSALARY
from ace where name = 'Stone';
