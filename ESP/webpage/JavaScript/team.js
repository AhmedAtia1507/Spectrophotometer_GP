
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

function formatWithLeadingZero(number) {
    return number < 10 ? `0${number}` : number;
  }
  function updateDateTime() {
    const now = new Date(); // Get the current date and time
    let hours = now.getHours();
    const minutes = formatWithLeadingZero(now.getMinutes());
    const seconds = formatWithLeadingZero(now.getSeconds());
    const amPm = hours >= 12 ? 'PM' : 'AM';
    hours = hours % 12 || 12;
    const dateTimeString = `${now.toDateString()} || ${hours}:${minutes} ${amPm}`;
    document.getElementById('DateTime').textContent = dateTimeString;
  }
  
  // Update the date and time every second
  setInterval(updateDateTime, 1000);
  
  // Initial update
  updateDateTime();
    /*============================ END OF TIME AND DATE ============================*/

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
    
    
    function validateInput(input, max) {
      if (parseInt(input.value) > max) {
        input.value = max;
      }
    }

    
/**------------------------------------------------------------------------
 *                           login functions
 *------------------------------------------------------------------------**/
function toggleLogin(){
  var login = document.getElementById("login");
  if(login.style.display=="none"){
    login.style.display="block";
  }
  else{
    login.style.display="none";
  }
}


document.getElementById("submit").addEventListener("click", function () {
  var user = document.getElementById("username").value;
  var pass = document.getElementById("password").value;
  console.log(user, pass);
  sendCredentials(user, pass);
});

function sendCredentials(user, pass) {
  if (websocket.readyState === WebSocket.OPEN) {
      var car = {
          username: user,
          password: pass,
      }

      // Assuming 'websocket' is your WebSocket object
      websocket.send(JSON.stringify(car));
  } else {
      console.log('WebSocket not open. Reinitializing...');
      initWebSocket();
  }
}
  // Set up the WebSocket onmessage event
  websocket.onmessage = function (event) {
    var myObj = JSON.parse(event.data);
    console.log(myObj);
    if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
    handleLogin()
    }
  }

function handleLogin(myObj) {
  console.log(myObj);

  if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
      // Check if the username and password are true
      if (myObj.username === true && myObj.password === true) {
          console.log("Login successful. Redirecting to control.html");
          // request control page
          window.location.href = "temp.html";
      } else {
          localStorage.setItem('username', 'false');
          console.log("Wrong username or password.");
          document.getElementById("wrongpass").innerHTML = "Wrong username or password.";
      }
  } 
   else {
      // Handle other error conditions, such as 404 (Not Found)
      console.log("Error: " + event.data);
      document.getElementById("wrongpass").innerHTML = "Error: " + event.data;
      
  }
}





    