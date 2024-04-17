/*
section 1 : intialize the websocket connection and handles login stuff (done)
section 2 : handles the webpage ui (ongoing)
section 3 : handles user messages (ongoing)
*/

/**
 * intialize the websocket connection section
 */

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
  sendCurrentLoginFlag();                               // asks the server if the user have logged in or not
  senduvStatus();                                      // send us lamp stutus to diplay it on open 
  sendviStatus();                                      // send visible lamp stutus to diplay it on open  

}

function onClose(event) {
  console.log("Connection closed");
  setTimeout(initWebSocket, 2000);                    //try to connect every 2 sec
}

/**
 * handles the webpage ui section
 */


//Toggles the visibility of the overlay element
function togglePageState(enable) {
  var overlay = document.getElementById('overlay');
  overlay.style.display = (overlay.style.display === 'none') ? 'block' : 'none';
}

// should be toggled for the first time to work properly
togglePageState("first");

// // toggle the visibility of the side menu on mouse hover or click and add some delay to make it robust
// document.querySelector("nav").addEventListener("mouseover", delayedShowNav);
// document.getElementById("li0").addEventListener("mouseover", delayedShowNav2);
// document.getElementById("li0").addEventListener("mouseout", delayedhideNav);
// document.querySelector("nav").addEventListener("mouseout", delayedhideNav);

// //constats to determine the hover time
// let hoverTimeout;
// let outTimeout;

// function delayedShowNav() {
//   // Set a new timeout
//   if (document.querySelector("nav").style.opacity == 1) {
//     clearTimeout(outTimeout);
//     hoverTimeout = setTimeout(function () {
//       showNav();
//     }, 300);
//   } // 300 milliseconds delay
// }
// function delayedShowNav2() {
//   // Set a new timeout
//   clearTimeout(outTimeout);
//   hoverTimeout = setTimeout(function () {
//     showNav();
//   }, 300); // 300 milliseconds delay
// }
// function delayedhideNav() {
//   clearTimeout(hoverTimeout);
//   outTimeout = setTimeout(() => {
//     hideNav(); // Execute hideNav() after 200ms when mouse leaves
//   }, 300);
// }

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
function login() {
  window.location.href = "login.html";
}

//open a session for 20 minutes after this period user need to login again
setInterval(login, 1200000);


//at the begaining li1 is the lamp page which should be active
document.getElementById("li1").classList.add("active");


// function to show the tab content
function showTab(tabId, li_id) {

  // Hide all tabs
  document.getElementById("li1").classList.add("active");
  var tabs = document.getElementsByClassName("tab-content");
  for (var i = 0; i < tabs.length; i++) {
    tabs[i].classList.remove("active");
  }
  var list = document.getElementsByClassName("list");
  for (var i = 0; i < list.length; i++) {
    list[i].classList.remove("active");
  }
  // Show the selected tab
  document.getElementById(tabId).classList.add("active");
  document.getElementById(li_id).classList.add("active");
  switch (tabId) {
    case "tab1":
      break;
    case "tab2":
      sendsupplystutus();
      break;
    case "tab3":
      sendmoterssteps();
      sendLampmoter();
      break;
    case "tab4":
      senddetector();
      break;
    case "tab5":
      loadtime();
      break;
    case "tab6":
      break;
  }
}


// Add event listener for changes in UV or VI devices
document.getElementById("uvin").addEventListener("change", toggleLamp);
document.getElementById("viin").addEventListener("change", toggleLamp);
// Function to toggle UV or VI device
function toggleLamp() {
  // Determine which device triggered the event
  const deviceId = this.id === "uvin" ? "uv" : "vi";
  // Get the state element and current state of the device
  const stateElement = document.getElementById(`${deviceId}state`);
  const currentState = stateElement.innerHTML;
  // Define the command to be sent based on the current state
  const command = currentState === "on" ? { [`turn${deviceId}off`]: "turnoff" } : { [`turn${deviceId}on`]: "turnon" };
  // Send command via WebSocket
  console.log(command);
  websocket.send(JSON.stringify(command));
}

//it is a global variable that contains the current state of the nav sidbar 
var NavCurrentstate = "none";

hideLabels(); //intially shrink the sidebar
let menu = document.getElementById("li0");
menu.addEventListener("click", toggleMenu);

// UI function to toggle menu visibility and labels
function toggleMenu() {
  const navElement = document.querySelector("nav");
  const containerElement = document.querySelector(".container");

  // Determine the desired width and opacity of the navigation menu
  const desiredWidth = NavCurrentstate === "block" ? "0%" : "30%";
  const desiredOpacity = NavCurrentstate === "block" ? "0" : "1";

  // Set the width and opacity of the navigation menu
  navElement.style.width = desiredWidth;
  navElement.style.opacity = desiredOpacity;

  // Set the background color, text alignment, and width of the menu button
  menu.style.backgroundColor = NavCurrentstate === "block" ? "#ccc9c9" : "#33324e";
  menu.style.textAlign = NavCurrentstate === "block" ? "left" : "center";
  menu.style.width = NavCurrentstate === "block" ? "fit-content" : "calc(30% - 20px)";

  // Toggle the visibility of labels in the container
  containerElement.style.opacity = NavCurrentstate === "block" ? "0" : "1";
  NavCurrentstate = NavCurrentstate === "block" ? "none" : "block";

  // Update the labels based on the current state
  if (NavCurrentstate === "block") {
    showLabels();
  } else {
    hideLabels();
  }
}

