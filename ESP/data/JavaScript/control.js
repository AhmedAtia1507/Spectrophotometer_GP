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
  redirectToLoginPage();
  sendStatus(); //send components stutus upon open
  loadtime(); //send current time time upon open
}

function onClose(event) {

  console.log("Connection closed");
  setTimeout(initWebSocket, 2000);
}

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
function sendStatus() {
  var vilampstutus = {
    vilampstutus: "send",
  };
  websocket.send(JSON.stringify(vilampstutus));

  var uvlampstutus = {
    uvlampstutus: "send",
  };
  websocket.send(JSON.stringify(uvlampstutus));
  var supplystutus = {
    supplystutus: "send",
  };
  websocket.send(JSON.stringify(supplystutus));
  var motors = {
    motors: "send",
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
        document.getElementById("li" + J).innerHTML = "Test tab";
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
setInterval(sendStatus, 5000);
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
      var check = document.getElementById("uvcheck");
      var thumb = document.getElementById("uvthumb");
      check.style.background = "green";
      thumb.style.transform = "translateX(20px)";
    } else if (myObj.uvstutus == "off") {
      console.log("uv lamp is off");
      document.getElementById("uvstate").innerHTML = "off";
      document.getElementById("uvstate").style.color = "white";
      document.getElementById("uvstate").style.background = "red";
      var check = document.getElementById("uvcheck");
      var thumb = document.getElementById("uvthumb");
      check.style.background = "red";
      thumb.style.transform = "translateX(0px)";
    } else {
      document.getElementById("uvstate").innerHTML =
        "error ocurred reload page";
    }
  } else if (myObj.hasOwnProperty("vistutus")) {
    if (myObj.vistutus === "on") {
      console.log("lamp is working fine");
      document.getElementById("vistate").innerHTML = "on";
      document.getElementById("vistate").style.color = "white";
      document.getElementById("vistate").style.background = "green";
      var check = document.getElementById("vicheck");
      var thumb = document.getElementById("vithumb");
      check.style.background = "green";
      thumb.style.transform = "translateX(20px)";
    } else if (myObj.vistutus == "off") {
      console.log("vi lamp is off");
      document.getElementById("vistate").innerHTML = "off";
      document.getElementById("vistate").style.color = "white";
      document.getElementById("vistate").style.background = "red";
      var check = document.getElementById("vicheck");
      var thumb = document.getElementById("vithumb");
      check.style.background = "red";
      thumb.style.transform = "translateX(0)";
    } else {
      document.getElementById("vistate").innerHTML =
        "error occured reload page";
    }
  } else if (myObj.hasOwnProperty("supplystutus")) {
    console.log("supplies recieved");
    document.getElementById("p12").textContent = myObj.p12;
    document.getElementById("n12").textContent = myObj.n12;
    document.getElementById("p5").textContent = myObj.p5;
    document.getElementById("p33").textContent = myObj.p33;
    document.getElementById("twelve").textContent = myObj.twelve;
  }
  else if (myObj.hasOwnProperty("currenttime")) {
    updateDateTime(myObj.currenttime);
    console.log("lllllllllllllllllllllllllllllaa");
  }
  else if (myObj.hasOwnProperty("timeupdated")) {
    var display = document.getElementById("timeupdated")
    display.style.color = "green"
    display.innerHTML = myObj.timeupdated;
    setTimeout(function () {
      document.getElementById("timeupdated").innerHTML = "";
    }, 4000);
  }
  else if (myObj.hasOwnProperty("motorssteps")) {
    console.log(myObj.motorssteps)
    const ary = myObj.motorssteps.split('-');
    document.getElementById("lampstep").textContent = ary[0];
    document.getElementById("gratingstep").textContent = ary[1];
    document.getElementById("filterstep").textContent = ary[2];
    document.getElementById("filterwave").textContent = ary[3];
    syncstep();
  }
  else if (myObj.hasOwnProperty("detector")) {
    console.log(myObj.detector)
    document.getElementById("detector").textContent = myObj.detector;
  }
  else if (myObj.hasOwnProperty("gohome")) {

    console.log(myObj);
    if (myObj.type == 'lampmotorhome') {
      console.log("lammmmmp");
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
    togglePageState();
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
  }
  else if (myObj.hasOwnProperty("motermoved")) {
    togglePageState();

  }
}

/**------------------------------------------------------------------------
 * ====================  Date and Time==========================
 *------------------------------------------------------------------------**/

// Get current date and time to initillaize the time data inputs to browser time
const currentDateTime = new Date();
const currentDate = currentDateTime.toISOString().split("T")[0];
document.getElementById("datepicker").value = currentDate;

function loadtime() {
  var loadtime = {
    loadtime: "loadtime",
  };
  // Assuming 'websocket' is your WebSocket object
  websocket.send(JSON.stringify(loadtime));
}


function saveDateTime() {
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

//sechronize current step with input
function syncstep() {
  var filterStepText = document.getElementById("filterstep").innerText;
  var filterStepNumber = parseInt(filterStepText, 10); // or parseFloat for decimal numbers
  document.getElementById("increasestep").value = filterStepNumber;
}




function validat(min, max) {
  var inputElement = document.getElementById('increasestep');
  var currentValue = parseInt(inputElement.value);
  if (currentValue < min) {
    inputElement.value = min;
  }
  else if (currentValue > max) {
    inputElement.value = max;
  }
  if (currentValue) {
    var latsetstep = document.getElementById('increasestep').value
    console.log(latsetstep);
    var moveto = {
      movemoter: "movto-" + latsetstep,
    };
    togglePageState();
    websocket.send(JSON.stringify(moveto));

  }
}


function gohome(element) {
  togglePageState();

  var motor = {
    gohome: "gohome",
    type: element.id
  }
  console.log(element.id);
  websocket.send(JSON.stringify(motor));
}
function savecalb() {
  var correctstep = document.getElementById('filterstep').textContent;
  var correctwave = document.getElementById('filterwave').textContent;

  console.log(correctstep);
  var savethis = {
    savethis: 'savestep-' + correctstep,
    wavelength: 'savewave-' + correctwave,
  }
  websocket.send(JSON.stringify(savethis));
}


//function to wait for the motor to move
function togglePageState() {
  var overlay = document.getElementById('overlay');
  overlay.style.display = (overlay.style.display === 'none') ? 'block' : 'none';
}
togglePageState();