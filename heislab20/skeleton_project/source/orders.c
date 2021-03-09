#include "orders.h"

int order_indicator[4][3] = {{0,0,0}, {0,0,0},{0,0,0},{0,0,0}};

int last_floor;

int elevator_movement;

void go_to_floor(int floor){
    
    float current_floor = get_floor();
    if(current_floor == 0) {

        current_floor = last_floor;
        if(elevator_movement = 1) {
            current_floor = last_floor - 0.5;
        }
        if(elevator_movement = 2 ) {
            current_floor = last_floor + 0.5;
        }
    }

    if (current_floor < floor){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            elevator_movement = 2;
    }
    if (current_floor > floor) {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            elevator_movement = 1;
    }
    printf("%d", current_floor);
    while (get_floor()!= floor){
        if(hardware_read_stop_signal()){
            stop_button();
            return;
        }
        if (get_floor()!=0) {
            last_floor = get_floor();
        }
        
        read_floor_signal();
        
        int f = get_floor();

        //printf("%d", last_floor);
        if(check_if_stop(f)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            open_door(); 
            if(elevator_movement ==1 ){
              hardware_command_movement(HARDWARE_MOVEMENT_DOWN);  
            }
            if (elevator_movement == 2){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
           

        }
        
                
    }
        
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    elevator_movement = 0;
    open_door();
}

void read_floor_signal(){

    for (int i = 0; i < 4; i++){
        
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
            order_indicator[i][0] = 1;
            hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, 1);
        }
        if (hardware_read_order(i,HARDWARE_ORDER_UP)){
            order_indicator[i][1] = 1;
            hardware_command_order_light(i,HARDWARE_ORDER_UP, 1);
        }
        if (hardware_read_order(i,HARDWARE_ORDER_DOWN)){
            order_indicator[i][2] = 1;
            hardware_command_order_light(i,HARDWARE_ORDER_DOWN, 1);
        }
        
    }

}


void execute_order(){
    read_floor_signal();
    order_light();
    stop_button();
    for (int i = 0; i < 4;i++ ){
        for (int j = 0; j < 3; j++)
        if (order_indicator[i][j]==1){
            go_to_floor(i+1);
            order_indicator[i][j] = 0;
            if(j==0){
                hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, 0);
            }
            if(j==1){
                hardware_command_order_light(i,HARDWARE_ORDER_UP, 0);
            }
            if(j==2){
                hardware_command_order_light(i,HARDWARE_ORDER_DOWN, 0);
            }
        }
  }
   
    
}

int check_if_stop(int f){
    if(elevator_movement==1){
        int current_floor = get_floor();
        if(order_indicator[f-1][2]){
            order_indicator[f-1][2]=0;
            return 1;
            
        }
    }
    if(elevator_movement ==2){
       int current_floor = get_floor();
       if(order_indicator[f-1][1]){
           order_indicator[f-1][1]=0;
           return 1;
           
       } 
    }
    else{
        
        return 0;
        }
}

void stop_button(){
    while(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        
        if(get_floor()!=0){
            open_door();
            return;
        }
        hardware_command_stop_light(1);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j<3; j++){
                order_indicator[i][j] = 0;
                clear_all_order_lights();
            }
         }
         
    }

    hardware_command_stop_light(0);
    
    
    
    
    
    
}





