document.getElementById('toggleButton').addEventListener('click', function() {
  var content = document.getElementById('fieldsetContent');
  var icon = this.querySelector('i');

  if (content.classList.contains('hidden')) {
      content.classList.remove('hidden');
      content.style.height = content.scrollHeight + "px";
      icon.className = 'fas fa-minus';
  } else {
      content.style.height = content.scrollHeight + "px";
      setTimeout(() => {
          content.style.height = 0;
      }, 10);
      icon.className = 'fas fa-plus';
      content.addEventListener('transitionend', function() {
          if (content.style.height === '0px') {
              content.classList.add('hidden');
          }
      }, { once: true });
  }
});


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
  updateWifiStutus('connected', 'green');
}

function onClose(event) {
  // in case connection down
  // try again after 2 sec
  updateWifiStutus('disconnected', 'red');
  console.log('Connection closed');
  setTimeout(initWebSocket, 20000);

}
function onMessage(event) {
  var myObj = JSON.parse(event.data);
  console.log(myObj);
  if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
    handleLogin(myObj);
  }

}
function toggleDarkMode() {
  document.body.classList.toggle('dark-mode');
}


/**========================================================================
 *                           Tabs control
 *========================================================================**/
function openTab(evt, Control) {
  var i, tabcontent, tablinks;

  // Hide all tab content
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }

  // Remove active class from all tab links
  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].classList.remove("active");
  }

  var currentTab = document.getElementById(Control);
  currentTab.style.display = "block";
  evt.currentTarget.classList.add("active");
  // Toggle the height of the tab container
  var tabContainer = document.getElementById("tab");
  tabContainer.classList.add("reduced-height");


}

/*============================ END OF Tabs ============================*/

/**========================================================================
 *                           STATE BAR
 *========================================================================**/
function updateWifiStutus(connectedStutus, color) {
  var wifi_stutus = document.getElementById('WifiStutus');
  wifi_stutus.textContent = connectedStutus;
  wifi_stutus.style.color = color;
}
// function toggleInteractiveElements() {
//   // Get all interactive elements
//   var interactiveElements = document.querySelectorAll('button, input, select');
//   // Loop through each element and toggle its disabled attribute
//   interactiveElements.forEach(function(element) {
//     element.disabled = !element.disabled;
//     // Add or remove 'disabled' class based on the disabled state
//     if (element.disabled) {
//       element.classList.add('disabled');
//     } else {
//       element.classList.remove('disabled');
//     }
//   });
// }

document.getElementById('sBarBtn').addEventListener('click', function () {

  const message = {
    command: 'StateBar',
    timeStamp: new Date().toISOString(),
  }
    ;
  websocket.send(JSON.stringify(message));



  // Set up the WebSocket onmessage event
  websocket.onmessage = function (event) {
    const data = JSON.parse(event.data);
    console.log(event.data); // for test
    const UV = data.UV;
    const VI = data.VI;
    // const WL = data.WL;
    document.getElementById('UVstateBar').textContent = UV;
    document.getElementById('VIstateBar').textContent = VI;
    // document.getElementById('WLstateBar').textContent = WL;
  }
});

/**========================================================================
 *                           SCAN T_T
 *========================================================================**/
// Initial chart setup
let PageIndecator;





function toggleVisibility() {
  var checkbox = document.getElementById("toggleCheckbox");
  var div = document.getElementById("MagicDiv");
  div.style.display = checkbox.checked ? "block" : "none";
}

let isScanning = false;
var intensityData = [];
var wavelengthData = [];
let chartScan;
let firstInit =0;
let chartData;
document.getElementById('chartType').addEventListener('click', function () {
  if (!validateInputs()) return;
  
let Numberofsamples =document.getElementById('numberofsamples').value;
document.getElementById('deleteBTN').click();
constructtable(Numberofsamples);
document.getElementById('myTable').scrollIntoView({ behavior: 'smooth' });
  
  let indicatorElement = document.getElementById('indecatorPage');
  if (firstInit) {
    chartScan.destroy();
    chartScan = null;
  }
  if (indicatorElement) {
    // PageIndecator = indicatorElement.textContent;
    PageIndecator = indicatorElement.value;
    console.log(PageIndecator); 
  }
  if (PageIndecator==='Wavelength') {
    const ctxScan = document.getElementById('chartScan').getContext('2d');
    createChart(ctxScan, 190, 1100, 'Wavelength (nm)', 'chartScan');
    }
    else if (PageIndecator==='Time') {
    const ctxScan = document.getElementById('chartScan').getContext('2d');
    createChart(ctxScan, 0, 1100, 'Time (s)', 'chartScanTime');
    
    }
    else if (PageIndecator==='Filter') {
    const ctxScan = document.getElementById('chartScan').getContext('2d');
    createChart(ctxScan, 0, 50, 'Filter (units)', 'chartScanFilter');
    }
    firstInit =1;

});


function createChart(ctx, xMin, xMax, xLabel, chartType) {
  const chartConfig = {
    type: 'line',
    data: chartData,
    options: {
      plugins: {
        crosshair: {
          tooltips: {
            enabled: false // Disable tooltips for the crosshair
          },
          sync: {
            enabled: true // Enable crosshair synchronization between multiple charts
          },
          zoom: {
            enabled: true // Enable crosshair zooming along the axis
          },
          line: {
            color: 'blue', // Crosshair line color
            width: 1 // Crosshair line width
          }
        },
      },
      scales: {
        x: {
          min: xMin,
          max: xMax,
          type: 'linear',
          position: 'bottom',
          title: {
            display: true,
            text: xLabel,
            color: 'black' // Change color of the x-axis label
          },
          ticks: {
            color: 'black' // Change color of x-axis ticks
          }
        },
        y: {
          type: 'linear',
          position: 'left',

          ticks: {
            color: 'black' // Change color of y-axis ticks
          }
        }
      },
      tooltips: {
        enabled: false
      },
      animation: {
        duration: 0
      },
      responsive: true, // Make the chart responsive
      maintainAspectRatio: true, // Maintain aspect ratio
      onHover: null // Disable the default onHover behavior
    }
  };
   // Set x-axis min and max based on chartType
   if (chartType === 'chartScan') {
    chartConfig.options.scales.x.min = xMin;
    chartConfig.options.scales.x.max = xMax;
  } else if (chartType === 'chartScanTime') {
    // Do not set x-axis min and max for Time chart
    chartConfig.options.scales.x.min = undefined;
    chartConfig.options.scales.x.max = undefined;
  } else if (chartType === 'chartScanFilter') {
    chartConfig.options.scales.x.min = xMin;
    chartConfig.options.scales.x.max = xMax;
  }
  /**========================================================================
   *                           Crouser - Never think to touch
   *========================================================================**/

  // Assign the chart to the appropriate global variable
  if (chartType === 'chartScan') {
    chartScan = new Chart(ctx, chartConfig);
  } else if (chartType === 'chartScanTime') {
    chartScan = new Chart(ctx, chartConfig);
    console.log("333");
  } else if (chartType === 'chartScanFilter') {
    chartScan = new Chart(ctx, chartConfig);
  }

  // Create a div dynamically
  const infoDiv = document.createElement('div');

  // Style the div
  infoDiv.style.position = 'absolute';
  infoDiv.style.background = 'rgba(255, 255, 255, 0.8)';
  infoDiv.style.padding = '5px';
  infoDiv.style.border = '1px solid #ccc';
  infoDiv.style.borderRadius = '5px';
  infoDiv.style.pointerEvents = 'none'; // To prevent the div from interfering with mouse events on underlying elements

  // Add the div to the body
  document.body.appendChild(infoDiv);

  // Add mousemove event listener to the canvas
  ctx.canvas.addEventListener('mousemove', function (event) {
    infoDiv.style.display = 'block';
    const canvasPosition = ctx.canvas.getBoundingClientRect();
    const mouseX = event.clientX - canvasPosition.left;
    const mouseY = event.clientY - canvasPosition.top;

    const xValue = chartType === 'chartScan' ? chartScan.scales['x'].getValueForPixel(mouseX) :
      chartType === 'chartScanTime' ? chartScan.scales['x'].getValueForPixel(mouseX) :
        chartScan.scales['x'].getValueForPixel(mouseX);

    const yValue = chartType === 'chartScan' ? chartScan.scales['y'].getValueForPixel(mouseY) :
      chartType === 'chartScanTime' ? chartScan.scales['y'].getValueForPixel(mouseY) :
        chartScan.scales['y'].getValueForPixel(mouseY);

    // Update the content of the div with x and y values
    infoDiv.innerHTML = `X: ${xValue.toFixed(2)}, Y: ${yValue.toFixed(2)}`;

    // Position the div near the mouse pointer
    infoDiv.style.left = `${event.clientX + 0}px`; // Adding 10px offset to the right
    infoDiv.style.top = `${event.clientY + 0}px`; // Adding 10px offset to the bottom
  });

  // Hide the div when the mouse leaves the canvas
  ctx.canvas.addEventListener('mouseleave', function () {
    infoDiv.style.display = 'none';
  });
}


