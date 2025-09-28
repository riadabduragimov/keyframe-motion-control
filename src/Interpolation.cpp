#include "stdafx.h"
#include "Interpolation.h"
#include "Globals.h"
#include <cmath>

// Define M_PI if it's not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//============================ Blend Function ============================
// Computes the interpolated value for one component using a cubic spline
// T: vector of powers of the animation parameter t (t^3, t^2, t, 1)
// MS: 4x4 spline coefficient matrix (Catmull-Rom or B-Spline)
// G: four control points for the current component
GLfloat blend(GLfloat T[4], GLfloat MS[16], GLfloat G[4]) {
    GLfloat B[4] = { 0 };
    B[0] = T[0] * MS[0] + T[1] * MS[1] + T[2] * MS[2] + T[3] * MS[3];
    B[1] = T[0] * MS[4] + T[1] * MS[5] + T[2] * MS[6] + T[3] * MS[7];
    B[2] = T[0] * MS[8] + T[1] * MS[9] + T[2] * MS[10] + T[3] * MS[11];
    B[3] = T[0] * MS[12] + T[1] * MS[13] + T[2] * MS[14] + T[3] * MS[15];
    return B[0] * G[0] + B[1] * G[1] + B[2] * G[2] + B[3] * G[3];
}

//============================ Quaternion Normalization ============================
// Ensures that a quaternion is a unit quaternion for valid rotation
// N_tempM: 7-element array, first 4 elements are quaternion components
void Normalization(GLfloat N_tempM[7]) {
    GLfloat s = N_tempM[0] * N_tempM[0] + N_tempM[1] * N_tempM[1] +
        N_tempM[2] * N_tempM[2] + N_tempM[3] * N_tempM[3];
    if (s != 0) {
        GLfloat base = sqrt(s);
        for (int i = 0; i < 4; i++) N_tempM[i] /= base;
    }
}

//============================ Convert Quaternion to Rotation Matrix ============================
// Converts a unit quaternion plus translation to a 4x4 OpenGL transformation matrix
// Q_tempM: quaternion (w,x,y,z) + translation (x,y,z)
// R: 4x4 matrix to store the result
void QuaternionRotationM(GLfloat Q_tempM[7], GLfloat R[16]) {
    GLfloat w = Q_tempM[0], x = Q_tempM[1], y = Q_tempM[2], z = Q_tempM[3];
    R[0] = 1 - 2 * y * y - 2 * z * z; R[4] = 2 * x * y - 2 * w * z; R[8] = 2 * x * z + 2 * w * y; R[12] = Q_tempM[4];
    R[1] = 2 * x * y + 2 * w * z;     R[5] = 1 - 2 * x * x - 2 * z * z; R[9] = 2 * y * z - 2 * w * x; R[13] = Q_tempM[5];
    R[2] = 2 * x * z - 2 * w * y;     R[6] = 2 * y * z + 2 * w * x;     R[10] = 1 - 2 * x * x - 2 * y * y; R[14] = Q_tempM[6];
    R[3] = R[7] = R[11] = 0;           R[15] = 1;
}

//============================ Euler to Quaternion ============================
// Converts Euler angles (degrees) to a quaternion representation
// E_tempM: first 3 elements are Euler angles (x,y,z), output quaternion stored in first 4 elements
void EulerToQuaternion(GLfloat E_tempM[7]) {
    GLfloat a = E_tempM[0] * M_PI / 180.0f / 2;
    GLfloat b = E_tempM[1] * M_PI / 180.0f / 2;
    GLfloat c = E_tempM[2] * M_PI / 180.0f / 2;

    GLfloat w = cos(a) * cos(b) * cos(c) + sin(a) * sin(b) * sin(c);
    GLfloat x = sin(a) * cos(b) * cos(c) - cos(a) * sin(b) * sin(c);
    GLfloat y = cos(a) * sin(b) * cos(c) + sin(a) * cos(b) * sin(c);
    GLfloat z = cos(a) * cos(b) * sin(c) - sin(a) * sin(b) * cos(c);

    E_tempM[0] = w; E_tempM[1] = x; E_tempM[2] = y; E_tempM[3] = z;
}

//============================ Quaternion Interpolation ============================
// Interpolates quaternion + translation using a cubic spline
// p_quaternion: array of control points (w,x,y,z + x,y,z translation)
// SplineM: spline coefficient matrix (Catmull-Rom or B-Spline)
void q_interpolate(GLfloat p_quaternion[7][7], GLfloat SplineM[16]) {
    GLfloat T[4] = { t * t * t, t * t, t, 1 }; // Powers of the interpolation parameter
    GLfloat tempM[7];

    // Blend each component separately
    for (int i = 0; i < 7; i++) {
        GLfloat G[4] = { p_quaternion[points][i], p_quaternion[points + 1][i],
                         p_quaternion[points + 2][i], p_quaternion[points + 3][i] };
        tempM[i] = blend(T, SplineM, G);
    }

    Normalization(tempM);
    QuaternionRotationM(tempM, M);
}

//============================ Euler Interpolation ============================
// Interpolates Euler angles + translation using a cubic spline
// Converts angles to quaternion for proper rotation blending
void e_interpolate(GLfloat p_euler[7][6], GLfloat SplineM[16]) {
    GLfloat T[4] = { t * t * t, t * t, t, 1 };
    GLfloat tempM[7]; // 4 quaternion components + 3 translation

    // Blend Euler angles (first 3 elements)
    for (int i = 0; i < 3; i++) {
        GLfloat G[4] = { p_euler[points][i], p_euler[points + 1][i],
                         p_euler[points + 2][i], p_euler[points + 3][i] };
        tempM[i] = blend(T, SplineM, G);
    }

    // Blend translation components (next 3 elements)
    for (int i = 0; i < 3; i++) {
        GLfloat G[4] = { p_euler[points][i + 3], p_euler[points + 1][i + 3],
                         p_euler[points + 2][i + 3], p_euler[points + 3][i + 3] };
        tempM[i + 4] = blend(T, SplineM, G);
    }

    EulerToQuaternion(tempM);   // Convert blended Euler angles to quaternion
    Normalization(tempM);       // Ensure quaternion is unit length
    QuaternionRotationM(tempM, M); // Apply rotation + translation to matrix
}
