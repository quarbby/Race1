//Figure of 8
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/select.h>

#include "picomms.h"
#include "robotMovement.h"

#define SPEED 40
#define TURNSPEED 15

int rightSideIR, leftSideIR, rightFrontIR, leftFrontIR;
int ultrasound;

void setAngles(){
    set_ir_angle(RIGHT, 45);
    set_ir_angle(LEFT, -45);
}

void getIRDist(){
    ultrasound = get_us_dist();
    get_side_ir_dists(&leftSideIR, &rightSideIR);
    get_front_ir_dists(&leftFrontIR, &rightFrontIR);
}

void goStraight(){
    getIRDist();
    while (1){
        if (ultrasound < 55)
        //if (ultrasound < 25)
            {   break; }
        if (rightSideIR == 40 && rightFrontIR == 100) 
            { 
                break;}
        straight(10 , SPEED);
        getIRDist();
    }
}

void goStraightLeft(){
    getIRDist();
    while (1){
        if (ultrasound < 55)
        //if (ultrasound < 25)
            {   break; }
        if (leftSideIR == 40 && leftFrontIR == 100) 
            {  
                            break;}
        straight(10 , SPEED);
        getIRDist();
    }
}

void firsteight(){
    getIRDist();

    goStraight();

    //turnRight(90, TURNSPEED);
    turnRight(95, TURNSPEED);

    straight(55, SPEED);  

    //turnRight(45,TURNSPEED);
    turnRight(55, TURNSPEED);

    goStraight();


    turnRight(90, TURNSPEED);
    straight(20, SPEED);
    //straight(50, SPEED);
    //turnRight(45, TURNSPEED);
    turnRight (45, TURNSPEED);

    getIRDist();
     while (1){
        if (rightSideIR < 40)
            {
                break;}
        straight(18, SPEED);
        getIRDist();
    }

    goStraight();
    

    // The second bit 
    straight(15, SPEED);
    //straight(18, SPEED);
    turnLeft(90, TURNSPEED);

    getIRDist();
    while (1){
        if (leftSideIR < 40)
            {
                break;}
        straight(15, SPEED);
        getIRDist();
    }

    goStraightLeft();

    if (SPEED <= 20)
        { straight(25, SPEED); } 
    straight(15, SPEED);

    turnLeft(95, TURNSPEED);
    
    if (SPEED <= 20)
        { straight(80, SPEED); }
    else { 
        straight(40, SPEED);
        //straight(25, SPEED);
    }

    //turnLeft (45, TURNSPEED);
    turnLeft(55, TURNSPEED);


    straight(15, SPEED);
    goStraightLeft();
    straight(35,SPEED);
    
    turnLeft(95, TURNSPEED);

    //straight(25, SPEED);
    straight (60, SPEED);

    //turnLeft(45, TURNSPEED);
    turnLeft(55, TURNSPEED);

    getIRDist();
    while (1){
        if (leftSideIR < 40)
            { 
                break;
            }
        straight(10, SPEED);
        getIRDist();
    }


    goStraightLeft();
    //For 60 only
    straight(15, SPEED);

    turnRight(90, TURNSPEED);
    getIRDist();
        while (1){
        if (rightSideIR < 40)
            {   straight (15, SPEED); 
                break;}
        straight(18, SPEED);
        getIRDist();
    }


}

int main(){	
	connect_to_robot();
	initialize_robot();

	setAngles();
	firsteight();
}



