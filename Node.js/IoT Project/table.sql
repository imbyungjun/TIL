USE iot;
CREATE TABLE sensor (
	id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	temp INT NOT NULL,
	co2 INT NOT NULL,
	time TIMESTAMP(8)
);