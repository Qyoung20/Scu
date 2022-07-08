create table comicbook(
isbn varchar(13) unique not null,
title varchar(20),
publishdate date,
copies int check (copies >= 0),
itemid varchar(14) primary key references storeitem(itemid)
);

