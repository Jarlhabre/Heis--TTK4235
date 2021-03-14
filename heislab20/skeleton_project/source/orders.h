#include "sensor.h"

void execute_order();
void go_to_floor(float floor);
void update_orders();
void stop_button();
int check_if_stop(int f);
int check_close(int f);
int check_below(int f);
int check_above(int floor);
float get_current_floor();
void set_elevator_movement(float floor, float current_floor);
void clear_floor_orders(int floor);
void clear_all_orders();