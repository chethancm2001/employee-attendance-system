const char webpageCode[] = R"=====(
<!doctype html>
<html>
<head>
  <title>Data Logger</title>
  <h1 style="text-align:center; color:red;">Contactless Employee attendece system</h1>
  <h3 style="text-align:center;">Employee Temperature Logger</h3>
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }
  /* Data Table Styling*/ 
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    text-align: center;
  }
  #dataTable td, #dataTable th {
    border: 1px solid #000000;
    padding: 8px;
  }
  #dataTable tr:nth-child(even){background-color: #f2f2f2;}
  #dataTable tr:hover {background-color: #ddd;}
  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: center;
    background-color: #3366ff;
    color: white;
  }
  </style>
</head>
<body>   
<div>
  <table id="dataTable">
    <tr><th>Time</th><th>Name </th><th>Temperature (&deg;C)</th></tr>
  </table>
</div>
<br>
<br>  
<script>
var Tvalues = [];
var Nvalues = [];
var timeStamp = [];
setInterval(function() {
  // Call a function repetatively with 5 Second interval
  getData();
}, 500); //5000mSeconds update rate
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
  var time = new Date().toLocaleTimeString();
  var txt = this.responseText;
  var obj = JSON.parse(txt); 
      Nvalues.push(obj.Name);
      Tvalues.push(obj.Temperature);
      timeStamp.push(time);
  //Update Data Table
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1); //Add after headings
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    var cell3 = row.insertCell(2);
    cell1.innerHTML = time;
    cell2.innerHTML = obj.Name;
    cell3.innerHTML = obj.Temperature;
    }
  };
  xhttp.open("GET", "reader", true); //Handle readData server on ESP8266
  xhttp.send();
}   
</script>
</body>
</html>

)=====";
