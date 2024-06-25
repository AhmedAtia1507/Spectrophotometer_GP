//180 sec 
//all wavelengths
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
      wavelengthsContainer.appendChild(input);

      var label2 = document.createElement('label');
      label2.textContent = ' nm';
      wavelengthsContainer.appendChild(label2);
      wavelengthsContainer.appendChild(document.createElement("br")); // Add a line break for spacing
    }
  }



  var formElements = document.querySelectorAll('.dropdown-button, .numbers1, .button1, .error, #submitButton');
  var checkbox = document.querySelector('.checkboxes1');

checkbox.addEventListener('change', function() {
    for (var element of formElements) {
      element.disabled = !this.checked;
    }
  });

 

  var submitButton2 = document.querySelector('.button11');
  submitButton2.addEventListener('click', function() {
    var userInputValues = getUserInputValues();
    var start = Math.min(...userInputValues) - 10;
    var end = Math.max(...userInputValues) + 10;
    addPoint1(start, end, 1);
  });
});

function getUserInputValues() {
  var userInputValues = [];
  var inputs = document.querySelectorAll('.numbers2');
  inputs.forEach(function(input) {
    var inputValue = parseFloat(input.value);
    userInputValues.push(inputValue);
  });
  return userInputValues;
}


var userInputValues = getUserInputValues();
var xData = [ 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200]
var errorLimit = parseInt(document.querySelector('.error').value);
var yData = [ 1, 2, 3, 1, 0, 1, 2, 1, 3, 0];


function compareValues(x,y) {

  var passesTest = compareWithPredefinedValues1(userInputValues, errorLimit,x, y);

  var messageContainer1 = document.getElementById('messageContainer1');
  var messageContainer2 = document.getElementById('messageContainer2');

  if (passesTest) {
    messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes!", "Show curve", "messageContainer2", "1");
  } else {
    messageContainer2.style.display = 'none';
    if (messageContainer1) {
      messageContainer1.textContent = '';
    }
    showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer1", "1");
  }

  document.getElementById('tableContainer').style.display = 'block';
  generateTable1( userInputValues, errorLimit, 'tableContainer',xData, yData);
}


function compareWithPredefinedValues1(userInputValues, errorLimit,xData, yData) {
  var count = [];
  for (var i = 0; i < userInputValues.length; i++) {
    var userValue = userInputValues[i];
    var scanned_wl = findClosestPeak(userValue,xData, yData); // Find the closest peak wavelength
    var distance = Math.abs(scanned_wl - userValue);
    if (distance <= errorLimit) {
      count.push(1);
    } else {
      count.push(0);
    }
  }

  // Check if all values in count are 1
  return count.every(val => val === 1);
}



function generateTable1(userInputValues, errorLimit, tableId,xData, yData) {
  var tableContainer = document.getElementById(tableId);

  tableContainer.innerHTML = '';

  var table = document.createElement('table');

  // Create table header
  var headerRow = table.insertRow();
  ['Entered Wavelength', 'Scanned Wavelength', 'Error', 'Status'].forEach(function(headerName) {
    var headerCell = headerRow.insertCell();
    headerCell.textContent = headerName;
    headerCell.style.fontWeight = '600';
  });

  var error, status;
  
  for (var i = 0; i < userInputValues.length; i++) {
    var userValue = userInputValues[i];
    var scanned_wl = findClosestPeak(userValue,xData, yData); // Find the closest peak
    var distance = Math.abs(scanned_wl - userValue);

    if (distance <= errorLimit) {
      error = distance;
      status = 'Done';
    } else {
      error = distance;
      status = 'Failed';
    }

    // Create a new row in the table
    var row = table.insertRow();
    // Add cell for entered wavelength
    var cell1 = row.insertCell();
    cell1.textContent = userValue;
    // Add cell for scanned wavelength or 'N/A' if no peak is found
    var cell2 = row.insertCell();
    cell2.textContent = scanned_wl !== null ? scanned_wl : 'N/A';
    // Add cell for error
    var cell3 = row.insertCell();
    cell3.textContent = error;
    // Add cell for status
    var cell4 = row.insertCell();
    cell4.textContent = status;
    cell4.style.color = status === 'Done' ? 'green' : 'red';
  }

  tableContainer.appendChild(table);
}


