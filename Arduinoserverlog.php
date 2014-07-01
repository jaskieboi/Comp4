<!DOCTYPE html>
<html>
<body>

<?php 
$file = 'log.txt';

$current = file_get_contents($file);
date_default_timezone_set('Europe/London');
$date = date('d/m/Y h:i:s' , time());

$content = "\n".$date . " :   " .$_GET['a']  ;  

$current .=  $content ;


file_put_contents($file, $current);

?>


<?php 
$filer = 'log.txt';

$currentr = file_get_contents($filer);

echo $currentr;

?>


</body>
</html>
