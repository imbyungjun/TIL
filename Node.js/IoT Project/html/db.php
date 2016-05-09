<?php
    $host="localhost";
    $login="root";
    $passwd="imb";
    $name="iot";
       
    $db =  mysql_connect($host,$login,$passwd);
    mysql_select_db($name);    

	/*
    $day = date('d');
    $month = date('m');
    $lastMonth = (string)($month-1);	
    $lastMonth = strlen($month - 1) == 1? '0'.$lastMonth : $lastMonth;
	 */
    $SQLString = "SELECT * FROM sensor";
										
    $result = mysql_query($SQLString);    
    $num = mysql_num_rows($result);   

# set heading	
    $data[0] = array('time','temp', 'co2');		
    for ($i=1; $i<($num+1); $i++)
    {
        $data[$i] = array(substr(mysql_result($result, $i-1, "time"), 11, 5),
			(int) mysql_result($result, $i-1, "temp"),
			(int) mysql_result($result, $i-1, "co2"));
    }	
    echo json_encode($data);
    mysql_close($db);
?>
