/*
section 1 : intialize the websocket connection and handles login stuff (done)
section 2 : handles the webpage ui (ongoing)
section 3 : handles user messages (ongoing)
section 4 : some function used by handle message (ongoing)
section 5 : login functions (done)
*/

/*================== intialize the websocket connection section 1===============*/

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// Init web socket when the page loads
window.addEventListener("load", onLoad);

function onLoad(event) {
  initWebSocket();
}

function initWebSocket() {
  console.log("Trying to open a WebSocket connection...");
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  // Set onmessage handler after the WebSocket is opened
  websocket.onmessage = function (event) {
    handleMessage(event);
  };
}

function onOpen(event) {
  console.log("Connection opened");
  // sendCurrentLoginFlag();                // asks the server if the user have logged in or not
  // senduvStatus();                        // send us lamp stutus to diplay it on open 
  // sendviStatus();                       // send visible lamp stutus to diplay it on open  
  // sendsupplystutus();
  // sendmoterssteps();
  // sendLampmoter();
  // senddetector();
  // loadtime();
}

function onClose(event) {
  console.log("Connection closed");
  setTimeout(initWebSocket, 2000);  //try to connect every 2 sec
}
/*===========================================================end of section 1===========================================================================*/



/*===========================================================handles the webpage ui section 2========================================================================*/

//Toggles the visibility of the overlay element that appears to wait for the moter to move
function togglePageState(enable) {
  var overlay = document.getElementById('overlay');
  overlay.style.display = (overlay.style.display === 'none') ? 'block' : 'none';
}
// should be toggled for the first time to work properly
togglePageState("first");

//function to check the login flag from the esp32
function sendCurrentLoginFlag() {
  var login = {
    flag: "islogin?",
  };
  websocket.send(JSON.stringify(login));
}

//function to ask the server to send the lamp stutus
function sendviStatus() {
  var vilampstutus = {
    vilampstutus: "send",
  };
  websocket.send(JSON.stringify(vilampstutus));
}

//function to ask the server to send the lamps stutus
function senduvStatus(){
  var uvlampstutus = {
    uvlampstutus: "send",
  };
  websocket.send(JSON.stringify(uvlampstutus));
}

//send the supply voltages
function sendsupplystutus(){
  var supplystutus = {
    supplystutus: "send",
  };
  websocket.send(JSON.stringify(supplystutus));
  
}

//send the current moters steps and wavelength
function sendmoterssteps(){
  var motors = {
    motors: "send",
  };
  websocket.send(JSON.stringify(motors));
}


//send the current position of the lamp moter 
function sendLampmoter(){
  var motors = {
    lampmotor: "send",
  };
  websocket.send(JSON.stringify(motors));
  
}


//read current detector values
function senddetector(){
  var detector={
    senddetector:"senddetector",
  }
  websocket.send(JSON.stringify(detector));
}

function loadtime() {
  var loadtime = {
    loadtime: "loadtime",
  };
  // Assuming 'websocket' is your WebSocket object
  websocket.send(JSON.stringify(loadtime));
}


function redirecttohome() {
  window.location.href = "index.html";
}

//open a session for 20 minutes after this period user need to login again
setInterval(redirecttohome, 1200000);


/*============================ END OF Nabbar ============================*/
function showSidebar() {
  const sidebar = document.querySelector('.sidebar');
  sidebar.style.display = 'flex';
}
function hideSidebar() {
  const sidebar = document.querySelector('.sidebar');
  sidebar.style.display = 'none';
}
/* ================================================================end of section 2===========================================================  */


/*======================================================== handles the esp32 messages section 3=================================================*/

function handleMessage(event) {
  var myObj = JSON.parse(event.data);
  console.log(myObj);

  if (myObj.hasOwnProperty("flag")) {
    if (myObj.flag) {
    } else {
      redirecttohome();
    }
  } else if (myObj.hasOwnProperty("uvstutus") || myObj.hasOwnProperty("vistutus")) {
    handleLampStatus(myObj);
  } else if (myObj.hasOwnProperty("supplystutus")) {
    handleSupplyStatus(myObj);
  } else if (myObj.hasOwnProperty("currenttime")) {
    updateDateTime(myObj.currenttime);
  } else if (myObj.hasOwnProperty("timeupdated")) {
    handleTimeUpdated(myObj.timeupdated);
  } else if (myObj.hasOwnProperty("currenlamp")) {
    document.getElementById("currentlamp").innerHTML = myObj.currenlamp;
  } else if (myObj.hasOwnProperty("motorssteps")) {
    handleMotorsSteps(myObj);
  } else if (myObj.hasOwnProperty("gohome")) {
    handleGoHome(myObj);
  } else if (myObj.hasOwnProperty("stepsaved")) {
    handleStepSaved(myObj.stepsaved);
  } else if (myObj.hasOwnProperty("motermoved")) {
    togglePageState("disable");
  } else if (myObj.hasOwnProperty("detreadings")) {
    handleDetReadings(myObj.detreadings);
  } else if(myObj.hasOwnProperty("DirectResponse")){
    document.getElementById("CMDresponse").innerHTML=myObj.DirectResponse;
  }
  else if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
    handleLogin(myObj);
  }
  
  
}

