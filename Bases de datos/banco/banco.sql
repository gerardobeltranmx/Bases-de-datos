DROP DATABASE IF EXISTS bancos;

CREATE DATABASE bancos CHARACTER SET utf8mb4;

use bancos;

CREATE TABLE cuentas 
  (
	idcuenta INT PRIMARY KEY AUTO_INCREMENT, 	
	nombre VARCHAR(40) NOT NULL, 
	email VARCHAR(30) DEFAULT 'desconocido@sindominio.net',
	fecha DATETIME DEFAULT NOW(),	
	foto BLOB
   ) ENGINE=INNODB; 

CREATE TABLE movimientos 
  (
	idmov INT PRIMARY KEY AUTO_INCREMENT,     
	idcuenta INT,   
	fechamov DATETIME DEFAULT NOW(),   
	tipo CHAR,
	cantidad FLOAT DEFAULT 0,
	FOREIGN KEY(idcuenta) REFERENCES cuentas(idcuenta) 
	   ON UPDATE CASCADE      
	   ON DELETE CASCADE 
   ) ENGINE=INNODB;

-- Datos

insert into  cuentas (nombre, email, fecha) VALUES ('Gerardo Medina Lopez', 'gerardo@dominio.mx', '1958-03-15'); 
insert into  cuentas (nombre, email, fecha) VALUES ('Patricia Herrera Castro', 'patty@dominio.mx', '1948-09-30'); 
insert into  cuentas (nombre, email, fecha) VALUES ('Claudia Gonzalez Gomez', 'claudia@dominio.mx', '1987-02-22'); 
insert into  cuentas (nombre, email, fecha) VALUES ('Luis Perez Hernandez', 'luis@dominio.mx', '1986-04-04'); 

insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (1,now(),'D', 1000);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (1,now(),'R', 500);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (1,now(),'D', 100);


insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (2, now(),'D', 2000);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (2, now(),'R', 200);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (2, now(),'R', 100);

insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (3, now(),'D', 2000);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (3, now(),'R', 50);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (3, now(),'D', 120);

insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (4, now(),'D', 3000);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (4, now(),'R', 700);
insert into movimientos (idcuenta, fechamov, tipo, cantidad) values (4, now(),'D', 150);
