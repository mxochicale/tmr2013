//Header for the PortDevice Class (PortDevice.h)
#ifndef PORTDEVICE_H
#define PORTDEVICE_H

#include <iostream>
#include <iomanip> // setw( 2 )

#include <stdio.h> //// Serial port libraries     // standard input / output functions
#include <stdlib.h> // system command

#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls

#include <vector> // dataRead and saving as a vector variable

#define USBDEVICE1 "/dev/ttyACM0" 
#define USBDEVICE2 "/dev/ttyACM1"


using namespace std;


class PortDevice
{
private:
 int FD; //PortDevice File Descriptor
 
public:
  /**
   * Constructor to reset, to allocate and configurate the ZSTAR USB Stick 
   */
  PortDevice();
  
  /**
   * SetPortDeviceFD
   */
  int AllocatePortDevice(); //AllocatePortDevice
  
  /**
   * ConfigPortDeviceFD
   */
  int ConfigPortDevice(); 
  
  /**
  * function to get the port's FILE DESCRIPTOR 
  */
  int GetPortDevice(); //GetFD
  
  
  /**
  * function to clean the Port Device
  */
  void CleanPortDevice();
  
  /**
   * ClosePortDevice
   */
  void ClosePortDevice();
  
};

#endif // PORTDEVICE_H
