var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// Disable forward button
history.pushState(null, null, document.URL);
window.addEventListener('popstate', function () {
    history.pushState(null, null, document.URL);
});

// Init web socket when the page loads
window.addEventListener('load', onLoad);
window.addEventListener('DOMContentLoaded', onLoad);

function onLoad(event) {
    initWebSocket();

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
}

function onClose(event) {
    // in case connection down
    // try again after 2 sec
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
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


function handleMessage(event) {
    var myObj = JSON.parse(event.data);
    console.log(myObj);

    if (myObj.hasOwnProperty('username') && myObj.hasOwnProperty('password')) {
        // Check if the username and password are true
        if (myObj.username === true && myObj.password === true) {
            console.log("Login successful. Redirecting to control.html");
            // request control page
            window.location.href = "control.html";
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

