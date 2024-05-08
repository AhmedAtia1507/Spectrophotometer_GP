
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
}

function onClose(event) {
  // in case connection down
  // try again after 2 sec
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
/**========================================================================
 *                           footer
 *========================================================================**/
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

/**========================================================================
 *                           Chart
 *========================================================================**/
/* 
PUT THIS IN HTML : <canvas id="chartScan" style="height: 95%; width: 95%;"></canvas>

var chartScan;
let chartData;
const ctxVal = document.getElementById('chartScan').getContext('2d');
chartScan = new Chart(ctxVal, {
  type: 'line',
  data: chartData,
  options: {
    tooltips: {
      enabled: false
    },
    animation: {
      duration: 0
    },
    responsive: false,
    maintainAspectRatio: false,
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
        // min: 190,
        // max: 1100,
        type: 'linear',
        position: 'bottom'
      },
      y: {
        type: 'linear',
        position: 'left'
      }
    },
    onHover: null // Disable the default onHover behavior
  }
});
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
  }

  chartScan.update(); // Update the chart
}




// funcation to remove all curves in chart js
function removeAllCurves() {
  chartScan.data.datasets = [];
  chartScan.update();
}
*/



/*

****************************WAvelength Accuracy********************************

*/


document.addEventListener("DOMContentLoaded", function() {
  var submitButton = document.querySelector('.button1');
  submitButton.addEventListener('click', function() {
    generateInputs();
  });

  function generateInputs() {
    var numWavelengths = parseInt(document.querySelector('.numbers1').value);
    var wavelengthsContainer = document.querySelector('.wavelengths-container');
  
    // Clear previous inputs
    wavelengthsContainer.innerHTML = '';
  
    // Generate new inputs
    for (var i = 0; i < numWavelengths; i++) {
      var label = document.createElement('label');
      label.textContent = 'Wavelength ' + (i + 1) + ': ';
      label.className = 'label1';
      wavelengthsContainer.appendChild(label);
  
      var input = document.createElement('input');
      input.type = 'number';
      input.className = 'numbers2'; // Add class for identification
      input.placeholder = '  0';
      // Set disabled state based on checkbox (optional)
    if (!checkbox.checked) {
      input.disabled = true;
    }

    wavelengthsContainer.appendChild(input);
      wavelengthsContainer.appendChild(input);
  
      var label2 = document.createElement('label');
      label2.textContent = '      nm';
      wavelengthsContainer.appendChild(label2);
      wavelengthsContainer.appendChild(document.createElement("br")); // Add a line break for spacing
    }
  }
  
  var formElements = document.querySelectorAll('.dropdown-button, .numbers1, .button1, .error, #submitButton'); // Select all relevant elements
  var checkbox = document.querySelector('.checkboxes1'); // Get the checkbox element

  checkbox.addEventListener('change', function() {
    for (var element of formElements) {
      element.disabled = !this.checked; // Toggle disabled based on checkbox state
    }
  });

  document.getElementById('submitButton').addEventListener('click', compareValues);
  var submitButton2 = document.querySelector('.button11'); // Targeting the new submit button
  submitButton2.addEventListener('click', compareValues);
});


function compareValues() {
  var dropdown = document.getElementById('Sampleselector');
  var selectedOption = dropdown.options[dropdown.selectedIndex].value;

    // Check if a valid option is selected
    if (selectedOption === "" || selectedOption === "disabled"  ) {
      alert("Please choose a sample from the dropdown menu before proceeding.");
      return; // Exit the function if no valid option is selected
    }

  // Get predefined values based on selected option
  var predefinedValues = getPredefinedValues(selectedOption);

  // Get user input values for wavelengths (assuming class 'wavelength-input')
  var userInputValues = [];
  var inputs = document.querySelectorAll('.numbers2'); // Update class name if necessary
  inputs.forEach(function(input) {
    var inputValue = parseFloat(input.value);
    userInputValues.push(inputValue);
  });

  var errorLimit= parseInt(document.querySelector('.error').value);
  // Compare user input values with predefined values
  var passesTest = compareWithPredefinedValues(userInputValues, predefinedValues,errorLimit);

  // Display the result of the comparison
  displayComparisonResult(passesTest);
}

function getPredefinedValues(option) {
  // Define predefined values for each option
  var predefinedValuesMap = {
    "Holmium oxide1": [200, 300, 400, 500, 600, 700],
    "Holmium oxide2": [100, 200, 300, 400, 500, 600],
    "Holmium oxide3": [30, 40, 50, 60, 70, 80]
  };

  // Get predefined values for the selected option
  var values = predefinedValuesMap[option] || [];

  return values;
}


function compareWithPredefinedValues(userInputValues, predefinedValues, errorLimit) {
  // Consider passing the errorLimit as an argumentd

  // Compare user input values with predefined values
  var passesTest = true;
  for (var i = 0; i < userInputValues.length; i++) {
    var difference = userInputValues[i] - predefinedValues[i]; 
    if (difference > errorLimit) {
      passesTest = false;
      break;
    } else if (difference < -errorLimit) {
      passesTest = false;
      break;
    }
    
  }
  return passesTest;
}


function displayComparisonResult(passesTest) {
  if (passesTest) {
    alert('Test passes!');
  } else {
    var continueTest = confirm('Test fails. Do you want to continue the test?');
    if (continueTest) {
      // Implement logic to continue the test (consider error handling)
    } else {
      // Redirect to direct control page (assuming you have a URL)
      window.location.href = "sssssssssss"; // Replace with your actual URL
    }
  }
}


/*

****************************Photometric Accuracy********************************

*/

var formElements2 = document.querySelectorAll('.numbers12, .button12, .error2'); // Select all relevant elements
var checkbox2 = document.querySelector('.checkboxes2'); // Get the checkbox element

checkbox2.addEventListener('change', function() {
  for (var element of formElements2) {
    element.disabled = !this.checked; // Toggle disabled based on checkbox state
  }
});



function showPopup() {
  alert("Place the First filter");
}




/*

****************************Baseline Stability********************************

*/

var formElements3 = document.querySelectorAll(' .numbers13, .button13, .error3 '); // Select all relevant elements
  var checkbox3 = document.querySelector('.checkboxes3'); // Get the checkbox element

  checkbox3.addEventListener('change', function() {
    for (var element of formElements3) {
      element.disabled = !this.checked; // Toggle disabled based on checkbox state
    }
  });


/*

****************************Photometric noise********************************

*/


var formElements4 = document.querySelectorAll(' .numbers14, .button14, .error4 '); // Select all relevant elements
  var checkbox4 = document.querySelector('.checkboxes4'); // Get the checkbox element

  checkbox4.addEventListener('change', function() {
    for (var element of formElements4) {
      element.disabled = !this.checked; // Toggle disabled based on checkbox state
    }
  });
