/**
  ******************************************************************************
  * @FileName			    Tracking.h
  * @Description
  * @author                 Yu Xinyi
  * @note
  ******************************************************************************
  *
  * Copyright (c) 2023 Team JiaoLong-ShanghaiJiaoTong University
  * All rights reserved.
  *
  ******************************************************************************
**/

#include "Tracking.h"


extern uint8_t question_state, question_stop;
extern uint8_t signal_en_flag;

uint8_t prev_question_state = 0;
uint32_t tick_start = 0;
uint32_t start_tick = 0, end_tick = 800;

Tracking::Tracking(Chassis *chassis, Controller *controller, PID_Controller *pid_controller) {
    this->chassis = chassis;
    this->controller = controller;
    this->pid_controller = pid_controller;
}

void Tracking::Handler() {

if(question_stop){
    chassis->state = CHASSIS_STOP;
    chassis->v_set = 0;
    chassis->w_set = 0;
    state = 0;
    tick_start = 0;
}else if(question_state == 1){
    switch (state) {
           case 0:{
               chassis->state = CHASSIS_STOP;
               chassis->v_set = 0;
               chassis->w_set = 0;
               r1_set = false;
               r2_set = false;
               if(tick_start++ > 1000) state = 1;
           } break;
           case 1:{ //A->B->C
               chassis->state = CHASSIS_RUN;
               controller->x_set = 1;
               controller->y_set = 0;
               controller->state = 1;

               if((chassis->inrange && controller->x_set - chassis->x < 0.2) || controller->reached){
                   controller->state = 0;
                   controller->reached = 0;
                   pid_controller->dir = -1;
                   pid_controller->state = 1;
                   pid_controller->self_turn = true;
                   start_tick = 0;
                   state++;
               }
           } break;
           case 2:{
               if(start_tick++ >= end_tick && chassis->inrange){
                   state++;
                   pid_controller->state = 0;
                   chassis->v_set = 0;
                   chassis->w_set = 0;
                   signal_en_flag = 1;
               }

           } break;

    }
}
else if(question_state == 2){
    switch (state) {
        case 0:{
            chassis->state = CHASSIS_STOP;
            chassis->v_set = 0;
            chassis->w_set = 0;
            controller->reached = false;
            r1_set = false;
            r2_set = false;
            if(tick_start++ > 1000) state = 1;
        } break;
        case 1:{ //A->B->C
            chassis->state = CHASSIS_RUN;
            controller->x_set = 1.0;
            controller->y_set = 0;
            controller->state = 1;
            if(chassis->inrange){
                if(!r1_set && 1 - chassis->x < 0.2){ //看到第一个点
                    signal_en_flag = 1;
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;

                    controller->state = 0;
                    pid_controller->dir = -1;
                    pid_controller->state = 1;
                    pid_controller->self_turn = true;
                }else{
                    r2.x = chassis->x_line;
                    r2.y = chassis->y_line;
                }
            } else{
                if(r1_set && chassis->y < -0.3){ //看不到第二个点
                    state++;
                    r2_set = true;
                    start_tick = 0;
                    pid_controller->self_turn = false;
                    calibrate_pos2(r1, r2, POINT_B, POINT_C);
                }
            }
        } break;
        case 2:{
            if(start_tick++ >= end_tick){
                signal_en_flag = 1;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                state++;
            }

        } break;
        case 3:{ //C->D
            controller->y_set = -0.8;
            controller->x_set = -0.0;
            controller->state = 1;
            if((chassis->inrange && chassis->x - controller->x_set < 0.1) || controller->reached){
                signal_en_flag = 1;
                controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                state++;
            }
        } break;
        case 4:{
            if(!chassis->inrange){
                pid_controller->state = 1;
                pid_controller->self_turn = true;

            }else{
                chassis->w_set = 0;
                r1_set = false;
                r2_set = false;
                pid_controller->state = 1;
                pid_controller->self_turn = false;
                state++;
            }
        } break;
        case 5:{
            if(!chassis->inrange){
                pid_controller->state = 0;
                chassis->w_set = 0;
                chassis->v_set = 0;
                state++;
            }
        } break;
        case 6:{
            controller->y_set = 0;
            controller->x_set = 0;
            controller->state = 1;
            if(-chassis->x + controller->x_set < 0.02 || controller->reached){
                start_tick = 0;
                state++;
            }

        } break;
        case 7:{
            if(start_tick++ >= end_tick){
                state++;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                signal_en_flag = 1;
            }

        } break;


    }

}
else if(question_state == 3){
    switch (state) {
        case 0:{
            chassis->state = CHASSIS_STOP;
            chassis->v_set = 0;
            chassis->w_set = 0;
            r1_set = false;
            r2_set = false;
            controller->reached = false;
            chassis->inrange = false;
            if(tick_start++ > 1000) state = 1;
        } break;
        case 1:{ // A->C->B
            chassis->state = CHASSIS_RUN;
            if(!init_pos){
                //chassis->x = init_x;
                //chassis->y = init_y;
                init_pos = 1;
            }
            controller->x_set = 1;
            controller->y_set = -0.8;
            controller->state = 1;

            if(chassis->inrange){
                if(!r1_set && chassis->y < -0.6){ //C
                    signal_en_flag = 1;
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;

                    controller->state = 0;
                    controller->reached = 0;
                    pid_controller->dir = 1;
                    pid_controller->state = 1;
                }else{
                    pid_controller->state = 1;
                    r2.x = chassis->x_line;
                    r2.y = chassis->y_line;
                }
            } else{
                if(r1_set && chassis->y > -0.2){ //B
                    r2_set = true;
                    pid_controller->self_turn = false;
                    calibrate_pos2(r1, r2, POINT_C, POINT_B);
                    start_tick = 0;
                    state++;
                }else if(controller->reached && !r1_set && 1 - chassis->x < 0.2){
                    pid_controller->state = 1;
                    pid_controller->dir = 1;
                    pid_controller->self_turn = true;
                    controller->state = 0;
                    controller->reached = 0;
                    //chassis->w_set = w_set;
                }
            }
        } break;
        case 2:{
            if(start_tick++ >= end_tick){//B
                state++;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                signal_en_flag = 1;
            }

        } break;
        case 3:{ // B->D
            controller->y_set = -0.8;
            controller->x_set = 0.0;
            controller->state = 1;
            if((chassis->inrange && chassis->x - controller->x_set < 0.2) || controller->reached){
                if(chassis->inrange){
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;
                }
                controller->state = 0;
                controller->reached = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                pid_controller->state = 1;
                pid_controller->dir = -1;
                pid_controller->self_turn = true;
                start_tick = 0;
                state++;
            }
        } break;
        case 4:{ //D
            if(!r1_set){
                if(chassis->inrange){
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;
                }
            }
            if(start_tick++ >= end_tick && r1_set){//D
                state++;
                signal_en_flag = 1;
                start_tick = 0;
            }

        } break;
        case 5:{ //D->A
            if(!chassis->inrange && chassis->y > -0.2){
                r2_set = true;
                pid_controller->self_turn = false;
                calibrate_pos2(r1, r2, POINT_D, POINT_A);
                r1_set = false;
                r2_set = false;
                state++;
            }else{
                if(chassis->inrange){
                    pid_controller->state = 1;
                    r2.x = chassis->x_line;
                    r2.y = chassis->y_line;
                }
//                }else{
//                    pid_controller->state = 0;
//                    chassis->v_set = 0;
//                    chassis->w_set = -w_set;
//                }

            }

        } break;
        case 6:{ //A

            if(start_tick++ >= end_tick){//D
                state++;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                signal_en_flag = 1;
                start_tick = 0;
            }

        } break;
        default: break;
    }
}else if(question_state == 4){
    switch (state) {
        case 0:{
            chassis->state = CHASSIS_STOP;
            chassis->v_set = 0;
            chassis->w_set = 0;
            r1_set = false;
            r2_set = false;
            controller->reached = false;
            chassis->inrange = false;
            if(tick_start++ > 1000) state = 1;
        } break;
        case 1:{ // A->C->B
            chassis->state = CHASSIS_RUN;
            if(!init_pos){
                //chassis->x = init_x;
                //chassis->y = init_y;
                init_pos = 1;
            }
            controller->x_set = 1;
            controller->y_set = -0.8;
            controller->state = 1;

            if(chassis->inrange){
                if(!r1_set && chassis->y < -0.6){ //C
                    signal_en_flag = 1;
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;

                    controller->state = 0;
                    controller->reached = 0;
                    pid_controller->dir = 1;
                    pid_controller->state = 1;
                }else{
                    pid_controller->state = 1;
                    r2.x = chassis->x_line;
                    r2.y = chassis->y_line;
                }
            } else{
                if(r1_set && chassis->y > -0.2){ //B
                    r2_set = true;
                    pid_controller->self_turn = false;
                    calibrate_pos2(r1, r2, POINT_C, POINT_B);
                    start_tick = 0;
                    state++;
                }else if(controller->reached && !r1_set && 1 - chassis->x < 0.2){
                    pid_controller->state = 1;
                    pid_controller->dir = 1;
                    pid_controller->self_turn = true;
                    controller->state = 0;
                    controller->reached = 0;
                    //chassis->w_set = w_set;
                }
            }
        } break;
        case 2:{
            if(start_tick++ >= end_tick){//B
                state++;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                signal_en_flag = 1;
            }

        } break;
        case 3:{ // B->D
            controller->y_set = -0.8;
            controller->x_set = 0.0;
            controller->state = 1;
            if((chassis->inrange && chassis->x - controller->x_set < 0.2) || controller->reached){
                if(chassis->inrange){
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;
                }
                controller->state = 0;
                controller->reached = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                pid_controller->state = 1;
                pid_controller->dir = -1;
                pid_controller->self_turn = true;
                start_tick = 0;
                state++;
            }
        } break;
        case 4:{ //D
            if(!r1_set){
                if(chassis->inrange){
                    r1_set = true;
                    r1.x = chassis->x_line;
                    r1.y = chassis->y_line;
                }
            }
            if(start_tick++ >= end_tick && r1_set){//D
                state++;
                signal_en_flag = 1;
                start_tick = 0;
            }

        } break;
        case 5:{ //D->A
            if(!chassis->inrange && chassis->y > -0.2){
                r2_set = true;
                pid_controller->self_turn = false;
                calibrate_pos2(r1, r2, POINT_D, POINT_A);
                r1_set = false;
                r2_set = false;
                state++;
            }else{
                if(chassis->inrange){
                    pid_controller->state = 1;
                    r2.x = chassis->x_line;
                    r2.y = chassis->y_line;
                }
//                }else{
//                    pid_controller->state = 0;
//                    chassis->v_set = 0;
//                    chassis->w_set = -w_set;
//                }

            }

        } break;
        case 6:{ //A

            if(start_tick++ >= end_tick){//D
                state = 1;
                r1_set = false;
                r2_set = false;
                controller->reached = false;
                chassis->inrange = false;
                pid_controller->state = 0;
                chassis->v_set = 0;
                chassis->w_set = 0;
                signal_en_flag = 1;
                start_tick = 0;
            }

        } break;
        default: break;
    }
}
}

