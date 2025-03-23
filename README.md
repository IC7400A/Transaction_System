
# 🌐 Transaction System

A **Transaction System** implemented in **C++** and **C**, with an interactive **Node.js Web Interface**.

---

## 📂 Project Structure
```
Transaction_System/
│
├── src/           # C/C++ Source Files
├── include/       # Header Files
├── web/           # Node.js Web Interface
└── README.md      # Project Documentation
```

---

## 🚀 Running the Web Interface

### 📌 Step 1: Navigate to the `web` Directory
```bash
cd web
```

### 📌 Step 2: Initialize the Project (One Time Only)
```bash
npm init -y
```

### 📌 Step 3: Install Required Packages
```bash
npm install express cors child_process
```

---

## ✅ Starting the Web Server

### 🔥 Default Run (Port 3000)
```bash
node server.js
```
- The server will run on **http://localhost:3000**

---

## 🌟 Running on a Custom Port (Optional)

You can run **multiple instances** of the server by specifying different ports:

```bash
node server.js <desired_port>
```

Example:
```bash
node server.js 4000
```
- The server will run on **http://localhost:4000**

---

## 📝 Notes
- The web server acts as a bridge between the browser and your **C/C++ Transaction System** binary.
- Default port is `3000` if no port is specified.
- Multiple instances can run simultaneously on different ports.

---

## 💻 Technologies Used
- **C/C++**
- **Node.js**
- **Express.js**
- **CORS**
- **child_process module**

---

## 📖 Example Usage
```bash
cd web
npm install
node server.js
```
Visit: **http://localhost:3000**

---

## 📧 Contact
For any issues or contributions, feel free to open a pull request or issue.

---
