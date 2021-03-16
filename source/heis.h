/**
 * @file
 * @brief Driver for the elevator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "orders.h"

/**
* @brief Moves the elevatorm down to closest floor
* if elevator starts inbetween floors at the program start, 
*/
void startup();

/**
* @brief Prevents the elevator from moving out of the floor range 
*/
void out_of_bounds();

/**
* @brief Main function, prints welcome messages and runs the elevator program
*/
void run();

/**
* @brief Opens door for 3 seconds
*/
void open_door();

/**
* @brief Timer for a number of @p seconds , keeps door open while stop button is pressed
* and obstruction signal is active
*
* @param seconds Number of seconds of the timer
*/
void door_delay(int seconds);


