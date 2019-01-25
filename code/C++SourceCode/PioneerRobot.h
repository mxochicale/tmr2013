
#ifndef PIONEERROBOT_H
#define PIONEERROBOT_H

#include <Aria.h>
#include <ArRobot.h>
#include <iostream>


using namespace std;


class PioneerRobot  
{
    
private:
//   ArRobot pioneer;
  ArActionGoto actionGoTo;
  
  ArArgumentParser *parser;
  ArSimpleConnector *connector;

  
public:
  PioneerRobot();
  ~PioneerRobot();

  // HERITAGE OF THE CLASS INTO ROBOT PIONER 
  // so as to use the following robot control promam
  //  {robot.pioneer.setVel2( -120, -120 );} 
  ArRobot pioneer; 
  
  virtual bool init();
  virtual void getCurrentConfiguration(std::vector< double >& q);
  virtual bool moveToConfiguration(std::vector< double > configuration);
  
  void MoveForward();
  void MoveBackward();
  void SpinLeftSlow();
  void SpinRightSlow();
  void SpinLeftFast();
  void SpinRightFast();
  
  
protected:
  double validateAngle(double angle);
  
};

#endif // PIONEERROBOT_H
