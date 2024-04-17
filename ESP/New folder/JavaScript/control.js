/*
section 1 : intialize the websocket connection and handles login stuff (done)
section 2 : handles the webpage ui (ongoing)
section 3 : handles user messages (ongoing)
*/

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
document.getElementById("li1").classList.add("active");
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
  
  // asks the server if the user have logged in or not
  //redirectToLoginPage();
  //senduvStatus();
  //sendviStatus();

}

function onClose(event) {

  console.log("Connection closed");
  setTimeout(initWebSocket, 2000);
}
//function to wait for the motor to move
function togglePageState(enable) {
  var overlay = document.getElementById('overlay');
  overlay.style.display = (overlay.style.display === 'none') ? 'block' : 'none';
}
togglePageState("first");

document.querySelector("nav").addEventListener("mouseover", delayedShowNav);
document.getElementById("li0").addEventListener("mouseover", delayedShowNav2);
document.getElementById("li0").addEventListener("mouseout", delayedhideNav);
document.querySelector("nav").addEventListener("mouseout", delayedhideNav);
let hoverTimeout;
let outTimeout;
function delayedShowNav() {
  // Set a new timeout
  if (document.querySelector("nav").style.opacity == 1) {
    clearTimeout(outTimeout);
    hoverTimeout = setTimeout(function () {
      showNav();
    }, 300);
  } // 300 milliseconds delay
}
function delayedShowNav2() {
  // Set a new timeout
  clearTimeout(outTimeout);
  hoverTimeout = setTimeout(function () {
    showNav();
  }, 300); // 300 milliseconds delay
}
function delayedhideNav() {
  clearTimeout(hoverTimeout);
  outTimeout = setTimeout(() => {
    hideNav(); // Execute hideNav() after 200ms when mouse leaves
  }, 300);
}
//function to ask the server to send the lamps stutus
//future stustus like supplies stutus can be placed her
function sendviStatus() {
  var vilampstutus = {
    vilampstutus: "send",
  };
  websocket.send(JSON.stringify(vilampstutus));
}

function senduvStatus(){
  var uvlampstutus = {
    uvlampstutus: "send",
  };
  websocket.send(JSON.stringify(uvlampstutus));
}
function sendsupplystutus(){
  var supplystutus = {
    supplystutus: "send",
  };
  websocket.send(JSON.stringify(supplystutus));
  
}
function sendmoterssteps(){
  var motors = {
    motors: "send",
  };
  websocket.send(JSON.stringify(motors));
}
function sendLampmoter(){
  var motors = {
    lampmotor: "send",
  };
  websocket.send(JSON.stringify(motors));
  
}





//ui function
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

document.getElementById("uvin").addEventListener("change", toggleuv);
document.getElementById("viin").addEventListener("change", togglevi);
//ui function
function toggleuv() {
  if (document.getElementById("uvstate").innerHTML === "on") {
    var turnuvoff = {
      turnuvoff: "turnoff",
    };
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnuvoff));
  } else {
    var turnuvon = {
      turnuvon: "turnon",
    };
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnuvon));
  }
}

//ui function
function togglevi() {
  
  if (document.getElementById("vistate").innerHTML === "on") {
    var turnvioff = {
      turnvioff: "turnoff",
    };
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnvioff));
  } else {
    var turnvion = {
      turnvion: "turnon",
    };
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnvion));
  }
}

var curruntstate = "none";

//ui function
hidelabel(); //intially shrink the sidebar
let menu = document.getElementById("li0");
menu.addEventListener("click", togglemenu);

