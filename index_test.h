const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <title> Tuto Chart.js</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
</head>

<style>
.bloc-graph{
  position:fixed;
  border: solid 1px;
  width:1000px;
  top:10px;
  left:500px;
  bottom: 200px;
  right:10px;
}
</style>
<body>

<form> 
  <input type="button" value="ON">
</form>
<p>OFF</p>

<div class="bloc-graph">
  <h1>Chart.js</h1>
  <canvas id="myChart"></canvas>
  
  <script >
    var ctx = document.getElementById('myChart').getContext('2d');
    var chart = new Chart(ctx, {
      // The type of chart we want to create
      type: 'line',

      // The data for our dataset
      data: {
        labels: [],
        datasets: [{
          label: 'My First dataset',
          backgroundColor: 'rgba(255, 99, 132,0)',
          borderColor: 'rgb(255, 99, 132)',
          data: []
        }]
      },

      // Configuration options go here
      options: {
        scales:{
          yAxes:[{
            ticks: {
            min: 0,
            max: 300,
            }
          }]
        }
      }
    });
  </script>
</div>

<table id="tableau" border="1">
	<thead>
		<tr>
			<th>Valeur</th>
			<th>Minutes</th>
			<th>Seconde</th>
			<th>Milliseconde</th>
		</tr>
	</thead>
</table>
	
<script>

/* ************************************************************** */
/* ************************************************************** */
setInterval(mainFunction(), 1000);      
/* ************************************************************** */
/* ************************************************************** */
var dat;

function mainFunction() {
  if (btn.value === 'OFF') {
    getData();
    if (document.getElementById("tableau").rows.length >6){
      supprimerLigne();
    }
    if(chart.data.labels.length >50){
      removeData(chart);
    }
  } 
}
    
/* ************************************************************** */
/* ************************************************************** */
var btn = document.querySelector('input');
var txt = document.querySelector('p');

btn.addEventListener('click', updateBtn);
/* ************************************************************** */
/* ************************************************************** */
function updateBtn() {
  if (btn.value === 'ON') {
    btn.value = 'OFF';
    txt.textContent = 'BEGIN !';
  } else {
    btn.value = 'ON';
    txt.textContent = 'END';
    document.getElementById("ADCValue").innerHTML = 0;
  }
}
/* ************************************************************** */
/* ************************************************************** */
function getData() {
  if (btn.value ==='OFF') {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      	dat = this.responseText;
	ajouterLigne();
     	}
    };
    xhttp.open("GET", "readADC", true);
    xhttp.timeout = 1000;
    xhttp.send();
  }
}
/* ************************************************************** */
/* ************************************************************** */

function ajouterLigne()
{
	var tableau = document.getElementById("tableau");
	var ligne = tableau.insertRow(-1);                                          //on a ajoute une ligne
	var colonne1 = ligne.insertCell(0);                                         //on a une ajoute une cellule
 	colonne1.innerHTML += dat;
  
	var date = new Date();
	var colonne2 = ligne.insertCell(1);
	colonne2.innerHTML += date.getMinutes();                                    //on ajoute le jour du mois
	
	var colonne3 = ligne.insertCell(2);
	colonne3.innerHTML += date.getSeconds();
	
	var colonne4 = ligne.insertCell(3);
	colonne4.innerHTML += date.getMilliseconds();

  	addData(chart, colonne4.innerHTML, colonne1.innerHTML);

}

/* ************************************************************** */
/* ************************************************************** */
function supprimerLigne(){
  document.getElementById("tableau").deleteRow(1);
}
/* ************************************************************** */
/* ************************************************************** */
function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}
/* ************************************************************** */
/* ************************************************************** */
function removeData(chart) {
    chart.data.labels.splice(0,1);
    chart.data.datasets.forEach((dataset) => {
      dataset.data.splice(0,1);
    }); 
    chart.update();
}
/* ************************************************************** */
/* ************************************************************** */

</script>
</body>
</html>
)=====";
