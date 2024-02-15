
/**========================================================================
 *                           Navbar
 *========================================================================**/
function showSidebar() {
  const sidebar = document.querySelector('.sidebar');
  sidebar.style.display = 'flex';
}
function hideSidebar() {
  const sidebar = document.querySelector('.sidebar');
  sidebar.style.display = 'none';
}
/*============================ END OF Nabbar ============================*/

/**========================================================================
 *                           WebSocket
 *========================================================================**/
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
// Init web socket when the page loads
window.addEventListener('load', onLoad);
function onLoad(event) {
 initWebSocket();
}



document.getElementById('sBarBtn').addEventListener('click', function () {
    websocket.send("barStates");
  });
function initWebSocket() {
 console.log('Trying to open a WebSocket connection...');
 websocket = new WebSocket(gateway);
 websocket.onopen = onOpen;
 websocket.onclose = onClose;
 websocket.onmessage = onMessage;
}
// When websocket is established
// call  function 
// use event listener  
function onOpen(event) {
 console.log('Connection opened');
}
 
function onClose(event) {
    // in case connection down
    // try again after 2 sec
 console.log('Connection closed');
 setTimeout(initWebSocket, 2000);
}
function onMessage(event) {
    var myObj = JSON.parse(event.data);
      // Check if the received data contains intensity information
      if (myObj.hasOwnProperty('intensityData')) {
        // Assuming intensityData is an array of objects { wavelength, intensity }
        var intensityData = myObj.intensityData;

        // Update the chart with the received intensity data
        updateChart(intensityData);
    }
    var keys = Object.keys(myObj);
    for (i in myObj.sbar) {
        var output = myObj.sbar[i].output; // UV , VI , WL
        var state = myObj.sbar[i].state; // on (1) , off (0)
     if (state != "0") {
            document.getElementById(output+"stateBar").textContent = state;
        }
    else{
        document.getElementById(output+"stateBar").textContent = "OFF";
    }  

    }
    console.log(event.data); // for debugging 
}




/**========================================================================
 *                           Tabs control
 *========================================================================**/
openTab(onLoad, 'scan');
function openTab(evt, Control) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
      tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
      tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(Control).style.display = "block";
    if(evt==onLoad){
      document.getElementById('first').classList.add('active');}
    else{evt.currentTarget.className += " active";
    if(Control!=='scan'){ document.getElementById('first').classList.add('inactive')
                        }
    else{document.getElementById('first').classList.add('active');
        console.log("inactive");}
  }
    
  }
