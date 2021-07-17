#ifndef LOWLEVEL_CONTROLLER
#define LOWLEVEL_CONTROLLER

#include <RobotController.h>
#include "LowLevelUserParameters.h"

////#define JPOS_TEST
//#define JPOS_UP_DOWN
class Lowlevel_Controller:public RobotController{
  public:
    Lowlevel_Controller():RobotController(){ }
    void leg_Interpolation(const size_t & curr_iter, size_t max_iter, int leg,
                           const Vec3<float> & ini, const Vec3<float> & fin);
    void leg_JointPD(int leg, Vec3<float> qDes, Vec3<float> qdDes);
    void leg_Passive(int leg);

    virtual ~Lowlevel_Controller(){}

    virtual void initializeController();
    virtual void runController();
    virtual void updateVisualization(){}
    virtual ControlParameters* getUserControlParameters() {
      return &userParameters;
    }
  protected:
    Vec3<float> _jpos_ini[4];
    Vec3<float> _jpos_fold[4];
    Vec3<float> _jpos_stand[4];
    Vec3<float> _jpos_pre_off[4];
    Vec3<float> zero_vec3;
    LowLevelUserParameters userParameters;
  private:
    Mat3<float> kpMat;
    Mat3<float> kdMat;
    const int fold_iter = 500;
    const int stand_iter = 500;
    const int squad_iter = 500;
    const int wait_iter = 1000;
    const int keep_iter = 5000;
    static const int FOLDLEG =0;
    static const int STANDUP =1;
    static const int SQUAD =2;
    int flag = FOLDLEG;
    long j_iter=0;
    int motion_iter=0;
};

#endif