/**========================================================================
 *                           Chart Funcations
 *========================================================================**/


function addCurve(xData, yData, color, curveName, fillCurve = false, drawMode = 'curve') {
  // Check if the curve already exists
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);

  // If the curve exists, update its data
  if (existingCurveIndex !== -1) {
    chartScan.data.datasets[existingCurveIndex].data = drawMode === 'curve' ?
      xData.map((x, index) => ({ x: x, y: yData[index] })) : // Draw curve
      xData.map((x, index) => ({ x: x, y: yData[index], showLine: false })); // Draw separate points

    chartScan.data.datasets[existingCurveIndex].borderColor = color;
    chartScan.data.datasets[existingCurveIndex].backgroundColor = fillCurve ? 'rgba(255, 0, 0, 0.3)' : undefined;
    chartScan.data.datasets[existingCurveIndex].showLine = drawMode !== 'points'; // Don't connect points if drawing separate points
  } else { // If the curve does't exist, add it

    var curveData = drawMode === 'curve' ?
      xData.map((x, index) => ({ x: x, y: yData[index] })) : // Draw curve
      xData.map((x, index) => ({ x: x, y: yData[index], showLine: false })); // Draw separate points

    var dataset = {
      label: curveName,
      data: curveData,
      borderColor: color,
      borderWidth: 2,
      pointRadius: drawMode === 'points' ? 5 : 0, // Set point radius if drawing points
      lineTension: drawMode === 'points' ? 0 : 0.4, // Set line tension if drawing points
      showLine: drawMode !== 'points' // Don't connect points if drawing separate points

    };

    if (fillCurve) {
      dataset.fill = 'origin';
      dataset.backgroundColor = 'rgba(255, 0, 0, 0.3)';
    }

    chartScan.data.datasets.push(dataset);
    // add to select 
    const selectElement = document.getElementById('chart-select');
    const option = document.createElement('option');
    option.value = curveName;
    option.text = curveName;
    selectElement.appendChild(option);

  }

  chartScan.update(); // Update the chart

}

/**------------------------------------------------------------------------
 *                           COLOR CHANGE
 *------------------------------------------------------------------------**/
// Function to change the color of a curve
function changeCurveColor(curveName, color) {
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);
  chartScan.data.datasets[existingCurveIndex].borderColor = color;
  chartScan.update(); // test name of chart scanChart
}

function changeColor() {
  var curveName = document.getElementById('chart-select').value;
  var color = document.getElementById('color-picker').value;
  changeCurveColor(curveName, color);
}

function hideCurve(curveName) {
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);
  if (existingCurveIndex !== -1) {
    const dataset = chartScan.data.datasets[existingCurveIndex];
    dataset.hidden = !dataset.hidden;
    chartScan.update();
  }
}
function hideSelectedCurve() {
  var curveName = document.getElementById('chart-select').value;
  hideCurve(curveName);
}
function deleteCurve(curveName) {
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);
  if (existingCurveIndex !== -1) {
    chartScan.data.datasets.splice(existingCurveIndex, 1);
    chartScan.update();
  }

  const selectElement = document.getElementById('chart-select');

  // Iterate through all options
  for (let i = 0; i < selectElement.options.length; i++) {
    if (selectElement.options[i].value === curveName) {
      selectElement.remove(i);
      break;
    }
  }


}
function deleteSelectedCurve() {
  var curveName = document.getElementById('chart-select').value;
  deleteCurve(curveName);
}

// function changeColor() {
//   var rIndex, table = document.getElementById('table');
//   checkboxes = document.getElementsByName("check-tab1");
//   for (var i = 1; i < table.rows.length; i++) {
//     table.rows[i].onclick = function () {
//       if (this.cells[7].querySelector('input').checked) {
//         rIndex = this.rowIndex;
//         var color = this.cells[6].querySelector('select').value;
//         changeCurveColor(rIndex - 1, color);
//       }
//     }
//   }
// }


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
  const stepInput = parseFloat(document.getElementById('step').value);

  if (isNaN(startInput) || isNaN(stopInput) || startInput < 190 || stopInput > 1200) {
    alert('Start and Stop values must be between 190 and 1200');
    return false;
  }

  if (!isValidDecimalDigits(startInput, 1) || !isValidDecimalDigits(stopInput, 1) ||!isValidDecimalDigits(stepInput, 1) ) {
    alert('Number of digits after the decimal point must not exceed 1');
    return false;
  }

  if (startInput > stopInput) {
    alert('Start value must be smaller than Stop value');
    return false;
  }

  return true;
}

function startScan(btn) {
  document.getElementById('chartandsettings').scrollIntoView({ behavior: 'smooth' });
  var row = btn.parentNode.parentNode; // Get the parent row of the button
  var index = row.rowIndex;  // Get the row index
  var SampleID = row.cells[2].innerHTML;
  var SampleDecribe = row.cells[3].innerHTML;
  // Regular expression to check for special characters
  var specialCharPattern = /[^a-zA-Z0-9 ]/;

  if (SampleID.trim() !== "") {
    if (specialCharPattern.test(SampleID)) {
      alert("Don't use special characters or data will be lost");
      return; // Exit the function if special characters are found
    }
  }
  console.log("index0:" + index);
  console.log("sampleID0:" + SampleID);

  if (!isScanning) {
    if (!validateInputs()) return;
    document.getElementById("CMDMB").innerHTML = '';
    btn.innerHTML = '<i class="fa-solid fa-stop"></i>';
    disableInputs();
    isScanning = true;
    scan(index, SampleID, SampleDecribe, btn); // send index to display message with index
  } else {
    stopScan(btn, index);
  }
}

