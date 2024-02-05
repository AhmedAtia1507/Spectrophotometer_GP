/*
section 1 : intialize the websocket connection and handles login stuff (done)
section 2 : handles the webpage ui (ongoing)
section 3 : handles user messages (ongoing)
*/


var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
document.getElementById('li1').classList.add('active');
// Init web socket when the page loads
window.addEventListener('load', onLoad);


function onLoad(event) {
    initWebSocket();
}

   // Function to redirect to the login page
   function redirectToLoginPage() {
    window.location.href = 'login.html'; 
}


function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    

    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    

    // Set onmessage handler after the WebSocket is opened
    websocket.onmessage = function (event) {
        handleMessage(event);
    };
}

function onOpen(event) {
    console.log('Connection opened');
    var login = {
        flag: "islogin?",
    }
    websocket.send(JSON.stringify(login));  // asks the server if the user have logged in or not 
    
    sendStatus();  //send lamp stutus upon open
}

function onClose(event) {
    // in case connection down
    // try again after 2 sec
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

document.querySelector('nav').addEventListener('mouseover', delayedShowNav);
document.getElementById('li0').addEventListener('mouseover', delayedShowNav2);
document.getElementById('li0').addEventListener('mouseout', delayedhideNav);
document.querySelector('nav').addEventListener('mouseout', delayedhideNav);
let hoverTimeout;
let outTimeout;
function delayedShowNav() {
    
    // Set a new timeout
    if(document.querySelector('nav').style.opacity==1){
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
        vilampstutus: "send"
    };
    websocket.send(JSON.stringify(vilampstutus));

    var uvlampstutus = {
        uvlampstutus: "send"
    };
    websocket.send(JSON.stringify(uvlampstutus));
}
// Set interval to run every 5 seconds (5000 milliseconds)
setInterval(sendStatus, 5000);
//open a session for 10 minutes after this period user need to login again
setInterval(redirectToLoginPage,600000);


//ui function
function showTab(tabId,li_id) {
    // Hide all tabs
    document.getElementById('li1').classList.add('active');
    var tabs = document.getElementsByClassName('tab-content');
    for (var i = 0; i < tabs.length; i++) {
        tabs[i].classList.remove('active');
    }
    var list = document.getElementsByClassName('list');
    for (var i = 0; i < list.length; i++) {
        list[i].classList.remove('active');
    }
    // Show the selected tab
    document.getElementById(tabId).classList.add('active');
    document.getElementById(li_id).classList.add('active');
}


document.getElementById('uvin').addEventListener('change',toggleuv);
document.getElementById('viin').addEventListener('change',togglevi);
//ui function
function toggleuv(){
if(document.getElementById("uvstate").innerHTML==='on'){
    var turnuvoff = {
        turnuvoff: "turnoff"
    }
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnuvoff));

} 
else {

    var turnuvon = {
        turnuvon: "turnon"
    }
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnuvon));

}
}


//ui function
function togglevi(){
if(document.getElementById("vistate").innerHTML==='on'){
    var turnvioff = {
        turnvioff: "turnoff"
    }
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnvioff));

} 
else {
    var turnvion = {
        turnvion: "turnon"
    }
    // Assuming 'websocket' is your WebSocket object
    websocket.send(JSON.stringify(turnvion));
}
}

var curruntstate="none";

//ui function
hidelabel(); //intially shrink the sidebar 
let menu= document.getElementById('li0');
menu.addEventListener('click',togglemenu)

function showNav() {
    const navElement = document.querySelector('nav');

    navElement.style.width="30%";
    navElement.style.opacity="1";
    menu.style.backgroundColor="#33324e";
    menu.style.textAlign="center";
    menu.style.width="calc(30% - 20px)";
    showlabel();
}
//ui function
function hideNav() {
    clearTimeout(hoverTimeout);
    const navElement = document.querySelector('nav');
    if(curruntstate==="none"){
        navElement.style.width="0%";
        navElement.style.opacity="0";
        menu.style.backgroundColor="#ccc9c9";
        menu.style.textAlign="left";
        menu.style.width="fit-content"
        hidelabel();
    }
    else{
        navElement.style.width="30%";
        navElement.style.opacity="1";
        menu.style.backgroundColor="#33324e";
        menu.style.textAlign="center";
        menu.style.width="calc(30% - 20px)";
        showlabel();
        }
    }
