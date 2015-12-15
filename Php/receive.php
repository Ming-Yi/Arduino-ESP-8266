<?php
  //判斷是否有GET value的參數
  if(isset($_GET['value']))
    $data = $_GET['value'];
  else
    exit;

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

  //sql新增語法
  $sql = "insert into $tableName (data) VALUES ($data)";
  $result = mysql_query($sql);

  //判斷Query 是否成功
  if($result==1)
    echo "success";
  else
    echo "error";
?>