function stopScan(btn, index) {
  // Add your stop scan logic here
  isScanning = false;
  if (btn && index) {
    btn.innerHTML = '<i class="fa-solid fa-play"></i>';
    changeState(index, 0, btn);
  }
  enableInputs();
  const message = {
    command: 'ScanStop',
    timeStamp: new Date().toISOString(),
  };
  console.log(message);
  websocket.send(JSON.stringify(message));
  console.log('Function is stopped!');
  animation.classList.add('hidden');
  animation.classList.remove('visible');
  playSound('Stop-sound'); // Play sound when function is done
}



function toggleInputs(disabled) {
  const inputs = document.querySelectorAll('#ScanVsWL input, #ScanVsWL select');
  const buttons = document.querySelectorAll('#ScanVsWL button');
  const NoDisable = document.getElementById('StopScanButton');
  inputs.forEach(input => (input.disabled = disabled)); //disable all inputs

  //disable(toggle) all button execpt the one that is used for stop
  buttons.forEach(button => {
    const icon = button.querySelector('i');
    if (icon && icon.classList.contains('fa-stop')) {
      button.disabled = false; // Enable the button with the stop icon
    } else {
      button.disabled = disabled;
    }
  });

  //sync the stop button from div to that from table
  NoDisable.addEventListener('click', function () {
    buttons.forEach(button => {
      const icon = button.querySelector('i');
      if (icon && icon.classList.contains('fa-stop')) {
        button.innerHTML = '<i class="fa-solid fa-play"></i>'
      }
    });
  })
  NoDisable.disabled = false;
}


function disableInputs() {
  toggleInputs(true);
}

function enableInputs() {
  toggleInputs(false);
}




  
function scan(index, SampleID, SampleDecribe, btn) {
  let x = []; // wavelength
  let y = []; // intensity
  
  let absorbtionAry = [];
  let transmissionAry = [];
  let AbsorptionAdjusted = [] ;
  let TransmissionAdjusted = [] ;
 
  let temp = document.getElementById('DateTime').textContent;
  var time = temp.replaceAll(":", " ");  //because file name can't contain :
  var time = time.replaceAll(",", " ");  //because file name can't contain ,
  const startInput = parseFloat(document.getElementById('start').value);
  const stopInput = parseFloat(document.getElementById('stop').value);
  const stepInput = parseFloat(document.getElementById('step').value);
  const modeInput = document.getElementById('mySelect').value;
  const lampmode = document.getElementById('LampsOFF').value;
  const timeInterval = parseFloat(document.getElementById('initTime').value);
  const specificWL = parseFloat(document.getElementById('specificWL').value);
  var colorSelectArr = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink', 'gray', 'black'];    // change color according to index
  runSpectrophotometer();             //play animation

let timer=0;
  function processScanData(data) {
    const currentTime = data.currentTime;
    let scanning, progress ; 
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    const transmission = Math.log10(intensitySample / intensityReference);
    const absorption = Math.log10(intensityReference / intensitySample);
    let wavelength;
    if (PageIndecator === "Wavelength") {
      wavelength = data.wavelength;
      scanning = data.scanning; //check if the scan end or not
      progress = data.current; //represent the progress to display the current progress
      x.push(wavelength);  
      changeState(index, progress, btn);
    }
    else if (PageIndecator === "Time") {

      x.push(timer);
      timer += 1;
    }




    // Update the chart data
    
    
    absorbtionAry.push(absorption);
    transmissionAry.push(transmission);



    if (modeInput == "absorption") {
      y.push(absorption);
    }
    else {
      y.push(transmission);
    }


    // Extract globalXref, globalAbsorptionref, globalTransmissionref for addCurve function auto_zero
    const rangeKey = `range_${stepInput}`; // to store the ref data on local storage
    const storedData = JSON.parse(localStorage.getItem(rangeKey)) || [];
    if (storedData.length > 0 && AutoZeroFlag == true) {
      globalXref = storedData.map(item => item.x);
      globalAbsorptionref = storedData.map(item => item.absorption);
      globalTransmissionref = storedData.map(item => item.transmission);
    }
    if (index == 'autozero') {
      document.getElementById('autozerotoggle').innerHTML = '<i class="fa-solid fa-toggle-on"></i>';
      const newData = {
        x: wavelength,
        absorption: absorption,
        transmission: transmission,
      }

      // Append new data to the existing data
      storedData.push(newData);
      // Sort the array in descending order based on the x value
      storedData.sort((a, b) => b.x - a.x);
      // Store the updated data in local storage
      localStorage.setItem(rangeKey, JSON.stringify(storedData));
      disableInputs();
      if (progress == 100 && index == 'autozero') {
        document.getElementById('start').value = globalStart;
        document.getElementById('stop').value = globalStop;
        console.log(AutoZeroResponse);
        if (AutoZeroResponse == "not equal and we need to perform zero method twice") {
          console.log(globalXref[globalXref.length - 1] - stepInput);
          document.getElementById('stop').value = globalXref[globalXref.length - 1] - stepInput;
          toggleLoginContainer('NextSample');
          if (AutoZeroResponse) {
            document.getElementById('AutoZeroMessage').textContent = AutoZeroResponse;

          }
          AutoZeroResponse = '';

        }
        enableInputs();
      }

    }

    if (index !== 'autozero') {
      //console.log(globalAbsorptionref.length);
      if(globalAbsorptionref.length>0&& AutoZeroFlag ==true){
        const index = absorbtionAry.length - 1; // Index for the new value in y
        const correspondingX = globalAbsorptionref[index % absorbtionAry.length]; // Get the corresponding x value, considering wrap-around using modulo
        const correspondingXt = globalTransmissionref[index % transmissionAry.length]; // Get the corresponding x value, considering wrap-around using modulo
        
        // Calculate the new z value
        const zValue = absorbtionAry[absorbtionAry.length-1] - correspondingX;
        const zValueT = transmissionAry[transmissionAry.length-1] - correspondingXt;
        
        // Push the new z value to z
        AbsorptionAdjusted.push(zValue);
        TransmissionAdjusted.push(zValueT);
        //  AbsorptionAdjusted = absorbtionAry.map((y, index) => y - globalAbsorptionref[index]);
        //  TransmissionAdjusted = transmissionAry.map((y, index) => y - globalTransmissionref[index]);
         addCurve(x, AbsorptionAdjusted, colorSelectArr[index+1], 'Autozeroed');
      }
     
      const res = currentTime + ": " + "|| Wavelength: " + wavelength + " ||Absorption: " + absorption + " ||Transmission: " + transmission;
      
      displayCMD(res, 'green', index);
      if (modeInput == "absorption") {
        addCurve(x, y, colorSelectArr[index], SampleID);
      }
      else {
        addCurve(x, y, colorSelectArr[index], SampleID);
      }
      StoreData(SampleID,  x, y);
    }

    // Play sound when function is done
    if (progress == 100) {
      playSound('completion-sound');
      animation.classList.add('hidden');
      animation.classList.remove('visible');
      sendCsvToESP32(SampleID,time,SampleDecribe,x,absorbtionAry,transmissionAry);
    }
    //  if(wavelength===stopInput){
    //   console.log("final wavelength is reached");
    //   savetosd(SampleID); 
    //  }

  }

  let isFirstTime = true;

  function continueScanning(wavelength) {
    if (isFirstTime) {
      if (PageIndecator === "Wavelength" ||index == 'autozero') {
        const message = {
          command: 'scan',
          startInput: startInput,
          stopInput: stopInput,
          stepInput: stepInput,
          lampmode: lampmode,
          timeStamp: new Date().toISOString()
          // modeInput: modeInput
        };
        websocket.send(JSON.stringify(message));
   
      }

      else if (PageIndecator === "Time") {
        const message = {
          command: 'scan-time',
          timeInterval: timeInterval,
          specificWL: specificWL,
          timeStamp: new Date().toISOString()
          // modeInput: modeInput
        };
        websocket.send(JSON.stringify(message));
   
      }

      isFirstTime = false;
    }
    else if (wavelength <= stopInput && isScanning) {
      // Continue scanning
    }
    else if(isScanning){
      // continue scanning
    }
    else {
      // Scanning is complete

      return;
    }

  }


  // Set up the WebSocket onmessage event
  websocket.onmessage = function (event) {
    let buffer = event.data.split('\n');
   // Process each part of the buffer
   buffer.forEach(dataBuffer => {
    // Trim any extraneous whitespace and ensure it's not empty
    if (dataBuffer.trim()) {
        try {
            // Parse the JSON string
            const data = JSON.parse(dataBuffer);
            
            // For testing purposes, log the parsed data
            console.log(data);

            // Process the JSON data
            processScanData(data);
        } catch (error) {
            console.error('Failed to parse JSON:', error);
        }
    }
}); 
    // Continue scanning for the next wavelength after a delay
    setTimeout(() => {
      continueScanning(data.wavelength + stepInput);
    }, 3000);
  };

  // Start the scanning process
  continueScanning(startInput);

}


