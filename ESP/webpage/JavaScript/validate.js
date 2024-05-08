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
          // Disable the input based on checkbox state
      input.disabled = !checkbox.checked;

    wavelengthsContainer.appendChild(input);
      wavelengthsContainer.appendChild(input);
  
      var label2 = document.createElement('label');
      label2.textContent = '      nm';
      wavelengthsContainer.appendChild(label2);
      wavelengthsContainer.appendChild(document.createElement("br")); // Add a line break for spacing
    }
  
  
  }
  
  var formElements = document.querySelectorAll('.dropdown-button, .numbers1, .numbers2, .button1, .error, #submitButton'); // Select all relevant elements
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