function showNav() {
  const navElement = document.querySelector("nav");

  navElement.style.width = "30%";
  navElement.style.opacity = "1";
  menu.style.backgroundColor = "#33324e";
  menu.style.textAlign = "center";
  menu.style.width = "calc(30% - 20px)";
  showlabel();
}
//ui function
function hideNav() {
  clearTimeout(hoverTimeout);
  const navElement = document.querySelector("nav");
  if (curruntstate === "none") {
    navElement.style.width = "0%";
    navElement.style.opacity = "0";
    menu.style.backgroundColor = "#ccc9c9";
    menu.style.textAlign = "left";
    menu.style.width = "fit-content";
    hidelabel();
  } else {
    navElement.style.width = "30%";
    navElement.style.opacity = "1";
    menu.style.backgroundColor = "#33324e";
    menu.style.textAlign = "center";
    menu.style.width = "calc(30% - 20px)";
    showlabel();
  }
}
//ui function
function togglemenu() {
  const navElement = document.querySelector("nav");
  if (curruntstate === "block") {
    navElement.style.width = "0%";
    menu.style.backgroundColor = "#ccc9c9";
    menu.style.textAlign = "left";
    menu.style.width = "fit-content";
    navElement.style.opacity = "0";
    hidelabel();
  } else {
    navElement.style.width = "30%";
    navElement.style.opacity = "1";
    showlabel();
    menu.style.backgroundColor = "#33324e";
    menu.style.textAlign = "center";
    menu.style.width = "calc(30% - 20px)";
    curruntstate = "block";
  }
}
//ui function
function hidelabel() {
  document.querySelector(".container").style.opacity = "0";
  curruntstate = "none";
  for (let i = 1; i <= 6; i++) {
    document.getElementById("li" + i).innerHTML = "";
  }
}

//ui function
function showlabel() {
  for (let J = 1; J <= 6; J++) {
    switch (J) {
      case 1:
        document.getElementById("li" + J).innerHTML = "Lamps test";
        break;
      case 2:
        document.getElementById("li" + J).innerHTML = "Supplies";
        break;
      case 3:
        document.getElementById("li" + J).innerHTML = "Motors";
        break;
      case 4:
        document.getElementById("li" + J).innerHTML = "Detector";
        break;
      case 5:
        document.getElementById("li" + J).innerHTML = "Date and Time";
        break;
      case 6:
        document.getElementById("li" + J).innerHTML = "Direct command";
        break;
    }
  }
  document.querySelector(".container").style.opacity = "1";
}

function redirectToLoginPage() {
  var login = {
    flag: "islogin?",
  };
  websocket.send(JSON.stringify(login));
}

// Set interval to run every 5 seconds (5000 milliseconds)
//setInterval(sendStatus, 5000);
function login() {
  window.location.href = "login.html";
}

//open a session for 20 minutes after this period user need to login again
setInterval(redirectToLoginPage, 1200000);

