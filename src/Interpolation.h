#pragma once
#include <GL/glut.h>

//============================ Utility Functions ============================

// Computes the blended value of a single component using the
// parameter vector T, the spline matrix MS, and control points G
GLfloat blend(GLfloat T[4], GLfloat MS[16], GLfloat G[4]);

// Normalizes a quaternion (first 4 elements of N_tempM) to unit length
// Ensures that the quaternion represents a valid rotation
void Normalization(GLfloat N_tempM[7]);

// Converts a quaternion and translation vector into a 4x4 transformation matrix
// Q_tempM: input quaternion [w, x, y, z] + translation [x, y, z]
// R: output 4x4 column-major matrix for OpenGL
void QuaternionRotationM(GLfloat Q_tempM[7], GLfloat R[16]);

// Converts Euler angles (degrees) and translation into a quaternion
// E_tempM: input Euler angles [xAngle, yAngle, zAngle] + translation [x, y, z]
// Output quaternion stored in the first 4 elements of E_tempM
void EulerToQuaternion(GLfloat E_tempM[7]);

//============================ Interpolation Functions ============================

// Performs quaternion-based interpolation using the specified spline matrix
// p_quaternion: control points [7][7], SplineM: 4x4 spline matrix
// Updates the global transformation matrix M
void q_interpolate(GLfloat p_quaternion[7][7], GLfloat SplineM[16]);

// Performs Euler-angle-based interpolation using the specified spline matrix
// p_euler: control points [7][6], SplineM: 4x4 spline matrix
// Converts Euler angles to quaternion, normalizes, and updates the global matrix M
void e_interpolate(GLfloat p_euler[7][6], GLfloat SplineM[16]);