/*============================ END OF Tabs ============================*/






  var absorptionData = [];
  var concentrationData = [];
  var chart;
  updateChart();
  function addPoint() {
    var absorptionValue = parseFloat(document.getElementById("absorption").value);
    var concentrationValue = parseFloat(document.getElementById("concentration").value);

    if (!isNaN(absorptionValue) && !isNaN(concentrationValue)) {
      absorptionData.push(absorptionValue);
      concentrationData.push(concentrationValue);

      displayMessage(`Point added - Absorption:  ${absorptionValue} , Concentration:  ${concentrationValue}`, 'blue');
      clearInputs(); updateChart();
    } else {
      alert("Please enter valid numerical values for absorption and concentration.");
    }
  }
  function updateChart() {
    if (chart) {
      chart.destroy(); // Destroy the existing chart to update with new data
    }
    var ctx = document.getElementById('myChart').getContext('2d');
    chart = new Chart(ctx, {
      type: 'scatter',
      data: {
        datasets: [{
          label: 'Data Points',
          data: getScatterData(),
          borderColor: 'rgba(75, 192, 192, 1)',
          backgroundColor: 'rgba(75, 192, 192, 1)',
          pointRadius: 5,
          showLine: false
        }, {
          label: 'Regression Line',
          data: calculateRegressionLine(),
          borderColor: 'rgba(255, 0, 0, 1)',
          backgroundColor: 'rgba(255, 0, 0, 0.2)',
          borderWidth: 2,
          pointRadius: 0,
          showLine: true
        }]
      },
      options: {
        scales: {
          x: {
            type: 'linear',
            position: 'bottom'
          },
          y: {
            type: 'linear',
            position: 'left'
          }
        }
      }
    });
  }
      
  

  function getScatterData() {
    var data = [];
    for (var i = 0; i < absorptionData.length; i++) {
      data.push({ x: absorptionData[i], y: concentrationData[i] });
    }
    return data;
  }

  function calculateRegressionLine() {
    var N = absorptionData.length;
  
    // Check if there are enough data points
    if (N < 2) {
      console.error("Insufficient data points for regression analysis.");
      return [];
    }
  
    var sumX = absorptionData.reduce((acc, x) => acc + x, 0);
    var sumY = concentrationData.reduce((acc, y) => acc + y, 0);
    var sumXY = 0;
    var sumX2 = 0;
  
    for (var i = 0; i < N; i++) {
      sumXY += absorptionData[i] * concentrationData[i];
      sumX2 += Math.pow(absorptionData[i], 2);
    }
  
    var numerator = N * sumXY - sumX * sumY;
    var denominator = N * sumX2 - Math.pow(sumX, 2);
  
    // Check if the denominator is zero
    if (denominator === 0) {
      console.error("Denominator is zero. Unable to calculate regression line.");
      return [];
    }
  
    var slope = numerator / denominator;
    var intercept = (sumY - slope * sumX) / N;
  
    // Check if slope and intercept are valid numbers
    if (isNaN(slope) || isNaN(intercept)) {
      console.error("Invalid slope or intercept. Unable to calculate regression line.");
      return [];
    }
  
    // Display the slope and intercept in the message box
    displayMessage(`Slope: ${slope.toFixed(2)}, Intercept: ${intercept.toFixed(2)}`, 'green');
  
    return [
      // ... because it array
      { x: Math.min(...absorptionData), y: slope * Math.min(...absorptionData) + intercept },
      { x: Math.max(...absorptionData), y: slope * Math.max(...absorptionData) + intercept }
    ];
  }
  
  
  function displayMessage(message, color) {
    var messageBox = document.getElementById("messageBox");
    var messageElement = document.createElement("p");
    messageElement.textContent = message;
    messageElement.style.color = color; // Set the text color
    messageBox.appendChild(messageElement);
  }
  
  function clearAll() {
    absorptionData = [];
    document.getElementById("messageBox").innerHTML="";
    concentrationData = [];
    updateChart();
    clearMessage();
  }
  function clearInputs() {
    document.getElementById("absorption").value = "";
    document.getElementById("concentration").value = "";
  }
/**========================================================================
 *                           SCAN T_T
 *========================================================================**/
  // Initial chart setup

  let isScanning = false;
  var intensityData  =[];
  var wavelengthData =[];
  var chartScan;

  // Initialize chartData
  let chartData = {
    labels: [],
    datasets: [{
      label: 'Scan Curve',
      data: [],
      borderColor: '#3498db',
      borderWidth: 2,
      fill: false,
      lineTension: 0.4 // Adjust the line tension for the curve
    }]
  };

  const ctxScan = document.getElementById('chartScan').getContext('2d');
  chartScan = new Chart(ctxScan, {
    type: 'line',
    data: chartData,
    options: {
      responsive: true, // Set responsive to false
        maintainAspectRatio: true, // Set maintainAspectRatio to false
        width: 400, // Set the width
        height: 400, // Set the height
      scales: {
        x: {
          type: 'linear',
          position: 'bottom'
        },
        y: {
          type: 'linear',
          position: 'left'
        }
      }
    }
  });
  function addCurve(xData, yData, color, curveName) {
    var curveData = xData.map((x, index) => ({ x: x, y: yData[index] }));
    chartScan.data.datasets.push({
      label: curveName,
      data: curveData,
      borderColor: color,
      borderWidth: 2,
      fill: false,
      lineTension: 0.4
    });
    chartScan.update();
  }
  // Function to remove a curve from the chart
