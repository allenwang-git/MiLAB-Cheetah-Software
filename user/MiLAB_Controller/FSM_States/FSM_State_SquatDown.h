//
// Created by allen on 2021/3/29.
//

#ifndef MILAB_CHEETAH_SOFTWARE_FSM_STATE_SQUATDOWN_H
#define MILAB_CHEETAH_SOFTWARE_FSM_STATE_SQUATDOWN_H

#include "FSM_State.h"

/**
 *
 */
template <typename T>
class FSM_State_SquatDown : public FSM_State<T> {
public:
    FSM_State_SquatDown(ControlFSMData<T>* _controlFSMData);

    // Behavior to be carried out when entering a state
    void onEnter();

    // Run the normal behavior for the state
    void run();

    // Checks for any transition triggers
    FSM_StateName checkTransition();

    // Manages state specific transitions
    TransitionData<T> transition();

    // Behavior to be carried out when exiting a state
    void onExit();

    TransitionData<T> testTransition();

private:
    // Keep track of the control iterations
    int iter = 0;
    int _motion_start_iter = 0;

    unsigned long long _state_iter;

    // JPos
    Vec3<T> squat_jpos[4];
    Vec3<T> initial_jpos[4];
    Vec3<T> zero_vec3;

    Vec3<T> f_ff;

    // 0.5 kHz
    const int squatdown_iter = 800;
    const int suqatdown_settle_iter = 1000;

    void _SetJPosInterPts(
            const size_t & curr_iter, size_t max_iter, int leg,
            const Vec3<T> & ini, const Vec3<T> & fin);

};


#endif //MILAB_CHEETAH_SOFTWARE_FSM_STATE_SQUATDOWN_H