//ui function
function togglemenu() {
    const navElement = document.querySelector('nav');
    if (curruntstate==="block") {
        
        navElement.style.width="0%";
        menu.style.backgroundColor="#ccc9c9";
        menu.style.textAlign="left";
        menu.style.width="fit-content"
        navElement.style.opacity="0";
        hidelabel();

        
    } else {
        navElement.style.width="30%";
        navElement.style.opacity="1";
        showlabel();
        menu.style.backgroundColor="#33324e";
        menu.style.textAlign="center";
        menu.style.width="calc(30% - 20px)";
        curruntstate="block";
    }
}
//ui function
function hidelabel() {
    document.querySelector(".container").style.opacity='0';
    curruntstate="none";
    for(let i = 1; i <= 6; i++){
    document.getElementById("li"+i).innerHTML="";
}
}





//ui function
function showlabel(){
    
    
    for(let J = 1; J <= 6; J++){
        switch(J){
                    
            case 1:
                document.getElementById("li"+J).innerHTML="Lamps test";
                break;
            case 2:
                document.getElementById("li"+J).innerHTML="Supplies";
                break;
            case 3:
                document.getElementById("li"+J).innerHTML="Motors";
                break;
            case 4:
                document.getElementById("li"+J).innerHTML="Detector";
                break;
            case 5:
                document.getElementById("li"+J).innerHTML="Date and Time";
                break;
            case 6:
                document.getElementById("li"+J).innerHTML="Test tab";
                break;
        }
        
    }
    document.querySelector(".container").style.opacity='1';
}
function handleMessage(event) {    
    var myObj = JSON.parse(event.data);
    console.log(myObj);
    if(myObj.hasOwnProperty('flag')){
        console.log("flag is sent");
        if(myObj.flag===true)
        {
            console.log("flag is true");
        }
        else{
            console.log("flag is false");
            redirectToLoginPage()};


    }
    else if (myObj.hasOwnProperty('uvlampstutus') ) {
        
        if (myObj.uvlampstutus === 'on') {
            console.log("lamp is working fine");
            document.getElementById("uvstate").innerHTML="on";
            document.getElementById("uvstate").style.color='white';
            document.getElementById("uvstate").style.background='green';
            var check=document.getElementById('uvcheck');
            var thumb=document.getElementById('uvthumb');
            check.style.background='green';
            thumb.style.transform='translateX(20px)';


        
        } 
        else if(myObj.uvlampstutus=='off') {    
            console.log("uv lamp is off");
            document.getElementById("uvstate").innerHTML = "off";
            document.getElementById("uvstate").style.color='white';
            document.getElementById("uvstate").style.background='red';
            var check=document.getElementById('uvcheck');
            var thumb=document.getElementById('uvthumb');
            check.style.background='red';
            thumb.style.transform='translateX(0px)';
    
        
        }
        else{
            document.getElementById("uvstate").innerHTML = "error ocurred reload page";
        }
    } 
    else if (myObj.hasOwnProperty('vilampstutus') ) {
        
        if (myObj.vilampstutus === 'on') {
            console.log("lamp is working fine");
            document.getElementById("vistate").innerHTML="on";
            document.getElementById("vistate").style.color='white';
            document.getElementById("vistate").style.background='green';
            var check=document.getElementById('vicheck');
            var thumb=document.getElementById('vithumb');
            check.style.background='green';
            thumb.style.transform='translateX(20px)';

        } 
        else if(myObj.vilampstutus=='off') {    
            console.log("vi lamp is off");
            document.getElementById("vistate").innerHTML = "off";
            document.getElementById("vistate").style.color='white';
            document.getElementById("vistate").style.background='red';
            var check=document.getElementById('vicheck');
            var thumb=document.getElementById('vithumb');
            check.style.background='red';
            thumb.style.transform='translateX(0)';
            
        }
        else{
            document.getElementById("vistate").innerHTML = "error occured reload page";
        }
    } 
    }


