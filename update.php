<?php
$servername='localhost';
$username='root';
$password='';
$dbname = "yourdatabasename";
try {
    $voltage = $_GET['voltage'];
    $current = $_GET['current'];
    $power1 = $_GET['power1'];
    $energy = $_GET['energy'];
	$frequency = $_GET['frequency'];
    $pf = $_GET['pf'];
    $currenta = $_GET['currenta'];
    $currentb = $_GET['currentb'];
    $voltagea = $_GET['voltagea'];
    $voltageb = $_GET['voltageb'];
    $powera = $_GET['powera'];
    $powerb = $_GET['powerb'];
    $energya = $_GET['energya'];
    $energyb = $_GET['energyb'];
    $frequencya = $_GET['frequencya'];
    $frequencyb = $_GET['frequencyb'];
    $pfa = $_GET['pfa'];
    $pfb = $_GET['pfb'];


	
    date_default_timezone_set("Asia/Calcutta");
    $insertdate = date("Y-m-d H:i:s");
    $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    /* set the PDO error mode to exception */
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
               $sql = "UPDATE pzemdata SET voltage='$voltage', current='$current', power1='$power1', energy='$energy', frequency='$frequency', pf='$pf', currenta='$currenta', currentb='$currentb', voltagea='$voltagea', voltageb='$voltageb', powera='$powera', powerb='$powerb', energya='$energya', energyb='$energyb', frequencya='$frequencya', frequencyb='$frequencyb', pfa='$pfa', pfb='$pfb'";
    $conn->exec($sql);
    echo " record updated successfully";
    }
catch(PDOException $e)
    {

    	echo $sql . "<br>" . $e->getMessage();
    }

$conn = null;
?>
