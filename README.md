# FalconOS Lite – Simulated Operating System 🖥️

A terminal-based simulated Operating System built in C++. This project demonstrates key OS functionalities such as user authentication, file handling, task management, and basic system utilities — all implemented from scratch for educational purposes.

This project was completed as part of the **Operating Systems Lab** course at FAST NUCES.

---

## 📌 Project Overview

FalconOS Lite simulates a mini operating system with command-line interaction, mimicking features found in real operating systems like:

- Multilevel queue scheduling
- User role-based command execution
- File and directory operations
- Simulated task manager and system statistics
- Process and memory simulation

---

## 🚀 Key Features

### 🔐 User Login System
- Username-password based login
- Separate privileges for **Admin** and **Guest** users

### 💻 Custom Shell
- Interactive terminal interface
- Interprets user commands based on access level

### 📁 File & Directory Management
- Create, open, write, delete files
- List directory contents and navigate file system

### 🧠 Process Simulation
- Basic process management
- View and terminate processes (Admin-only)

### ⚙️ System Utilities
- Display current system time and uptime
- Monitor system memory usage and status

### 👥 User Management
- Admins can create/delete users
- Change passwords and manage user sessions

---

## 🏗️ Tech Stack

- **Language:** C++
- **Interface:** Command Line (CLI)
- **Platform:** Ubuntu (tested using VMware)
- **IDE/Tools:** Visual Studio Code / g++

---

## 🛠️ How to Run the Project

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/falconos-lite.git
cd falconos-lite