function removeCurve(index) {
  chartScan.data.datasets.splice(index, 1);
  chartScan.update();
}

  function isValidDecimalDigits(value, maxDigits) {
    const decimalDigits = (value.toString().split('.')[1] || '').length;
    return decimalDigits <= maxDigits;
  }
  function validateInputs() {
    // parsefloat < conv from string to float
    const startInput = parseFloat(document.getElementById('start').value);
    const stopInput = parseFloat(document.getElementById('stop').value);

    if (isNaN(startInput) || isNaN(stopInput) || startInput < 100 || stopInput > 1200) {
      alert('Start and Stop values must be between 100 and 1200');
      return false;
    }
  
    if (!isValidDecimalDigits(startInput, 5) || !isValidDecimalDigits(stopInput, 5)) {
      alert('Number of digits after the decimal point must not exceed 5');
      return false;
    }
  
    if (startInput >= stopInput) {
      alert('Start value must be smaller than Stop value');
      return false;
    }
  
    return true;
  }
  function startScan() {
    if (!isScanning) {
      if (!validateInputs()) return;
  
      isScanning = true;
      disableInputs();
      scan();
    }
  }
  function toggleInputs(disabled) {
    const inputs = document.querySelectorAll('#scan input, #scan select');
    inputs.forEach(input => (input.disabled = disabled));
  }
  
  function disableInputs() {
    toggleInputs(true);
  }
  
  function enableInputs() {
    toggleInputs(false);
  }
  
  function pauseScan() {
    isScanning = false;
    enableInputs();
  }
  function scan() {
    const startInput = parseFloat(document.getElementById('start').value);
    const stopInput = parseFloat(document.getElementById('stop').value);
    const stepInput = parseFloat(document.getElementById('step').value);
    const speedInput = parseFloat(document.getElementById('speed').value);
    const initTimeInput = parseFloat(document.getElementById('initTime').value);
    const modeInput = document.getElementById('mode').value;
  
   
  
    chartData.labels = []; // wavelength
    chartData.datasets[0].data = []; // intensity
  
    function processScanData(data) {
      const wavelength = data.wavelength;
      const intensitySample = data.intensitySample;
      const intensity0 = data.intensity0;
  // Update the chart data
  chartData.labels.push(wavelength);
  
  if (modeInput=="absorption"){
      // Calculate absorption
      var absorption = Math.log10(intensity0/intensitySample );
      chartData.datasets[0].data.push(absorption);}
  else  {
    var transmission = Math.log10(intensity0/intensitySample );
    chartData.datasets[0].data.push(transmission);
  }
  
  
      // Update the chart
      chartScan.data.labels = chartData.labels;
      chartScan.data.datasets[0].data = chartData.datasets[0].data;
      chartScan.update();
    }
  
    function sendScanRequest(wavelength) {
      const message = {
        command: 'Scan',
        wavelength: wavelength,
      //  modeInput: modeInput,
      //  startInput: startInput,
      //  stopInput: startInput,

      };
      websocket.send(JSON.stringify(message));
    }
  
    function continueScanning(wavelength) {
      if (wavelength <= stopInput && isScanning) {
        sendScanRequest(wavelength);
      } else {
        // Scanning is complete
        isScanning = false;
        enableInputs();
        return;
      }
    }
  
    // Set up the WebSocket onmessage event
    websocket.onmessage = function (event) {
      const data = JSON.parse(event.data);
      console.log(event.data);
      processScanData(data);
  
      // Continue scanning for the next wavelength after a delay
      setTimeout(() => {
        continueScanning(data.wavelength + stepInput);
      }, speedInput * 1000);
    };
  
    // Start the scanning process
    continueScanning(startInput);
  }
  /*================preset section==============*/
  