/*=============================================================end of secion 3========================================================== */



/*========================================================function used by handle messages section 4=====================================*/ 


// Function to toggle UV or VI device
function toggleLamp(deviceId) {
  // Get the state element and current state of the device
  const stateElement = document.getElementById(`${deviceId}state`);
  const currentState = stateElement.innerHTML;
  
  // Define the command to be sent based on the current state
  const command = currentState === "on" ? { [`turn${deviceId}off`]: "turnoff" } : { [`turn${deviceId}on`]: "turnon" };
  
  // Send command via WebSocket
  console.log(command);
  websocket.send(JSON.stringify(command));
}


function handleLampStatus(myObj) {
  var lampType = myObj.hasOwnProperty("uvstutus") ? "uv" : "vi";
  var stateElement = document.getElementById(lampType + "state");
  var icon = document.getElementById(lampType + "icon");
  
  if (myObj[lampType + "stutus"] === "on") {
    console.log("lamp is working fine");
    stateElement.innerHTML = "on";
    stateElement.style.color = "white";
    stateElement.style.background = "green";

    // Update toggle icon
    icon.classList.remove("fa-toggle-off");
    icon.classList.add("fa-toggle-on");
  } else if (myObj[lampType + "stutus"] === "off") {
    console.log(lampType + " lamp is off");
    stateElement.innerHTML = "off";
    stateElement.style.color = "white";
    stateElement.style.background = "red";
    
    // Update toggle icon
    icon.classList.remove("fa-toggle-on");
    icon.classList.add("fa-toggle-off");
  } 
  else if (myObj[lampType + "stutus"] === "fault") {
    console.log(lampType + " lamp is fault");
    stateElement.innerHTML = "fault";
    stateElement.style.color = "white";
    stateElement.style.background = "red";
    
    // Update toggle icon
    icon.classList.remove("fa-toggle-on");
    icon.classList.add("fa-toggle-off");
 
}
}

function handleSupplyStatus(myObj) {
  console.log("supplies received");
  const ary =myObj.voltages.split(' ');
  document.getElementById("p12").textContent = ary[0];
  document.getElementById("n12").textContent = ary[1];
  document.getElementById("p5").textContent = ary[2];
  document.getElementById("p33").textContent = ary[3];
  document.getElementById("twelve").textContent = ary[4];
}

function handleTimeUpdated(message) {
  var display = document.getElementById("timeupdated");
  display.style.color = "green";
  display.innerHTML = message;
  setTimeout(function () {
    display.innerHTML = "";
  }, 4000);
}

function handleMotorsSteps(myObj) {
  const ary = myObj.motorssteps.split('-');
  document.getElementById("lampstep").textContent = ary[0];
  document.getElementById("gratingstep").textContent = ary[1];
  document.getElementById("filterstep").textContent = ary[2];
  document.getElementById("filterwave").textContent = ary[3];
  document.getElementById("gratingmotorwl").value = parseFloat(ary[3]);
}

function handleGoHome(myObj) {
  togglePageState("disable");
  const type = myObj.type.replace("motorhome", "step");
  document.getElementById(type).textContent = myObj.step;
  document.getElementById("filterwave").textContent = myObj.wavelength;
}

function handleStepSaved(message) {
  console.log(message);
  var display = document.getElementById("stepsaved");
  display.style.color = "green";
  display.textContent = message;
  setTimeout(function () {
    display.innerHTML = "";
  }, 4000);

}

function handleDetReadings(detReadings) {
  console.log(detReadings);
  const ary = detReadings.split('-');
  document.getElementById("smallref").textContent = ary[0];
  document.getElementById("largeref").textContent = ary[1];
  document.getElementById("smallmes").textContent = ary[2];
  document.getElementById("largemes").textContent = ary[3];
  document.getElementById("RefGain").textContent = ary[4];
  document.getElementById("SampleGain").textContent = ary[5];

  
  gainaccurecy();
}

