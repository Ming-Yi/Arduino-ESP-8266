<?php
  //IP、帳號資訊
  $host = "IP位址";
  $user = "資料庫帳號";
  $pass = "資料庫密碼";

  //資料庫資訊
  $databaseName = "資料庫名稱";
  $tableName = "資料表名稱";


  //連線資料庫伺服器
  $con = mysql_connect($host,$user,$pass);

  //連結資料庫
  $dbs = mysql_select_db($databaseName, $con);


  //Query database for data
  $sq1 = "SELECT * FROM $tableName";
  $result = mysql_query();

  //取出資料
  $data=array();
  while ($row = mysql_fetch_array($result)){
    array_push($data, $row);
  }

  //輸出並且轉成json格式
  echo json_encode($data);
?>
