
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
      addPoint1();
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

function addPoint1(start, end) {
  let xtest = [700,699,698,697,696,695,694,693,692,691,690,689,688];
  let ytest = [0.02234,0.02244,0.02247,0.0225,0.02263,0.02253,0.02244,0.0226,0.02237,0.02265,0.02274,0.02255,0.02267];
  toggleLoginContainer(id="chartdiv");
  addCurve(xtest, ytest, 'black', "Intensity");

  // const message = { // message for websocket
  //   command: 'Scan',
  //   startInput: start,
  //   stopInput: end,
  //   stepInput: 1
  // };
  // websocket.send(JSON.stringify(message)); // websocket sent
  // websocket.onmessage = function (event) { // WebSocket onmessage event
  //   const data = JSON.parse(event.data);
  //   console.log(event.data); // for test
  //   const currentTime = data.currentTime;
  //   const wavelength = data.wavelength;
  //   const intensityReference = data.intensityReference;
  //   const intensitySample = data.intensitySample;
  //   absorptionValue = Math.log10(intensityReference / intensitySample);
  // };

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
      input.placeholder = '0';
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
  generateTable(predefinedValues);
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

function generateTable(predefinedValues) {
  var numRows = parseInt(document.querySelector('.numbers1').value);
  var numColumns = 4;
  var headerNames = ['Entered Wavelength', 'Theoretical Wavelength', 'Error', 'Status'];

  var userInputValues = [];
  var inputs = document.querySelectorAll('.numbers2'); // Update class name if necessary
  inputs.forEach(function(input) {
    var inputValue = parseFloat(input.value);
    userInputValues.push(inputValue);
  });

  var errorLimit = parseInt(document.querySelector('.error').value);
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

  var tableContainer = document.getElementById('tableContainer');
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

  tableContainer.appendChild(table);
}

/*

****************************Photometric Accuracy********************************

*/
var formElements2 = document.querySelectorAll('.numbers12, .button12, .error2');
var checkbox2 = document.querySelector('.checkboxes2');

checkbox2.addEventListener('change', function() {
  for (var element of formElements2) {
    element.disabled = !this.checked; // Toggle disabled based on checkbox state
  }
});



document.addEventListener("DOMContentLoaded", function() {
  var submitButton1 = document.querySelector('.button12');
  submitButton1.addEventListener('click', function() {
    
    var numfilrters = parseInt(document.querySelector('.numbers12').value);
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
    if (numfilrters === 0 || numfilrters === "") {
      showMessage("Please Enter the number of filters first","ok","messageContainer12");
    } 
    else {
      generateInputs1();
      showMessage3("Start placing filters", "Done", "messageContainer31",numfilrters); 
    };
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
      label1.textContent = 'Filters ' + (i + 1) + ' wavelength: ';
      label1.className = 'label1';
      filtersContainer.appendChild(label1);
    
      var input1 = document.createElement('input');
      input1.type = 'number';
      input1.className = 'numbers2'; // Add class for identification
      input1.placeholder = '  0';
      input1.id = 'filter_' + i;

      filtersContainer.appendChild(input1);
      filtersContainer.appendChild(input1);
    
      var label21 = document.createElement('label');
      label21.textContent = '      nm';
      filtersContainer.appendChild(label21);
      filtersContainer.appendChild(document.createElement("br")); // Add a line break for spacing
  } 
}


function getPredefinedValues1() {

      var predefinedValues = [100, 200, 300];

      // Get user input values for wavelengths (assuming class 'wavelength-input')
      var userInputValues = [];
      var inputs = document.querySelectorAll('.numbers2'); // Update class name if necessary
      inputs.forEach(function(input) {
      var inputValue = parseFloat(input.value);
      userInputValues.push(inputValue);
  });
}

function CompareValues1() {
  getPredefinedValues1();
  var errorLimit= parseInt(document.querySelector('.error2').value);

      for (i = 0; i < 3; i++) {
        var filterId = 'filter_' + i;
        var filterInput = document.getElementById(filterId).value;
        var filterInput2 = filterInput.value;          
      }

      var passesTest = compareWithPredefinedValues2(userInputValues, filterInput2, errorLimit);
 if (passesTest){
    
    messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes! " , "Show curve","messageContainer2" );
    
 }
 else{

  messageContainer2.style.display = 'none';
  if (messageContainer1) {
    messageContainer1.textContent = '';
  }
  showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve","messageContainer1" );
 
 }
}




// function compareWithPredefinedValues2(userInputValues, predefinedValues, errorLimit) {
//   // Compare user input values with predefined values
//   for (var i = 0; i < userInputValues.length; i++) {
//       var difference = userInputValues[i] - predefinedValues[i];
//       if (Math.abs(difference) > errorLimit) {
//           return false;
//       }
//   }
//   return true;
// }

// var passesTest2 = 

// if (passesTest2){
    
//    messageContainer1.style.display = 'none';
//     if (messageContainer2) {
//       messageContainer2.textContent = '';
//     }
//     showMessaget("Test passes! " , "Show curve","messageContainer22" );
    
//  }
//  else{

//   messageContainer2.style.display = 'none';
//   if (messageContainer1) {
//     messageContainer1.textContent = '';
//   }
//   showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve","messageContainer12" );
 
//  }




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
  
  /* if (passesTest3){
    
     messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes! " , "Show curve","messageContainer23" );
    
 }
 else{

  messageContainer2.style.display = 'none';
  if (messageContainer1) {
    messageContainer1.textContent = '';
  }
  showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve","messageContainer13" );
 
 }

*/

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

  /*if (passesTest4){
    
     messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes! " , "Show curve","messageContainer24" );
    
 }
 else{

  messageContainer2.style.display = 'none';
  if (messageContainer1) {
    messageContainer1.textContent = '';
  }
  showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve","messageContainer14" );
 
 }
*/


    /**========================================================================
 *                           common functions
 *========================================================================**/
 

    //   var chartScan;
    //   let chartData;
      
      
    //   const ctxScan = document.getElementById('chartScan').getContext('2d');
    //   chartScan = new Chart(ctxScan, {
    //     type: 'line',
    //     data: chartData,
    //     options: {
    //       tooltips: {
    //         enabled: false
    //       },
    //       animation: {
    //         duration: 0
    //       },
    //       responsive: false,
    //       maintainAspectRatio: false,
    //       plugins: {
    //         crosshair: {
    //           tooltips: {
    //             enabled: false // Disable tooltips for the crosshair
    //         },
    //           sync: {
    //             enabled: true // Enable crosshair synchronization between multiple charts
    //           },
    //           zoom: {
    //             enabled: true // Enable crosshair zooming along the axis
    //           },
    //           line: {
    //             color: 'blue', // Crosshair line color
    //             width: 1 // Crosshair line width
    //           }
    //         },
           
    //       },
    //       scales: {
    //         x: {
    //           min: 190,
    //           max: 1100,
    //           type: 'linear',
    //           position: 'bottom'
    //         },
    //         y: {
    //           type: 'linear',
    //           position: 'left'
    //         }
    //       },
    //       onHover: null // Disable the default onHover behavior
    //     }
    //   });
      
      



    // var absorptionData = [];
    // var concentrationData = [];
    // var chart;
  
    
    


    
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
  if (numFilters === 0 || numFilters === "") {
    showMessage("Please Enter the number of filters first", "ok", "messageContainer12");
    return; // Exit the function if validation fails
  }

  // Create a local variable to track current filter placement (outside the function)
  var currentFilter = 0;

  messageContainer.style.display = 'block';

  // Function for handling "Done" button click
  var handleDoneClick = function() {
    currentFilter++; // Increment filter counter

    // Check if all filters have been placed
    if (currentFilter === numFilters) {
      showMessage("All filters placed!", "", containerId); // Display completion message
      messageContainer.style.display = 'none'; // Hide container after completion
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


    //Update the message content (without overwriting button)

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
      console.log("Option 2 clicked");
      addPoint1();
    };
  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
}
    


// // SCAN
// /**========================================================================
//  *                           Chart
//  *========================================================================**/
// /* 
// PUT THIS IN HTML : <canvas id="chartScan" style="height: 95%; width: 95%;"></canvas>
// */
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

// ////////////////////////////////scan///////////////
var absorptionData = [];
var concentrationData = [];
var chart;