function runSpectrophotometer() {
  var animation = document.getElementById('animation');
  animation.classList.add('visible');
  animation.classList.remove('hidden');
}


function playSound(id) {
  var audio = document.getElementById(id);
  audio.play();
}

// Function to create and send CSV file
function sendCsvToESP32(SampleID,time,SampleDecribe,xArray,absorptionArray,transmissionArray) {
  let csvContent=`${SampleID},${SampleDecribe},${time}\n`;
  csvContent += "Wavelength,Absorption,Transmission\n";
  csvContent += `${xArray[i]},${absorptionArray[i]},${transmissionArray[i]}\n`;
  for (let i = 0; i < xArray.length; i++) {
      csvContent += `${xArray[i]},${absorptionArray[i]},${transmissionArray[i]}\n`;
  }
  let blob = new Blob([csvContent], { type: 'text/csv' });
  let formData = new FormData();
  formData.append('file', blob, '/readings/'+SampleID+ ' === '+time+'.csv');

  fetch('http://192.168.4.1/savetosd', {
      method: 'POST',
      body: formData
  })
  .then(response => response.text())
  .then(data => console.log(data))
  .catch(error => console.error('Error:', error));
}

/*====================================preset/readings section====================================*/

// function to display the preset name container 
function savepreset() {
  const flyoutMenu = document.getElementById('presetname');
  flyoutMenu.classList.toggle('active');
}

var myList = document.getElementById("presetlist");
function addtolist() {
  var itemName = document.getElementById("prestinput").value;
  
  // Regular expression to check for special characters
  var specialCharPattern = /[^a-zA-Z0-9 ]/;

  if (itemName.trim() !== "") {
    if (specialCharPattern.test(itemName)) {
      alert("Don't use special characters or data will be lost");
      return; // Exit the function if special characters are found
    }
  }

  if (itemName.trim() !== "") {
    let startInput = parseFloat(document.getElementById('start').value);
    let stopInput = parseFloat(document.getElementById('stop').value);
    let stepInput = parseFloat(document.getElementById('step').value);
    let initTimeInput = parseFloat(document.getElementById('initTime').value);
    let modeInput = document.getElementById('mySelect').value;
    let temp = document.getElementById('DateTime').textContent;
    var time = temp.replaceAll(":", " "); //file name can't contain : or ,
    time = time.replaceAll(",", " ");
    
    var csvContent = `name,time,start,stop,step,inittime,mode\n${itemName},${time},${startInput},${stopInput},${stepInput},${initTimeInput},${modeInput}`;
    let blob = new Blob([csvContent], { type: 'text/csv' });
    let formData = new FormData();
    formData.append('file', blob, '/presets/'+itemName +' === '+time +'.csv');
    
    fetch('http://192.168.4.1/savetosd', {
      method: 'POST',
      body: formData
    })
    .then(response => response.text())
    .then(data => console.log(data))
    .catch(error => console.error('Error:', error));
  } else {
    document.getElementById('nameexist').innerHTML = 'Preset name required';
  }
}


function fetchPreset(filename) {
  fetch(`http://192.168.4.1/download?filename=${filename}`)
    .then(response => response.text())
    .then(data => processPresetData(data))
    .catch(error => console.error('Error:', error));
}

function processPresetData(data) {
  var rows = data.split('\n')[1].split(',');
  var startValue = parseFloat(rows[2]);
  var stopValue = parseFloat(rows[3]);
  var stepValue = parseFloat(rows[4]);
  var initTimeValue = parseFloat(rows[5]);
  document.getElementById('start').value = isNaN(startValue) ? '' : startValue;
  document.getElementById('stop').value = isNaN(stopValue) ? '' : stopValue;
  document.getElementById('step').value = isNaN(stepValue) ? '' : stepValue;
  document.getElementById('initTime').value = isNaN(initTimeValue) ? '' : initTimeValue;
  selectMode(rows[6].trim());
}

//function to select transmission or absorbtion when laod an preset from sd
function selectMode(mode) {
  var selectElement = document.getElementById("mySelect");
  var modeIndex = Array.from(selectElement.options).findIndex(option => option.value === mode);
  if (modeIndex !== -1) {
    selectElement.selectedIndex = modeIndex;
  } else {
    console.error("Mode not found: " + mode);
  }
}

//function to delete item from sd and  the preset list
function deleteItem(myList, names, newItem, action) {
  var deleteButton = document.createElement("div");
  deleteButton.innerHTML = '<i class="fa-solid fa-trash-can"></i>';
  deleteButton.classList.add("delete-button");
  deleteButton.addEventListener("click", function (event) {
    event.stopPropagation(); // Stop event propagation to prevent parent element click event
    myList.removeChild(newItem);
    var message = {
      [action]: action,
      name: names,
      timeStamp: new Date().toISOString(),
    };
    websocket.send(JSON.stringify(message));
    var type = action.replaceAll("delete", "")
    showItems(type);
  });
  // Append the delete button to the new list item
  newItem.appendChild(deleteButton);
}