function selectAbsorption() {
  var selectElement = document.getElementById("mySelect");
  // Find the index of the "absorption" option and set it as the selected index
  var absorptionIndex = Array.from(selectElement.options).findIndex(option => option.value === "absorption");
  selectElement.selectedIndex = absorptionIndex;
}
function selectTransmission() {
  var selectElement = document.getElementById("mySelect");
  
  // Find the index of the "transmission" option and set it as the selected index
  var transmissionIndex = Array.from(selectElement.options).findIndex(option => option.value === "transmission");
  selectElement.selectedIndex = transmissionIndex;
}

var myList = document.getElementById("presetlist");
function showpreset(){

  var message={
    showpreset:'showpreset'
  };
  const flyoutMenu = document.getElementById('presets');
  const computedStyle = window.getComputedStyle(flyoutMenu);
  if (computedStyle.display === 'none') {
  websocket.send(JSON.stringify(message));
  }  
websocket.onmessage = function (event) {
 
    var myObj = JSON.parse(event.data);
    console.log(myObj);
  if (myObj.hasOwnProperty('presetsno')){
        
        let i= myObj.presetsno;
        if(i==0){
          console.log('iiiii b =0');
          var nopresetsDiv = document.getElementById('nopresets');
          nopresetsDiv.innerHTML = 'No presets available';
         }
           
       
         else{
          console.log('iiiii mesh b =0');
          var nopresetsDiv = document.getElementById('nopresets');
          nopresetsDiv.innerHTML = '';
          for (var j = myList.children.length - 1; j >= 0; j--) {
            var child = myList.children[j];
            console.log(child.id);
            // Check if the element has an id and it is not "nopresets"
            if (child.id !== 'nopresets'&&child.id!=='search') {
            
              
              myList.removeChild(child);
              console.log('i deletet the child');
            }
          }
          
          for ( i ; i >0; i--) {
          (function (i) {
            let file = 'file' + i;
            console.log(myObj[file] + ": ");
            var newItem = document.createElement("li");
            var itemName = myObj[file];
            var textSpan = document.createElement("span");
            var textNode = document.createTextNode(itemName);
           
            textSpan.appendChild(textNode);
            newItem.appendChild(textSpan);
            myList.insertBefore(newItem, myList.lastChild);
            deletepreset(myList, itemName, newItem);

        
            newItem.addEventListener("click", function () {
              console.log("Clicked on item: " + itemName);
              var message = {
                loadthis: itemName
                        };
              websocket.send(JSON.stringify(message));
              
websocket.onmessage = function (event) {
  var myObj = JSON.parse(event.data);
  console.log(myObj);
var myreadings = document.getElementById("scanReadings");
var newItem = document.createElement("p");
var itemName = event.data;
var textNode = document.createTextNode(itemName);
newItem.appendChild(textNode);

myreadings.insertBefore(newItem, myreadings.lastChild);
  if(myObj.hasOwnProperty('loaded')){
  var startValue = parseInt(myObj.start, 10);
  var stopValue = parseInt(myObj.stop, 10);
  var stepValue = parseInt(myObj.step, 10);
  var speedValue = parseInt(myObj.speed, 10);
  var initTimeValue = parseInt(myObj.inittime, 10);
  document.getElementById('start').value = isNaN(startValue) ? '' : startValue;
  document.getElementById('stop').value = isNaN(stopValue) ? '' : stopValue;
  document.getElementById('step').value = isNaN(stepValue) ? '' : stepValue;
  document.getElementById('speed').value = isNaN(speedValue) ? '' : speedValue;
  document.getElementById('initTime').value = isNaN(initTimeValue) ? '' : initTimeValue;

  if((myObj.mode.trim() === 'transmission')){
      selectTransmission();
    }
    else{
      selectAbsorption();
    }

  }
  

}

            });
          })(i);
        }
      }
        
      
    
  }
}
  openlist();
    
}



