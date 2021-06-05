<html>
  <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title> λ:/0X4F/LYR/01/</title>
        <link href="style.css" rel="stylesheet" type="text/css" media="all">
  </head>

  <body>
    <div class="title">
      <b><h1>/0x4F Guestbook/<h1></b>
    </div>
      <pre>
        <form action="addcomment.php" method="post" name="guest">
          Name:    <input type="text" name="name" />
	  
	  Comment: 
	  <textarea cols="50" name="message" rows="10"> </textarea>

          <input type="submit" value="Submit" />
        </form>
      </pre>
  </body>
</html>

<?php
	$host="localhost"; //Add your SQL Server host here
	$user="root"; //SQL Username
	$pass="p@ssWord#12345";
	$dbname="site_data"; //SQL Database Name
	$con=mysqli_connect($host,$user,$pass,$dbname);
	
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	$result = mysqli_query($con,"SELECT name,message FROM guestbook");
	
	while($row = mysqli_fetch_array($result)) { ?>
		<link href="style.css" rel="stylesheet" type="text/css" media="all">
		<title>0x4F Guestbook</title>
		<div class="projectTop">
			<h3>Name: <?php echo $row['name']; ?></h3>
			<p><?php echo $row['message']; ?></p>
		</div>
		<br>
	<?php }
	mysqli_close($con);
?>
