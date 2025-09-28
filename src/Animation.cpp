#include "stdafx.h"
#include "Animation.h"
#include "Globals.h"
#include "Interpolation.h"

//============================ Draw Text on Screen ============================
// Draws a 2D overlay text using GLUT bitmap font
// x, y: screen coordinates in pixels
// text: string to render
void drawText(float x, float y, std::string text) {
    // Switch to projection mode for 2D rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, g_screenWidth, 0, g_screenHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1, 1, 1); // white color for text
    glRasterPos2f(x, y);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    // Restore previous matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//============================ Animate Teapot ============================
// Selects interpolation mode and applies resulting transformation to teapot
void teapotAnimation() {
    switch (mode) {
    case QUAT_CR:   q_interpolate(point_quaternion, CRSplineM); break;
    case QUAT_BS:   q_interpolate(point_quaternion, BSplineM); break;
    case EULER_CR:  e_interpolate(point_euler, CRSplineM); break;
    case EULER_BS:  e_interpolate(point_euler, BSplineM); break;
    }

    // Apply computed transformation matrix
    glLoadMatrixf(M);

    // Draw teapot with current transformation
    glutSolidTeapot(1.0);
}

//============================ Timer Callback ============================
// Updates animation parameter and schedules next timer tick
void timer(int value) {
    glutPostRedisplay(); // Request redraw

    t += dt; // Increment animation parameter
    if (t >= 1) {
        t = 0;
        points = (points < number - 4) ? points + 1 : 0; // Move to next segment
    }

    glutTimerFunc(16, timer, 0); // Approx. 60 FPS
}

//============================ Render Scene ============================
// Clears buffers, sets up lighting and depth, draws teapot, and overlays text
void render() {
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth testing and lighting for 3D rendering
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat LightPos[] = { 5, 5, 5, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    teapotAnimation(); // Draw animated teapot

    // Disable lighting/depth for overlay text
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);

    // Determine mode label
    std::string modeText;
    switch (mode) {
    case QUAT_CR:   modeText = "Mode: Quaternion + Catmull-Rom"; break;
    case QUAT_BS:   modeText = "Mode: Quaternion + B-Spline"; break;
    case EULER_CR:  modeText = "Mode: Euler + Catmull-Rom"; break;
    case EULER_BS:  modeText = "Mode: Euler + B-Spline"; break;
    }

    // Draw mode text on top-left corner
    glColor3f(1, 1, 0); // bright yellow
    drawText(10, g_screenHeight - 40, modeText);

    glutSwapBuffers(); // Swap front/back buffers
}

//============================ Keyboard Input ============================
// Handles user key presses for switching modes and adjusting speed
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1': mode = QUAT_CR; break;
    case '2': mode = QUAT_BS; break;
    case '3': mode = EULER_CR; break;
    case '4': mode = EULER_BS; break;
    case '+': dt += 0.005f; break; // Increase animation speed
    case '-': dt -= 0.005f; if (dt < 0.001f) dt = 0.001f; break; // Decrease speed
    case 27: exit(0); break; // ESC to exit
    }
}

//============================ Window Reshape Callback ============================
// Updates viewport and projection matrix when window size changes
void reshape(int w, int h) {
    g_screenWidth = w;
    g_screenHeight = h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 2000.0);
}
