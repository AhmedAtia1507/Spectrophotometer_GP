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


  
/*============================ Login ============================*/
function toggleLoginContainer(){
    var login = document.getElementById("login");
    if(login.style.display=="none"){
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
    /**========================================================================
 *                           STATE BAR
 *========================================================================**/
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