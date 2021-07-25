//
// Created by allen on 2021/3/29.
//

#include "FSM_State_SquatDown.h"


/**
 * Constructor for the FSM State that passes in state specific info to
 * the generic FSM State constructor.
 *
 * @param _controlFSMData holds all of the relevant control data
 */
template <typename T>
FSM_State_SquatDown<T>::FSM_State_SquatDown(ControlFSMData<T>* _controlFSMData)
        : FSM_State<T>(_controlFSMData, FSM_StateName::SQUAT_DOWN, "SQUAT_DOWN"){
    // Set the pre controls safety checks
    this->checkSafeOrientation = false;

    // Post control safety checks
    this->checkPDesFoot = false;
    this->checkForceFeedForward = false;

    zero_vec3.setZero();

    squat_jpos[0] << -0.0f, -1.45f, 2.78f;
    squat_jpos[1] << 0.0f, -1.45f, 2.78f;
    squat_jpos[2] << -0.0f, -1.45f, 2.78f;
    squat_jpos[3] << 0.0f, -1.45f, 2.78f;
    f_ff << 0.f, 0.f, -65.f;
}

template <typename T>
void FSM_State_SquatDown<T>::onEnter() {
    // Default is to not transition
    this->nextStateName = this->stateName;

    // Reset the transition data
    this->transitionData.zero();

    // Reset iteration counter
    iter = 0;
    _state_iter = 0;

    // initial configuration, position
    for(size_t i(0); i < 4; ++i) {
        initial_jpos[i] = this->_data->_legController->datas[i].q;
    }


}

/**
 * Calls the functions to be executed on each control loop iteration.
 */
template <typename T>
void FSM_State_SquatDown<T>::run() {

    T body_height = this->_data->_stateEstimator->getResult().position[2];
    bool something_wrong(false);
    if( body_height > 0.5 || (body_height < 0.075 ) ) {
        something_wrong = true;
    }
    if(!something_wrong){
        int curr_iter = _state_iter - _motion_start_iter;
        for(size_t leg(0); leg<4; ++leg){
            _SetJPosInterPts(curr_iter, squatdown_iter,
                             leg, initial_jpos[leg], squat_jpos[leg]);
        }
    }

    ++_state_iter;
}
/*
 * Joint PD control
 * */
template <typename T>
void FSM_State_SquatDown<T>::_SetJPosInterPts(
        const size_t & curr_iter, size_t max_iter, int leg,
        const Vec3<T> & ini, const Vec3<T> & fin){

    float a(0.f);
    float b(1.f);

    // if we're done interpolating
    if(curr_iter <= max_iter) {
        b = (float)curr_iter/(float)max_iter;
        a = 1.f - b;
    }

    // compute setpoints
    Vec3<T> inter_pos = a * ini + b * fin;

    // do control
    this->jointPDControl(leg, inter_pos, zero_vec3);

}
/**
 * Manages which states can be transitioned into either by the user
 * commands or state event triggers.
 *
 * @return the enumerated FSM state name to transition into
 */
template <typename T>
FSM_StateName FSM_State_SquatDown<T>::checkTransition() {
    this->nextStateName = this->stateName;
    iter++;

    // Switch FSM control mode
    switch ((int)this->_data->controlParameters->control_mode) {
        case K_SQUAT_DOWN:
            break;

        case K_RECOVERY_STAND:
            this->nextStateName = FSM_StateName::RECOVERY_STAND;
            break;

        case K_PASSIVE:
            this->nextStateName = FSM_StateName::PASSIVE;
            break;

        case K_BALANCE_STAND:
            this->nextStateName = FSM_StateName::BALANCE_STAND;
            break;

        case K_STAND_UP:
            this->nextStateName = FSM_StateName::STAND_UP;
            break;

        default:
            std::cout << "[CONTROL FSM] Bad Request: Cannot transition from "
                      << K_SQUAT_DOWN << " to "
                      << this->_data->controlParameters->control_mode << std::endl;
    }

    // Get the next state
    return this->nextStateName;
}

/**
 * Handles the actual transition for the robot between states.
 * Returns true when the transition is completed.
 *
 * @return true if transition is complete
 */
template <typename T>
TransitionData<T> FSM_State_SquatDown<T>::transition() {
    // Switch FSM control mode
    switch (this->nextStateName) {
        case FSM_StateName::RECOVERY_STAND:
            this->transitionData.done = true;
            break;

        case FSM_StateName::STAND_UP:
            this->transitionData.done = true;
            break;

        case FSM_StateName::BALANCE_STAND:
            this->transitionData.done = true;
            break;

        case FSM_StateName::PASSIVE:
            this->transitionData.done = true;
            break;

        default:
            std::cout << "[CONTROL FSM] Bad Request: Cannot transition from "
                      << K_SQUAT_DOWN << " to "
                      << this->_data->controlParameters->control_mode << std::endl;
    }
    // Finish transition
    this->transitionData.done = true;

    // Return the transition data to the FSM
    return this->transitionData;
}

/**
 * Cleans up the state information on exiting the state.
 */
template <typename T>
void FSM_State_SquatDown<T>::onExit() {
    // Nothing to clean up when exiting
}

// template class FSM_State_SquatDown<double>;
template class FSM_State_SquatDown<float>;
