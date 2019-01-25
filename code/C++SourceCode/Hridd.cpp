//Implementation for Hridd Class (Hridd.cpp)

#include "Hridd.h"




int Hridd::Kbhit(void ) 
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  } 
  return 0;
}

void Hridd::SetACCFrameWord(unsigned int framevalue)
{
    sensor.SetFrameWord(framevalue);
}


void Hridd::GestureControl()
{
  
    sensor.ACCAcquisition();  

    sensor.ACCXFrame();         
    sensor.ACCXFrameAverage();  
    sensor.ACCYFrame();         
    sensor.ACCYFrameAverage();  
    sensor.ACCZFrame();         
    sensor.ACCZFrameAverage();  
    
	    
      if( ( sensor.GetACCYFrameAvarage()<1.1 && sensor.GetACCYFrameAvarage()>0.8)  ) //HAND DOWN
      {robot.SpinLeftFast();}  
      else if(  (  sensor.GetACCYFrameAvarage()<0.8 &&  sensor.GetACCYFrameAvarage()>0.5)   )  //HAND DOWN
      {robot.SpinLeftSlow();} 
      else if  (  (sensor.GetACCYFrameAvarage()<0.5  && sensor.GetACCYFrameAvarage()>-0.3)   )  //HAND IN THE MIDDLE 
	{
	if (sensor.GetACCZFrameAvarage() > 0.5)
	  {robot.MoveBackward();} 	//HAND NORMAL
	else{robot.MoveForward();} 	//HAND UPSIDE-DOWN
	}
      else if  (  (sensor.GetACCYFrameAvarage()<-0.3 && sensor.GetACCYFrameAvarage()>-0.4)   )  // HAND UP
      {robot.SpinRightSlow();}
      else if  (  (sensor.GetACCYFrameAvarage()<-0.4 && sensor.GetACCYFrameAvarage()>-1.1)   )  // HAND UP
      {robot.SpinRightFast();}
      else {}

}


    