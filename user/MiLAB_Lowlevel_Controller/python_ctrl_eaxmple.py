# Wang Yinuo, 07/25/2021, dbdxwyn@163.com
# If you want to control robot by python, use this example and add your controller to it.

import lcm
from exlcm import lowlevel_cmd, lowlevel_state


# Receive robot state from C++
def robot_state_handler(channel, data):
    msg = lowlevel_state.decode(data)
    print("Received message on channel \"%s\"" % channel)
    print("   q    = %s" % str(msg.q))
    print("   qd   = %s" % str(msg.qd))
    print("   p    = %s" % str(msg.p))
    print("   v    = %s" % str(msg.v))
    print("   rpy         = %s" % str(msg.rpy))
    print("   position    = %s" % str(msg.position))
    print("   orientation = %s" % str(msg.quat))
    print("   vWorld      = %s" % str(msg.vWorld))
    print("   vBody       = %s" % str(msg.vBody))
    print("   omegaWorld  = %s" % str(msg.omegaWorld))
    print("   omegaBody   = %s" % str(msg.omegaBody))
    print("   aWorld      = %s" % str(msg.aWorld))
    print("   aBody       = %s" % str(msg.aBody))
    print(" ")


# Prepare commands for LCM
cmd = lowlevel_cmd()
cmd.q_des = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.qd_des = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.p_des = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.v_des = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.kp_joint = (300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300)
cmd.kd_joint = (15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15)
cmd.kp_cartesian = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.kd_cartesian = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.tau_ff = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
cmd.f_ff = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

# LCM communication
lc = lcm.LCM()
lc.subscribe("low_level_states", robot_state_handler)
try:
    while True:
        lc.handle()
        lc.publish("low_level_cmds", cmd.encode())
except KeyboardInterrupt:
    pass
