<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <?php require_once('inc/connection.php'); ?>

    <title>MY Attendence System </title>

<?php 
  $atten_list = '';

  $query = "SELECT * FROM attendence";

  $result = mysqli_query($connection, $query);

  $row = mysqli_fetch_array($result, MYSQLI_ASSOC); 

  while($row = mysqli_fetch_array($result))
  {
      $atten_list .= "<tr>";
      $atten_list .= "<td>" . $row['emp_id'] . "</td>";
      $atten_list .= "<td>" . $row['allow'] . "</td>";
      $atten_list .= "<td>" . $row['time'] . "</td>";
      $atten_list .= "</tr>";
  }
 
 ?>


    <link rel="stylesheet" href="css/style.css">


</head>

<body>

    <div class="table-users">
        <div class="header">Users</div>

        <table cellspacing="0">
            


    
  <div class = "scroll" >
    <table id="Attendence">
      <tr>
          <th><b>Employee ID</b></th>
          <th><b>Allow</b></th>

          <div id="last_login">
              <th><b>Last Login</b></th>  
          </div>
        </tr>
      <?php echo $atten_list; ?>
    </table>
  </div><!--scroll-->