// Function to find peaks in an array
function findPeaks(arr) {
    var peaks = [];
    // var numPeaks = 5; 
    for (var i = 1; i < arr.length - 1; i++) {
      if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
        peaks.push(arr[i]);
      }
    }

    peaks.sort((a, b) => b - a); // Sort peaks in descending order
//return peaks[0];
    // Return the specified number of highest peaks
  return peaks.slice(0, 5);
}


function findClosestPeak(userValue, xData, yData) {
  var closestPeak ;
  var minDifference = Infinity;
  const result = findPeaks(yData);
  var index = yData.indexOf(result);
  var peakX = [];

  for (var i = 0; i <index.length; i++) { 
     peakX[i] = xData[index[i]];
  }

  for (var i = 0; i <5; i++) { 
    var peakWavelength =peakX[i];
    var difference = Math.abs(peakWavelength - userValue);
      // Update closest peak if this peak is closer to the user-entered wavelength
      if (difference < minDifference) {
        minDifference = difference;
        closestPeak = peakWavelength;
      }
    }

  return closestPeak;
} 




function addPoint1(start, end, step) {
  // let xData = [];
  // for (let value = start; value <= end; value += step) {
  //   xData.push(value);
  // }
  // let yData = generateYData(xData); // Generate yData based on xData

  let color = 'cadetblue';
  let curveName = 'Absorption Curve';

let x = []
let y = []
  const message = {
    command: 'scan',
    startInput: start,
    stopInput: end,
    stepInput: step,
    lampmode:'both',
  };
  websocket.send(JSON.stringify(message));
  websocket.onmessage = function (event) {
    let buffer = event.data.split('\n');
    buffer.forEach(dataBuffer => {
      if (dataBuffer.trim()) {
        try {
          const data = JSON.parse(dataBuffer);
          console.log(data);
          processScanData(data)

        } catch (error) {
          console.error("Error parsing data buffer: ", error);
        }
      }
    });
  };
  function processScanData(data){
    const currentTime = data.currentTime;
    let scanning, progress ; 
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    const transmission = Math.log10(intensitySample / intensityReference);
    const absorption = Math.log10(intensityReference / intensitySample);
    const wavelength = data.wavelength;
    scanning = data.scanning; //check if the scan end or not
    progress = data.current; //represent the progress to display the current progress
    x.push(wavelength); 
    y.push(absorption);
    if(progress==100){
      compareValues(x,y);
      openChartInNewTab(x, y, color, curveName);
      
    }
 
  }
  


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
      if (messageContainer12) {
        messageContainer12.textContent = '';
        messageContainer31.textContent = '';
      }
      showMessage("Please Enter the number of filters first", "ok", "messageContainer12");
    } else {
      if (messageContainer22) {
        messageContainer22.textContent = '';
        messageContainer31.textContent = '';
      }
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
    label1.textContent = 'Filters ' + (i + 1) + ' Wavelength: ';
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
    showMessaget("Test passes!", "Show curve", "messageContainer22","2"); // Updated ID
  } else {
    messageContainer22.style.display = 'none';
    if (messageContainer12) {
      messageContainer12.textContent = '';
    }
    showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer12","2");
  }

  // Show the table with the results
  document.getElementById('tableContainer1').style.display = 'block';
  generateTable(predefinedValues, 'numbers12', 'numbers3', 'error2', 'tableContainer1');
}

/*

****************************Baseline Stability********************************

*/

var formElements3 = document.querySelectorAll('.button13, .error3'); // Select all relevant elements
var checkbox3 = document.querySelector('.checkboxes3'); // Get the checkbox element

