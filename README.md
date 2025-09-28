<h1 align = center> Basic Key-Framing Motion Control System </h1>

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Controls](#controls)
- [Prerequisites](#prerequisites)
- [Build Instructions](#build-instructions)
- [Running the Program](#running-the-program)


---

## Introduction

Key-framing is a fundamental technique in computer animation, where specific positions (key frames) of an object are defined over time, and intermediate frames are generated through interpolation.  

This project implements:

1. **Euler angle interpolation** – Using fixed angles for rotation.  
2. **Quaternion interpolation** – Avoiding gimbal lock for smooth rotation.  
3. **Spline types** – Catmull-Rom and B-Spline for smooth path interpolation.  

The animated object is a 3D teapot, and the system allows switching between interpolation methods and animation modes in real time.

---

## Features

- Key-frame animation using fixed Euler angles and quaternion rotation.
- Interpolation using:
  - Catmull-Rom spline
  - B-Spline
- Real-time 3D rendering of a teapot.
- Switch between modes using keyboard input.
- Adjustable animation speed.

---

## Controls

| Key | Function |
|-----|---------|
| 1   | Quaternion + Catmull-Rom |
| 2   | Quaternion + B-Spline |
| 3   | Euler + Catmull-Rom |
| 4   | Euler + B-Spline |
| +   | Increase animation speed |
| -   | Decrease animation speed |
| ESC | Exit program |

---


## Prerequisites
1. **C++ Compiler** (Visual Studio recommended for Windows)  
2. **OpenGL & GLUT**:
   - `glut32.lib`, `glut.h`, and `glut.def` are included in `/lib`
   - Users need `glut32.dll` in their system or next to the executable. Download from [GLUT official site](https://www.opengl.org/resources/libraries/glut/).

---
## Build Instructions
1. Open Visual Studio and create a **new Win32 Console Project** (or empty C++ project).  
2. Copy all files from the `src` folder into your project directory.  
3. Add the following include path for headers:  Project Properties → C/C++ → General → Additional Include Directories → keyframe-motion-control/src
4. Add the following library path:  Project Properties → Linker → General → Additional Library Directories → keyframe-motion-control/lib
5. Link against `glut32.lib`: Project Properties → Linker → Input → Additional Dependencies → glut32.lib
6. Ensure `glut32.dll` is available in your system PATH or project directory for runtime execution.

---
## Running the Program
1. Set `main.cpp` as the **startup file** in your project.  
2. Build the project.  
3. Run the executable.  
4. Use the following keyboard controls during animation:
- `1` → Quaternion + Catmull-Rom  
- `2` → Quaternion + B-Spline  
- `3` → Euler + Catmull-Rom  
- `4` → Euler + B-Spline  
- `+` → Increase animation speed  
- `-` → Decrease animation speed  
- `ESC` → Exit  

---