/**------------------------------------------------------------------------
 * ====================  Date and Time==========================
 *------------------------------------------------------------------------**/

// Get current date and time to initillaize the time data inputs to browser time
const currentDateTime = new Date();
const currentDate = currentDateTime.toISOString().split("T")[0];
document.getElementById("datepicker").value = currentDate;


function saveDateTime(target) {  
  const selectedDate = new Date(document.getElementById("datepicker").value);
  const selectedTime = document.getElementById("timepicker").value;
  const dateTimeString = `${selectedDate.toLocaleDateString().split("T")[0].replace(/-/g, '/')} ${selectedTime}`;
  console.log(dateTimeString);

  var updatetime = {
    updatetime: dateTimeString,
  };
  // Assuming 'websocket' is your WebSocket object
  websocket.send(JSON.stringify(updatetime));
  loadtime();
}

/*
 * Updates the text content of an element with the current date and time.
 */

let intervalId; // Variable to store the interval ID

function updateDateTime(initialDateTimeString) {
  // Clear the existing interval if it's set
  if (intervalId) {
    clearInterval(intervalId);
  }

  // Convert the initial date time string to a Date object
  let currentDateTime = new Date(initialDateTimeString);

  // Update the HTML element initially
  updateElement(currentDateTime);

  // Set up a new interval to update the time every second
  intervalId = setInterval(function () {
    // Increase the time by one second
    currentDateTime.setSeconds(currentDateTime.getSeconds() + 1);
    // Update the HTML element with the new date and time
    updateElement(currentDateTime);
  }, 1000);
}



function updateElement(dateTime) {
  // Get the current date and time in a formatted string
  const formattedDateTime = dateTime.toLocaleString();
  // Update the HTML element with the formatted date and time
  document.getElementById('currentDateTime').innerText = formattedDateTime;

}

/**------------------------------------------------------------------------
 * ==================== motors ==========================
 *------------------------------------------------------------------------**/



function validat(target,min, max) {
  var inputElement = document.getElementById(target.id);
  var currentValue = parseInt(inputElement.value);
  if (currentValue < min) {
    inputElement.value = min;
  }
  else if (currentValue > max) {
    inputElement.value = max;
  }
  
}
//function to toggle Lamp motor position
function toggleLampMoter(){
  togglePageState("enable");
  var currentfunction =document.getElementById("currentlamp");
  var icon=document.getElementById("lampchangeicon");
    // Toggle the icon class
    if (icon.classList.contains("fa-toggle-off")) {
      // If the icon is currently off, toggle it on
      icon.classList.remove("fa-toggle-off");
      icon.classList.add("fa-toggle-on");
    } else {
      // If the icon is currently on, toggle it off
      icon.classList.remove("fa-toggle-on");
      icon.classList.add("fa-toggle-off");
    }

  if(currentfunction.innerHTML=="UV Lamp")
  {
    var message = {
      Lampmotortoggle: 'VI',
    };
    websocket.send(JSON.stringify(message));
    
  }
  else {
    var message = {
      Lampmotortoggle: 'UV',
    };
    websocket.send(JSON.stringify(message));

  }
}


function moveto(event){
  console.log(event.target.id);
  switch(event.target.id){
    case "filtermotermove":
    console.log("this is filter case");
    movefiltermoter(event);  
    break;
      
    case "gratingmotermove":
    console.log("this is grating case");
    movegratingmoter(event);
    break;
  }
}

function movefiltermoter(targetevent){
  var step = document.getElementById('filtermotorstep').value;
        if(targetevent.target.classList=="fa-regular fa-circle-left"){
          if(step){
            var moveto = {
              movemoter: "set-filtermoter-to-L-" + step,
            };
            console.log(moveto);
            websocket.send(JSON.stringify(moveto));
            togglePageState("enable");
          }
        }

      
        else if(targetevent.target.classList=="fa-regular fa-circle-right"){
        if(step){
          var moveto = {
            movemoter: "set-filtermoter-to-R-" + step,
          };
          console.log(moveto);
          websocket.send(JSON.stringify(moveto));
          togglePageState("enable");
        }
      }
    
    
      
      else{
        var selectElement = document.getElementById("filterselector");
        var lateststep = selectElement.value;
        if(lateststep){
          var moveto = {
            movemoter: "set-filtermoter-to-" + lateststep,
          };
          togglePageState("enable");
          console.log(moveto);
          websocket.send(JSON.stringify(moveto));
      
        }
      }  
    

    

}

