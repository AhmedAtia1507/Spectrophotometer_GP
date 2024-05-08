document.addEventListener("DOMContentLoaded", function() {
  var submitButton = document.querySelector('.button1');
  submitButton.addEventListener('click', function() {
    generateInputs();
  });

  var submitButton2 = document.querySelector('.submit-button'); // Targeting the new submit button
  submitButton2.addEventListener('click', function() {
    submitForm();
  });
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
    wavelengthsContainer.appendChild(input);

    var label2 = document.createElement('label');
    label2.textContent = '      nm';
    wavelengthsContainer.appendChild(label2);
    wavelengthsContainer.appendChild(document.createElement("br")); // Add a line break for spacing
  }
}


function submitForm() {
  var dropdown = document.getElementById('Sampleselector');
  var selectedOption = dropdown.options[dropdown.selectedIndex].value;

  // Get predefined values based on selected option
  var predefinedValues = getPredefinedValues(selectedOption);

  // Get user input values
  var inputs = document.querySelectorAll('.numbers2');
  var errorLimit = parseFloat(document.querySelector('.error').value);

  // Store user input values
  var inputValues = [];
  inputs.forEach(function(input) {
    var inputValue = parseFloat(input.value);
    inputValues.push(inputValue);
  });

  // Take the first 6 predefined values
  var comparisonValues = predefinedValues.slice(0, 6);

  // Compare user input with predefined values
  var passesTest = true;
  for (var i = 0; i < 6; i++) {
    var difference = Math.abs(inputValues[i] - comparisonValues[i]);

    // Check if the difference is within the error limit
    if (difference > errorLimit | difference < errorLimit) {
      passesTest = false;
      break;
    }
  }

  function getPredefinedValues(option) {
    // Define predefined values for each option
    var predefinedValuesMap = {
      "Holmium oxide1": [200, 300, 400, 500, 600, 700],
      "Holmium oxide2": [100, 200, 300, 400, 500, 600],
      "Holmium oxide3": [30, 40, 50, 60, 70, 80]
    };

  // Display result in a pop-up window
  if (passesTest) {
    alert('Test passes!');
  } else {
    var continueTest = confirm('Test fails. Do you want to continue the test?');
    if (continueTest) {
      // Continue the test
    } else {
      alert('Test aborted.');
    }
  }
}

  // Get predefined values for the selected option
  var values = predefinedValuesMap[option] || [];

  // Return at most 6 values
  return values;
}

