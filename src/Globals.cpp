#include "stdafx.h"
#include "Globals.h"

//============================ Screen Settings ============================
// Current window dimensions, updated by reshape callback
int g_screenWidth = 0;
int g_screenHeight = 0;

//============================ Animation Variables ============================
// Current segment index in the spline
int points = 0;

// Total number of control points
int number = 7;

// Animation parameter (0 <= t <= 1)
GLfloat t = 0;

// Animation speed (increment per timer tick)
GLfloat dt = 0.01f;

// Transformation matrix applied to the teapot (4x4 column-major)
GLfloat M[16] = { 0 };

//============================ Animation Mode ============================
// Current animation mode (Quaternion/Euler + Catmull-Rom/B-Spline)
AnimMode mode = QUAT_CR;

//============================ Spline Matrices ============================
// Catmull-Rom spline matrix (4x4)
GLfloat CRSplineM[16] = {
    -0.5f, 1.0f, -0.5f, 0.0f,
     1.5f, -2.5f, 0.0f, 1.0f,
    -1.5f, 2.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f
};

// B-Spline matrix (4x4)
GLfloat BSplineM[16] = {
    -1.0f / 6.0f, 3.0f / 6.0f, -3.0f / 6.0f, 1.0f / 6.0f,
     3.0f / 6.0f, -6.0f / 6.0f, 0.0f / 6.0f, 4.0f / 6.0f,
    -3.0f / 6.0f, 3.0f / 6.0f, 3.0f / 6.0f, 1.0f / 6.0f,
     1.0f / 6.0f, 0.0f / 6.0f, 0.0f / 6.0f, 0.0f
};

//============================ Control Points ============================
// Quaternion control points: [w, x, y, z, posX, posY, posZ]
// Define orientation (quaternion) and position for each keyframe
GLfloat point_quaternion[7][7] = {
    {1,0,0,0,-5,0,-5}, {0,1,0,0,-3,3,-10}, {0,0,1,0,-1,1,-15},
    {0,0,0,1,0,-5,-20}, {0,0,1,0,1,1,-15}, {0,1,0,0,3,3,-10},
    {1,0,0,0,5,0,-5}
};

// Euler control points: [xAngle, yAngle, zAngle, posX, posY, posZ]
// Define orientation (Euler angles) and position for each keyframe
GLfloat point_euler[7][6] = {
    {90,0,45,-5,0,-5}, {70,20,65,-3,3,-10}, {50,40,85,-1,1,-15},
    {30,60,105,0,-5,-20}, {50,40,85,1,1,-15}, {70,20,65,3,3,-10},
    {90,0,45,5,0,-5}
};