function deletepreset(myList,names,newItem){
  var deleteButton = document.createElement("button");
            deleteButton.innerHTML = "delete";
            deleteButton.classList.add("delete-button");
            deleteButton.addEventListener("click", function () {
            myList.removeChild(newItem);
            var message={
              deletepreset:'deletepreset',
              name:names,
            };
            websocket.send(JSON.stringify(message));
            showpreset();
           });
            
            // Append the delete button to the new list item
            newItem.appendChild(deleteButton);
            
}
  function savepreset(){
    document.getElementById('nameexist').innerHTML=''; 
    openname();  
    showpreset();
    openlist(); 
}

function addtolist() {
  var itemName = document.getElementById("prestinput").value;
  var myList = document.getElementById("presetlist");
  if (itemName.trim() !== "") {
    if (!nameExists(itemName, myList)) {
      let startInput = parseFloat(document.getElementById('start').value);
      let stopInput = parseFloat(document.getElementById('stop').value);
      let stepInput = parseFloat(document.getElementById('step').value);
      let speedInput = parseFloat(document.getElementById('speed').value);
      let initTimeInput = parseFloat(document.getElementById('initTime').value);
      let modeInput = document.getElementById('mySelect').value;
      var message = {
          savepreset: 'savepreset',
          id: '1',
          name: itemName,
          start: startInput,
          stop: stopInput,
          step: stepInput,
          speed: speedInput,
          inittime: initTimeInput,
          mode: modeInput,
                  };
        websocket.send(JSON.stringify(message));
        cancelpreset();
    } else {
      document.getElementById('nameexist').innerHTML='name exist try another name';
    }
  }
}

function nameExists(name, list) {
  // Check if the name already exists in the list
  var items = list.getElementsByTagName("li");

  for (var i = 0; i < items.length; i++) {
    var spans = items[i].getElementsByTagName("span");
    if (spans.length > 0) {
      var text = spans[0].textContent;
      if (text === name) {
        return true; // Name already exists
      }
    }
  }
  return false; // Name does not exist
}

function cancelpreset(){
  const flyoutMenu = document.getElementById('presetname');
  flyoutMenu.classList.remove('active');
}

document.addEventListener('click', function (event) {
  const flyoutBtn = document.getElementById('loadpreset');
  const flyoutMenu = document.getElementById('presets');

  if (event.target !== flyoutBtn && event.target !== flyoutMenu && !flyoutMenu.contains(event.target)) {
    // Click outside the button and the flyout menu, close the flyout menu
    flyoutMenu.classList.remove('active');
  }
});


function openname() {
  const flyoutMenu = document.getElementById('presetname');
  flyoutMenu.classList.toggle('active');
}

function openlist() {
  const flyoutMenu = document.getElementById('presets');
  flyoutMenu.classList.toggle('active');

}

var input = document.getElementById("search");

input.addEventListener('input', filter);
function filter() {
  var search = input.value.toLowerCase();
  var myListArray= myList.querySelectorAll('li');
  myListArray.forEach(function (li) {
    var span = li.querySelector('span'); // Get the span element inside the list item
    var textNode = span.firstChild; // Get the text node inside the span
    var text = textNode.nodeValue.toLowerCase(); // Get the text content of the text node

    var found = text.indexOf(search);
    
    if (search === '' || found !== -1) {
     
      li.style.display='block';
    } else {
      li.style.display='none';
      
    
    }
  });
}


/*============table================*/
setTimeout( showfoot,1000);
document.getElementById('hidefoot').addEventListener('click',showfoot)
function showfoot() {
  var but= document.getElementById('hidefoot');
  var foot =document.getElementById('hidethis'); 
  if (but.innerHTML === 'hide') {
    but.innerHTML = 'show';
  } 
  else {
    but.innerHTML = 'hide';
  }
  foot.classList.toggle('inactive'); 
}

function validateInput(input, max) {
  if (parseInt(input.value) > max) {
      input.value = max;
  }
}
function handletable(){
  handelrow();
  handleColumn();
}

  
document.getElementById('trow0').addEventListener('click',handelny);
   
