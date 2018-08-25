

<?php
	require_once('inc/connection.php');

	$id    = $_GET['emp_id'];
	$value = $_GET['allow'];
	
	$Query = "INSERT INTO attendence(emp_id, allow) VALUES($id, $value)";
	
	if(!mysqli_query($connection, $Query)){
		die('Erro :' . mysqli_error($connection));
	}
	else{
		echo "Record Insert Successfully";
	}
	
	mysqli_close($connection);

?>