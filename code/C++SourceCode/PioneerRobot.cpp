#include "PioneerRobot.h"

PioneerRobot::PioneerRobot()
{
    PioneerRobot::init();
}


PioneerRobot::~PioneerRobot()
{
  Aria::exit(0); 
  sleep(2);
}

bool PioneerRobot::init()
{
    system("clear"); //clean the terminal screen
    cout << "Initializing Robot Pioneer" << endl;
  

  int argc = 3;
  char *argv[10];
  argv[0] = "./aria_test";
  argv[1] = "-rp";
  argv[2] = "/dev/ttyUSB0";
  
  parser = new ArArgumentParser(&argc, argv);
  connector = new ArSimpleConnector(parser);
  
  /* Connection to robot */
    parser->loadDefaultArguments(); 

    /* Connection to robot */
    parser->loadDefaultArguments(); //Load default values 8
    if (!connector->parseArgs()) //Parse connector arguments 9
    { 
      cout << "Unknown settings\n"; 
      Aria::exit(0); 
      exit(1); 
    } 

    if (!connector->connectRobot(&pioneer)) //Connect to the robot 13
    { 
      cout << "Unable to connect\n"; 
      Aria::exit(0); 
      exit(1); 
    } 
    
   
       // set the acceleration and desacceleration
   pioneer.setTransAccel(200);
   pioneer.setTransDecel(200);
   
   pioneer.runAsync(true); //Run in asynchronous mode 17
    
    pioneer.addAction(&actionGoTo, 70);
    
    pioneer.lock(); //Lock robot during set up 18
    pioneer.comInt(ArCommands::ENABLE, 1); //Turn on the motors 19
    pioneer.unlock(); //Unlock the robot 20
    
    //robot.setHeading(-45);
    //robot.move(500);
    //robot.setVel(200);
    
    pioneer.resetTripOdometer();
    pioneer.setAbsoluteMaxTransVel(250);
    cout << "trans vel " << pioneer.getAbsoluteMaxTransVel() << endl;
    pioneer.setAbsoluteMaxRotVel(35);
    cout << "rot vel " << pioneer.getAbsoluteMaxRotVel() << endl;
    
  //  ready = true;
}


void PioneerRobot::getCurrentConfiguration(std::vector< double >& q)
{
    
  ArPose pose;
  pose = pioneer.getPose();
  q.clear();
  q.resize(3);
  q[0] = (double) pose.getX() / 1000; 
  q[1] = (double) pose.getY() / 1000;
  q[2] = (double) pose.getThRad();
  
  cout << "pose: " << pose.getX() << " " << pose.getY() << " " << pose.getTh() << endl;
}


bool PioneerRobot::moveToConfiguration(std::vector< double > configuration)
{
    //return RobotMobile::moveToConfiguration(configuration);
  float x1,y1,theta1;
  x1 = (float) configuration[0] * 1000;
  y1 = (float) configuration[1] * 1000;
  //WARNING test if correct!
  theta1 =  (float) configuration[2] * 180 / M_PI;
  
  ArPose pose(x1,y1,theta1);
  
  cout << "Robot pioneer info: " ;
  cout << "moving to: " << x1 << " " << y1 << " " << theta1 << endl;
    
  pioneer.setDeltaHeading( pioneer.findDeltaHeadingTo(pose));

  while(!pioneer.isHeadingDone()){
  }
  
  pioneer.clearDirectMotion();
  
  actionGoTo.setGoal(pose);
  while(!actionGoTo.haveAchievedGoal()){
  }
 
  pioneer.setHeading(theta1);
  while(!pioneer.isHeadingDone()){
  }
  
  pioneer.clearDirectMotion();
  
//   pose = pioneer.getPose();
//   currentConfig[0] = pose.getX() / 1000;
//   currentConfig[1] = pose.getY() / 1000;
//   currentConfig[2] = pose.getThRad();
  
  return true;
}



double PioneerRobot::validateAngle(double angle)
{
  if(angle > M_PI)
    return (-2 * M_PI + angle);
  
  if(angle < -M_PI)
    return (2*M_PI - angle);
  
  return angle;
}


void PioneerRobot::MoveBackward()
{
pioneer.setVel2( -120, -120 );
}

void PioneerRobot::MoveForward()
{
pioneer.setVel2( 120, 120 );
}

void PioneerRobot::SpinLeftSlow()
{
pioneer.setVel2( 30, 110); 
}

void PioneerRobot::SpinRightSlow()
{
pioneer.setVel2( 110, 30); 
}

void PioneerRobot::SpinLeftFast()
{
pioneer.setVel2( 30, 150); 
}

void PioneerRobot::SpinRightFast()
{
pioneer.setVel2( 150, 30); 
}