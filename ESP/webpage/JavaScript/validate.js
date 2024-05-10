
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
    showMessage("Please choose a sample from the dropdown menu before proceeding.", "ok", "messageContainer1" );
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
  var passesTest = compareWithPredefinedValues(userInputValues, predefinedValues, errorLimit);

  // Display the comparison result
 // showMessage(passesTest ? "Test passes!" : "Test fails. Do you want to continue the test?");

 var messageContainer1 = document.getElementById('messageContainer1');
 var messageContainer2 = document.getElementById('messageContainer2');

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
  // Compare user input values with predefined values
  for (var i = 0; i < userInputValues.length; i++) {
      var difference = userInputValues[i] - predefinedValues[i];
      if (Math.abs(difference) > errorLimit) {
          return false;
      }
  }
  return true;
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

    var localCounter = 1;

    if (numfilrters === 0 || numfilrters === "") {
      showMessage("Please Enter the number of filters first","ok","messageContainer12");
    } 
    else {
      showMessage3("Start placing filters", "Done", "messageContainer31",numfilrters); 
    };
  });
});




/*if (passesTest2){
    
   messageContainer1.style.display = 'none';
    if (messageContainer2) {
      messageContainer2.textContent = '';
    }
    showMessaget("Test passes! " , "Show curve","messageContainer22" );
    
 }
 else{

  messageContainer2.style.display = 'none';
  if (messageContainer1) {
    messageContainer1.textContent = '';
  }
  showMessagef("Test fails. Do you want to continue the test?", "cancel", "Show curve","messageContainer12" );
 
 }

*/


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

    // Update the message content (without overwriting button)
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
      console.log("Option 1 clicked");
      window.location.href = "http://127.0.0.1:5500/ESP/webpage/chart.html";// Redirect if user chooses not to continue
  };
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
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
      window.location.href = "http://127.0.0.1:5500/ESP/webpage/temp.html"; // Redirect if user chooses not to continue
    };
  var option2Button = document.createElement('button');
  option2Button.textContent = option2Text;
  option2Button.className = 'optionButton'; // Apply custom CSS class
  option2Button.onclick = function() {
      // Logic for option 2
      console.log("Option 2 clicked");
      window.location.href = "http://127.0.0.1:5500/ESP/webpage/chart.html"; // Redirect if user chooses not to continue  
    };
  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
}