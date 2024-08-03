#include "PID_Controller.h"

void PID_Controller::Handler() {
    if(state){
        if(chassis->inrange){
            err = target - (*feedback);
            w_out = kv * v_set * dir + kp * err;
            INRANGE(w_out, w_out_max);
            chassis->v_set = v_set;
            chassis->w_set = w_out;
        }else{
            if(self_turn){
                chassis->w_set = 0.1 * dir;
                chassis->v_set = 0.05;
            }else{
                err = 0;
                w_out = kv * v_set * dir + kp * err;
                INRANGE(w_out, w_out_max);
                chassis->v_set = v_set;
                chassis->w_set = w_out;
            }
        }
    }
}

PID_Controller::PID_Controller(Chassis *chassis) {
    this->chassis = chassis;
    feedback = &(chassis->mid_point);
}
