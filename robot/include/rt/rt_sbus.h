/*!
 * @file rt_sbus.h
 * @brief Communication with RC controller receiver
 */

#ifndef _rt_sbus
#define _rt_sbus

#include <stdint.h>
/*
 * There are two kinds of remote controllers, and we use AT9S now.
 * */
#define RC_AT9S
//#define TARANIS_X7

void unpack_sbus_data(uint8_t sbus_data[], uint16_t *channels);

int read_sbus_data(int port, uint8_t *sbus_data);

int read_sbus_channel(int channel);

int receive_sbus(int port);

int init_sbus(int is_simulator);
#ifdef RC_AT9S
// Two-state switch states
enum AT9s_SwitchStateBool{
    AT9S_BOOL_UP=0,
    AT9S_BOOL_DOWN=1,
};
// Three-state switch states
enum AT9s_SwitchStateTri{
    AT9S_TRI_UP=0,
    AT9S_TRI_MIDDLE=1,
    AT9S_TRI_DOWN=2,
};
// Define of all rc switches and sticks
struct AT9s_data{
    AT9s_SwitchStateBool SWF,SWA,SWB,SWD;
    AT9s_SwitchStateTri SWE,SWC,SWG;
    float left_stick_x,left_stick_y;
    float right_stick_x,right_stick_y;
    float varB;
};
void update_at9s(AT9s_data* data);
#endif

#ifdef TARANIS_X7
enum TaranisSwitchState {
  SWITCH_UP = 0,
  SWITCH_MIDDLE = 1,
  SWITCH_DOWN = 2,
};

struct Taranis_X7_data {
  TaranisSwitchState left_upper_switch, left_lower_left_switch, left_lower_right_switch,
  right_upper_switch, right_lower_left_switch, right_lower_right_switch;

  float left_stick[2];
  float right_stick[2];
  float knobs[2];
};

void update_taranis_x7(Taranis_X7_data* data);
#endif

#endif
