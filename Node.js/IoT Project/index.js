var express = require('express');
var app = express();
var jsonfile = require('jsonfile');
var mysql = require("mysql");

// Create a connection to the db
var conn = mysql.createConnection({
    host: "localhost",
    user: "user",
    password: "passwd",
	database: "DBname"
});

// Connect to db
conn.connect(function(err){
    if(err){
		console.log('Error connecting to Db');
		return;
	}
	console.log('Connection established');
});


app.get('/', function(req, res) {
	var inst = { temp : req.query.temp, co2 : req.query.co2 };
	conn.query('INSERT INTO sensor SET ?', inst, function(err, res) {
		if (err) throw err;
		
		console.log('Inserted ID :', res.insertId);
	});

	conn.query('SELECT * FROM sensor', function(err, rows) {
		if (err) throw err;
	
		jsonfile.writeFile('./data.json', rows, function(err) {
			console.error(err);
		});
	});

	res.send('Hello\n');
});

app.listen(3000, function() {
	console.log("Lestening on port 3000!");
});
