#ifndef JPOS_CONTROLLER
#define JPOS_CONTROLLER

#include <RobotController.h>
//#include <RobotRunner.h>
#include "JPosUserParameters.h"
#include <Controllers/FootSwingTrajectory.h>
#include <Controllers/StateEstimatorContainer.h>
#include <Dynamics/Quadruped.h>
//#define JPOS_TEST
//#define JPOS_UP_DOWN
#define JPOS_CARTESIAN

class JPos_Controller:public RobotController{
  public:
    JPos_Controller():RobotController(){ }
    void leg_Interpolation(const size_t & curr_iter, size_t max_iter, int leg,
                           const Vec3<float> & ini, const Vec3<float> & fin);
    void leg_JointPD(int leg, Vec3<float> qDes, Vec3<float> qdDes);
    void leg_Passive(int leg);


//    Vec3<float> getHipLocation(int leg);
    void leg_CartesianPD(int leg, double stepHeight,int motion_iter, Mat3<float> rBody, Vec3<float> position, Vec3<float> vWorld, Vec3<float> pHip);

    virtual ~JPos_Controller(){}
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
    Vec3<float> _pfoot_ini;
    Vec3<float> zero_vec3;
    JPosUserParameters userParameters;
//    StateEstimate<float> _stateEstimator;

  private:
    StateEstimatorContainer<float>* _stateEstimator;
    Mat3<float> kpMat;
    Mat3<float> kdMat;
    Mat3<float> kpcMat;
    Mat3<float> kdcMat;
    FootSwingTrajectory<float> footSwingTrajectories[4];
    const int fold_iter = 400;
    const int stand_iter = 300;
    const int squad_iter = 500;
    const int wait_iter = 500;
    const int keep_iter = 1000;
    const int cart_iter = 2000;
    static const int FOLDLEG =0;
    static const int STANDUP =1;
    static const int SQUAD =2;
    static const int CARTESIAN =3;
    int flag = FOLDLEG;
    long j_iter=0;
    int motion_iter=0;
};

#endif
