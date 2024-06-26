
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
  function toggleDarkMode() {
    document.body.classList.toggle('dark-mode');
  }
  
/**========================================================================
 *                           STATE BAR
 *========================================================================**/
function updateWifiStutus(connectedStutus,color){
    var wifi_stutus = document.getElementById('WifiStutus');
    wifi_stutus.textContent=connectedStutus;
    wifi_stutus.style.color=color ;
  }
  function toggleInteractiveElements() {
    // Get all interactive elements
    var interactiveElements = document.querySelectorAll('button, input, select');
    // Loop through each element and toggle its disabled attribute
    interactiveElements.forEach(function(element) {
      element.disabled = !element.disabled;
      // Add or remove 'disabled' class based on the disabled state
      if (element.disabled) {
        element.classList.add('disabled');
      } else {
        element.classList.remove('disabled');
      }
    });
  }
  
  document.getElementById('sBarBtn').addEventListener('click', function () {
  
    const message = {
      command: 'StateBar',
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
    
/**------------------------------------------------------------------------
 *                           FLC
 *------------------------------------------------------------------------**/

var absorptionData = [];
var concentrationData = [];
var chart;
updateChart();
function addPoint() {
  var absorptionValue;
  var concentrationValue = parseFloat(document.getElementById("concentration").value);
  var WLine = document.getElementById("WLine").value; // get wavelength
  const message = { // message for websocket
    command: 'scan',
    lampmode:'both',
    startInput: WLine,
    stopInput: WLine,
    stepInput: 0
  };
  websocket.send(JSON.stringify(message)); // websocket sent
  websocket.onmessage = function (event) { // WebSocket onmessage event
    const data = JSON.parse(event.data);
    console.log(event.data); // for test
    const currentTime = data.currentTime;
    const wavelength = data.wavelength;
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    absorptionValue = Math.log10(intensityReference / intensitySample);
    
  };


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
          type: 'linear',
          position: 'bottom',
          ticks: {
            color: 'red' // Change color of x-axis ticks
          }
        },
        y: {
          type: 'linear',
          position: 'left',
          ticks: {
            color: 'blue' // Change color of y-axis ticks
          }
        }
      },
      onHover: null // Disable the default onHover behavior
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
  document.getElementById("messageBox").innerHTML = "";
  concentrationData = [];
  updateChart();
  clearMessage();
}
function clearInputs() {
  document.getElementById("absorption").value = "";
  document.getElementById("concentration").value = "";
}
setTimeout(showfoot, 1000); //autohide foot in 1sec

document.getElementById('hidefoot').addEventListener('click', showfoot)


function showfoot() {
  var but = document.getElementById('hidefoot');
  var foot = document.getElementById('hidethis');
  var footer = document.getElementById('sticky');

  if (but.innerHTML === 'hide') {
    but.innerHTML = 'show';
    footer.style.backgroundColor='transparent';    
  }
  else {
    but.innerHTML = 'hide';
    footer.style.backgroundColor='#2d2e33';
  }
  foot.classList.toggle('inactive');
}

/*============================ Login ============================*/
function toggleLoginContainer(id="login"){
    var login = document.getElementById(id);
    if(!login.style.display || login.style.display === "none"){
      login.style.display="block"; 
    }
    else{
      login.style.display="none";
    }
  }
  
  // Get the submit button element
  var submitButton = document.getElementById('submit');
  function login(){
    var user = document.getElementById("username").value;
    var pass = document.getElementById("password").value;
    var car = {
        username: user,
        password: pass,
    }
    websocket.send(JSON.stringify(car));
  };
  
   document.addEventListener('keydown', function(event) {
     // Check if the key pressed is Enter and the login container is opened
     if (event.key == 'Enter' && document.getElementById('login').style.display=='block') {
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