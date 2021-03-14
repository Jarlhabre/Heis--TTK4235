#include "orders.h"
#include <stdio.h>


int order_indicator[4][3] = {{0,0,0}, {0,0,0},{0,0,0},{0,0,0}};
int last_floor;
int elevator_movement;
HardwareOrder order_types[3] = {
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_DOWN
    };


void go_to_floor(float floor){
    if(get_floor() == floor){
        clear_floor_orders(floor);
        return;
    }
    update_orders();    
    float current_floor; 
    current_floor = get_current_floor();
    set_elevator_movement(floor, current_floor);
    while (get_floor()!= floor){
        update_orders();
        if (get_floor()!=0) {
            last_floor = get_floor();
        }
        int f = get_floor();
        if(check_if_stop(f)){
            clear_floor_orders(f);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            open_door(); 
            if(elevator_movement == 1 ){
              hardware_command_movement(HARDWARE_MOVEMENT_DOWN);  
            }
            if (elevator_movement == 2){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
        }
        if(hardware_read_stop_signal()){
            stop_button();
            return;
        }
        if(elevator_movement ==1){
            if(check_below(floor)!=0){
                floor = check_below(floor);
                }
            }
        }
    clear_floor_orders(get_floor());
    
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    open_door();
}

void update_orders(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            HardwareOrder type = order_types[j];
            if(hardware_read_order(i, type)){
                order_indicator[i][j] = 1;
                hardware_command_order_light(i,type, 1);
            }
        }
    }
}

void execute_order(){
    update_orders();
    stop_button();
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS;floor++ ){
        for (int i = 0; i < 3;i++){
            HardwareOrder type = order_types[i];
            if (order_indicator[floor][i]==1){
                go_to_floor(floor+1);
            } 
        }
    }
}

int check_if_stop(int f){
    switch (elevator_movement)
    {
    case 1:
        if(order_indicator[f-1][2] || order_indicator[f-1][0]){
                clear_floor_orders(f);
                return 1;
            }
        break;
    case 2: 
        if(order_indicator[f-1][1] || order_indicator[f-1][0]){
            clear_floor_orders(f);

           return 1;  
       } 
        break;
    default:
        return 0;
        break;
    }        
}

void stop_button(){
    while(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_stop_light(1);
        if(get_floor()!=0 && hardware_read_stop_signal()){
            open_door();
            break;
        }
        clear_all_orders();
       }
    hardware_command_stop_light(0);
}

int check_below(int f){
    update_orders();
    for(int floor = f; floor > 0; floor--){
        if(order_indicator[floor-1][0] || order_indicator[floor-1][2]){
                return floor;
            }
        }
    return 0;
}

float get_current_floor(){
    float current_floor = get_floor();
    if(current_floor == 0) {
        current_floor = last_floor;
        if(elevator_movement == 1) {
            current_floor = last_floor - 0.5; 
        }
        if(elevator_movement == 2 ) {
            current_floor = last_floor + 0.5;
        }
    } 
    return current_floor;
}

void set_elevator_movement(float floor, float current_floor){
    
    if (current_floor <floor ){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            elevator_movement = 2;
    }
    if (current_floor> floor){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            elevator_movement = 1;
    }
}

void clear_floor_orders(int floor) {
    for(int i = 0; i < 3; i++){
        order_indicator[floor-1][i] = 0;
        HardwareOrder order_typ = order_types[i];
        hardware_command_order_light(floor-1, order_typ, 0);
    }
}

void clear_all_orders() {
    for(int i = 0; i < 4; i++){
            for(int j = 0; j<3; j++){
                order_indicator[i][j] = 0;
                clear_all_order_lights();
            }
         }
}