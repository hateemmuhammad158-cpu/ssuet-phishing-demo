# ssuet-phishing-demo
Educational phishing demonstration for BCNS course - Built with C and Raylib

# 🛡️ Phishing Awareness Demonstration System

A cybersecurity education tool that demonstrates how phishing attacks work by comparing a legitimate student portal with a malicious clone.

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-Raylib-green.svg)](https://www.raylib.com/)
[![License](https://img.shields.io/badge/License-Educational-yellow.svg)]()

---

## 📋 About The Project

An interactive demonstration showcasing how phishing attacks work by displaying two identical student portals side-by-side:
- **Left Panel**: Legitimate SSUET Student Portal
- **Right Panel**: Phishing Clone

The system captures login credentials on the phishing side to educate users about cybersecurity threats and the importance of URL verification.

### ⚠️ Key Learning Point
Users cannot visually distinguish between the legitimate and phishing portals - highlighting why security awareness is critical!

---

## ✨ Features

- **🎨 Graphical User Interface**: Professional UI built with Raylib
- **🔐 Registration System**: User signup with Student ID, Email, and Password
- **🔑 Login Authentication**: Secure credential validation
- **📊 Student Portal**: Full-featured portal with 6 interactive tabs
  - Dashboard (Today's classes and stats)
  - Courses (Enrolled courses with instructors)
  - Grades (Semester grade report)
  - Attendance (Course-wise attendance tracking)
  - Fees (Fee structure and payment status)
  - Schedule (Weekly class timetable)
- **💾 Data Logging**: Credentials saved to text files for demonstration
- **⚡ Loading Animations**: Smooth transitions and visual effects
- **🎭 Side-by-Side Comparison**: Real-time comparison of both portals

---

## 🚀 Getting Started

### Prerequisites

- **Windows OS** with MSYS2 installed
- **GCC Compiler** (MinGW)
- **Raylib Library**

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/hateemmuhammad158-cpu/ssuet-phishing-demo.git
   cd ssuet-phishing-demo
   ```

2. **Install Raylib** (if not already installed)
   ```bash
   pacman -S mingw-w64-x86_64-raylib
   ```

3. **Compile the program**
   ```bash
   gcc ssuet_phishing_demo.c -o ssuet_phishing_demo.exe -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

4. **Run the program**
   ```bash
   ./ssuet_phishing_demo.exe
   ```

---

## 🎮 How To Use

### Step 1: Registration
1. Click **REGISTER** on either panel (left or right)
2. Enter Student ID, Email, and Password
3. Click **REGISTER** button

### Step 2: Login
1. Click **LOGIN** on either panel
2. Enter your registered credentials
3. Click **LOGIN** button
4. Watch the loading animation

### Step 3: Explore Portal
- Navigate through the 6 tabs using the sidebar menu
- View courses, grades, attendance, fees, and schedule
- Click **LOGOUT** to return to welcome screen

### Step 4: View Captured Data
- Check `phishing_captured.txt` - Contains credentials from phishing panel
- Check `legitimate_data.txt` - Contains credentials from legitimate panel

---

## 💻 Technologies Used

| Technology | Purpose |
|------------|---------|
| **C Language** | Core programming language |
| **Raylib** | Graphics library for GUI |
| **GCC** | Compiler (MinGW) |
| **File I/O** | Data persistence |
| **MSYS2** | Build environment |

---

## 📚 Code Structure

```
ssuet-phishing-demo/
│
├── ssuet_phishing_demo.c    # Main source code
├── phishing_captured.txt     # Phishing credentials log (generated)
├── legitimate_data.txt       # Legitimate credentials log (generated)
└── README.md                 # This file
```

### Key Functions

- `RegUser()` - Registers new users
- `CheckUser()` - Validates login credentials
- `SaveLog()` - Saves credentials to file
- `DrawTab()` - Renders portal tab content
- `DrawLoadingScreen()` - Displays loading animation
- `HandleInput()` - Processes keyboard input

---

## 🎓 Learning Outcomes

Through this project, we gained understanding of:

- ✅ Phishing attack mechanisms
- ✅ GUI development in C using Raylib
- ✅ User authentication systems
- ✅ File handling and data persistence
- ✅ Structures and data organization
- ✅ Event-driven programming
- ✅ Cybersecurity awareness education

---

## 👥 Team Members

| Name | Roll Number |
|------|-------------|
| **Rana Muhammad Hateem** | 136 |
| **Abdullah Ali** | 115 |
| **Muhammad Ahmed** | 117 |
| **Muhammad Arman** | 135 |

**Department**: BCNS_C  
**Semester**: 1st  
**Courses**: Introduction to Programming (ITP), Introduction to Model Driven Development  
**Supervisors**: Engr. Noreem Akram & Engr. Ayesha Rafique

---

## 🏫 Institution

**Sir Syed University of Engineering & Technology (SSUET)**  
Karachi, Pakistan

---

## ⚠️ Disclaimer

This project is for **educational purposes only**. It demonstrates cybersecurity concepts to raise awareness about phishing attacks. Do not use this for malicious purposes.

---

## 📝 License

This project is licensed for educational use at SSUET.

---

## 🙏 Acknowledgments

- **Raylib** community for excellent graphics library
- **SSUET Faculty** for guidance and support
- **Claude AI** for development assistance

---

## 📧 Contact

For questions or feedback about this project:
- GitHub: [@hateemmuhammad158-cpu](https://github.com/hateemmuhammad158-cpu)

---

**Built with ❤️ for cybersecurity education**
