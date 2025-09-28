#pragma once
#include <string>
#include <GL/glut.h>

//============================ Text Rendering ============================

// Draws a string of text on the screen at position (x, y)
// Uses GLUT's bitmap font rendering (Helvetica 18)
// Parameters:
//   x, y: screen coordinates (pixels)
//   text: string to be displayed
void drawText(float x, float y, std::string text);

//============================ Animation ============================

// Performs the animation of the teapot based on the current mode
// Interpolates either quaternion or Euler control points
// Updates the global transformation matrix and draws the teapot
void teapotAnimation();

//============================ GLUT Callbacks ============================

// Render callback for GLUT
// Clears the screen, sets up lighting and 3D transformations,
// calls teapotAnimation, and draws overlay text
void render();

// Keyboard input callback for GLUT
// Handles mode switching, animation speed adjustment, and exit
// Parameters:
//   key: the pressed key
//   x, y: current mouse position (unused)
void keyboard(unsigned char key, int x, int y);

// Window reshape callback for GLUT
// Adjusts viewport and projection when the window size changes
// Parameters:
//   w: new window width
//   h: new window height
void reshape(int w, int h);

// Timer callback for GLUT
// Advances the animation parameter t and updates current segment
// Re-registers itself for continuous animation
// Parameters:
//   value: user-defined timer value (unused)
void timer(int value);
