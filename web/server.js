const express = require('express');
const { spawn } = require('child_process');
const path = require('path');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

let binaryProcess = null;
let binaryOutput = '';

const binaryPath = path.join(__dirname, '../bin/transaction_system');

function startBinary() {
  binaryProcess = spawn(binaryPath, [], {
    cwd: path.join(__dirname, '../'),
    stdio: ['pipe', 'pipe', 'pipe']
  });

  binaryProcess.stdout.on('data', (data) => {
    console.log(`Binary output: ${data}`);
    binaryOutput += data.toString();
  });

  binaryProcess.stderr.on('data', (data) => {
    console.error(`Binary error: ${data}`);
    binaryOutput += data.toString();
  });

  binaryProcess.on('close', (code) => {
    console.log(`Binary exited with code ${code}`);
    binaryProcess = null;
  });
}

startBinary();

app.post('/api/send', (req, res) => {
  const userInput = req.body.input;
  if (binaryProcess) {
    binaryProcess.stdin.write(userInput + '\n');
    res.json({ status: 'Input sent' });
  } else {
    res.status(500).json({ error: 'Binary not running' });
  }
});
app.get('/api/output', (req, res) => {
  res.json({ output: binaryOutput });
  binaryOutput = ''; 
});
const PORT = process.env.PORT || process.argv[2] || 3000;
app.listen(PORT, () => {
  console.log(`✅ Server running at http://localhost:${PORT}`);
});
