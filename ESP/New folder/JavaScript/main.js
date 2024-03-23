
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
  setTimeout(initWebSocket, 20000);
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
      document.getElementById(output + "stateBar").textContent = state;
    }
    else {
      document.getElementById(output + "stateBar").textContent = "OFF";
    }

  }
  console.log(event.data); // for debugging 
}




/**========================================================================
 *                           Tabs control
 *========================================================================**/
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
  evt.currentTarget.className += " active";
}
/*============================ END OF Tabs ============================*/




/**------------------------------------------------------------------------
 *                           FLC
 *------------------------------------------------------------------------**/

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
  document.getElementById("messageBox").innerHTML = "";
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
var intensityData = [];
var wavelengthData = [];
var chartScan;
let chartData;


const ctxScan = document.getElementById('chartScan').getContext('2d');
chartScan = new Chart(ctxScan, {
  type: 'line',
  data: chartData,
  options: {
    responsive: true, // Set responsive to false
    maintainAspectRatio: true, // Set maintainAspectRatio to false
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
function addCurve(xData, yData, color, curveName, fillCurve = false) {
  // Check if the curve already exists
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);

  // If the curve exists, update its data
  if (existingCurveIndex !== -1) {
    chartScan.data.datasets[existingCurveIndex].data = xData.map((x, index) => ({ x: x, y: yData[index] }));
    chartScan.data.datasets[existingCurveIndex].borderColor = color;
    chartScan.data.datasets[existingCurveIndex].backgroundColor = fillCurve ? 'rgba(255, 0, 0, 0.3)' : undefined;
  } else { // If the curve doesn't exist, add it
    var curveData = xData.map((x, index) => ({ x: x, y: yData[index] }));
    var dataset = {
      label: curveName,
      data: curveData,
      borderColor: color,
      borderWidth: 2,
      pointRadius: 0,
      lineTension: 0.4
    };

    if (fillCurve) {
      dataset.fill = 'origin';
      dataset.backgroundColor = 'rgba(255, 0, 0, 0.3)';
    }

    chartScan.data.datasets.push(dataset);
  }

  chartScan.update(); // Update the chart
}

// funcation to remove all curves in chart js
function removeAllCurves() {
  chartScan.data.datasets = [];
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

function startScan(btn) {
  document.getElementById("CMDMB").innerHTML='';
  var row = btn.parentNode.parentNode; // Get the parent row of the button
  var index=row.rowIndex;  // Get the row index
  var SampleID = row.cells[2].innerHTML; 
  console.log("index0:"+index);
  console.log("sampleID0:"+SampleID);
   
  if (!isScanning) {
    if (!validateInputs()) return;
    disableInputs();
    isScanning = true;
    scan(index,SampleID); // send index to display message with index
    enableInputs();
    isScanning = false;
  }
  changeState(index, "Completed");
  
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


function scan(index,SampleID) {
  console.log("index1:"+index);
  console.log("sampleID1:"+SampleID);
  
  const startInput = parseFloat(document.getElementById('start').value);
  const stopInput = parseFloat(document.getElementById('stop').value);
  const stepInput = parseFloat(document.getElementById('step').value);
  const modeInput = document.getElementById('mySelect').value;
  var colorSelectArr = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink', 'gray', 'black'];    // change color according to index
  
  let x = []; // wavelength
  let y = []; // intensity
  function processScanData(data) {
    const currentTime = data.currentTime;
    const wavelength = data.wavelength;
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    const transmission = Math.log10(intensitySample / intensityReference);
    const absorption = Math.log10(intensityReference/ intensitySample);


    // Update the chart data
    x.push(wavelength);

    if (modeInput == "absorption") {
      y.push(absorption);
    }
    else {
      y.push(transmission);
    }
    const res = currentTime +": " +"|| Wavelength: "+wavelength + " ||Absorption: " + absorption + " ||Transmission: " + transmission;
    displayCMD(res, 'green', index);
    addCurve(x, y , colorSelectArr[index], SampleID);
   if(wavelength===stopInput){
    console.log("final wavelength is reached");
    savetosd(SampleID); 
   }

  }



  let isFirstTime = true;

  function continueScanning(wavelength) {
    if (isFirstTime) {
      const message = {
        command: 'Scan',
        startInput: startInput,
        stopInput: stopInput,
        stepInput: stepInput
        // modeInput: modeInput
      };
      websocket.send(JSON.stringify(message));
      isFirstTime = false;
    } 
    else if (wavelength <= stopInput && isScanning) {
        // Continue scanning
      }
    else {
        // Scanning is complete
        isScanning = false;
        enableInputs();
        return;
      }
    
  }
  

  // Set up the WebSocket onmessage event
  websocket.onmessage = function (event) {
    const data = JSON.parse(event.data);
    console.log(event.data); // for test
    processScanData(data);

    // Continue scanning for the next wavelength after a delay
    setTimeout(() => {
      continueScanning(data.wavelength + stepInput);
    }, 3000);
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

function showpreset() {
  var myList = document.getElementById("presetlist");

  var message = {
    showpreset: 'showpreset'
  };
  const flyoutMenu = document.getElementById('presets');
  const computedStyle = window.getComputedStyle(flyoutMenu);
  if (computedStyle.display === 'none') {
    websocket.send(JSON.stringify(message));
  }
  websocket.onmessage = function (event) {

    var myObj = JSON.parse(event.data);
    console.log(myObj);
    if (myObj.hasOwnProperty('presetsno')) {

      let i = myObj.presetsno;
      if (i == 0) {
        console.log('iiiii b =0');
        var nopresetsDiv = document.getElementById('noreadings');
        nopresetsDiv.innerHTML = 'No Readings available';
      }


      else {
        console.log('iiiii mesh b =0');
        var nopresetsDiv = document.getElementById('nopresets');
        nopresetsDiv.innerHTML = '';
        for (var j = myList.children.length - 1; j >= 0; j--) {
          var child = myList.children[j];
          console.log(child.id);
          // Check if the element has an id and it is not "nopresets"
          if (child.id !== 'nopresets' && child.id !== 'search') {
            myList.removeChild(child);
          }
        }

        for (i; i > 0; i--) {
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
                Dictionary:"presets",
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
                //myreadings.insertBefore(newItem, myreadings.lastChild);
                if (myObj.hasOwnProperty('loaded')) {
                  var startValue = parseInt(myObj.start, 10);
                  var stopValue = parseInt(myObj.stop, 10);
                  var stepValue = parseInt(myObj.step, 10);
                  var nameValue = myObj.id;
                  var discription = myObj.speed;
                  var initTimeValue = parseInt(myObj.inittime, 10);

                  document.getElementById('start').value = isNaN(startValue) ? '' : startValue;
                  document.getElementById('stop').value = isNaN(stopValue) ? '' : stopValue;
                  document.getElementById('step').value = isNaN(stepValue) ? '' : stepValue;
                  document.getElementById('SampleID').value = nameValue;
                  document.getElementById('SampleDecribe').value = discription;
                  document.getElementById('initTime').value = isNaN(initTimeValue) ? '' : initTimeValue;

                  if ((myObj.mode.trim() === 'transmission')) {
                    selectTransmission();
                  }
                  else {
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



function deletepreset(myList, names, newItem) {
  var deleteButton = document.createElement("div");
  deleteButton.textContent = "delete";
  deleteButton.classList.add("delete-button");
  deleteButton.addEventListener("click", function () {
    myList.removeChild(newItem);
    var message = {
      deletepreset: 'deletepreset',
      name: names,
    };
    websocket.send(JSON.stringify(message));
    showpreset();
  });
  // Append the delete button to the new list item
  newItem.appendChild(deleteButton);
}
function savepreset() {
  document.getElementById('nameexist').innerHTML = '';
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
      let nameInput = document.getElementById('SampleID').value;
      let disInput = document.getElementById('SampleDecribe').value;
      let initTimeInput = parseFloat(document.getElementById('initTime').value);
      let modeInput = document.getElementById('mySelect').value;
      var message = {
        savepreset: 'savepreset',
        id: nameInput,
        name: itemName,
        start: startInput,
        stop: stopInput,
        step: stepInput,
        speed: disInput,
        inittime: initTimeInput,
        mode: modeInput,
      };
      websocket.send(JSON.stringify(message));
      cancelpreset();
    } else {
      document.getElementById('nameexist').innerHTML = 'name exist try another name';
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

function cancelpreset() {
  const flyoutMenu = document.getElementById('presetname');
  flyoutMenu.classList.remove('active');
}

document.addEventListener('click', function (event) {
  const flyoutBtn = document.getElementById('loadpreset');
  const flyoutMenu = document.getElementById('presets');
  const raedingsbutton= document.getElementById('loadreadings');

  if (event.target !== flyoutBtn &&event.target!==raedingsbutton&& event.target !== flyoutMenu && !flyoutMenu.contains(event.target)) {
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
  console.log("anaaaaaa")

}

var input = document.getElementById("search");

input.addEventListener('input', filter);
function filter() {
  var search = input.value.toLowerCase();
  var myListArray = myList.querySelectorAll('li');
  myListArray.forEach(function (li) {
    var span = li.querySelector('span'); // Get the span element inside the list item
    var textNode = span.firstChild; // Get the text node inside the span
    var text = textNode.nodeValue.toLowerCase(); // Get the text content of the text node

    var found = text.indexOf(search);

    if (search === '' || found !== -1) {

      li.style.display = 'block';
    } else {
      li.style.display = 'none';


    }
  });
}


/**------------------------------------------------------------------------
 *                           TABLE
 *------------------------------------------------------------------------**/





/**------------------------------------------------------------------------
 *                           COLOR CHANGE
 *------------------------------------------------------------------------**/
// Function to change the color of a curve
function changeCurveColor(index, color) {
  chartScan.data.datasets[index].borderColor = color;
  chartScan.update(); // test name of chart scanChart
}

function changeColor() {
  var rIndex, table = document.getElementById('table');
  checkboxes = document.getElementsByName("check-tab1");
  for (var i = 1; i < table.rows.length; i++) {
    table.rows[i].onclick = function () {
      if (this.cells[7].querySelector('input').checked) {
        rIndex = this.rowIndex;
        var color = this.cells[6].querySelector('select').value;
        changeCurveColor(rIndex - 1, color);
      }
    }
  }
}

setTimeout(showfoot, 1000); //autohide foot in 1sec

document.getElementById('hidefoot').addEventListener('click', showfoot)


function showfoot() {
  var but = document.getElementById('hidefoot');
  var foot = document.getElementById('hidethis');
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




//edit name and disc
function edit(event) {
  var id = event.target.id;
  event.target.contentEditable = true;
  console.log(id);

}
//save them
function save(event) {
  var id = event.target.id;
  event.target.contentEditable = false;
  console.log(id);
}

/**------------------------------------------------------------------------
 *                           TIME AND DATE
 *------------------------------------------------------------------------**/

function updateDateTime() {

  document.getElementById('DateTime').textContent = new Date().toDateString() + " ," + new Date().toLocaleTimeString();
}

// Update the date and time every second
setInterval(updateDateTime, 1000);

// Initial update
updateDateTime();




/**========================================================================
 *                           ADC
 *========================================================================**/

function pauseReading() {
  startReadADC = 0;
  document.getElementById("i2cValue").innerHTML = "";

}
let startReadADC = 0;
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

/**------------------------------------------------------------------------
 *                           SCAN II TABLE
 *------------------------------------------------------------------------**/
function constructtable(num){
  var table = document.getElementById("myTable");
  
  for (var i = 1; i <= num; i++) {
    var row = table.insertRow(-1);
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    var cell3 = row.insertCell(2);
    var cell4 = row.insertCell(3);
    var cell5 = row.insertCell(4);
    var cell6 = row.insertCell(5);
    cell1.innerHTML = i;
    cell2.innerHTML = "Not Started";
    cell3.innerHTML = "Name " + i;
    cell4.innerHTML = "Description " + i;
    cell5.innerHTML = "<button onclick='startScan(this)'>Scan</button>";
    cell6.innerHTML = "Nabil";

    cell3.contentEditable = "true";
    cell4.contentEditable = "true";
    // Add event listener to the newly created 'cmd' input
    var cmdInput = cell6.querySelector('.cmd');

  }
}

document.getElementById('SampleNumBTN').addEventListener('click', function(){
  var num = document.getElementById('SampleNum').value; // Enclosed 'SampleNum' in quotes
 constructtable(num);
});
// remove all rows
document.getElementById('deleteBTN').addEventListener('click', function(){
  var table = document.getElementById("myTable");
  var mb = document.getElementById("CMDMB");
  removeAllCurves();
  mb.textContent = '';
  var rowCount = table.rows.length;
  for (var i = rowCount - 1; i > 0; i--) {
    table.deleteRow(i);
  }
  var headerCells = table.rows[0].cells;
  for (var i = headerCells.length - 1; i > 5; i--) {
    table.rows[0].deleteCell(i);
  }
});


/**------------------------------------------------------------------------
 *                           AREA under the curve 
 *------------------------------------------------------------------------**/


function changeState(rowIndex, newState) {
  var table = document.getElementById("myTable");
  var cell = table.rows[rowIndex].cells[1]; // Index 1 corresponds to the State cell
  cell.style.color = "green";
  cell.innerHTML = newState;
}

function trap(xPoints, yPoints) {
if (xPoints.length !== yPoints.length) {
    throw new Error("Number of x and y points must be the same.");
}

const n = xPoints.length;

let result = 0;

for (let i = 1; i < n; i++) {
    const trapezoidArea = 0.5 * (yPoints[i] + yPoints[i - 1]) * (xPoints[i] - xPoints[i - 1]);
    result += trapezoidArea;
}
return result;
}
// Example usage:
// const xValues = [700,699,698,697,696,695,694,693,692,691,690,689,688,687,686,685,684,683,682,681,680,679,678,677,676,675,674,673,672,671,670,669,668,667,666,665,664,663,662,661,660,659,658,657,656,655,654,653,652,651,650,649,648,647,646,645,644,643,642,641,640,639,638,637,636,635,634,633,632,631,630,629,628,627,626,625,624,623,622,621,620,619,618,617,616,615,614,613,612,611,610,609,608,607,606,605,604,603,602,601,600,599,598,597,596,595,594,593,592,591,590,589,588,587,586,585,584,583,582,581,580,579,578,577,576,575,574,573,572,571,570,569,568,567,566,565,564,563,562,561,560,559,558,557,556,555,554,553,552,551,550,549,548,547,546,545,544,543,542,541,540,539,538,537,536,535,534,533,532,531,530,529,528,527,526,525,524,523,522,521,520,519,518,517,516,515,514,513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,494,493,492,491,490,489,488,487,486,485,484,483,482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,463,462,461,460,459,458,457,456,455,454,453,452,451,450,449,448,447,446,445,444,443,442,441,440,439,438,437,436,435,434,433,432,431,430,429,428,427,426,425,424,423,422,421,420,419,418,417,416,415,414,413,412,411,410,409,408,407,406,405,404,403,402,401,400,399,398,397,396,395,394,393,392,391,390,389,388,387,386,385,384,383,382,381,380,379,378,377,376,375,374,373,372,371,370,369,368,367,366,365,364,363,362,361,360,359,358,357,356,355,354,353,352,351,350,349,348,347,346,345,344,343,342,341,340,339,338,337,336,335,334,333,332,331,330,329,328,327,326,325,324,323,322,321,320,319,318,317,316,315,314,313,312,311,310,309,308,307,306,305,304,303,302,301,300,299,298,297,296,295,294,293,292,291,290,289,288,287,286,285,284,283,282,281,280,279,278,277,276,275,274,273,272,271,270,269,268,267,266,265,264,263,262,261,260,259,258,257,256,255,254,253,252,251,250];
// const yValues = [0.02234,0.02244,0.02247,0.0225,0.02263,0.02253,0.02244,0.0226,0.02237,0.02265,0.02274,0.02255,0.02267,0.02261,0.02275,0.02288,0.0227,0.02303,0.02294,0.02304,0.02313,0.02327,0.02347,0.02343,0.02344,0.0238,0.02398,0.02453,0.02492,0.02623,0.02783,0.03071,0.03561,0.04003,0.04439,0.04769,0.0513,0.05325,0.05321,0.05159,0.0496,0.04809,0.04671,0.0453,0.04582,0.0478,0.05092,0.05624,0.06206,0.06895,0.07599,0.0784,0.0761,0.07425,0.07339,0.07221,0.07159,0.07205,0.07575,0.08285,0.09243,0.10083,0.10491,0.10434,0.10021,0.09375,0.08347,0.07018,0.05825,0.04889,0.04257,0.03817,0.03515,0.03327,0.03156,0.03022,0.02928,0.02843,0.02766,0.02734,0.02677,0.02645,0.02593,0.02577,0.02554,0.02531,0.02499,0.02512,0.02501,0.02502,0.02495,0.02487,0.02491,0.02478,0.02474,0.0246,0.02459,0.02465,0.02468,0.02447,0.02458,0.02462,0.02444,0.02467,0.02465,0.02453,0.02456,0.02434,0.02422,0.02416,0.02411,0.02404,0.02443,0.02433,0.02462,0.02449,0.02469,0.02506,0.02544,0.02562,0.0258,0.0264,0.02652,0.02689,0.02722,0.02761,0.02779,0.02785,0.02834,0.02857,0.02848,0.02872,0.02872,0.02919,0.02888,0.02897,0.02937,0.0294,0.0294,0.02949,0.02944,0.0295,0.03008,0.03064,0.0324,0.03581,0.04131,0.04587,0.04853,0.05166,0.05632,0.06351,0.07405,0.07908,0.07995,0.07867,0.07831,0.08163,0.09221,0.10707,0.12825,0.16216,0.19453,0.20988,0.21171,0.18648,0.14277,0.1036,0.0757,0.06007,0.0502,0.04474,0.04053,0.03814,0.03615,0.0346,0.03343,0.03253,0.03177,0.03132,0.03083,0.03043,0.03066,0.03012,0.03042,0.03038,0.03015,0.03036,0.03006,0.0303,0.03097,0.03068,0.03072,0.03007,0.03003,0.02999,0.03013,0.0297,0.02968,0.02979,0.02976,0.03008,0.03076,0.03145,0.03316,0.03575,0.03863,0.04314,0.05021,0.05607,0.06269,0.07103,0.07353,0.06963,0.06919,0.07468,0.07744,0.06806,0.06032,0.05305,0.04654,0.04341,0.04568,0.05466,0.0671,0.07488,0.07921,0.0766,0.07283,0.06931,0.06514,0.06935,0.08389,0.10123,0.12107,0.17581,0.28013,0.38436,0.45968,0.60599,0.6733,0.55068,0.35602,0.28656,0.34277,0.45544,0.57377,0.55374,0.44017,0.35037,0.36305,0.53452,0.87108,1.19864,1.52639,1.4128,0.7816,0.3186,0.16443,0.11064,0.08583,0.07091,0.06015,0.05236,0.04784,0.04494,0.04394,0.04396,0.04283,0.04145,0.04203,0.04491,0.05047,0.0597,0.07054,0.07513,0.06943,0.05927,0.06482,0.08834,0.12146,0.14571,0.13558,0.09944,0.07767,0.07555,0.07272,0.062,0.05048,0.0432,0.03989,0.03789,0.03695,0.03618,0.03581,0.03596,0.03581,0.03598,0.03604,0.03622,0.03568,0.03592,0.03618,0.03629,0.0357,0.03622,0.03705,0.03954,0.04242,0.0448,0.04262,0.04203,0.0479,0.05951,0.06634,0.05958,0.0483,0.05176,0.06,0.05639,0.04352,0.04146,0.03931,0.03937,0.03869,0.0382,0.03923,0.04076,0.04403,0.05415,0.06622,0.07438,0.07695,0.08271,0.10044,0.13299,0.15769,0.20891,0.32465,0.60804,0.36616,0.17272,0.11024,0.07852,0.06575,0.06036,0.06124,0.0619,0.06393,0.06189,0.0639,0.0728,0.07918,0.0734,0.06985,0.07072,0.06979,0.066,0.06633,0.06497,0.06424,0.06363,0.06827,0.06802,0.07111,0.08246,0.1133,0.0875,0.07205,0.06591,0.05975,0.05833,0.05745,0.05843,0.05888,0.06009,0.06181,0.06291,0.06351,0.06459,0.06504,0.06673,0.06823,0.0694,0.07159,0.07312,0.0751,0.07729,0.07949,0.08153,0.08402,0.08668,0.08999,0.09309,0.0956,0.09871,0.1023,0.10615,0.11008,0.11487,0.11987,0.12678,0.13418,0.14342,0.15239,0.1626,0.17317,0.18143,0.1903,0.22734,0.25164,0.24429,0.32932,0.28155,0.22248,0.22278,0.23069,0.24206,0.26148,0.28955,0.39305,0.40237,0.32548,0.32363,0.33042,0.34142,0.35018,0.3595,0.37066,0.38637,0.39886,0.41183,0.42682,0.44379,0.46173,0.48214,0.50347,0.53878,0.556,0.56991,0.58464,0.59192,0.60936,0.62944,0.65129,0.67347,0.69756,0.72395,0.75808,0.79345,0.80799];
let xValues=[];
let yValues=[];
var result1 = trap(xValues.slice(140, 180 + 1), yValues.slice(140, 180 + 1));
console.log("Approximated trap Area(560 to 520 ):",result1);
var result2 = trap(xValues.slice(230, 270 + 1), yValues.slice(230, 270 + 1));
console.log("Approximated trap Area(430 to 470):", result2);




/**------------------------------------------------------------------------
 *                           COMMANDS 
 *------------------------------------------------------------------------**/

var cmdInput = document.querySelector('.cmd');
var table = document.querySelector('table');

cmdInput.addEventListener('keyup', function(event) {
  if (event.key === 'Enter') {
    const inputValue = this.value.trim();
    if (inputValue !== '') {
      // Regular expression to match the command with its parameter
      const match = inputValue.match(/^=(\w+)\((\d+)\)$/);

      if (match) {
        const cmdName = match[1].toUpperCase(); // Extract the command name
        const cmdParam = parseInt(match[2]); // Extract the parameter as an integer
        const rows = table.querySelectorAll('tr'); // Declare rows variable here
        switch (cmdName) {
          case 'TABLE':
            if (!isNaN(cmdParam)) {
              constructtable(cmdParam); // Pass the parameter to the constructTable function
            } else {
              alert('Invalid parameter for SCAN command');
            }
            break;
          case 'CAUC':
          rows.forEach(function(row,index) {
            const cells = row.querySelectorAll('td');
            if (cells.length >= 5) {
              const rowIndex = index;
              const result = trap(xValues, yValues);
              cells[5].textContent = result;
              displayCMD(result, 'green', rowIndex);
            }
          });

          // Clear the input field after processing the command
          this.value = '';
            break;
          case 'PEAK':
          rows.forEach(function(row,index) {
            const cells = row.querySelectorAll('td');
            if (cells.length >= 5) {
              const rowIndex = index;
              cells[5].textContent = "peak";
              displayCMD("peak", 'green', rowIndex);
            }
          });

          // Clear the input field after processing the command
          this.value = '';
            break;
          case 'ADDCURVE':
                // Update the fifth cell in each row with the calculated result
                break;
          default:
            alert('Invalid command: ' + cmdName);
        }
      } else {
        alert('Invalid command format: ' + inputValue);
      }

      // Clear the input field after processing the command
      this.value = '';
    } else {
      alert('Please enter a command before pressing Enter.');
    }
  }
});

function displayCMD(message, color, num) {
  var messageBox = document.getElementById("CMDMB");
  var messageElement = document.createElement("p");
  messageElement.textContent = num +":" + message;
  messageElement.style.color = color; // Set the text color
  messageBox.appendChild(messageElement);
}

function getAllTextContent() {
  var messageBox = document.getElementById("CMDMB");
  var allTextContent = "";
  
  // Loop through all child elements of CMDMB
  for (var i = 0; i < messageBox.children.length; i++) {
    var child = messageBox.children[i];
    // Check if the child element is a <p> element
    if (child.tagName === 'P') {
      // Concatenate its textContent to the string
      allTextContent += child.textContent+"\n" ;
    }
  }
  
  // Return the string containing all textContent
 
  return allTextContent;

}



/**------------------------------------------------------------------------
 *                           SD Save Readings
 *------------------------------------------------------------------------**/
function savetosd(SampleID){
// Example usage:
var content = getAllTextContent();
console.log(content);
  var message={
  command:"sdsave",
  name:SampleID,
  content:content,
}
console.log(message);
websocket.send(JSON.stringify(message));
}


function showreadings(){
  var myList = document.getElementById("presetlist");
  var message = {
    showreadings: 'showreadings'
  };
  const flyoutMenu = document.getElementById('presets');
  const computedStyle = window.getComputedStyle(flyoutMenu);
  if (computedStyle.display === 'none') {
    websocket.send(JSON.stringify(message));
  }

  websocket.onmessage = function (event) {
  console.log(event.data);
  var myObj = JSON.parse(event.data);
    console.log(myObj);
    if (myObj.hasOwnProperty('readingsno')) {

      let i = myObj.readingsno;
      if (i == 0) {
     
        var nopresetsDiv = document.getElementById('nopresets');
        nopresetsDiv.innerHTML = 'No readings available';
      }


      else {
     
        var nopresetsDiv = document.getElementById('nopresets');
        nopresetsDiv.innerHTML = '';
        for (var j = myList.children.length - 1; j >= 0; j--) {
          var child = myList.children[j];
          console.log(child.id);
          // Check if the element has an id and it is not "nopresets"
          if (child.id !== 'nopresets' && child.id !== 'search') {
            myList.removeChild(child);
          }
        }

        for (i; i > 0; i--) {
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
            deletereading(myList, itemName, newItem);


            newItem.addEventListener("click", function () {
              console.log("Clicked on item: " + itemName);
              var message = {
                Dictionary:"readings",
                loadthis: itemName
              };
              websocket.send(JSON.stringify(message));

              websocket.onmessage = function (event) {
                var myObj = JSON.parse(event.data);
                console.log(myObj);
                if (myObj.hasOwnProperty('loadedReadings')) {
                  displayCMD(myObj.name,"red",i);
                  displayCMD(myObj.content,"green",i+1);

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
  





function deletereading(myList, names, newItem) {
  var deleteButton = document.createElement("div");
  deleteButton.textContent = "delete";
  deleteButton.classList.add("delete-button");
  deleteButton.addEventListener("click", function () {
    myList.removeChild(newItem);
    var message = {
      deletereading: 'deletereading',
      name: names,
    };
    websocket.send(JSON.stringify(message));
    showreadings();
  });
  // Append the delete button to the new list item
  newItem.appendChild(deleteButton);
}