void Tracking::calibrate_pos(Point r1, Point r2, ref_point_e ref_r) {
    Point ref_r1 = ref_points[ref_r];
    //鏍规嵁璺濈绠楀悜閲�
    float temp_cos = dist / 2 / TRACK_R;
    float temp_sin;
    arm_sqrt_f32(1 - temp_cos * temp_cos, &temp_sin);
    float dx = dist * temp_sin;
    float dy = dist * temp_cos;
    switch (ref_r) {
        case POINT_A:{
            dy = -dy;
        } break;
        case POINT_B:{

        } break;
        case POINT_C:{
            dx = -dx;
        } break;
        case POINT_D:{
            dx = -dx;
            dy = -dy;
        } break;

    }
    Point ref_r21 = {dx, dy};
    Point r21 = {r2.x - r1.x, r2.y - r1.y};
    //璁＄畻涓ゅ悜閲忓す瑙�
    float ang = acosf((ref_r21.x * r21.x + ref_r21.y + r21.y) / (dist * dist)) / M_PI * 180;
    //璁＄畻鍚戦噺鏃嬭浆鏂瑰悜
    float dir = r21.x * ref_r21.y - r21.y * ref_r21.x;
    if(dir < 0) ang = -ang;
    //姣旇緝涓や釜鍚戦噺鏍℃灏忚溅
    chassis->x += ref_r1.x - r1.x;
    chassis->y += ref_r1.y - r1.y;
    chassis->ang += ang;
    MOD(chassis->ang, 360);



}