checkbox3.addEventListener('change', function() {
  for (var element of formElements3) {
    element.disabled = !this.checked; // Toggle disabled based on checkbox state
  }
});

// Attach event listener to button13 inside DOMContentLoaded
document.getElementById('button13').addEventListener('click', function() {
  console.log("clicked");
  addPoint3(70, 150, 10);
});

function addPoint3(start, end, step) {
  let xData = [190,230,270,310,350,390,430,470,510,550,590,630,670,710,750,790,830,870,910,950,990,1100];
  let yData = [0,0,0,0.3,0,0,0.5,0,0,0,0,0,0.1,0,0,0.07,0,0,0,0.2,0,0];
  let color = 'cadetblue';
  let curveName = 'Absrbtion Curve';

  openChartInNewTab1(xData, yData, color, curveName); // Open initial chart
  CompareValues2(yData);

  const message = { // message for websocket
    command: 'Scan',
    startInput: start,
    stopInput: end,
    stepInput: step,
    lampmode:'both'
  };
  websocket.send(JSON.stringify(message)); // websocket sent
  websocket.onmessage = function (event) { // WebSocket onmessage event
    let buffer = event.data.split('\n');
    //process each part of the buffer
    buffer.foreach(dataBuffer => {
      // Trim any extraneous whitespace and ensure it’s not empty
      if(dataBuffer.trim()){
        try {
          //parse the json string
          const data = JSON.parse(dataBuffer);

          // For testing purposes, log the parsed data
          console.log(data);

          // Process the json data
          const wavelength = data.wavelength;
          const intensityReference = data.intensityReference;
          const intensitySample = data.intensitySample;
          absorptionValue = Math.log10(intensityReference / intensitySample);
          xData.length = 0;
          yData.length = 0;
          xData.push(wavelength);
          yData.push(absorptionValue);
        } catch (error){
          console.error('Failed to parse JSON:', error);
        }
      }
    });
  };
  openChartInNewTab1(xData, yData, color, curveName);
  CompareValues2(yData);
}

function CompareValues2(absorptionValue) {
  var errorLimit = parseFloat(document.querySelector('.error3').value);

  var passesTest3 = absorptionValue.every(value => Math.abs(value) <= errorLimit);

  console.log('Passes Test:', passesTest3);

  var messageContainer13 = document.getElementById('messageContainer13'); // Updated ID
  var messageContainer23 = document.getElementById('messageContainer23'); // Updated ID

  if (passesTest3) {
    messageContainer13.style.display = 'none';
    if (messageContainer23) {
      messageContainer23.textContent = '';
    }
    showMessaget("Test passes!", "Show curve", "messageContainer23","3"); // Updated ID
  } else {
    messageContainer23.style.display = 'none';
    if (messageContainer13) {
      messageContainer13.textContent = '';
    }
    showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer13","3");
  }
}

  

/*

****************************Photometric noise********************************

*/


