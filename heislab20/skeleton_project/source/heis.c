#include "heis.h"


void startup(){
    while(!get_floor()){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_floor_indicator_on(get_floor()-1);
}
void out_of_bounds(){
    /* Code block that makes the elevator go up when it reach the botton*/
        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }

        /* Code block that makes the elevator go down when it reach the top floor*/
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }

}




void door_delay(int seconds){
    int milli_seconds = 1000* seconds;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds){
        while (hardware_read_obstruction_signal()){
            hardware_command_door_open(1);
            start_time = clock();
        }
        while( hardware_read_stop_signal()) {
            hardware_command_stop_light(1);
            start_time = clock();
        }
        hardware_command_stop_light(0);
        read_floor_signal();
    }
}

void open_door(){
    int door = 1;
    while (door){
        hardware_command_door_open(door);
        door_delay(2000);
        door = 0;
        hardware_command_door_open(door);
    }
    
    
}




void run(){
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    printf("=== Heisprosjekt gruppe 20 ===\n");
    printf("=== God tur===\n");
    
    
    startup();
    while(1){
        
        out_of_bounds();
        //read_floor_signal();
        execute_order();
    }

    return;
}