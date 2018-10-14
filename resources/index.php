<h3>Info about client:</h3>
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

<h3>FORM</h3>
<form action="index.php" method="post">
	<br>Name: <input type="text" name="name">
	<br>E-mail: <input type="text" name="email">
	<input type="submit">
</form>

<h3>RESPONSE</h3>
Welcome <?php echo $_POST["name"]; ?><br>
Your email address is: <?php echo $_POST["email"]; ?>