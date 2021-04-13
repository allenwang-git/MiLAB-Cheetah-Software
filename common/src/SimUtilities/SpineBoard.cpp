/*! @file SpineBoard.cpp
 *  @brief Spine Board Code, used to simulate the SpineBoard.
 */

#include <stdio.h>
#include "iostream"
#include "SimUtilities/SpineBoard.h"

/*!
 * Spine board setup (per board)
 */
void SpineBoard::init(float sideSign, s32 board) {
  this->board_num = board;
  this->side_sign = sideSign;
}

/*!
 * Reset all data for the board
 */
void SpineBoard::resetData() {
  if (data == nullptr) {
    printf(
        "[ERROR: SPINE board] reset_spine_board_data called when "
        "cheetahlcm_spi_data_t* was null\n");
    return;
  }

  data->flags[board_num] = 0;
  data->qd_abad[board_num] = 0.f;
  data->qd_hip[board_num] = 0.f;
  data->qd_knee[board_num] = 0.f;
  data->q_abad[board_num] = 0.f;
  data->q_hip[board_num] = 0.f;
  data->q_knee[board_num] = 0.f;
  data->spi_driver_status = 0;
}

/*!
 * Reset all commands for the board
 */
void SpineBoard::resetCommand() {
  if (cmd == nullptr) {
    printf(
        "[ERROR: SPINE board] reset_spine_board_command called when "
        "cheetahlcm_spi_command_t* was null\n");
    return;
  }

  cmd->flags[board_num] = 0;
  cmd->kd_abad[board_num] = 0.f;
  cmd->kd_hip[board_num] = 0.f;
  cmd->kd_knee[board_num] = 0.f;
  cmd->kp_abad[board_num] = 0.f;
  cmd->kp_hip[board_num] = 0.f;
  cmd->kp_knee[board_num] = 0.f;
  cmd->qd_des_abad[board_num] = 0.f;
  cmd->qd_des_hip[board_num] = 0.f;
  cmd->qd_des_knee[board_num] = 0.f;
  cmd->q_des_abad[board_num] = 0.f;
  cmd->q_des_hip[board_num] = 0.f;
  cmd->q_des_knee[board_num] = 0.f;
  cmd->tau_abad_ff[board_num] = 0.f;
  cmd->tau_hip_ff[board_num] = 0.f;
  cmd->tau_hip_ff[board_num] = 0.f;
  cmd->tau_knee_ff[board_num] = 0.f;
}

/*!
 * Run spine board control
 */
void SpineBoard::run(bool milab) {
  iter_counter++;
  if (cmd == nullptr || data == nullptr) {
    printf(
        "[ERROR: SPINE board] run_spine_board_iteration called with null "
        "command or data!\n");
    torque_out[0] = 0.f;
    torque_out[1] = 0.f;
    torque_out[2] = 0.f;
    return;
  }
  if (milab){
      for (int i = 0; i < 3; ++i) {
          max_torque[i] = milab_max_torque[i];
          q_limit_upper[i] = milab_q_limit_upper[i];
          q_limit_low[i] = milab_q_limit_low[i];
      }
      kp_softstop = milab_kp_softstop;
      kd_softstop = milab_kd_softstop;

      //  MiLAB robot's abad limitations is different for left and right legs
      if (board_num == 1 || board_num == 3){  //left[-0.75,1.5]
          q_limit_upper[0] = -milab_q_limit_low[0];
          q_limit_low[0] = -milab_q_limit_upper[0];
      }
  }
  /// Check abad softstop ///
  if (data->q_abad[board_num] > q_limit_upper[0]) {
    torque_out[0] = kp_softstop * (q_limit_upper[0] - data->q_abad[board_num]) -
                    kd_softstop * (data->qd_abad[board_num]) +
                    cmd->tau_abad_ff[board_num];
  } else if (data->q_abad[board_num] < q_limit_low[0]) {
    torque_out[0] = kp_softstop * (q_limit_low[0] - data->q_abad[board_num]) -
                    kd_softstop * (data->qd_abad[board_num]) +
                    cmd->tau_abad_ff[board_num];
  } else {
    torque_out[0] = cmd->kp_abad[board_num] *
                        (cmd->q_des_abad[board_num] - data->q_abad[board_num]) +
                    cmd->kd_abad[board_num] * (cmd->qd_des_abad[board_num] -
                                               data->qd_abad[board_num]) +
                    cmd->tau_abad_ff[board_num];
  }

  /// Check hip softstop ///
  if (data->q_hip[board_num] > q_limit_upper[1]) {
    torque_out[1] = kp_softstop * (q_limit_upper[1] - data->q_hip[board_num]) -
                    kd_softstop * (data->qd_hip[board_num]) +
                    cmd->tau_hip_ff[board_num];
  } else if (data->q_hip[board_num] < q_limit_low[1]) {
    torque_out[1] = kp_softstop * (q_limit_low[1] - data->q_hip[board_num]) -
                    kd_softstop * (data->qd_hip[board_num]) +
                    cmd->tau_hip_ff[board_num];
  } else {
    torque_out[1] = cmd->kp_hip[board_num] *
                        (cmd->q_des_hip[board_num] - data->q_hip[board_num]) +
                    cmd->kd_hip[board_num] *
                        (cmd->qd_des_hip[board_num] - data->qd_hip[board_num]) +
                    cmd->tau_hip_ff[board_num];
  }

  /// Check knee softstop ///
    if (data->q_knee[board_num] > q_limit_upper[2]) {
        torque_out[2] = kp_softstop * (q_limit_upper[2] - data->q_knee[board_num]) -
                        kd_softstop * (data->qd_knee[board_num]) +
                        cmd->tau_knee_ff[board_num];

            std::cout<<board_num<<" "<<torque_out[2]<<kp_softstop<<std::endl;
    } else if (data->q_knee[board_num] < q_limit_low[2]) {
        torque_out[2] = kp_softstop * (q_limit_low[2] - data->q_knee[board_num]) -
                        kd_softstop * (data->qd_knee[board_num]) +
                        cmd->tau_knee_ff[board_num];
    } else {
        torque_out[2] = cmd->kp_knee[board_num] *
                        (cmd->q_des_knee[board_num] - data->q_knee[board_num]) +
                        cmd->kd_knee[board_num] *
                        (cmd->qd_des_knee[board_num] - data->qd_knee[board_num]) +
                        cmd->tau_knee_ff[board_num];
    }


  const float* torque_limits = disabled_torque;
// flags=1 leg enable/ 0 leg unable
  if (cmd->flags[board_num] & 0b1) { //1&1
    if (cmd->flags[board_num] & 0b10) //1&2
      torque_limits = wimp_torque;
    else
      torque_limits = max_torque;
  }

  for (int i = 0; i < 3; i++) {
    if (torque_out[i] > torque_limits[i]) torque_out[i] = torque_limits[i];
    if (torque_out[i] < -torque_limits[i]) torque_out[i] = -torque_limits[i];
  }

}