function movegratingmoter(targetevent){
      var wavelength = document.getElementById('gratingmotorwl').value;
      var step=document.getElementById('gratingmotorstep').value;
      if(targetevent.target.classList=="fa-solid fa-angles-right"){
      if(wavelength){
        var moveto = {
          movemoter: "set-gratingmoter-to-WL-" + wavelength,
        };
        console.log(moveto);
        websocket.send(JSON.stringify(moveto));
        togglePageState("enable");
      }

    }  
    else if(targetevent.target.classList=="fa-regular fa-circle-left"){
      if(step){
        var moveto = {
          movemoter: "set-gratingmoter-to-L-" + step,
        };
        console.log(moveto);
        websocket.send(JSON.stringify(moveto));
        togglePageState("enable");
      }
    }
    else if(targetevent.target.classList=="fa-regular fa-circle-right"){
      if(step){
        var moveto = {
          movemoter: "set-gratingmoter-to-R-" + step,
        };
        console.log(moveto);
        websocket.send(JSON.stringify(moveto));
        togglePageState("enable");
      }
    }
    
    
    
    

}


function gohome(element) {
 
  var motor = {
    gohome: "gohome",
    type: element.id
  }
  console.log(element.id);
  websocket.send(JSON.stringify(motor));
  togglePageState("enable");
}
function savecalb(type) {
  var correctfilterstep = document.getElementById('filterstep').textContent;
  var correctgratingstep = document.getElementById('gratingstep').textContent;
  var correctwave = document.getElementById('filterwave').textContent;


if(type=='filter'){
  var savethis = {
    savethis: 'save-filter-step-'+correctfilterstep,
    wavelength: 'save-filter-wave-'+correctwave,
  }
  console.log(savethis);
  websocket.send(JSON.stringify(savethis));
}
if(type=='grating'){
  var savethis = {
    savethis: 'save-grating-step-'+correctgratingstep,
    wavelength: 'save-grating-wave-'+correctwave,
  }
  console.log(savethis);
  websocket.send(JSON.stringify(savethis));

}
  
}





/**------------------------------------------------------------------------
 * ==================== photodetector ==========================
 *------------------------------------------------------------------------**/ 
//ui function to display the current slider value
function updategain(target){
  console.log(target.value);
  console.log(target.id);
  if(target.id=="CurrentSampleGain"){
    var display=document.getElementById('SampleGain');
    display.textContent=target.value;
  
  }
  else if(target.id=="CurrentRefGain"){
    var display=document.getElementById('RefGain');
    display.textContent=target.value;

  }
  
}




//send the new value pot to esp
function sendnewgain(type){
  if(type=="sample"){
    var currentgain= document.getElementById('CurrentSampleGain');  
  }
  else if(type=="ref"){
    var currentgain= document.getElementById('CurrentRefGain');
  }
  
  console.log(currentgain.value);
  var gaain={
    newgain:currentgain.value,
    gaintype:type,
  }
  console.log(gaain);
  websocket.send(JSON.stringify(gaain));
}

//gain calcualtions
function gainaccurecy(){
  var Refdigital =parseInt(document.getElementById('RefGain').innerText);
  var Sampledigital =parseInt(document.getElementById('SampleGain').innerText);
  document.getElementById("CurrentRefGain").value=Refdigital;
  document.getElementById("CurrentSampleGain").value=Sampledigital;
  
  var smallref = parseInt(document.getElementById('smallref').innerText);
  var largeref = parseInt(document.getElementById('largeref').innerText);
  var smallmes = parseInt(document.getElementById('smallmes').innerText);
  var largemes = parseInt(document.getElementById('largemes').innerText);
  var calcgain1= largemes/smallmes;
  var calcgain2=largeref/smallref;
  var meserror=parseFloat(calcgain1/Sampledigital )*100;
  var referror=parseFloat(calcgain2/Refdigital )*100;
  document.getElementById('calcgainref').innerText=calcgain2.toFixed(2);
  document.getElementById('calcgainmes').innerText=calcgain1.toFixed(2);
  document.getElementById('gainerrorref').innerText=referror.toFixed(2);
  document.getElementById('gainerrormes').innerText=meserror.toFixed(2);
  
}

gainaccurecy();

//direct cmd
function SendCMD(){
  var command =document.getElementById("commandinput").value;
  var CMD={
    DirectCommand:command,
  }
  websocket.send(JSON.stringify(CMD));

}

/*=======================================================================end of section 4=======================================================*/ 



/*======================================================================== Login section 5 =====================================================*/
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
  /*========================================================= END OF section 5===============================================================*/