const fs = require('fs');

// Define the file path using forward slashes or escaped backslashes
const filePath = 'data/JavaScript/readings.txt';

// Read the file asynchronously
fs.readFile(filePath, 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }

    // Split the file content by newline character
    let lines = data.split('\n');

    // Initialize arrays to store x and y values
    let xValues = [];
    let yValues = [];

    // Iterate through each line
    lines.forEach((line, index) => {
        // Split the line by whitespace
        let parts = line.split(/\s+/); // Use regex to split by any whitespace

        // Ensure that the line has at least two parts
        if (parts.length >= 2) {
            // Parse the values and push them into respective arrays
            let x = parseFloat(parts[0]);
            let y = parseFloat(parts[1]);

            // Check if both x and y are valid numbers
            if (!isNaN(x) && !isNaN(y)) {
                xValues.push(x);
                yValues.push(y);
            } else {
                console.warn(`Invalid values in line ${index + 1}: ${line}`);
            }
        } else {
            console.warn(`Invalid format in line ${index + 1}: ${line}`);
        }
    });

    // Convert arrays to stringified JSON
    const xValuesJSON = JSON.stringify(xValues);
    const yValuesJSON = JSON.stringify(yValues);

    // Write xValues to a file
    fs.writeFile('xValues.txt', xValuesJSON, err => {
        if (err) {
            console.error('Error writing xValues file:', err);
        } else {
            console.log('xValues file has been saved successfully.');
        }
    });

    // Write yValues to a file
    fs.writeFile('yValues.txt', yValuesJSON, err => {
        if (err) {
            console.error('Error writing yValues file:', err);
        } else {
            console.log('yValues file has been saved successfully.');
        }
    });
});
