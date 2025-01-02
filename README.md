# Solar System Simulation

A C++ application that simulates a solar system using OpenGL. The project demonstrates basic 2D graphics rendering and simple physics for celestial objects.

## Features
- 2D rendering of planets and their orbits.
- Simulated orbital mechanics.

---

## Dependencies
To build and run this project, the following dependencies are required:

### Linux
- `g++`: GNU Compiler Collection for C++.
- `freeglut`: Free OpenGL Utility Toolkit.
- `pkg-config`: For managing library paths.

Install dependencies on Debian-based systems (e.g., Ubuntu, Pop!_OS):
```bash
sudo apt update
sudo apt install g++ freeglut3-dev pkg-config
```

---

## Build Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/your-username/solar-system.git
cd solar-system
```

### 2. Build the Project
Run the following command to build for Linux:
```bash
make
```

### 3. Run the Application
```bash
./solar-system-linux
```

---

## Project Structure
```
/solar-system
├── src/                  # Source files
│   ├── main.cpp          # Main application logic
├── Makefile              # Build configuration
├── README.md             # Project documentation
```

---

## Troubleshooting
### Missing FreeGLUT Header
If you encounter the error:
```
fatal error: GL/freeglut.h: No such file or directory
```
Ensure that FreeGLUT is correctly installed on your system:
```bash
sudo apt install freeglut3-dev
```

---

## Contributing
Contributions are welcome! Please open an issue or submit a pull request.

---
