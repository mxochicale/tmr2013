//Header for the Zxtar Class (Zxtar.h)
#ifndef ZXTAR_H
#define ZXTAR_H

#include <iostream>  // std::cout, std::endl

#include <unistd.h>   //kbhit for GNU/Linux linux
#include <fstream>  // MEAN AND STANDARD DEVIATION
#include <cmath>
#include <cstdlib>

#include <stdio.h>  //Timer
#include <stdlib.h>  //Timer
#include <sys/time.h> //Timer

// http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison
#include <cmath>
#include <limits>


#include <vector> // dataRead and saving as a vector variable

#include "PortDevice.h" //PortDevice Class



using namespace std;

/**  Zxtar class permitis to extract a frame, and compute the avarage and Standar
  *  Deviation, as well to get these values for the X, Y and Z axis. 
  *  The following code is an example for its use; uncomment the code for further test.
  * 
  * 	Zxtar sensor;   // Declaration of the sensor Zstar class type
  * 
  * 	sensor.ACCXFrame();	    // Getting the ACC of the X-axis frame word
  * 
  * 	sensor.ACCXFrameAverage();	// X-axis ACC frame mean
  * 
  *     sensor.ACCXFrameStdDeviation(); // X-axis ACC frame Standard Deviation
  * 
  * 	cout << sensor.GetACCXFrameAvarage() << endl;  //Printing the ACCX value of the frame avarage
  * 
  * 	cout << sensor.GetACCXFrameStdDeviation() << endl;  //Printing the ACCX value of the frame standard deviation
  * 
  */	      

class Zxtar
{
private:
  double _ACCX; // last value of x-axis acceleration
  double _ACCY; // last value of y-axis acceleration
  double _ACCZ; // last value of z-axis acceleration
  double _gnormalization; // g-range value for normalization
  timeval _startTime; // startTime for the Timer function
  bool _AvailableACCAxis(double _getACCval); 
  unsigned int _dtsample;  // For saving the Discrete Time Sample which were measured   (unsigned int: 0 to 4294967295)
  unsigned int _framevalue;
  
  vector<double> _vACCXframeAux;  //vector Auxiliar variable for X Axis ACC frame 
  vector<double> _vACCXframe;  //vector Auxiliar variable for X Axis ACC  frame 
  
  vector<double> _vACCYframeAux;  //vector Auxiliar variable for Y Axis ACC frame 
  vector<double> _vACCYframe;  //vector Auxiliar variable for Y Axis ACC  frame 

  vector<double> _vACCZframeAux;  //vector Auxiliar variable for Z Axis ACC frame 
  vector<double> _vACCZframe;  //vector Auxiliar variable for Z Axis ACC  frame 
  
 double _ACCXframemean; // X-axis ACC frame mean
 double _ACCXframestd;  // X-axis ACC frame Standard Deviation
 
 double _ACCYframemean; // Y-axis ACC frame mean
 double _ACCYframestd;  // Y-axis ACC frame Standard Deviation
 
 double _ACCZframemean; // Z-axis ACC frame mean
 double _ACCZframestd;  // Z-axis ACC frame Standard Deviation
 
 
      //************ Change the name of the member function (Descriptive names)

    
public:
    
  
  
  /**
   * Data Member for the use fo the PortDevice class with the sensor board
   */
  PortDevice ZSTAR; 
  

  /**
   * Default Constructor with the default values for sensitibility and data rate: 2g and 60Hz
   */
  Zxtar();  
  /**
   * Constructor with parameter options, so as the user is able to configure the sensor by using the following values
   * 
   * Zxtar name(g-range, DataRate); 
   * 
   *  ..............|........|
   * 
   *  .............|........|--------- Available Values for DataRate are 30, 60, and 120
   * 
   * .............|------------------- Available Values for g-range parameter are 2, 4, and 8.
   * 
   */
  Zxtar(int gSensitivity, int setRate); // Parameter Constructor 
  

  
  /**
   * To wait until the data is available by using a while loop
   */
  void AvailableACC();
  

  /**
   * Method for the keyboard hit
   */
  int Kbhit (void);
  
  /**
  * Method to select the g-range for the accelerometer Sensor Board
  * BY SENDING A g0 g1 or g2 you are able to change the SENSITIVITY
  * g0 = 8g  ;  g1 = 2g  ; g2 = 4g
  */
  void SetSensitivity(int gSensitivity); //
  
  /**
  * Method to set the Data Rate
  */
  void DataRate(int setRate);
  
  /**
  * Method for the Acceleration Acquisition
  */
  void ACCAcquisition();

  /**
  * Method to get X-axis Acceleration
  */
  double GetACCX();
  
  /**
  *  Method to get Y-axis Acceleration
  */
  double GetACCY();
 
  /**
  *  Method to get Z-axis Acceleration
  */
  double GetACCZ();  
  
  /**
   * Method to print the Acceleartion Values
   */
  void ACCPrint();

  /**
  * Method to start the timer
  */
  void startTimer();
  
  /**
  * Method to stop the timer
  */ 
  double stopTimer();
  
  /**
  * Method to print the timer
  */ 
  static void printTime(double duration);
  
  /** 
  * Method to set the frame word of the acceleration readings
  */
  void SetFrameWord(unsigned int framevalue);

  
  
  
  
  
  /**
   * Method for the adquisition of X-axis data frame
   */
  void ACCXFrame();
  
  /**
   * Method for printing the X-axis data frame 
   */
  void ACCXFramePrint();  
  
  /**
   * Method to compute the X-axis data frame avarage
   */
  double ACCXFrameAverage();
  
  /**
   * Method to get the X-axis data frame avarage
   */
  double GetACCXFrameAvarage();
  
   /**
   * Method to compute the X-axis data frame standard deviation
   */  
  double ACCXFrameStdDeviation();
  
  
   /**
   * Method to get the X-axis data frame standard deviation
   */  
  double GetACCXFrameStdDeviation();

  
  
  
  
  
  /**
   * Method for the adquisition of Y-axis data frame
   */
  void ACCYFrame();
  
  /**
   * Method for printing the Y-axis data frame 
   */
  void ACCYFramePrint();  
  
   /**
   * Method to compute the Y-axis data frame avarage
   */
  double ACCYFrameAverage();
  
  /**
   * Method to get the Y-axis data frame avarage
   */
  double GetACCYFrameAvarage();
  
   /**
   * Method to compute the Y-axis data frame standard deviation
   */  
  double ACCYFrameStdDeviation();

   /**
   * Method to get the Y-axis data frame standard deviation
   */  
  double GetACCYFrameStdDeviation();
  
  
  
  
  
  
  
  /**
   * Method for the adquisition of Z-axis data frame
   */  
  void ACCZFrame();
  /**
   * Method for printing the Z-axis data frame 
   */
  void ACCZFramePrint();  
  
   /**
   * Method to compute the Z-axis data frame avarage
   */
  double ACCZFrameAverage();
  
  /**
   * Method to get the Z-axis data frame avarage
   */
  double GetACCZFrameAvarage();
  
   /**
   * Method to compute the Z-axis data frame standard deviation
   */  
  double ACCZFrameStdDeviation();
   /**
   * Method to get the Z-axis data frame standard deviation
   */  
  double GetACCZFrameStdDeviation();
  
  

  

};
#endif // ZXTAR_H
