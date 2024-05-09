
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
    showMessage("Please choose a sample from the dropdown menu before proceeding.");
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

 if (passesTest){
    showMessage("Test passes!");
    window.location.href = "http://127.0.0.1:5500/ESP/webpage/chart.html";
 }
 else{
  showMessage1("Test fails. Do you want to continue the test?", "Ok", "cancel");
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

function showMessage(message) {
  // respond of data entered
  var messageContainer = document.getElementById('messageContainer1');

  // Clear previous inputs
  messageContainer.innerHTML = '';
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message; 
  messageContainer.appendChild(messageDiv);
}

function showMessage1(message, option1Text, option2Text) {
  var messageContainer = document.getElementById('messageContainer1');

  // Clear previous content
  messageContainer.innerHTML = '';

  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;

  // Create buttons for the options
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButton'; // Apply custom CSS class
  option1Button.onclick = function() {
      // Logic for option 1
      console.log("Option 1 clicked");
      messageContainer.innerHTML = '';
  };

  var option2Button = document.createElement('button');
  option2Button.textContent = option2Text;
  option2Button.className = 'optionButton'; // Apply custom CSS class
  option2Button.onclick = function() {
      // Logic for option 2
      console.log("Option 2 clicked");
      window.location.href = "http://127.0.0.1:5500/ESP/webpage/temp.html"; // Redirect if user chooses not to continue
      messageContainer.innerHTML = '';
    };

  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
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


function showMessage2(message) {
  // respond of data entered
  var messageContainer = document.getElementById('messageContainer2');

  // Clear previous inputs
  messageContainer.innerHTML = '';
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message; 
  messageContainer.appendChild(messageDiv);
}

function showMessage3(message, option1Text, option2Text) {
  var messageContainer = document.getElementById('messageContainer2');

  // Clear previous content
  messageContainer.innerHTML = '';

  // Create a div for the message text
  var messageDiv = document.createElement('div');
  messageDiv.textContent = message;

  // Create buttons for the options
  var option1Button = document.createElement('button');
  option1Button.textContent = option1Text;
  option1Button.className = 'optionButton'; // Apply custom CSS class
  option1Button.onclick = function() {
      // Logic for option 1
      console.log("Option 1 clicked");
      messageContainer.innerHTML = '';
  };

  var option2Button = document.createElement('button');
  option2Button.textContent = option2Text;
  option2Button.className = 'optionButton'; // Apply custom CSS class
  option2Button.onclick = function() {
      // Logic for option 2
      console.log("Option 2 clicked");
      window.location.href = "http://127.0.0.1:5500/ESP/webpage/temp.html"; // Redirect if user chooses not to continue
      messageContainer.innerHTML = '';
    };

  // Append message and options to the container
  messageContainer.appendChild(messageDiv);
  messageContainer.appendChild(option1Button);
  messageContainer.appendChild(option2Button);
}

function showPopup() {
  showMessage2("Place the First filter");
  //showMessage3("Test fails. Do you want to continue the test?", "Ok", "cancel");
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

  function showMessage4(message) {
    // respond of data entered
    var messageContainer = document.getElementById('messageContainer3');
  
    // Clear previous inputs
    messageContainer.innerHTML = '';
    var messageDiv = document.createElement('div');
    messageDiv.textContent = message; 
    messageContainer.appendChild(messageDiv);
  }

  function showMessage5(message, option1Text, option2Text) {
    var messageContainer = document.getElementById('messageContainer3');
  
    // Clear previous content
    messageContainer.innerHTML = '';
  
    // Create a div for the message text
    var messageDiv = document.createElement('div');
    messageDiv.textContent = message;
  
    // Create buttons for the options
    var option1Button = document.createElement('button');
    option1Button.textContent = option1Text;
    option1Button.className = 'optionButton'; // Apply custom CSS class
    option1Button.onclick = function() {
        // Logic for option 1
        console.log("Option 1 clicked");
        messageContainer.innerHTML = '';
    };
  
    var option2Button = document.createElement('button');
    option2Button.textContent = option2Text;
    option2Button.className = 'optionButton'; // Apply custom CSS class
    option2Button.onclick = function() {
        // Logic for option 2
        console.log("Option 2 clicked");
        window.location.href = "http://127.0.0.1:5500/ESP/webpage/temp.html"; // Redirect if user chooses not to continue
        messageContainer.innerHTML = '';
      };
  
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
    messageContainer.appendChild(option1Button);
    messageContainer.appendChild(option2Button);
  }

  function showPopup1() {
    showMessage5("Test fails. Do you want to continue the test?", "Ok", "cancel");
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

  function showMessage6(message) {
    // respond of data entered
    var messageContainer = document.getElementById('messageContainer4');
  
    // Clear previous inputs
    messageContainer.innerHTML = '';
    var messageDiv = document.createElement('div');
    messageDiv.textContent = message; 
    messageContainer.appendChild(messageDiv);
  }

  function showMessage7(message, option1Text, option2Text) {
    var messageContainer = document.getElementById('messageContainer4');
  
    // Clear previous content
    messageContainer.innerHTML = '';
  
    // Create a div for the message text
    var messageDiv = document.createElement('div');
    messageDiv.textContent = message;
  
    // Create buttons for the options
    var option1Button = document.createElement('button');
    option1Button.textContent = option1Text;
    option1Button.className = 'optionButton'; // Apply custom CSS class
    option1Button.onclick = function() {
        // Logic for option 1
        console.log("Option 1 clicked");
        messageContainer.innerHTML = '';
    };
  
    var option2Button = document.createElement('button');
    option2Button.textContent = option2Text;
    option2Button.className = 'optionButton'; // Apply custom CSS class
    option2Button.onclick = function() {
        // Logic for option 2
        console.log("Option 2 clicked");
        window.location.href = "http://127.0.0.1:5500/ESP/webpage/temp.html"; // Redirect if user chooses not to continue
        messageContainer.innerHTML = '';
      };
  
    // Append message and options to the container
    messageContainer.appendChild(messageDiv);
    messageContainer.appendChild(option1Button);
    messageContainer.appendChild(option2Button);
  }

  function showPopup2() {
    showMessage7("Test fails. Do you want to continue the test?", "Ok", "cancel");
  }
