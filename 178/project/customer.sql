create table custom(
ctype varchar (1),
custid varchar (2) primary key,
name varchar(30),
phone int not null unique,
address varchar(30),
joindate date,
constraint type_ck check (ctype = 'r' or ctype = 'g')
);