function handleMessage(event) {
  var myObj = JSON.parse(event.data);
  console.log(myObj);
  if (myObj.hasOwnProperty("flag")) {
    console.log("flag is sent");
    if (myObj.flag === true) {
      console.log("flag is true");
    } else {
      console.log("flag is false");
      login();
    }
  } else if (myObj.hasOwnProperty("uvstutus")) {
    if (myObj.uvstutus === "on") {
      console.log("lamp is working fine");
      document.getElementById("uvstate").innerHTML = "on";
      document.getElementById("uvstate").style.color = "white";
      document.getElementById("uvstate").style.background = "green";

      document.getElementById("uvstate2").innerHTML = "on";
      document.getElementById("uvstate2").style.color = "white";
      document.getElementById("uvstate2").style.background = "green";
      
      var check = document.getElementById("uvcheck");
      var thumb = document.getElementById("uvthumb");
      check.style.background = "green";
      thumb.style.transform = "translateX(20px)";
    } else if (myObj.uvstutus == "off") {
      console.log("uv lamp is off");
      document.getElementById("uvstate").innerHTML = "off";
      document.getElementById("uvstate").style.color = "white";
      document.getElementById("uvstate").style.background = "red";

      document.getElementById("uvstate2").innerHTML = "off";
      document.getElementById("uvstate2").style.color = "white";
      document.getElementById("uvstate2").style.background = "red";

      var check = document.getElementById("uvcheck");
      var thumb = document.getElementById("uvthumb");
      check.style.background = "red";
      thumb.style.transform = "translateX(0px)";
    } else {
      document.getElementById("uvstate2").innerHTML =
        "error ocurred reload page";
    }
  } else if (myObj.hasOwnProperty("vistutus")) {
    if (myObj.vistutus === "on") {
      console.log("lamp is working fine");
      document.getElementById("vistate").innerHTML = "on";
      document.getElementById("vistate").style.color = "white";
      document.getElementById("vistate").style.background = "green";
     
      document.getElementById("vistate2").innerHTML = "on";
      document.getElementById("vistate2").style.color = "white";
      document.getElementById("vistate2").style.background = "green";
     
      var check = document.getElementById("vicheck");
      var thumb = document.getElementById("vithumb");
      check.style.background = "green";
      thumb.style.transform = "translateX(20px)";
    } else if (myObj.vistutus == "off") {
      console.log("vi lamp is off");
      document.getElementById("vistate").innerHTML = "off";
      document.getElementById("vistate").style.color = "white";
      document.getElementById("vistate").style.background = "red";
      
      document.getElementById("vistate2").innerHTML = "off";
      document.getElementById("vistate2").style.color = "white";
      document.getElementById("vistate2").style.background = "red";
      
      var check = document.getElementById("vicheck");
      var thumb = document.getElementById("vithumb");
      check.style.background = "red";
      thumb.style.transform = "translateX(0)";
    } else {
      document.getElementById("vistate2").innerHTML =
        "error occured reload page";
    }
  } else if (myObj.hasOwnProperty("supplystutus")) {
    console.log("supplies recieved");
    document.getElementById("p12").textContent = myObj.p12;
    document.getElementById("n12").textContent = myObj.n12;
    document.getElementById("p5").textContent = myObj.p5;
    document.getElementById("p33").textContent = myObj.p33;
    document.getElementById("twelve").textContent = myObj.twelve;
    document.getElementById("suppliesvalues").textContent=myObj.supplystutus;
  }
  else if (myObj.hasOwnProperty("currenttime")) {
    updateDateTime(myObj.currenttime);
    
  }
  else if (myObj.hasOwnProperty("timeupdated")) {
    var display = document.getElementById("timeupdated")
    display.style.color = "green"
    display.innerHTML = myObj.timeupdated;
    setTimeout(function () {
      document.getElementById("timeupdated").innerHTML = "";
    }, 4000);
  }
  else if(myObj.hasOwnProperty("currenlamp")){
    
    var currenlamp=document.getElementById("currentlamp");
    currenlamp.innerHTML=myObj.currenlamp;
  }
  else if (myObj.hasOwnProperty("motorssteps")) {
    const ary = myObj.motorssteps.split('-');
    document.getElementById("lampstep").textContent = ary[0];
    document.getElementById("gratingstep").textContent = ary[1];
    document.getElementById("filterstep").textContent = ary[2];
    document.getElementById("filterwave").textContent = ary[3];
    document.getElementById("gratingmotorwl").value=parseFloat(ary[3]);
    document.getElementById("motorssteps").textContent=myObj.motorssteps;
    syncstep();
  }
  else if (myObj.hasOwnProperty("gohome")) {
    togglePageState("disable");
    if (myObj.type == 'lampmotorhome') {
      document.getElementById("lampstep").textContent = myObj.step;
      document.getElementById("filterwave").textContent = myObj.wavelength;
    }
    else if (myObj.type == 'gratingmotorhome') {
      document.getElementById("gratingstep").textContent = myObj.step;
      document.getElementById("filterwave").textContent = myObj.wavelength;
    }
    else if (myObj.type == 'filtermotorhome') {
      document.getElementById("filterstep").textContent = myObj.step;
      document.getElementById("filterwave").textContent = myObj.wavelength;
    }
    syncstep();
  }
  else if (myObj.hasOwnProperty("stepsaved")) {
    console.log(myObj.stepsaved);
    var display = document.getElementById("stepsaved");
    display.style.color = "green";
    display.textContent = myObj.stepsaved;
    setTimeout(function () {
      document.getElementById("stepsaved").innerHTML = "";
    }, 4000);
    
    var display2 = document.getElementById("stepsaved2");
    display2.style.color = "green";
    display2.textContent = myObj.stepsaved;
    setTimeout(function () {
      document.getElementById("stepsaved2").innerHTML = "";
    }, 4000);
    



  }
  else if (myObj.hasOwnProperty("motermoved")) {
    togglePageState("disable");

  }
  else if (myObj.hasOwnProperty("detreadings")){
    console.log(myObj.detreadings)
    const ary = myObj.detreadings.split('-');
    document.getElementById("smallref").textContent = ary[0];
    document.getElementById("largeref").textContent = ary[1];
    document.getElementById("smallmes").textContent = ary[2];
    document.getElementById("largemes").textContent = ary[3];
    document.getElementById("potgain").textContent = ary[4];
    document.getElementById('CMDdetect').textContent=myObj.detreadings;
    gainaccurecy();
  }
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
function toggleLamp(){
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
  document.getElementById('gainerrormes').innerText=meserror  ;
  


}
gainaccurecy();


showTab('tab3','li3');
