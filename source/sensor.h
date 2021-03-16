/**
 * @file
 * @brief Driver for the elevator sensor.
 */
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>

/**
* @brief Returns the floor the elevator is currently at
*
* @return floor number, 0 if elevator is not at a floor
*/
int get_floor(); 

/**
* @brief Clears all the order lights
*/
void clear_all_order_lights();

/**
* @brief Sets the order light of the floor that has an order 
*/
void order_light();

/**
* @brief Iterates thorugh the array "order_indicator", to find a destination,
* calls go_to_floor 
*/
