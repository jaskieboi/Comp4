<!DOCTYPE html>
<html>
<body>

<?php 
$file = 'data.txt';

$current = file_get_contents($file);

$current =  $_GET['a'] . $_GET['b']. $_GET['c']. $_GET['d']. $_GET['e']. $_GET['f']. $_GET['g'].$_GET['h'].$_GET['i'];

if ($_GET['a'] == '9'){
$current = '9' ; 
}

file_put_contents($file, $current);

?>


<?php 
$filer = 'data.txt';

$currentr = file_get_contents($filer);

echo $currentr;

?>


</body>
</html>
