#pragma once
#include <GL/glut.h>

//============================ Screen Settings ============================
// Current window dimensions, updated by the reshape callback
extern int g_screenWidth;
extern int g_screenHeight;

//============================ Animation Variables ============================
// Current segment index in the spline
extern int points;

// Total number of control points
extern int number;

// Animation parameter (0 <= t <= 1)
extern GLfloat t;

// Animation speed (increment per timer tick)
extern GLfloat dt;

// Transformation matrix applied to the teapot (4x4 column-major)
extern GLfloat M[16];

//============================ Animation Modes ============================
// Enumeration of supported animation modes
// QUAT_CR: Quaternion interpolation + Catmull-Rom spline
// QUAT_BS: Quaternion interpolation + B-Spline
// EULER_CR: Euler angles interpolation + Catmull-Rom spline
// EULER_BS: Euler angles interpolation + B-Spline
enum AnimMode { QUAT_CR, QUAT_BS, EULER_CR, EULER_BS };
extern AnimMode mode;

//============================ Spline Matrices ============================
// Catmull-Rom spline matrix (4x4)
extern GLfloat CRSplineM[16];

// B-Spline matrix (4x4)
extern GLfloat BSplineM[16];

//============================ Control Points ============================
// Quaternion control points: [w, x, y, z, posX, posY, posZ]
// Define orientation (quaternion) and position for each keyframe
extern GLfloat point_quaternion[7][7];

// Euler control points: [xAngle, yAngle, zAngle, posX, posY, posZ]
// Define orientation (Euler angles) and position for each keyframe
extern GLfloat point_euler[7][6];
