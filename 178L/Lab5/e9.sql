Create or Replace Function countByTitle(p_title in
ace.title%type)
RETURN NUMBER IS
	l_cnt Integer;
BEGIN
/* Complete the query below */
	Select count(title) as count into l_cnt from ace
	Group by title
	Having p_title = title;
	return l_cnt;
END;
/
