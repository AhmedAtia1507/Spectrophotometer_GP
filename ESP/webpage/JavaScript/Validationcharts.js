/**========================================================================
 *                           Chart
 *========================================================================**/
/* 
PUT THIS IN HTML : <canvas id="chartScan" style="height: 95%; width: 95%;"></canvas>
*/
var chartScan;
let chartData;
const ctxVal = document.getElementById('chartScan').getContext('2d');
chartScan = new Chart(ctxVal, {
  type: 'line',
  data: chartData,
  options: {
    tooltips: {
      enabled: false
    },
    animation: {
      duration: 0
    },
    responsive: false,
    maintainAspectRatio: false,
    plugins: {
      crosshair: {
        tooltips: {
          enabled: false // Disable tooltips for the crosshair
      },
        sync: {
          enabled: true // Enable crosshair synchronization between multiple charts
        },
        zoom: {
          enabled: true // Enable crosshair zooming along the axis
        },
        line: {
          color: 'blue', // Crosshair line color
          width: 1 // Crosshair line width
        }
      },
     
    },
    scales: {
      x: {
        // min: 190,
        // max: 1100,
        type: 'linear',
        position: 'bottom'
      },
      y: {
        type: 'linear',
        position: 'left'
      }
    },
    onHover: null // Disable the default onHover behavior
  }
});
function addCurve(xData, yData, color, curveName, fillCurve = false, drawMode = 'curve') {
  // Check if the curve already exists
  const existingCurveIndex = chartScan.data.datasets.findIndex(dataset => dataset.label === curveName);

  // If the curve exists, update its data
  if (existingCurveIndex !== -1) {
    chartScan.data.datasets[existingCurveIndex].data = drawMode === 'curve' ? 
      xData.map((x, index) => ({ x: x, y: yData[index] })) : // Draw curve
      xData.map((x, index) => ({ x: x, y: yData[index], showLine: false })); // Draw separate points
    
    chartScan.data.datasets[existingCurveIndex].borderColor = color;
    chartScan.data.datasets[existingCurveIndex].backgroundColor = fillCurve ? 'rgba(255, 0, 0, 0.3)' : undefined;
    chartScan.data.datasets[existingCurveIndex].showLine = drawMode !== 'points'; // Don't connect points if drawing separate points
  } else { // If the curve does't exist, add it
    var curveData = drawMode === 'curve' ? 
      xData.map((x, index) => ({ x: x, y: yData[index] })) : // Draw curve
      xData.map((x, index) => ({ x: x, y: yData[index], showLine: false })); // Draw separate points
    
    var dataset = {
      label: curveName,
      data: curveData,
      borderColor: color,
      borderWidth: 2,
      pointRadius: drawMode === 'points' ? 5 : 0, // Set point radius if drawing points
      lineTension: drawMode === 'points' ? 0 : 0.4, // Set line tension if drawing points
      showLine: drawMode !== 'points' // Don't connect points if drawing separate points
    };

    if (fillCurve) {
      dataset.fill = 'origin';
      dataset.backgroundColor = 'rgba(255, 0, 0, 0.3)';
    }

    chartScan.data.datasets.push(dataset);
  }

  chartScan.update(); // Update the chart
}




// funcation to remove all curves in chart js
function removeAllCurves() {
  chartScan.data.datasets = [];
  chartScan.update();
}

////////////////////////////////scan///////////////
var absorptionData = [];
var concentrationData = [];
var chart;
updateChart();

function addPoint() {
  var absorptionValue;
  var concentrationValue = parseFloat(document.getElementById("concentration").value);
  var WLine = document.getElementById("WLine").value; // get wavelength
  const message = { // message for websocket
    command: 'Scan',
    startInput: 100,
    stopInput: 200,
    stepInput: 2
  };
  websocket.send(JSON.stringify(message)); // websocket sent
  websocket.onmessage = function (event) { // WebSocket onmessage event
    const data = JSON.parse(event.data);
    console.log(event.data); // for test
    const currentTime = data.currentTime;
    const wavelength = data.wavelength;
    const intensityReference = data.intensityReference;
    const intensitySample = data.intensitySample;
    absorptionValue = Math.log10(intensityReference / intensitySample);
    addCurve(wavelength, intensitySample, black, Intensity, fillCurve = false, drawMode = 'curve');
  };
}

