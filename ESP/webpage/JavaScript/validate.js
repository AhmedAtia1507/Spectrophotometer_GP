
function showMessaget(message, option1Text,ContainerID) {
  var messageContainer = document.getElementById(ContainerID);
  messageContainer.style.display = 'block';
  // Store in session storage
  sessionStorage.setItem('message', message);
  sessionStorage.setItem('option1Text', option1Text);
  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;
  // Create buttons for the options
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButtont'; // Apply custom CSS class
   option1Button.onclick = function() {
      // Logic for option 1

      var inputs = document.querySelectorAll('.numbers2');
      var values = Array.from(inputs).map(input => parseFloat(input.value)).filter(value => !isNaN(value));
      var max = Math.max(...values);
      var min = Math.min(...values);
      var start = max +100;
      var end = min - 100;
      addPoint1(start, end, 1);
  };
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
    messageContainer.appendChild(option1Button);
}
function toggleLoginContainer(id="chartScan"){
  var login = document.getElementById(id);
  if(!login.style.display || login.style.display === "none"){
    login.style.display="block"; 
  }
  else{
    login.style.display="none";
  }
}


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
  updateWifiStutus('connected','green');
}

function onClose(event) {
  // in case connection down
  // try again after 2 sec
  updateWifiStutus('disconnected','red');
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
function updateWifiStutus(connectedStutus,color){
  var wifi_stutus = document.getElementById('WifiStutus');
  wifi_stutus.textContent=connectedStutus;
  wifi_stutus.style.color=color ;
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




/*

****************************WAvelength Accuracy********************************

*/


document.addEventListener("DOMContentLoaded", function() {
  var submitButton1 = document.querySelector('.button1');
  submitButton1.addEventListener('click', function() {
    generateInputs();
    document.getElementById('tableContainer').style.display = 'none';
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
      input.placeholder = '   0';
      // Set disabled state based on checkbox (optional)
      if (!checkbox.checked) {
        input.disabled = true;
      }
      wavelengthsContainer.appendChild(input);

      var label2 = document.createElement('label');
      label2.textContent = ' nm';
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
  if (selectedOption === "" || selectedOption === "disabled") {
    if (document.getElementById('messageContainer1')) {
      document.getElementById('messageContainer1').textContent = '';
    }
    showMessage("Please choose a sample from the dropdown menu before proceeding.", "ok", "messageContainer1");
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

  var errorLimit = parseInt(document.querySelector('.error').value);
  // Compare user input values with predefined values
  var passesTest = compareWithPredefinedValues(userInputValues, predefinedValues, errorLimit);
  // Display the comparison result
  var messageContainer1 = document.getElementById('messageContainer1');
  var messageContainer2 = document.getElementById('messageContainer2');

  if (passesTest) {
    messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes!", "Show curve", "messageContainer2");
  } else {
    messageContainer2.style.display = 'none';
    if (messageContainer1) {
      messageContainer1.textContent = '';
    }
    showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer1");
  }
  // Show the table with the results
  document.getElementById('tableContainer').style.display = 'block';
  generateTable(predefinedValues, 'numbers1', 'numbers2', 'error', 'tableContainer');
}

function getPredefinedValues(option) {
  // Define predefined values for each option
  var predefinedValuesMap = {
    "Holmium oxide1": [200, 300, 400, 500, 600, 700],
    "Holmium oxide2": [100, 200, 300, 400, 500, 600],
    "Holmium oxide3": [30, 40, 50, 60, 70, 80]
  };

  // Get predefined values for the selected option
  return predefinedValuesMap[option] || [];
}


/*

************************************photometric Accuracy***************************************************

*/

document.addEventListener("DOMContentLoaded", function() {
  var formElements2 = document.querySelectorAll('.numbers12, .button12, .error2');
  var checkbox2 = document.querySelector('.checkboxes2');

  checkbox2.addEventListener('change', function() {
    for (var element of formElements2) {
      element.disabled = !this.checked; // Toggle disabled based on checkbox state
    }
  });

  var submitButton1 = document.querySelector('.button12');
  submitButton1.addEventListener('click', function() {
    document.getElementById('tableContainer1').style.display = 'none';
    var numfilters = parseInt(document.querySelector('.numbers12').value);
    var messageContainer12 = document.getElementById('messageContainer12');
    if (messageContainer12) {
      messageContainer12.textContent = '';
    }
    var messageContainer22 = document.getElementById('messageContainer22');
    if (messageContainer22) {
      messageContainer22.textContent = '';
    }
    var messageContainer31 = document.getElementById('messageContainer31');
    if (messageContainer31) {
      messageContainer31.textContent = '';
    }
    if (numfilters === 0 || isNaN(numfilters)) {
      showMessage("Please Enter the number of filters first", "ok", "messageContainer12");
    } else {
      generateInputs1();
      showMessage3("Start placing filters", "Done", "messageContainer31", numfilters);
    }
  });

  // Attach event listener to button22 inside DOMContentLoaded
  document.getElementById('button22').addEventListener('click', function() {
    CompareValues1();
  });
});

function generateInputs1() {
  var numfilterslengths = parseInt(document.querySelector('.numbers12').value);
  var filtersContainer = document.querySelector('.filters-container');
  
  // Clear previous inputs
  filtersContainer.innerHTML = '';

  // Generate new inputs
  for (var i = 0; i < numfilterslengths; i++) {
    var label1 = document.createElement('label');
    label1.textContent = 'Filters ' + (i + 1) + ' absorpation value: ';
    label1.className = 'label1';
    filtersContainer.appendChild(label1);
  
    var input1 = document.createElement('input');
    input1.type = 'number';
    input1.className = 'numbers3'; // Add class for identification
    input1.placeholder = '  0';
    input1.id = 'filter_' + i;

    filtersContainer.appendChild(input1);
  
    var label21 = document.createElement('label');
    label21.textContent = ' nm';
    filtersContainer.appendChild(label21);
    filtersContainer.appendChild(document.createElement("br")); // Add a line break for spacing
  }
}

function getPredefinedValues1() {
  return [100, 200, 300, 400];
}

function CompareValues1() {
  var predefinedValues = getPredefinedValues1();
  var errorLimit = parseInt(document.querySelector('.error2').value);
  var userInputValues = [];

  var inputs = document.querySelectorAll('.numbers3'); // Update class name if necessary
  inputs.forEach(function(input) {
    var inputValue = parseFloat(input.value);
    userInputValues.push(inputValue);
  });

  var passesTest2 = compareWithPredefinedValues(userInputValues, predefinedValues, errorLimit);
  var messageContainer12 = document.getElementById('messageContainer12'); // Updated ID
  var messageContainer22 = document.getElementById('messageContainer22'); // Updated ID

  if (passesTest2) {
    messageContainer12.style.display = 'none';
    if (messageContainer22) {
      messageContainer22.textContent = '';
    }
    showMessaget("Test passes!", "Show curve", "messageContainer22"); // Updated ID
  } else {
    messageContainer22.style.display = 'none';
    if (messageContainer12) {
      messageContainer12.textContent = '';
    }
    showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer12");
  }

  // Show the table with the results
  document.getElementById('tableContainer1').style.display = 'block';
  generateTable(predefinedValues, 'numbers12', 'numbers3', 'error2', 'tableContainer1');
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
  

  function compareWithzero(userInputValues, errorLimit) {
    for (var i = 0; i < userInputValues.length; i++) {
      var difference = userInputValues[i] - predefinedValues[i];
      if (Math.abs(difference) > errorLimit) {
        return false;
      }
    }
    return true;
  }

  function CompareValues2() {
    var errorLimit = parseInt(document.querySelector('.error3').value);
    var userInputValues = [];
  
    var passesTest3 = compareWithzero(userInputValues, errorLimit);
    var messageContainer1 = document.getElementById('messageContainer13'); // Updated ID
    var messageContainer2 = document.getElementById('messageContainer23'); // Updated ID
  
    if (passesTest3) {
      messageContainer1.style.display = 'none';
      if (messageContainer2) {
        messageContainer2.textContent = '';
      }
      showMessaget("Test passes!", "Show curve", "messageContainer23"); // Updated ID
    } else {
      messageContainer2.style.display = 'none';
      if (messageContainer1) {
        messageContainer1.textContent = '';
      }
      showMessage("Test fails. Do you want to continue the test?", "Cancel", "messageContainer12"); // Updated ID
    }
  }

  

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

  
    
    


    
function showMessage(message,option1Text,ContainerID) {
  // respond of data entered
  var messageContainer = document.getElementById(ContainerID);
  messageContainer.style.display = 'block';

  // Store in session storage
  sessionStorage.setItem('message', message);
  sessionStorage.setItem('option1Text', option1Text);
  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;
  // Create buttons for the options
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButtont'; // Apply custom CSS class
  option1Button.onclick = function() {
      // Logic for option 1
      console.log("Option 1 clicked");
      messageContainer.style.display = 'none';
      messageContainer.textContent = '';// Redirect if user chooses not to continue 
  };
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
    messageContainer.appendChild(option1Button);
}




function showMessage3(message, option1Text, containerId, numFilters) {
  var messageContainer = document.getElementById(containerId);

  // Validate numFilters input
  if (numFilters === 0 || isNaN(numFilters)) {
    showMessage("Please Enter the number of filters first", "ok", "messageContainer12");
    return; // Exit the function if validation fails
  }

  // Create a local variable to track current filter placement
  var currentFilter = 0;

  messageContainer.style.display = 'block';

  // Function for handling "Done" button click
  var handleDoneClick = function() {
    currentFilter++; // Increment filter counter

    // Check if all filters have been placed
    if (currentFilter === numFilters) {
      messageContainer.style.display = 'none'; // Hide container after completion


      var button22 = document.getElementById('button22');
      button22.style.display = 'block';
      
      CompareValues1();

      currentFilter = 0; // Reset filter counter for next sequence (optional)
      return; // Exit the function after completing all filters
    }

    var messageNode = messageContainer.querySelector('div'); // Select the existing message element
    if (messageNode) {
      messageNode.textContent = "Place filter number " + (currentFilter + 1);
    } else {
      // Create a message element if it doesn't exist
      messageNode = document.createElement('div');
      messageNode.textContent = "Place filter number " + (currentFilter + 1);
      messageContainer.appendChild(messageNode);
    }
  };

  // Create the "Done" button and attach click handler
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButtont'; // Apply custom CSS class
  option1Button.onclick = handleDoneClick;

  // Create a message element initially (optional)
  var messageNode = document.createElement('div');
  messageNode.textContent = message;
  messageContainer.appendChild(messageNode);

  // Append "Done" button to the container
  messageContainer.appendChild(option1Button);
}







function showMessagef(message, option1Text, option2Text,ContainerID) {
  var messageContainer = document.getElementById(ContainerID);
  messageContainer.style.display = 'block';
  // Store in session storage
  sessionStorage.setItem('message', message);
  sessionStorage.setItem('option1Text', option1Text);
  sessionStorage.setItem('option2Text', option2Text);
  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButton'; // Apply custom CSS class
  option1Button.onclick = function() {
      // Logic for option 1
      console.log("Option 1 clicked");
      window.open("temp.html", "_blank");
    };
  var option2Button = document.createElement('button');
  option2Button.textContent = option2Text;
  option2Button.className = 'optionButton'; // Apply custom CSS class
  option2Button.onclick = function() {
      // Logic for option 2
      var inputs = document.querySelectorAll('.numbers2');
      var values = Array.from(inputs).map(input => parseFloat(input.value)).filter(value => !isNaN(value));
      var max = Math.max(...values);
      var min = Math.min(...values);
      var start = max +100;
      var end = min - 100;
      addPoint1(start, end, 1);
    };
  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
}




function generateTable(predefinedValues, numClass, inputClass, errorClass, tableid) {
  var numRows = parseInt(document.querySelector(`.${numClass}`).value);
  var numColumns = 4;
  var headerNames = ['Entered Wavelength', 'Theoretical Wavelength', 'Error', 'Status'];

  var userInputValues = [];
  var inputs = document.querySelectorAll(`.${inputClass}`); // Update class name if necessary
  inputs.forEach(function(input) {
      var inputValue = parseFloat(input.value);
      userInputValues.push(inputValue);
  });

  var errorLimit = parseInt(document.querySelector(`.${errorClass}`).value);
  var column1Values = [], column2Values = [], column3Values = [], column4Values = [];

  for (var i = 0; i < numRows; i++) {
      var userValue = userInputValues[i % userInputValues.length];
      var predefinedValue = predefinedValues[i % predefinedValues.length];
      var error = Math.abs(userValue - predefinedValue);
      var state = compareWithPredefinedValues([userValue], [predefinedValue], errorLimit) ? 'Done' : 'Failed';

      column1Values.push(userValue); // Cycle through user input values
      column2Values.push(predefinedValue); // Cycle through predefined values
      column3Values.push(error);
      column4Values.push(state); // Set the status based on comparison
  }

  var tableContainer = document.getElementById(tableid);
  if (!tableContainer) {
      console.error(`Table container with id "${tableid}" not found.`);
      return;
  }

  tableContainer.innerHTML = ''; // Clear previous table

  var table = document.createElement('table');
  var headerRow = table.insertRow();
  for (var i = 0; i < numColumns; i++) {
      var headerCell = headerRow.insertCell();
      headerCell.textContent = headerNames[i];
      headerCell.style = "font-weight: 600;";
  }

  for (var i = 0; i < numRows; i++) {
      var row = table.insertRow();
      for (var j = 0; j < numColumns; j++) {
          var cell = row.insertCell();
          switch (j) {
              case 0:
                  cell.textContent = column1Values[i];
                  break;
              case 1:
                  cell.textContent = column2Values[i];
                  break;
              case 2:
                  cell.textContent = column3Values[i];
                  break;
              case 3:
                  cell.textContent = column4Values[i];
                  cell.style.color = column4Values[i] === 'Done' ? 'green' : 'red'; // Set color based on status
                  break;
              default:
                  cell.textContent = '';
          }
      }
  }

  console.log("Appending new table to container.");
  tableContainer.appendChild(table);
}


function compareWithPredefinedValues(userInputValues, predefinedValues, errorLimit) {
  // Compare user input values with predefined values
  for (var i = 0; i < userInputValues.length; i++) {
    var difference = userInputValues[i] - predefinedValues[i];
    if (Math.abs(difference) > errorLimit) {
      return false;
    }
  }
  return true;
}




// // SCAN
// /**========================================================================
//  *                           Chart
//  *========================================================================**/
// /* 
// */

var absorptionData = [];
var concentrationData = [];
var chart;

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
    responsive: true,
    maintainAspectRatio: true,
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
          color: 'light_gray', // Crosshair line color
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


function openChartInNewTab(xData, yData, color, curveName) {
  // Create a new window
  const newWindow = window.open('', '_blank');

  // Check if the new window opened successfully
  if (newWindow) {
    // Write the HTML structure for the new window
    newWindow.document.write(`
      <!DOCTYPE html>
      <html lang="en">
      <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Chart</title>
        <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
        <style>
          body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 1;
          }
          canvas {
            width: 90%;
            max-width: 800px;
            height: 50%;
          }
        </style>
      </head>
      <body>
        <canvas id="chartCanvas"></canvas>
        <script>
          // Function to add the curve
          function addCurve(xData, yData, color, curveName) {
            const ctx = document.getElementById('chartCanvas').getContext('2d');
            const chart = new Chart(ctx, {
              type: 'line',
              data: {
                labels: xData,
                datasets: [{
                  label: curveName,
                  data: yData,
                  borderColor: color,
                  fill: false
                }]
              },
              options: {
                scales: {
                  x: {
                    type: 'linear',
                    position: 'bottom'
                  }
                },
                animation: false // Disable animations
              }
            });
          }

          // Call the function to add the curve
          addCurve(${JSON.stringify(xData)}, ${JSON.stringify(yData)}, "${color}", "${curveName}");
        </script>
      </body>
      </html>
    `);
  } else {
    alert('Failed to open new window. Please allow pop-ups for this website.');
  }
}



// funcation to remove all curves in chart js
function removeAllCurves() {
  chartScan.data.datasets = [];
  chartScan.update();
}


function addPoint1(start, end, step) {
  let xData = [];
    for (let value = start; value >= end; value -= step) {
      xData.push(value);
    }
  let yData = [0.02234,0.02244,0.02247,0.0225,0.02263,0.02253, 0.02244,0.0226,0.02237,0.02265,0.02274,0.02255,0.02267];
  let color = 'cadetblue';
  let curveName = 'Absrbtion Curve';
  toggleLoginContainer(id="chartdiv");
  openChartInNewTab(xData, yData, color, curveName);

  const message = { // message for websocket
    command: 'Scan',
    startInput: start,
    stopInput: end,
    stepInput: step
  };
  websocket.send(JSON.stringify(message)); // websocket sent
  websocket.onmessage = function (event) { // WebSocket onmessage event
    const data = JSON.parse(event.data);
    console.log(event.data); // for test
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    absorptionValue = Math.log10(intensityReference / intensitySample);
  };

}



