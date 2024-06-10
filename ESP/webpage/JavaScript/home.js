
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
function updateWifiStutus(connectedStutus,color){
    var wifi_stutus = document.getElementById('WifiStutus');
    wifi_stutus.textContent=connectedStutus;
    wifi_stutus.style.color=color ;
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