var formElements4 = document.querySelectorAll(' .numbers14, .numbers24, .button14, .error4 '); // Select all relevant elements
  var checkbox4 = document.querySelector('.checkboxes4'); // Get the checkbox element

  checkbox4.addEventListener('change', function() {
    for (var element of formElements4) {
      element.disabled = !this.checked; // Toggle disabled based on checkbox state
    }
  });

  // Attach event listener to button22 inside DOMContentLoaded
  document.getElementById('button14').addEventListener('click', function() {
    console.log = ("clicked");
    addPoint4(70,150,10);
  });

  function addPoint4(start, end, step) {
    let xData = [];
    for (let value = 180; value >= 0; value -= 0.5) {
      xData.push(value);
    }
    let yData = [5,5,5,5,5,5,5,5,5,5.1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.92,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.88,5,5,5,5,5,5,5,5,5,5,5,5,5,5.15,5,5,5,5,4.94,5,5,5.1,5,5,5,5.2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5.05,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5.05,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5.05,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.96,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4.88,5,5,5,5,5,5,5,5,5,5,5,5,5,5,,5,5,5,5.1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5.2,5,5,5,5,5,5.5,5,5,5,5,5,5,5,5,5,4.82,5,5.2,5,5,5,,5];
    let absorptionValue = [30, 40, 50, 60, 100];
    let color = 'cadetblue';
    let curveName = 'Absrbtion Curve';
  
    openChartInNewTab1(xData, yData, color, curveName); // Open initial chart
    CompareValues3(absorptionValue, xData, yData);
    
    const message = { // message for websocket
      command: 'Scan',
      startInput: start,
      stopInput: end,
      stepInput: step,
      lampmode:'both',
    };
    websocket.send(JSON.stringify(message)); // websocket sent
    websocket.onmessage = function (event) { // WebSocket onmessage event
      let buffer = event.data.split('\n');
      //process each part of the buffer
      buffer.foreach(dataBuffer => {
        // Trim any extraneous whitespace and ensure it’s not empty
        if(dataBuffer.trim()){
          try {
            //parse the json string
            const data = JSON.parse(dataBuffer);
  
            // For testing purposes, log the parsed data
            console.log(data);
  
            // Process the json data
            const wavelength = data.wavelength;
            const intensityReference = data.intensityReference;
            const intensitySample = data.intensitySample;
            absorptionValue = Math.log10(intensityReference / intensitySample);
            yData.length = 0;
            yData.push(absorptionValue);
          } catch (error){
            console.error('Failed to parse JSON:', error);
          }
        }
      });
    };
    openChartInNewTab1(xData, yData, color, curveName);
      CompareValues3(absorptionValue);
}
  function CompareValues3(absorptionValue) {
    var errorLimit = parseInt(document.querySelector('.error4').value);
    var userInputValues = [];
    var inputs = document.querySelectorAll('.numbers14'); // Update class name if necessary
    inputs.forEach(function(input) {
      var inputValue = parseFloat(input.value);
      userInputValues.push(inputValue);
    });
  
    var passesTest4 = compare(userInputValues, errorLimit, absorptionValue);
    var messageContainer14 = document.getElementById('messageContainer14'); // Updated ID
    var messageContainer24 = document.getElementById('messageContainer24'); // Updated ID
  
    if (passesTest4) {
      messageContainer14.style.display = 'none';
      if (messageContainer24) {
        messageContainer24.textContent = '';
      }
      showMessaget("Test passes!", "Show curve", "messageContainer24","4"); // Updated ID
    } else {
      messageContainer24.style.display = 'none';
      if (messageContainer14) {
        messageContainer14.textContent = '';
      }
      showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve", "messageContainer14","4");
    }
  }



    

/*

**********************************************COMMON FUNCTIONS***********************************************

*/


function compare(userInputValues, errorLimit, absorptionValue) {
  for (var i = 0; i < userInputValues.length; i++) {
    var difference = userInputValues[i] - absorptionValue[i];
    if (Math.abs(difference) > errorLimit) {
      return false;
    }
  }
  return true;
}






function showMessage(message, option1Text, ContainerID) {
  var messageContainer = document.getElementById(ContainerID);
  messageContainer.style.display = 'block';

  // Clear previous message content if any
  messageContainer.innerHTML = '';

  // Store in session storage
  sessionStorage.setItem('message', message);
  sessionStorage.setItem('option1Text', option1Text);

  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;
  
  // Apply custom styles based on the option1Text
  if (option1Text === 'ok') {
    messageDiv.style.color = 'green';
  } else if (option1Text === 'cancel') {
    messageDiv.style.color = 'red';
  }

  // Create a button for the option
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButton'; // Apply custom CSS class

  option1Button.onclick = function() {
    if (option1Text === 'ok') {
      messageContainer.style.display = 'none';
      messageContainer.textContent = ''; // Clear message content
    } else if (option1Text === 'cancel') {
      window.open("temp.html", "_blank");
    }
  };

  // Append message and option button to the container
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







function showMessagef(message, option1Text, option2Text,ContainerID,functions) {
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

      var inputs2 = document.querySelectorAll('.numbers3');
      var values2 = Array.from(inputs2).map(input2 => parseFloat(input2.value)).filter(value => !isNaN(value));
      var max2 = Math.max(...values2);
      var min2 = Math.min(...values2);
      
      var start2 = max2 +100;
      var end2 = min2 - 100;

      if (functions==1) {
        addPoint1(start, end, 1);
      }
      else if (functions==2)
        {
          addPoint1(start2, end2, 1);
        }
      else if (functions==3)
        {
          addPoint3(190, 1100, 10);
        }
      else if (functions==4)
        {
          addPoint4(190, 1100, 10);
        }
    };
  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
}


