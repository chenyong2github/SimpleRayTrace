#ifndef PLATFORM_H
#define PLATFORM_H

#include <cstdlib>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "Windows.h"

#include "graphics.h"

/*
 * Defines the platform-agnostic windowing and drawing API.
 */

/*
 * Perform platform-specific initialization. 
 *
 * This must be called before anything else!
 */
void InitWindow(float width, float height);

/*
 * Pulls all events from the event queue and dispatches them.
 */
void Loop();

/*
 * Sets a pixel in the window back buffer.
 *
 * The origin of the coordinate system is the upper-left corner of the window.
 */
void SetColor(int x, int y, Color color);

/*
 * Draws the window back buffer to the screen.
 */
void Draw();

#endif
