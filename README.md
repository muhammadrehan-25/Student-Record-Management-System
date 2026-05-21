# 📚 Student Record Management System (C++ & Qt)

![C++](https://img.shields.io/badge/Language-C++-blue)
![Qt](https://img.shields.io/badge/Framework-Qt-green)
![CMake](https://img.shields.io/badge/Build-CMake-red)
![Status](https://img.shields.io/badge/Status-Active-brightgreen)

---

## 🌟 Project Description

This project is a desktop application developed as part of the **Project Based Learning (PBL)** course.

It provides a robust Graphical User Interface (GUI) tool to manage student records, including data entry, searching, updating, and viewing of existing information. The application is built using **C++** and the **Qt Framework**, making it cross-platform and professional in appearance.

---

## ✨ Key Features

* 🎓 **Student Registration** — Simple interface to add new student records
* 📋 **Data Listing** — View all student records in a clean tabular format
* 🔍 **Search Functionality** — Efficiently search students by ID or Name
* ✏️ **Update Records** — Edit and update existing student information
* 🗑️ **Delete Records** — Remove student entries when no longer needed
* 💾 **Persistent Data Storage** — Data is saved and loaded using `students.csv` and `students.txt`
* 🖥️ **Cross-Platform GUI** — Developed using the Qt Framework for a professional interface

---

## 🛠️ Technology Stack

| Component | Technology Used | Relevant Files |
| :--- | :--- | :--- |
| **Programming Language** | C++ (Standard) | `main.cpp`, `mainwindow.cpp` |
| **GUI Framework** | Qt Widgets (C++) | `mainwindow.h`, `mainwindow.ui` |
| **Build System** | CMake | `CMakeLists.txt` |
| **Data Storage** | CSV / Plain Text | `students.csv`, `students.txt` |

---

## 📁 Project Structure

```
StudentRecordSystem/
│
├── main.cpp              → Entry point of the application
├── mainwindow.cpp        → Main window logic and functionality
├── mainwindow.h          → Header file for main window
├── mainwindow.ui         → Qt Designer UI file
├── CMakeLists.txt        → CMake build configuration
├── students.csv          → Student data in CSV format
└── students.txt          → Student data in plain text format
```

---

## 🚀 Getting Started

### ✅ Prerequisites

Before running this project, make sure you have the following installed:

- **Qt Framework** (version 5.x or above) — [Download Qt](https://www.qt.io/download)
- **CMake** (version 3.x or above) — [Download CMake](https://cmake.org/download/)
- **Qt Creator IDE** (recommended) — comes with Qt installation

---

### 📥 Steps to Run

**Step 1 — Download the Code**
> Click the green **"<> Code"** button on this page and select **"Download ZIP"**

**Step 2 — Extract the ZIP**
> Extract the downloaded folder to your desired location on your computer

**Step 3 — Open Project in Qt Creator**
> Open **Qt Creator** → Go to **File** → **Open File or Project** → Select `CMakeLists.txt`

**Step 4 — Configure the Project**
> Qt Creator will ask you to configure the project → Click **"Configure Project"**

**Step 5 — Build the Project**
> Click the **Build** button or press `Ctrl + B` to compile the project

**Step 6 — Run the Application**
> Click the **Run** button or press `Ctrl + R` to launch the application

---

## 🖼️ Application Preview

```
+-----------------------------------------------+
|       Student Record Management System        |
+-----------------------------------------------+
|  [Add Student]  [View All]  [Search]          |
+-----------------------------------------------+
|  ID  |  Name        |  Course   |  Semester   |
|------|--------------|-----------|-------------|
|  001 |  Ali Hassan  |  CS       |  3rd        |
|  002 |  Sara Ahmed  |  SE       |  5th        |
+-----------------------------------------------+
```

---

## 📅 Development Log

| Date | Update |
| :--- | :--- |
| May 2025 | ✅ Project created — basic structure setup |
| May 2025 | ✅ Student registration feature added |
| May 2025 | ✅ Search and listing features implemented |
| May 2025 | ✅ GUI improvements with Qt Framework |
| May 2025 | ✅ Data persistence with CSV and TXT files |

---

## 🔮 Future Improvements

- [ ] Add login/authentication system
- [ ] Export data to PDF format
- [ ] Add student grade management
- [ ] Implement database (SQLite) instead of flat files
- [ ] Add dark mode support

---

## 🧑‍💻 Developer

| Field | Details |
| :--- | :--- |
| **Name** | Muhammad Rehan |
| **Roll Number** | K25SW003 |
| **Project Type** | Project Based Learning (PBL) |
| **Language** | C++ with Qt Framework |

---

## 📬 Contact

Feel free to reach out for any questions, suggestions, or contributions regarding this project!

---

## 📄 License

This project is developed for educational purposes as part of a university course.

---

⭐ **If you found this project helpful, please give it a Star!** ⭐
