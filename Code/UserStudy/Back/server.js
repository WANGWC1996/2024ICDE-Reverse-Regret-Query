const express = require('express');
const fs = require('fs');
const cors = require('cors');
const app = express();

// Use cors middleware and allow all origins
app.use(cors({ origin: '*' }));
app.options('*', cors());

app.use(express.json());

app.post('/save-text', (req, res) => {
    const userName = req.body.text1;
    const userEmail = req.body.text2;
    const fileContent1 = req.body.text3;
    const fileContent2 = req.body.text4;

    console.log(`Received Name: ${userName}`);
    console.log(`Received Email: ${userEmail}`);
    console.log(`Received fileContent1: ${fileContent1}`);
    console.log(`Received fileContent2: ${fileContent2}`);

    // Concatenate
    const combinedfilename = userName + '\n' + userEmail;
    const combinedContent = userName + '\n' + userEmail +'\n' + fileContent1 + '\n' + fileContent2;

    // Write the combinedContent to a file with fileName1
    fs.writeFile(`${combinedfilename}.txt`, combinedContent, err => {
        if (err) {
            console.error(err);
            res.status(500).json({ error: 'Failed to save file' });
        } else {
            res.status(200).json({ message: 'File saved successfully' });
        }
    });
});

// Define the port
const port = 4000;

// Listen on the defined port
app.listen(port, () => console.log(`HTTP Server is running on port ${port}`));  // Update this line