// Function to hide labels in the container
function hideLabels() {
  for (let i = 1; i <= 6; i++) {
    document.getElementById("li" + i).innerHTML = "";
  }
}

// Function to show labels in the container
function showLabels() {
  const labels = ["Lamps test", "Supplies", "Motors", "Detector", "Date and Time", "Direct command"];
  for (let j = 1; j <= 6; j++) {
    document.getElementById("li" + j).innerHTML = labels[j - 1];
  }
}





/**
 * handles the webpage ui section
 */

function handleMessage(event) {
  var myObj = JSON.parse(event.data);
  console.log(myObj);

  if (myObj.hasOwnProperty("flag")) {
    console.log("flag is sent");
    if (myObj.flag) {
      console.log("flag is true");
    } else {
      console.log("flag is false");
      login();
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
  }
}

function handleLampStatus(myObj) {
  var lampType = myObj.hasOwnProperty("uvstutus") ? "uv" : "vi";
  var stateElement = document.getElementById(lampType + "state");
  var stateElement2 = document.getElementById(lampType + "state2");

  if (myObj[lampType + "stutus"] === "on") {
    console.log("lamp is working fine");
    stateElement.innerHTML = "on";
    stateElement.style.color = "white";
    stateElement.style.background = "green";

    stateElement2.innerHTML = "on";
    stateElement2.style.color = "white";
    stateElement2.style.background = "green";
    
    var check = document.getElementById(lampType + "check");
    var thumb = document.getElementById(lampType + "thumb");
    check.style.background = "green";
    thumb.style.transform = "translateX(20px)";
  } else if (myObj[lampType + "stutus"] === "off") {
    console.log(lampType + " lamp is off");
    stateElement.innerHTML = "off";
    stateElement.style.color = "white";
    stateElement.style.background = "red";

    stateElement2.innerHTML = "off";
    stateElement2.style.color = "white";
    stateElement2.style.background = "red";

    var check = document.getElementById(lampType + "check");
    var thumb = document.getElementById(lampType + "thumb");
    check.style.background = "red";
    thumb.style.transform = "translateX(0px)";
  } else {
    stateElement2.innerHTML = "error occurred, reload page";
  }
}

function handleSupplyStatus(myObj) {
  console.log("supplies received");
  document.getElementById("p12").textContent = myObj.p12;
  document.getElementById("n12").textContent = myObj.n12;
  document.getElementById("p5").textContent = myObj.p5;
  document.getElementById("p33").textContent = myObj.p33;
  document.getElementById("twelve").textContent = myObj.twelve;
  document.getElementById("suppliesvalues").textContent = myObj.supplystutus;
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
  document.getElementById("motorssteps").textContent = myObj.motorssteps;
  syncstep();
}

function handleGoHome(myObj) {
  togglePageState("disable");
  const type = myObj.type.replace("motorhome", "step");
  document.getElementById(type).textContent = myObj.step;
  document.getElementById("filterwave").textContent = myObj.wavelength;
  syncstep();
}

function handleStepSaved(message) {
  console.log(message);
  var display = document.getElementById("stepsaved");
  display.style.color = "green";
  display.textContent = message;
  setTimeout(function () {
    display.innerHTML = "";
  }, 4000);

  var display2 = document.getElementById("stepsaved2");
  display2.style.color = "green";
  display2.textContent = message;
  setTimeout(function () {
    display2.innerHTML = "";
  }, 4000);
}

function handleDetReadings(detReadings) {
  console.log(detReadings);
  const ary = detReadings.split('-');
  document.getElementById("smallref").textContent = ary[0];
  document.getElementById("largeref").textContent = ary[1];
  document.getElementById("smallmes").textContent = ary[2];
  document.getElementById("largemes").textContent = ary[3];
  document.getElementById("potgain").textContent = ary[4];
  document.getElementById('CMDdetect').textContent = detReadings;
  gainaccurecy();
}

/**------------------------------------------------------------------------
 * ====================  Date and Time==========================
 *------------------------------------------------------------------------**/

// Get current date and time to initillaize the time data inputs to browser time
const currentDateTime = new Date();
const currentDate = currentDateTime.toISOString().split("T")[0];
document.getElementById("datepicker").value = currentDate;

const currentDateTime2 = new Date();
const currentDate2 = currentDateTime2.toISOString().split("T")[0];
document.getElementById("datepicker2").value = currentDate2;

function loadtime() {
  var loadtime = {
    loadtime: "loadtime",
  };
  // Assuming 'websocket' is your WebSocket object
  websocket.send(JSON.stringify(loadtime));
}


function saveDateTime(target) {

  if(target.classList.value==="page"){
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
else{
  console.log(target.classList.value);
  const selectedDate2 = new Date(document.getElementById("datepicker2").value);
  const selectedTime2 = document.getElementById("timepicker2").value;
  const dateTimeString2 = `${selectedDate2.toLocaleDateString().split("T")[0].replace(/-/g, '/')} ${selectedTime2}`;
  console.log(dateTimeString2);

  var updatetime = {
    updatetime: dateTimeString2,
  };
  // Assuming 'websocket' is your WebSocket object
  websocket.send(JSON.stringify(updatetime));
  loadtime();

}
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

//sechronize current step with input
function syncstep() {
  var filterStepText = document.getElementById("filterstep").innerText;
  var filterStepNumber = parseInt(filterStepText, 10); 
  document.getElementById("increasestep").value = filterStepNumber;
  document.getElementById("increasestep2").value = filterStepNumber;
}




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


let i=0
function moveto(event){
  console.log(event.target.id);
  console.log(i);
  i++;
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
  if (targetevent.inputType === 'insertText') {
  }

else {
    if (targetevent.target.classList.value==="page") {
      if(targetevent.target.innerHTML !== "Select"){
      var lateststep = document.getElementById('increasestep').value
      console.log(lateststep);
      }
      else{
        var selectElement = document.getElementById("filterselector");
        var lateststep = selectElement.value;
        console.log(lateststep);
      }
    }
    else{
      if(targetevent.target.innerHTML !=="Select"){
        var lateststep = document.getElementById('increasestep2').value
        console.log(lateststep);
        }
        else{
          var selectElement = document.getElementById("filterselector2");
          var lateststep = selectElement.value;
          console.log(lateststep);
        }
      }
    if(lateststep){
      var moveto = {
        movemoter: "set-filtermoter-to-" + lateststep,
      };
      togglePageState("enable");
      websocket.send(JSON.stringify(moveto));
  
    }

    }

}

function movegratingmoter(targetevent){
  if (targetevent.inputType === 'insertText') {
    // Input from the keyboard
    console.log("Input from keyboard: " + targetevent.target.value);
  }

  else {
    // Input from arrows
    console.log("Input from arrows: " + targetevent.target.value);
    // Add your additional logic for arrow input
    if (targetevent.target.classList.value==="page"&&targetevent.target.innerHTML !=="Select") {
      var lateststep = document.getElementById('gratingmotorwl').value
      console.log(lateststep);
    }
    else if(targetevent.target.innerHTML !=="Select"){
      var lateststep = document.getElementById('gratingmotorwl2').value
      console.log(lateststep);
    }

    if(lateststep){
      var moveto = {
        movemoter: "set-gratingmoter-to-" + lateststep,
      };
      
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
function savecalb(event) {
  console.log(event.classList.value);
  var correctstep = document.getElementById('filterstep').textContent;
  var correctwave = document.getElementById('filterwave').textContent;
  var correctstep2 = document.getElementById('increasestep2').value;
  var correctwave2 = document.getElementById('filterwave').textContent;

  if(event.classList.value==="page"){
  console.log(correctstep);
  var savethis = {
    savethis: 'savestep-' + correctstep,
    wavelength: 'savewave-' + correctwave,
  }
  websocket.send(JSON.stringify(savethis));
}
else{
  console.log(correctstep2);
  var savethis = {
    savethis: 'savestep-' + correctstep2,
    wavelength: 'savewave-' + correctwave2,
  }
  websocket.send(JSON.stringify(savethis));

}
}





/**------------------------------------------------------------------------
 * ==================== photodetector ==========================
 *------------------------------------------------------------------------**/ 
//ui function to display the current slider value
function updategain(target){
  console.log(target.value);
  var display=document.getElementById('gaain');
  display.textContent=target.value;

}


//read current detector values
function senddetector(){
  var detector={
    senddetector:"senddetector",
  }
  websocket.send(JSON.stringify(detector));
}



//send the new value pot to esp
function sendnewgain(){
  var currentgain= document.getElementById('currentgain');
  console.log(currentgain.value);
  var gaain={
    newgain:currentgain.value,
  }
  console.log(currentgain.value)
  websocket.send(JSON.stringify(gaain));
}

//gain calcualtions
function gainaccurecy(){
  var digital =parseInt(document.getElementById('potgain').innerText);
  var smallref = parseInt(document.getElementById('smallref').innerText);
  var largeref = parseInt(document.getElementById('largeref').innerText);
  var smallmes = parseInt(document.getElementById('smallmes').innerText);
  var largemes = parseInt(document.getElementById('largemes').innerText);
  var calcgain1= largemes/smallmes;
  var calcgain2=largeref/smallref;
  var meserror=parseFloat(calcgain1/digital )*100;
  var referror=parseFloat(calcgain2/digital )*100;
  document.getElementById('calcgainref').innerText=calcgain2;
  document.getElementById('calcgainmes').innerText=calcgain1;
  document.getElementById('gainerrorref').innerText=referror;
  document.getElementById('gainerrormes').innerText=meserror;
  
}

gainaccurecy();



