
<?php 
$file = 'log.txt';

$current = file_get_contents($file);

$concat = 'Q' . $current . 'Z' ;

echo $concat;



?>

