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



document.getElementById('li1').classList.add('active');
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