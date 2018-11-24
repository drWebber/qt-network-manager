<?php
if(!isset($_COOKIE["Test"])){
	setcookie("Test", "HELLO", 0, '/');
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Aloha, username!</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular.min.js"></script>
</head>
<body>
<div class="container" ng-app="myApp" ng-controller="myCtrl">
	<h3>FORM</h3>
	<form action="index.php" method="post">
		<div class="input-group mb-3">
			<div class="input-group-prepend">
			  <span class="input-group-text">Name</span>
			</div>
			<input name="name" type="text" class="form-control">
		</div>
		<div class="input-group mb-3">
			<div class="input-group-prepend">
			  <span class="input-group-text">E-mail</span>
			</div>
			<input name="email" type="text" class="form-control">
		</div>
		<input type="submit">
	</form>

	<h3>RESPONSE</h3>
	<p>Welcome <?php echo $_POST["name"]; ?></p>
	<p>Your email address is: <?php echo $_POST["email"]; ?></p>
	<h3>Client's info:</h3>
	<?php	
		echo '$_SERVER[HTTP_CONNECTION] = ' . $_SERVER ['HTTP_CONNECTION'] . "<br />";
		echo '$_SERVER[HTTP_PROXY_CONNECTION] = ' . $_SERVER ['HTTP_PROXY_CONNECTION'] . "<br />";
		echo '$_SERVER[HTTP_CACHE_CONTROL] = ' . $_SERVER ['HTTP_CACHE_CONTROL'] . "<br />";
		echo '$_SERVER[HTTP_USER_AGENT] = ' . $_SERVER ['HTTP_USER_AGENT'] . "<br />";
		echo '$_SERVER[HTTP_ACCEPT] = ' . $_SERVER ['HTTP_ACCEPT'] . "<br />";
		echo '$_SERVER[HTTP_REFERER] = ' . $_SERVER ['HTTP_REFERER'] . "<br />";
		echo '$_SERVER[HTTP_ACCEPT_ENCODING] = ' . $_SERVER ['HTTP_ACCEPT_ENCODING'] . "<br />";
		echo '$_SERVER[HTTP_ACCEPT_LANGUAGE] = ' . $_SERVER ['HTTP_ACCEPT_LANGUAGE'] . "<br />";

		echo '<h3>$_POST:</h3>';
		print_r ( $_POST );
		echo '<h3>$_GET:</h3>';
		print_r ( $_GET );
		echo '<h3>$_FILES:</h3>';
		print_r ( $_FILES );
		echo '<h3>$_COOKIE:</h3>';
		print_r ( $_COOKIE );
	?>
	<div>{{selfie}}</div>
</div>
<script>
	angular.module("myApp", []).controller("myCtrl", function ($scope) {
	});
</script>
</body>
</html>