float Tracking::calc_dist(Point r1, Point r2) {
    float x_diff = r2.x - r1.x;
    float y_diff = r2.y - r1.y;
    arm_sqrt_f32(x_diff * x_diff + y_diff * y_diff, &dist);
    return dist;
}

void Tracking::calibrate_pos2(Point r1, Point r2, ref_point_e ref1, ref_point_e ref2) {
    Point ref_r1 = ref_points[ref1];
    Point ref_r2 = ref_points[ref2];

    //calc_dist(r1, r2);
    chassis->x += ref_r2.x - r2.x;
    chassis->y += ref_r2.y - r2.y;

    Point ref_r21 = {ref_r2.x - ref_r1.x, ref_r2.y - ref_r1.y};
    Point r21 = {r2.x - r1.x, r2.y - r1.y};
    //璁＄畻涓ゅ悜閲忓す瑙�
    float ang = acosf((ref_r21.x * r21.x + ref_r21.y + r21.y) / (dist * dist)) / M_PI * 180;
    //璁＄畻鍚戦噺鏃嬭浆鏂瑰悜
    float dir = r21.x * ref_r21.y - r21.y * ref_r21.x;
    if(dir < 0) ang = -ang;
    chassis->ang += ang;
    MOD(chassis->ang, 360);

    /*if(!init_pos){
        init_x = ref_r2.x - r2.x;
        init_y = ref_r2.y - r2.y;
        init_ang = ang;
        MOD(init_ang, 360);
        init_pos = true;
    }*/



}