// a function that dynamically show the files in sd card into web list
function showItems(type) {
  const flyoutMenu = document.getElementById('presets');
  const computedStyle = window.getComputedStyle(flyoutMenu);
  if (computedStyle.display === 'none') {
      for (var j = myList.children.length - 1; j >= 0; j--) {
          var child = myList.children[j];
          if (child.id !== 'nopresets' && child.id !== 'search') {
              myList.removeChild(child);
          }
      }
      fetchFileNames(type).then(fileNames => {
        var nopresetsDiv = document.getElementById('nopresets');
        console.log(fileNames.length);
        console.log(fileNames[0]);
        
        if (fileNames.length == 0 || fileNames[0]=='') {
            nopresetsDiv.innerHTML = `No ${type} available`;
        } else {
            nopresetsDiv.innerHTML = '';
            fileNames.forEach(itemName => {
                var newItem = document.createElement("li");
                var textSpan = document.createElement("span");
                let temp;
                temp=itemName.replace("/readings/","");
                temp=temp.replace("/presets/","");
                temp=temp.replace(".csv","");
                
                var textNode = document.createTextNode(temp);
                textSpan.appendChild(textNode);
                newItem.appendChild(textSpan);
                myList.insertBefore(newItem, myList.lastChild);
                deleteItem(myList, itemName, newItem, "delete" + type);
                newItem.addEventListener("click", function () {
                    console.log("Clicked on item: " + itemName);
                    loadItem(type, itemName);
                });
            });
        }
        openlist();
    }).catch(error => {
        console.error('Error fetching file names:', error);
    });
  }

  
}

async function fetchFileNames(type) {
  let response;
  if(type == 'presets'){
    response = await fetch(`http://192.168.4.1/download?filename=/presetsDB.txt`);
  }
  else {
    response = await fetch(`http://192.168.4.1/download?filename=/ReadingsDB.txt`);
  }
  if (!response.ok) {
      throw new Error('Network response was not ok');
  }
  const text = await response.text();
  return text.trim().split('\n');
}

// a function that shows the presets or readings list
function openlist() {
  const flyoutMenu = document.getElementById('presets');
  flyoutMenu.classList.toggle('active');
}

// a function that shows the presets or readings items when i click one of them
function loadItem(dictionary, itemName) {
  if (dictionary === "presets") {//it is a preset
 fetchPreset(itemName) 
}
// Handle specific actions based on dictionary
if (dictionary === "readings") {
  fetchAndParseCSV(itemName);
}
 
}
var samplename = "";
async function fetchAndParseCSV(filename) {
  try {
    const response = await fetch(`http://192.168.4.1/download?filename=${filename}`);
    if (!response.ok) {
        throw new Error('Network response was not ok');
    }

      const csvText = await response.text();
      console.log("CSV Content:\n", csvText);

      // Parse CSV content
      const lines = csvText.trim().split('\n');
      const name = lines[0].split(',');
      const headers = lines[1].split(',');


      const xArray = [];
      const absorptionArray = [];
      const transmissionArray = [];

      for (let i = 1; i < lines.length; i++) {
          const values = lines[i].split(',');
          xArray.push(parseFloat(values[0]));
          absorptionArray.push(parseFloat(values[1]));
          transmissionArray.push(parseFloat(values[2]));
      }
          displayCMD(csvText, "black", "SD");
          addCurve(xArray, absorptionArray, "blue", name[0]);

      console.log('xArray:', xArray);
      console.log('absorptionArray:', absorptionArray);
      console.log('transmissionArray:', transmissionArray);
  } catch (error) {
      console.error('Error fetching or parsing CSV:', error);
  }
}




document.addEventListener('click', function (event) {
  const flyoutBtn = document.getElementById('loadpreset');
  const flyoutMenu = document.getElementById('presets');
  const raedingsbutton = document.getElementById('loadreadings');


  if (event.target !== flyoutBtn && event.target !== raedingsbutton && event.target !== flyoutMenu && !flyoutMenu.contains(event.target)) {
    // Click outside the button and the flyout menu, close the flyout menu
    flyoutMenu.classList.remove('active');
  }
});


