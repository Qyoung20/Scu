Create table BANKCUST_6 (custno VARCHAR(5) Primary Key,custname
VARCHAR(20),street VARCHAR(30), city VARCHAR(20));

Create table ACCOUNTS_6 (AccountNo VARCHAR(5) Primary Key,accountType
VARCHAR(10), amount NUMBER(10,2), custno varchar(5),
CONSTRAINT accounts_fkey FOREIGN Key (custno)REFERENCES BANKCUST_6(custno));

Create table TOTALS_6 (custno VARCHAR(5), totalAmount Number(10,2), CONSTRAINT
totals_fkey FOREIGN Key (custno)REFERENCES BANKCUST_6(custno));
