/**
 * @file
 * @brief Driver for the elevator orders
 */


#include "sensor.h"

/**
* @brief Iterates thorugh the array "order_indicator", to find a destination,
* calls go_to_floor 
*/
void execute_order();

/**
 * @brief Goes to floor @p floor , while moving checks for updates, stop signal 
 * and if it should stop on the way
 * 
 * @param floor Floor destination
 */
void go_to_floor(float floor);

/**
* @brief Checks if an order is active, turns on the light for the given order
* and updates order_indicator 
*/
void update_orders();

/**
* @brief read signal from stop button, stops the elevator, 
* turns on stop light and deletes orders. Opens door if the elevator is on a floor
*/
void stop_button();

/**
* @brief Checks if the elevator should stop at the floor @p f
*
* @param f Floor to check if the elevator should stop
*
* @return 1 if the elevator should stop at @p f, 0 otherwise
*/
int check_if_stop(int f);

/**
* @brief Checks if there are any orders below the floor @p f
*
* @param f Floor to check orders below
*
* @return floor number if order is below @p f
*/
int check_below(int f);

/**
* @brief Checks if elevator is at a floor or inbetweeen
*
* @return current_floor, if elevator is inbetween floors, current_floor +-= 0.5
*/
float set_current_floor();

/**
* @brief Initializes the elevatormovement based on @p floor and @p current_floor
*
* @param floor Floor that elevator is ordered to
* @param current_floor Floor the elevator is currently at
*/
void set_elevator_movement(float floor, float current_floor);

/**
* @brief Deletes all active orders at floor @p floor
*
* @param floor Floor to delete all orders from
*/
void clear_floor_orders(int floor);

/**
* @brief Deletes all active orders 
*/
void clear_all_orders();