const input = document.getElementById("search");
input.addEventListener('input', filter);
function filter() {
  var myList = document.getElementById("presetlist");
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












setTimeout(showfoot, 1000); //autohide foot in 1sec

document.getElementById('hidefoot').addEventListener('click', showfoot);

function showfoot() {
  var but = document.getElementById('hidefoot');
  var foot = document.getElementById('hidethis');
  var footer = document.getElementById('sticky');

  foot.classList.toggle('inactive');

  if (foot.classList.contains('inactive')) {
    but.innerHTML = '<i class="fas fa-arrow-up-short-wide"></i>';
    footer.style.backgroundColor = 'transparent';
  } else {
    but.innerHTML = '<i class="fas fa-arrow-down-short-wide"></i>';
    footer.style.backgroundColor = '#2d2e33';
  }
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
      timeStamp: new Date().toISOString(),
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

function constructtable(num) {
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
    cell2.innerHTML = "";
    cell3.innerHTML = "Name " + i;
    cell4.innerHTML = "Description " + i;
    cell5.innerHTML = "<button onclick='startScan(this)'><i class='fa-solid fa-play'></i></button> ";
    cell6.innerHTML = "Nabil";

    cell3.contentEditable = "true";
    cell4.contentEditable = "true";
    // Add event listener to the newly created 'cmd' input
    var cmdInput = cell6.querySelector('.cmd');

  }
}
let AutoZeroResponse;
let AutoZeroFlag = false;
function DoAutoZero (){
  if (!validateInputs()) return;
  
  let toggle = document.getElementById('autozerotoggle');
  if (toggle.innerHTML == '<i class="fa-solid fa-toggle-off"></i>'){
    AutoZeroFlag = true ;
    AutoZeroResponse = AutoZero(); //check the range if there is auto zero for it
    console.log(AutoZeroResponse);
  
    if (AutoZeroResponse == "not equal and we need to perform zero method" || AutoZeroResponse == "No Auto zero data for this range do you want to perform auto zero ?" || AutoZeroResponse == "not equal and we need to perform zero method twice") {
      toggleLoginContainer('NextSample');
      document.getElementById('AutoZeroMessage').textContent = AutoZeroResponse;
    }
    else{
      document.getElementById('autozerotoggle').innerHTML = '<i class="fa-solid fa-toggle-on"></i>';
    }
  }
  else{
    toggle.innerHTML = '<i class="fa-solid fa-toggle-off"></i>'
    AutoZeroFlag = false;
  }
  
}




// remove all rows
document.getElementById('deleteBTN').addEventListener('click', function () {
  colorindex = 0;
  var table = document.getElementById("myTable");
  var mb = document.getElementById("CMDMB");
  mb.textContent = '';
  var rowCount = table.rows.length;
  for (var i = rowCount - 1; i > 0; i--) {
    table.deleteRow(i);
  }
  var headerCells = table.rows[0].cells;
  for (var i = headerCells.length - 1; i > 5; i--) {
    table.rows[0].deleteCell(i);
  }
   removeAllCurves();

});


/**------------------------------------------------------------------------
 *                           AREA under the curve 
 *------------------------------------------------------------------------**/


function changeState(rowIndex, progress, btn) {
  var table = document.getElementById("myTable");
  var cell = table.rows[rowIndex].cells[1]; // Index 1 corresponds to the State cell

  var stateSpan = cell.querySelector("p");
  
  // If the state span doesn't exist, create it
  if (!stateSpan) {
    stateSpan = document.createElement("p");
    cell.appendChild(stateSpan);
  }

  stateSpan.innerHTML = progress.toFixed(0).trim() + " %";
  stateSpan.style.color = "rgb(0, 35, 151)";
  if (progress == 100) {
    stateSpan.innerHTML = "✓"; // Displaying the check mark symbol when progress is 100
    stateSpan.style.color = "green";
    // toggleInteractiveElements();  
    btn.innerHTML = '<i class="fa-solid fa-play"></i>';
    enableInputs();
    isScanning = false;
    // toggleLoginContainer('NextSample');

  }
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
/**========================================================================
 *                           Global Data
 *========================================================================**/

let data = {};

let xtest = [700, 699, 698, 697, 696, 695, 694, 693, 692, 691, 690, 689, 688, 687, 686, 685, 684, 683, 682, 681, 680, 679, 678, 677, 676, 675, 674, 673, 672, 671, 670, 669, 668, 667, 666, 665, 664, 663, 662, 661, 660, 659, 658, 657, 656, 655, 654, 653, 652, 651, 650, 649, 648, 647, 646, 645, 644, 643, 642, 641, 640, 639, 638, 637, 636, 635, 634, 633, 632, 631, 630, 629, 628, 627, 626, 625, 624, 623, 622, 621, 620, 619, 618, 617, 616, 615, 614, 613, 612, 611, 610, 609, 608, 607, 606, 605, 604, 603, 602, 601, 600, 599, 598, 597, 596, 595, 594, 593, 592, 591, 590, 589, 588, 587, 586, 585, 584, 583, 582, 581, 580, 579, 578, 577, 576, 575, 574, 573, 572, 571, 570, 569, 568, 567, 566, 565, 564, 563, 562, 561, 560, 559, 558, 557, 556, 555, 554, 553, 552, 551, 550, 549, 548, 547, 546, 545, 544, 543, 542, 541, 540, 539, 538, 537, 536, 535, 534, 533, 532, 531, 530, 529, 528, 527, 526, 525, 524, 523, 522, 521, 520, 519, 518, 517, 516, 515, 514, 513, 512, 511, 510, 509, 508, 507, 506, 505, 504, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494, 493, 492, 491, 490, 489, 488, 487, 486, 485, 484, 483, 482, 481, 480, 479, 478, 477, 476, 475, 474, 473, 472, 471, 470, 469, 468, 467, 466, 465, 464, 463, 462, 461, 460, 459, 458, 457, 456, 455, 454, 453, 452, 451, 450, 449, 448, 447, 446, 445, 444, 443, 442, 441, 440, 439, 438, 437, 436, 435, 434, 433, 432, 431, 430, 429, 428, 427, 426, 425, 424, 423, 422, 421, 420, 419, 418, 417, 416, 415, 414, 413, 412, 411, 410, 409, 408, 407, 406, 405, 404, 403, 402, 401, 400, 399, 398, 397, 396, 395, 394, 393, 392, 391, 390, 389, 388, 387, 386, 385, 384, 383, 382, 381, 380, 379, 378, 377, 376, 375, 374, 373, 372, 371, 370, 369, 368, 367, 366, 365, 364, 363, 362, 361, 360, 359, 358, 357, 356, 355, 354, 353, 352, 351, 350, 349, 348, 347, 346, 345, 344, 343, 342, 341, 340, 339, 338, 337, 336, 335, 334, 333, 332, 331, 330, 329, 328, 327, 326, 325, 324, 323, 322, 321, 320, 319, 318, 317, 316, 315, 314, 313, 312, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 300, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250];
let ytest = [0.02234, 0.02244, 0.02247, 0.0225, 0.02263, 0.02253, 0.02244, 0.0226, 0.02237, 0.02265, 0.02274, 0.02255, 0.02267, 0.02261, 0.02275, 0.02288, 0.0227, 0.02303, 0.02294, 0.02304, 0.02313, 0.02327, 0.02347, 0.02343, 0.02344, 0.0238, 0.02398, 0.02453, 0.02492, 0.02623, 0.02783, 0.03071, 0.03561, 0.04003, 0.04439, 0.04769, 0.0513, 0.05325, 0.05321, 0.05159, 0.0496, 0.04809, 0.04671, 0.0453, 0.04582, 0.0478, 0.05092, 0.05624, 0.06206, 0.06895, 0.07599, 0.0784, 0.0761, 0.07425, 0.07339, 0.07221, 0.07159, 0.07205, 0.07575, 0.08285, 0.09243, 0.10083, 0.10491, 0.10434, 0.10021, 0.09375, 0.08347, 0.07018, 0.05825, 0.04889, 0.04257, 0.03817, 0.03515, 0.03327, 0.03156, 0.03022, 0.02928, 0.02843, 0.02766, 0.02734, 0.02677, 0.02645, 0.02593, 0.02577, 0.02554, 0.02531, 0.02499, 0.02512, 0.02501, 0.02502, 0.02495, 0.02487, 0.02491, 0.02478, 0.02474, 0.0246, 0.02459, 0.02465, 0.02468, 0.02447, 0.02458, 0.02462, 0.02444, 0.02467, 0.02465, 0.02453, 0.02456, 0.02434, 0.02422, 0.02416, 0.02411, 0.02404, 0.02443, 0.02433, 0.02462, 0.02449, 0.02469, 0.02506, 0.02544, 0.02562, 0.0258, 0.0264, 0.02652, 0.02689, 0.02722, 0.02761, 0.02779, 0.02785, 0.02834, 0.02857, 0.02848, 0.02872, 0.02872, 0.02919, 0.02888, 0.02897, 0.02937, 0.0294, 0.0294, 0.02949, 0.02944, 0.0295, 0.03008, 0.03064, 0.0324, 0.03581, 0.04131, 0.04587, 0.04853, 0.05166, 0.05632, 0.06351, 0.07405, 0.07908, 0.07995, 0.07867, 0.07831, 0.08163, 0.09221, 0.10707, 0.12825, 0.16216, 0.19453, 0.20988, 0.21171, 0.18648, 0.14277, 0.1036, 0.0757, 0.06007, 0.0502, 0.04474, 0.04053, 0.03814, 0.03615, 0.0346, 0.03343, 0.03253, 0.03177, 0.03132, 0.03083, 0.03043, 0.03066, 0.03012, 0.03042, 0.03038, 0.03015, 0.03036, 0.03006, 0.0303, 0.03097, 0.03068, 0.03072, 0.03007, 0.03003, 0.02999, 0.03013, 0.0297, 0.02968, 0.02979, 0.02976, 0.03008, 0.03076, 0.03145, 0.03316, 0.03575, 0.03863, 0.04314, 0.05021, 0.05607, 0.06269, 0.07103, 0.07353, 0.06963, 0.06919, 0.07468, 0.07744, 0.06806, 0.06032, 0.05305, 0.04654, 0.04341, 0.04568, 0.05466, 0.0671, 0.07488, 0.07921, 0.0766, 0.07283, 0.06931, 0.06514, 0.06935, 0.08389, 0.10123, 0.12107, 0.17581, 0.28013, 0.38436, 0.45968, 0.60599, 0.6733, 0.55068, 0.35602, 0.28656, 0.34277, 0.45544, 0.57377, 0.55374, 0.44017, 0.35037, 0.36305, 0.53452, 0.87108, 1.19864, 1.52639, 1.4128, 0.7816, 0.3186, 0.16443, 0.11064, 0.08583, 0.07091, 0.06015, 0.05236, 0.04784, 0.04494, 0.04394, 0.04396, 0.04283, 0.04145, 0.04203, 0.04491, 0.05047, 0.0597, 0.07054, 0.07513, 0.06943, 0.05927, 0.06482, 0.08834, 0.12146, 0.14571, 0.13558, 0.09944, 0.07767, 0.07555, 0.07272, 0.062, 0.05048, 0.0432, 0.03989, 0.03789, 0.03695, 0.03618, 0.03581, 0.03596, 0.03581, 0.03598, 0.03604, 0.03622, 0.03568, 0.03592, 0.03618, 0.03629, 0.0357, 0.03622, 0.03705, 0.03954, 0.04242, 0.0448, 0.04262, 0.04203, 0.0479, 0.05951, 0.06634, 0.05958, 0.0483, 0.05176, 0.06, 0.05639, 0.04352, 0.04146, 0.03931, 0.03937, 0.03869, 0.0382, 0.03923, 0.04076, 0.04403, 0.05415, 0.06622, 0.07438, 0.07695, 0.08271, 0.10044, 0.13299, 0.15769, 0.20891, 0.32465, 0.60804, 0.36616, 0.17272, 0.11024, 0.07852, 0.06575, 0.06036, 0.06124, 0.0619, 0.06393, 0.06189, 0.0639, 0.0728, 0.07918, 0.0734, 0.06985, 0.07072, 0.06979, 0.066, 0.06633, 0.06497, 0.06424, 0.06363, 0.06827, 0.06802, 0.07111, 0.08246, 0.1133, 0.0875, 0.07205, 0.06591, 0.05975, 0.05833, 0.05745, 0.05843, 0.05888, 0.06009, 0.06181, 0.06291, 0.06351, 0.06459, 0.06504, 0.06673, 0.06823, 0.0694, 0.07159, 0.07312, 0.0751, 0.07729, 0.07949, 0.08153, 0.08402, 0.08668, 0.08999, 0.09309, 0.0956, 0.09871, 0.1023, 0.10615, 0.11008, 0.11487, 0.11987, 0.12678, 0.13418, 0.14342, 0.15239, 0.1626, 0.17317, 0.18143, 0.1903, 0.22734, 0.25164, 0.24429, 0.32932, 0.28155, 0.22248, 0.22278, 0.23069, 0.24206, 0.26148, 0.28955, 0.39305, 0.40237, 0.32548, 0.32363, 0.33042, 0.34142, 0.35018, 0.3595, 0.37066, 0.38637, 0.39886, 0.41183, 0.42682, 0.44379, 0.46173, 0.48214, 0.50347, 0.53878, 0.556, 0.56991, 0.58464, 0.59192, 0.60936, 0.62944, 0.65129, 0.67347, 0.69756, 0.72395, 0.75808, 0.79345, 0.80799];


// addCurve(xtest, ytest, 'red', 'Name 1', false);

// xtest.reverse();
// ytest.reverse();
let xValues = [];
let yValues = [];
let i = 0;

// setInterval(function () {
//   xValues[i]=xtest[i];
//   yValues[i]=ytest[i];
//   addCurve(xValues, yValues, 'red', 'Name 1',false);
//   i++;
// }, 100);
function StoreData2(SampleID, xData, yData) {
  if (!(SampleID in data)) {
    data[SampleID] = { x: xData, y: yData };
  } else {
    // Update existing data
    data[SampleID].x = xData;
    data[SampleID].y = yData;
  }
}

StoreData2('Name 1',xtest,ytest);


function StoreData(SampleID, xData, yData ) {
  if (!(SampleID in data)) {
    // get the begining time
    data[SampleID] = { x: xData, y: yData };

  }

  else {
    // Update existing data
    data[SampleID].x = xData;
    data[SampleID].y = yData;
  
  }
 
}

//var result1 = trap(xValues.slice(140, 180 + 1), yValues.slice(140, 180 + 1));
//console.log("Approximated trap Area(560 to 520 ):",result1);
//var result2 = trap(xValues.slice(230, 270 + 1), yValues.slice(230, 270 + 1));
//console.log("Approximated trap Area(430 to 470):", result2);


function findPeaks(arr) {
  var peaks = [];
  var numPeaks = 5; // Number of peaks to return
  for (var i = 1; i < arr.length - 1; i++) {
    if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
      peaks.push(arr[i]);
    }
  }

  peaks.sort((a, b) => b - a); // Sort peaks in descending order

  // Return the specified number of highest peaks
  return peaks.slice(0, numPeaks);
}

/**------------------------------------------------------------------------
 *                           COMMANDS - NEVER THINK TO TOUCH ANYTHING HERE
 *------------------------------------------------------------------------**/

var cmdInput = document.querySelector('.cmd');
var table = document.getElementById('myTable');

cmdInput.addEventListener('keyup', function (event) {
  if (event.key === 'Enter') {
    const inputValue = this.value.trim();
    displayCMD(inputValue, 'black', "CMD: ");
    if (inputValue !== '') {
      
      // Regular expression to match the command with its parameter
      const match = inputValue.match(/(\w)(\d+)/);

      if (match) {
        const cmdName = match[1].toUpperCase(); // Extract the command name, 'T' in this case
        console.log(cmdName);
        const cmdParam = parseInt(match[2]); // Extract the parameter as an integer
        console.log(cmdParam);

        const rows = table.querySelectorAll('tr'); // Declare rows variable here
        switch (cmdName) {
          case 'T': // Done
            if (!isNaN(cmdParam) && cmdParam > 0 && cmdParam <= 10) {
              constructtable(cmdParam); // Pass the parameter to the constructTable function
            } else {
              alert('Invalid parameter for SCAN command');
            }
            break;


          case 'A': // area under curve for one 
            rows.forEach(function (row, index) {
            
              const cells = row.querySelectorAll('td');
              if (cells.length >= 5 && index == cmdParam) {
                const rowIndex = index;
                var SampleID = table.rows[rowIndex].cells[2].textContent;
                console.log("blah");
                const result = trap(data[SampleID].x, data[SampleID].y);
                console.log(-1* result.toFixed(3));
                cells[5].textContent = -1* result.toFixed(3);
                displayCMD(-1* result.toFixed(3), 'green', rowIndex);
              }
            });

            // Clear the input field after processing the command
            this.value = '';
            break;
          case 'B': //area for all
            rows.forEach(function (row, index) {
              const cells = row.querySelectorAll('td');
              if (cells.length >= 5) {
                const rowIndex = index;
                var SampleID = table.rows[rowIndex].cells[2].textContent;
                const result = trap(data[SampleID].x, data[SampleID].y);
                cells[5].textContent = result;
                displayCMD(result, 'green', rowIndex);
              }
            });

            // Clear the input field after processing the command
            this.value = '';
            break;
          case 'S': // specific range for area
            rows.forEach(function (row, index) {
              const cells = row.querySelectorAll('td');
              if (cells.length >= 5 && index == cmdParam) {
                const rowIndex = index;
                var SampleID = table.rows[rowIndex].cells[2].textContent;
                // input from user to specify the range
                var sRange = parseInt(prompt("Enter Start Wavelength:"));
                var eRange = parseInt(prompt("Enter End Wavelength:"));
                var sIndex = data[SampleID].x.indexOf(sRange);
                var eIndex = data[SampleID].x.indexOf(eRange);
                const result = trap(data[SampleID].x.slice(sIndex, eIndex + 1), data[SampleID].y.slice(sIndex, eIndex + 1));
                cells[5].textContent = -1* result.toFixed(3);
                displayCMD(-1* result.toFixed(3), 'green', rowIndex);
                var curveName = SampleID + " " + sRange + " : " + eRange;
                addCurve(data[SampleID].x.slice(sIndex, eIndex + 1), data[SampleID].y.slice(sIndex, eIndex + 1), 'green', curveName, true);
              }
            });

            // Clear the input field after processing the command
            this.value = '';
            break;

          case 'P': // find peaks
            rows.forEach(function (row, index) {
              const cells = row.querySelectorAll('td');
              if (cells.length >= 5 && index == cmdParam) {
                const rowIndex = index;
                var SampleID = table.rows[rowIndex].cells[2].textContent;
                // input from user to specify the range
                const result = findPeaks(data[SampleID].y);
                cells[5].textContent = 'LOOK COMMAND';
                var numbers = [];
                for (var i = 0; i < result.length; i++) {
                  numbers[i] = data[SampleID].x[data[SampleID].y.indexOf(result[i])];
                  displayCMD(" " + result[i], 'green', rowIndex + " Peaks at " + numbers[i]);
                }
                addCurve(numbers, result, 'green', SampleID + " Peaks", false, 'points');
              }
            });

            // Clear the input field after processing the command
            this.value = '';
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
  messageElement.textContent = "#" + num + ": " + message;
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
      allTextContent += child.textContent + "\n";
    }
  }

  // Return the string containing all textContent

  return allTextContent;

}



/**------------------------------------------------------------------------
 *                           SD Save Readings
 *------------------------------------------------------------------------**/

/*============================ Login ============================*/
function toggleLoginContainer(id = "login") {
  var login = document.getElementById(id);
  if (!login.style.display || login.style.display === "none") {
    login.style.display = "block";
  }
  else {
    login.style.display = "none";
  }
}

// Get the submit button element
var submitButton = document.getElementById('submit');
function login() {
  var user = document.getElementById("username").value;
  var pass = document.getElementById("password").value;
  var car = {
    username: user,
    password: pass,
    timeStamp: new Date().toISOString(),
  }
  websocket.send(JSON.stringify(car));
};

document.addEventListener('keydown', function (event) {
  // Check if the key pressed is Enter and the login container is opened
  if (event.key == 'Enter' && document.getElementById('login').style.display == 'block') {
    // Simulate a click on the submit button
    submitButton.click();
  }
});



//function to handle the esp32 login message 
function handleLogin(myObj) {
  console.log(myObj);
  if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
    if (myObj.username === true && myObj.password === true) {
      window.location.href = "temp.html";
    } else {
      document.getElementById("wrongpass").innerHTML = "Wrong username or password.";
    }
  }
}
/*============================ END OF LOGIN ============================*/

/*============================ Time Scan ============================*/
function startTimeScan(target) {
  if (target.innerHTML === '<i class="fa-solid fa-stop"></i>') {

    target.innerHTML = '<i class="fa-solid fa-play"></i>';
  }
  else {
    target.innerHTML = '<i class="fa-solid fa-stop"></i>';

  }
}

/**
 * =================Auto-zero method===============
 */

// Define global variables
let globalXref = [];
let globalTransmissionref = [];
let globalAbsorptionref = [];
let globalStart;
let globalStop;
function AutoZero() {
  if (!validateInputs()) return;
  const start = parseFloat(document.getElementById('start').value);
  const stop = parseFloat(document.getElementById('stop').value);
  const step = parseFloat(document.getElementById('step').value);
  globalStart = start;
  globalStop = stop;

 
  const rangeKey = `range_${step}`;
  console.log(rangeKey);
  const storedData = JSON.parse(localStorage.getItem(rangeKey)) || [];


  if (storedData) {
    if (storedData.length > 0) {
      globalXref = storedData.map(item => item.x);


      let needZeroMethod = 0;

      if (stop > globalXref[0]) {
        document.getElementById('start').value = globalXref[0] + step;
        needZeroMethod++;
      }

      if ((start < (globalXref[globalXref.length - 1] - step))) {
        if (needZeroMethod == 0) {
          document.getElementById('stop').value = globalXref[globalXref.length - 1] - step;
        }
        needZeroMethod++;
      }

      if (needZeroMethod) {
        if (needZeroMethod == 2) {
          return "not equal and we need to perform zero method twice";
        }
        // performPartialZeroMethod(rangeKey, index, SampleID, SampleDecribe, btn);
        return "not equal and we need to perform zero method";
      }


    }
    else {
      return "No Auto zero data for this range do you want to perform auto zero ?"
    }


  }
  else {
    // performPartialZeroMethod(rangeKey, index, SampleID, SampleDecribe, btn);
    return "No Auto zero data for this range do you want to perform auto zero ?"
  }
}

document.getElementById('clearStorage').addEventListener('click', function () {
  localStorage.clear();
  clearautozero();
  alert('Auto zero values cleared.');
});


function clearautozero(){
  globalAbsorptionref = [];
  globalTransmissionref = [];
  globalXref = [];
}
// Get all input fields
const startInput = document.getElementById('start');
const stopInput = document.getElementById('stop');
const stepInput = document.getElementById('step');

// Add change event listeners
startInput.addEventListener('change', disableAutoZero);
stopInput.addEventListener('change', disableAutoZero);
stepInput.addEventListener('change', disableAutoZero);


function disableAutoZero(){
  toggle.innerHTML = '<i class="fa-solid fa-toggle-off"></i>'
  AutoZeroFlag = false;
  clearautozero();
}


// document.getElementById('fullscreenButton').addEventListener('click', function() {
//   const chartContainer = document.getElementById('chartScan');
// console.log(chartContainer);
//   if (!document.fullscreenElement) {
//     if (chartContainer.requestFullscreen) {
//       chartContainer.requestFullscreen();
//     } else if (chartContainer.mozRequestFullScreen) { // Firefox
//       chartContainer.mozRequestFullScreen();
//     } else if (chartContainer.webkitRequestFullscreen) { // Chrome, Safari and Opera
//       chartContainer.webkitRequestFullscreen();
//     } else if (chartContainer.msRequestFullscreen) { // IE/Edge
//       chartContainer.msRequestFullscreen();
//     }
//   } else {
//     if (document.exitFullscreen) {
//       document.exitFullscreen();
//     } else if (document.mozCancelFullScreen) { // Firefox
//       document.mozCancelFullScreen();
//     } else if (document.webkitExitFullscreen) { // Chrome, Safari and Opera
//       document.webkitExitFullscreen();
//     } else if (document.msExitFullscreen) { // IE/Edge
//       document.msExitFullscreen();
//     }
//   }
// });