function handelrow() {
  
  var rowNumber = document.getElementById('rowno').value;
  rowNumber--;
  var sampleRow = document.getElementById('trow0');
  var tableBody = document.getElementById('t_body');
 //remove first
  while (tableBody.children.length > 1) {
    tableBody.removeChild(tableBody.lastChild);
  }

// Add new rows
for (var i = 0; i < rowNumber; i++) {
    var newRow = sampleRow.cloneNode(true);
    newRow.id = 'trow' + (i + 1);
    newRow.querySelector('#curveIndex').innerText = (i + 2);
    tableBody.appendChild(newRow);
    document.getElementById(newRow.id).addEventListener('click',handelny);
    // Update indices for each cell in the row
    var cells = newRow.querySelectorAll('td');
    for (var j = 0; j < cells.length; j++) {
      cells[j].id = 'data-index' + (i + 1) + (j + 1);
      // Add event listener to input element inside the cell
      var inputElement = cells[j].querySelector('button');
      if (inputElement) {
          inputElement.addEventListener('click', handecell);
      }
  }
  
}
}

function handelny(event){
  var rowclicked=event.target.id;
  console.log("Clicked Row ID: " + rowclicked);
  
}

function handecell(event) {
  var clickedCellId = event.target.id;
  console.log("Clicked cell ID: " + clickedCellId);
}
function handleColumn() {
  var table = document.getElementById('samplestable');
  var rowCount = table.rows.length;
 
  for (var i = table.rows[0].cells.length - 1; i >= 6; i--) {
    table.rows[0].deleteCell(i);
    for (var j = 1; j < table.rows.length; j++) {
      table.rows[j].deleteCell(i);
    }
  }
var j=document.getElementById('colno').value;
j=j-1;
for(j;j>0;j--){
  // Add header cell
  var headerCell = document.createElement('th');
  headerCell.textContent = 'Function ';
  table.rows[0].appendChild(headerCell);

  // Add data cells for each row
  for (var i = 1; i < rowCount; i++) {

    var cellClone = table.rows[i].lastElementChild.cloneNode(true);
    table.rows[i].appendChild(cellClone);
    
  }
}
}

function updateClock(initialDateTimeString) {
  let currentDate = new Date(initialDateTimeString);  
  setInterval(function () {
    currentDate.setSeconds(currentDate.getSeconds() + 1);
    let formattedDate = currentDate.toLocaleString('en-GD', { 
      day: 'numeric', 
      month: 'numeric', 
      year: 'numeric', 
      hour: 'numeric', 
      minute: 'numeric', 
      second: 'numeric', 
      hour12: true
    });
    document.getElementById('DateTime').innerText = formattedDate;
  }, 1);
}
updateClock("1/13/2021 13:32:12");



  
/**========================================================================
 *                           ADC
 *========================================================================**/


function pauseReading() {
  startReadADC = 0;
  document.getElementById("i2cValue").innerHTML="";

}
let startReadADC=0;
function readADC() {
  startReadADC = 1;
  function sendADCRequest() {
    const message = {
      command: 'ADC',
    };
    websocket.send(JSON.stringify(message));
  }

  function continueReadADC() {
    if (startReadADC == 1) {
      sendADCRequest();
    } else {
      enableADC();
      return;
    }
  }
  function processADCData(data) {
    var messageBox = document.getElementById("i2cValue");
    var messageElement = document.createElement("p");
    messageElement.textContent = data;
    messageElement.style.color = 'black'; // Set the text color
    messageBox.appendChild(messageElement);
  }
  // Set up the WebSocket onmessage event
  websocket.onmessage = function (event) {
    const data = JSON.parse(event.data);
    console.log(event.data);
    processADCData(data);

    // Continue scanning for the next wavelength after a delay
    setTimeout(() => {
      continueReadADC();
    }, 1000);
  };

  continueReadADC();
}
