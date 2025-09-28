#include "stdafx.h"
#include "Animation.h"

int main(int argc, char** argv) {
    // Initialize the GLUT library
    // This sets up internal data structures and processes command-line arguments
    glutInit(&argc, argv);

    // Set the initial display mode:
    // GLUT_DOUBLE: use double buffering to prevent flickering
    // GLUT_RGB: use RGB color mode
    // GLUT_DEPTH: enable depth buffer for 3D rendering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Set the initial window size (width x height)
    glutInitWindowSize(1000, 800);

    // Create the window with the given title
    glutCreateWindow("Quaternion & Euler Interpolation");

    // Register the display callback function
    // This function will be called whenever the window needs to be redrawn
    glutDisplayFunc(render);

    // Register the reshape callback function
    // Called whenever the window is resized to adjust viewport and projection
    glutReshapeFunc(reshape);

    // Register the keyboard callback function
    // Handles key presses for switching modes, adjusting animation speed, and exiting
    glutKeyboardFunc(keyboard);

    // Register the timer callback function
    // Sets up periodic updates for the animation (approx. 60 FPS)
    glutTimerFunc(16, timer, 0);

    // Enter the GLUT main loop
    // This starts the event-driven processing and keeps the application running
    glutMainLoop();

    // Return success (this line is never reached because glutMainLoop never exits)
    return 0;
}