function showMessaget(message, option1Text,ContainerID,functions) {
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
      var inputs = document.querySelectorAll('.numbers2');
      var values = Array.from(inputs).map(input => parseFloat(input.value)).filter(value => !isNaN(value));
      var max = Math.max(...values);
      var min = Math.min(...values);
      
      var start = max +100;
      var end = min - 100;

      var inputs2 = document.querySelectorAll('.numbers3');
      var values2 = Array.from(inputs2).map(input2 => parseFloat(input2.value)).filter(value => !isNaN(value));
      var max2 = Math.max(...values2);
      var min2 = Math.min(...values2);
      
      var start2 = max2 +100;
      var end2 = min2 - 100;

      if (functions==1) {
        addPoint1(start, end, 1);
      }
      else if (functions==2)
        {
          addPoint1(start2, end2, 1);
        }
      else if (functions==3)
        {
          addPoint3(max, min, 10);
        }
      else if (functions==4)
        {
          addPoint4(max, min, 1);
        }
  };
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
    messageContainer.appendChild(option1Button);
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





function compare(userInputValues, errorLimit, absorptionValue) {
  for (var i = 0; i < userInputValues.length; i++) {
    var difference = userInputValues[i] - absorptionValue[i];
    if (Math.abs(difference) > errorLimit) {
      return false;
    }
  }
  return true;
}


function addPoint1(start, end, step) {
  let xData = [];
    for (let value = start; value >= end; value -= step) {
      xData.push(value);
    }
    let yData = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
  //let yData = [0.02244,0.02247,1.3,1.7,2.7,2.97,3,2.8,2,1.3,0.02267,0.02267,0.02267,0.02267,0.5,1,1.7,2,1.9,1.6,1.2,0.02267,0.02267];
  let color = 'cadetblue';
  let curveName = 'Absrbtion Curve';
 
 // toggleLoginContainer(id="chartdiv");
  openChartInNewTab(xData, yData, color, curveName);

  const message = { // message for websocket
    command: 'Scan',
    startInput: start,
    stopInput: end,
    stepInput: step,
    lampmode:'both'
  };
  websocket.send(JSON.stringify(message)); // websocket sent
  websocket.onmessage = function (event) { // WebSocket onmessage event
    let buffer = event.data.split('\n');
    //process each part of the buffer
    buffer.foreach(dataBuffer => {
      // Trim any extraneous whitespace and ensure it’s not empty
      if(dataBuffer.trim()){
        try {
          //parse the json string
          const data = JSON.parse(dataBuffer);

          // For testing purposes, log the parsed data
          console.log(data);

          // Process the json data
          const wavelength = data.wavelength;
          const intensityReference = data.intensityReference;
          const intensitySample = data.intensitySample;
          absorptionValue = Math.log10(intensityReference / intensitySample);
          xData.length = 0;
          yData.length = 0;
          xData.push(wavelength);
          yData.push(absorptionValue);
        } catch (error){
          console.error('Failed to parse JSON:', error);
        }
      }
    });
  };
  openChartInNewTab(xData, yData, color, curveName);
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

function openChartInNewTab1(xData, yData, color, curveName) {
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
            margin: 0;
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
                  },
                  y: {
                    min: 2,
                    max: 7
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