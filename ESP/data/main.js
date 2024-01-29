
/**========================================================================
 *                           Navbar
 *========================================================================**/
const menu = document.querySelector('.nav_menu');
const menubtn = document.querySelector('#open_menu_btn');
const closebtn = document.querySelector('#close_menu_btn');

menubtn.addEventListener('click', () => {
    menu.classList.add('show');
    closebtn.style.display = 'inline-block';
    menubtn.style.display = 'none';
});

const closeNav = () => {
    menu.classList.remove('show');
    closebtn.style.display = 'none';
    menubtn.style.display = 'inline-block';
};

closebtn.addEventListener('click', closeNav);

// Check screen size on page load and resize
window.addEventListener('load', handleScreenSize);
window.addEventListener('resize', handleScreenSize);

function handleScreenSize() {
    if (window.innerWidth > 962) {
        menubtn.style.display = 'none';
        closebtn.style.display = 'none';
    } else {
        menubtn.style.display = 'inline-block';
        closebtn.style.display = 'none';
    }
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
 *                           Bottombar Clock
 *========================================================================**/
function formatWithLeadingZero(number) {
    return number < 10 ? `0${number}` : number;
}

// Function to update date and time
function updateDateTime() {
    // Get the current date and time
    const now = new Date();

    // Extract hours, minutes, and seconds
    let hours = now.getHours();
    const minutes = formatWithLeadingZero(now.getMinutes());
    const seconds = formatWithLeadingZero(now.getSeconds());
    const amPm = hours >= 12 ? 'PM' : 'AM';

    // Convert to 12-hour format
    hours = hours % 12 || 12;

    // Display the date and time with seconds
    const dateTimeString = `${now.toDateString()} ${hours}:${minutes}:${seconds} ${amPm}`;
    document.getElementById('DateTime').textContent = dateTimeString;
}

// Update the date and time every second
setInterval(updateDateTime, 1000);

// Initial update
updateDateTime();

/*============================ END OF Clock ============================*/

 




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
      command: 'sd',
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

websocket.onmessage = function (event) {
  const data = JSON.parse(event.data);
  console.log(event.data);
  getElementById("content")=data;
}

  