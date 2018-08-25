


<?php
	$dbhost = "localhost";
	$dbuser = "root";
	$dbpass = "";
	$dbname = "rfid_attendence";
	
	$connection = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	if(mysqli_connect_errno()){
		die('Database connection  failed'.mysqli_connect_error());
	}
	else{
		echo "Database connection OK";
	}
	



?>