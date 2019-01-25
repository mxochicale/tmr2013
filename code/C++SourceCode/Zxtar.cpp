//Implementation for Zxtar Class (Zxtar.cpp)
#include "Zxtar.h"

Zxtar::Zxtar() //Constructor
{
  cout.setf(ios::fixed);  //  This makes cout display floating point values in fixed point notation.
  cout.setf(ios::showpoint);  // Display a decimal and extra zeros, even when not needed.
  cout.precision(4);   //is limiting the precision of your number to 5 decimal places
   
 
  Zxtar::AvailableACC();
  
   Zxtar::SetSensitivity(2); // 2g as a default value for sensitivity
   _gnormalization=63.0; // set the gnormalization value for 2g
   Zxtar::DataRate(60); // 60Hz for a default data rate
   
  _dtsample=-1;  
}

// overloading class constructors //http://www.cplusplus.com/doc/tutorial/classes/
Zxtar::Zxtar(int gSensitivity, int setDataRate)
{  
  switch(gSensitivity){
    case 2: _gnormalization=63.0; break;
    case 4: _gnormalization=31.0; break;
    case 8: _gnormalization=15.0; break;
    default:
      cout << "Unknown operator gSensitivity valuse" << endl;      
  }
  
  cout.setf(ios::fixed);  //  This makes cout display floating point values in fixed point notation.
  cout.setf(ios::showpoint);  // Display a decimal and extra zeros, even when not needed.
  cout.precision(4);   //is limiting the precision of your number to 5 decimal places
  
  
   Zxtar::AvailableACC();
   Zxtar::SetSensitivity(gSensitivity); 
   Zxtar::DataRate(setDataRate);
   
  _dtsample=-1; 
}


bool Zxtar::_AvailableACCAxis(double _getACCval)
{
  return std::fabs(_getACCval ) < std::numeric_limits<double>::epsilon(); //def epsilon 
}



void Zxtar::AvailableACC() // Runs while the sensor is obtainig values different from zero
{
  Zxtar::startTimer();
  bool flagSensorActivation = 0;		
	
  while ( flagSensorActivation==0 )
    {
    Zxtar::ACCAcquisition();  
    flagSensorActivation = !(_AvailableACCAxis(GetACCX()) || _AvailableACCAxis(GetACCY()) ||  _AvailableACCAxis(GetACCZ()) );
  
    usleep(31250);     
    }
    double duration = Zxtar::stopTimer();
    cout << "Sensor Board's  Initialization Time: ";
    Zxtar::printTime(duration);
}



int Zxtar::Kbhit ( void )  // REFERENCE: http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
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

void Zxtar::SetSensitivity(int gSensitivity)
{
  char ZSTARCOMMAND[] = {0x67, 0x32};  // g1 character to set +/- 2g  // variable declararion with a Defautl Value for 2g
  
  switch(gSensitivity) 
  {
    case 2: ZSTARCOMMAND[0] = {0x67}; ZSTARCOMMAND[1] = {0x31}; break; // g1 character to set +/- 2g 
    case 4: ZSTARCOMMAND[0] = {0x67}; ZSTARCOMMAND[1] = {0x32}; break; // g2 character to set +/- 4g
    case 8: ZSTARCOMMAND[0] = {0x67}; ZSTARCOMMAND[1] = {0x30}; break;  // g0 character to set +/- 8g
    default: 
      cout << "Unknown operator for the gSensitivity value" << endl;
//     default: ZSTARCOMMAND[0] = {0x67}; ZSTARCOMMAND[1] = {0x32};  break;  // g0 character to set +/- 8g
  }
  
    const int buffSize = 1024;
    char data_in[buffSize] = {'\0'};
    int count = 0; // set a value zero to the count variable
  
    write(ZSTAR.GetPortDevice(), ZSTARCOMMAND, sizeof (ZSTARCOMMAND));  //Send characters to the USB zstar device
    tcdrain(ZSTAR.GetPortDevice());	// waits until all output written to the object referred to by fd has been transmitted.
  
//     count = read(ZSTAR.GetPortDevice(), data_in, sizeof (data_in));	
//     cout << count << endl;
  
//   cout << "END seting G-range" << endl;
}


void Zxtar::DataRate(int setRate)
{
  char ZSTARCOMMAND[] = {0x4D, 0x32};  // M2 -- 60Hz Default Value
  
   switch(setRate) 
  {
    case 30: ZSTARCOMMAND[0] = {0x4D}; ZSTARCOMMAND[1] = {0x31}; break; // M1 to set 30Hz
    case 60: ZSTARCOMMAND[0] = {0x4D}; ZSTARCOMMAND[1] = {0x32}; break; // M2 to set 60Hz
    case 120: ZSTARCOMMAND[0] = {0x4D}; ZSTARCOMMAND[1] = {0x30}; break; // M0 to set 120Hz
    default: 
      cout << "Unknown operator for the Data Rate value" << endl;
  }
            
   const int buffSize = 1024;
   char data_in[buffSize] = {'\0'};
   int count = 0; // set a value zero to the count variable
  
   write(ZSTAR.GetPortDevice(), ZSTARCOMMAND, sizeof (ZSTARCOMMAND));  //Send characters to the USB zstar device
   tcdrain(ZSTAR.GetPortDevice());	// waits until all output written to the object referred to by fd has been transmitted.
  
//    count = read(ZSTAR.GetPortDevice(), data_in, sizeof (data_in));	
//    cout << count << endl;
}


void Zxtar::ACCAcquisition()
{   
  char ZSTARCOMMAND[] = {0x56}; // V character to get the ACC X Y Z
  const int buffSize = 1024;
  char data_in[buffSize] = {'\0'};
  int count = 0; // set a value zero to the count variable
  
 write(ZSTAR.GetPortDevice(), ZSTARCOMMAND, sizeof (ZSTARCOMMAND));  //Send characters to the USB zstar device
 tcdrain(ZSTAR.GetPortDevice());	// waits until all output written to the object referred to by fd has been transmitted.
 count = read(ZSTAR.GetPortDevice(), data_in, sizeof (data_in));
  
  _ACCX = (double)  data_in[1] / _gnormalization; 
  _ACCY = (double)  data_in[3] / _gnormalization; 
  _ACCZ = (double)  data_in[5] / _gnormalization;
 
  _dtsample = _dtsample++;
   usleep(31250);  // 1/32 = 0.031250
}




double Zxtar::GetACCX()
{
  return _ACCX;
}

double Zxtar::GetACCY()
{
  return _ACCY;
}

double Zxtar::GetACCZ()
{
  return _ACCZ;
}

void Zxtar::ACCPrint()
{
//   cout << ZSTAR.GetACCX() << endl;
//   cout << ZSTAR.GetACCY() << endl;
//   cout << ZSTAR.GetACCZ() << endl;
    cout<< setw(5)  << Zxtar::GetACCX() << setw(10)  << Zxtar::GetACCY()  << setw(10) <<  Zxtar::GetACCZ() << endl;
}




void Zxtar::startTimer()
{
        gettimeofday(&_startTime, NULL);
}

double Zxtar::stopTimer()
{
        timeval endTime;
        long seconds, mseconds;
        double duration;

        gettimeofday(&endTime, NULL);

        seconds  = endTime.tv_sec  - _startTime.tv_sec;
        mseconds = endTime.tv_usec - _startTime.tv_usec;

        duration = seconds + mseconds/1000000.0;

        return duration;
}

void Zxtar::printTime(double duration)
{
        printf("%5.3f seconds\n", duration);
}




void Zxtar::SetFrameWord(unsigned int framevalue)
{
_framevalue = framevalue;
}




void Zxtar::ACCXFrame()
{
//   cout << _dtsample << endl; // display the discrete time sample
  if (  _dtsample % (_framevalue )== 0 ){
      _vACCXframeAux.clear(); 
      _vACCXframeAux.push_back( Zxtar::GetACCX() );
  }
  else{
	_vACCXframeAux.push_back( Zxtar::GetACCX() );  
	    if ( (_dtsample % _framevalue ) == (_framevalue-1)  ){
	      _vACCXframe =_vACCXframeAux ; }
  }
}

void Zxtar::ACCXFramePrint()
{

  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  for(unsigned int i=0;i<_vACCXframe.size();i++)
  {
    cout << _vACCXframe[i] << endl; 
  }
  }
}



double Zxtar::ACCXFrameAverage()
{ 
//   _ACCXframemean = 0; //Clear the last mean value
  
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  double sum=0;
  for(unsigned int i=0;i<_vACCXframe.size();i++)
    sum+=_vACCXframe[i];
  _ACCXframemean = sum/ static_cast<double>(   _vACCXframe.size()  );
//   cout << "ACCX mean: " << _ACCXframemean << endl;
    return _ACCXframemean; 
  }
  
}

double Zxtar::GetACCXFrameAvarage()
{
return _ACCXframemean;
}


double Zxtar::ACCXFrameStdDeviation()
{
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
    double E=0;
    // Quick Question - Can vector::size() return 0?
    double inverse = 1.0 / static_cast<double>(_vACCXframe.size());
    for(unsigned int i=0;i<_vACCXframe.size();i++)
    {
        E += pow(static_cast<double>(_vACCXframe[i]) - _ACCXframemean, 2);
    }
    _ACCXframestd = sqrt(inverse * E);
//     cout << "ACCX Std: " << _ACCXframestd << endl;
    return _ACCXframestd;
  }
}

double Zxtar::GetACCXFrameStdDeviation()
{
    return _ACCXframestd;
}


void Zxtar::ACCYFrame()
{
//   cout << _dtsample << endl; // display the discrete time sample
  if (  _dtsample % (_framevalue )== 0 ){
      _vACCYframeAux.clear(); 
      _vACCYframeAux.push_back( Zxtar::GetACCY() );
  }
  else{
	_vACCYframeAux.push_back( Zxtar::GetACCY() );  
	    if ( (_dtsample % _framevalue ) == (_framevalue-1)  ){
	      _vACCYframe =_vACCYframeAux ; }
  }
}

void Zxtar::ACCYFramePrint()
{

  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  for(unsigned int i=0;i<_vACCYframe.size();i++)
  {
    cout << _vACCYframe[i] << endl; 
  }
  }
}



double Zxtar::ACCYFrameAverage()
{ 
//   _ACCYframemean = 0; //Clear the last mean value
  
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  double sum=0;
  for(unsigned int i=0;i<_vACCYframe.size();i++)
    sum+=_vACCYframe[i];
  _ACCYframemean = sum/ static_cast<double>(   _vACCYframe.size()  );
//   cout << "ACCY mean: " << _ACCYframemean << endl;
    return _ACCYframemean; 
  }
  
}

double Zxtar::GetACCYFrameAvarage()
{
return _ACCYframemean;
}

double Zxtar::ACCYFrameStdDeviation()
{
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
    double E=0;
    // Quick Question - Can vector::size() return 0?
    double inverse = 1.0 / static_cast<double>(_vACCYframe.size());
    for(unsigned int i=0;i<_vACCYframe.size();i++)
    {
        E += pow(static_cast<double>(_vACCYframe[i]) - _ACCYframemean, 2);
    }
    _ACCYframestd = sqrt(inverse * E);
//     cout << "ACCY Std: " << _ACCYframestd << endl;
    return _ACCYframestd;
  }
}

double Zxtar::GetACCYFrameStdDeviation()
{
    return _ACCYframestd;
}





void Zxtar::ACCZFrame()
{
//   cout << _dtsample << endl; // display the discrete time sample
  if (  _dtsample % (_framevalue )== 0 ){
      _vACCZframeAux.clear(); 
      _vACCZframeAux.push_back( Zxtar::GetACCZ() );
  }
  else{
	_vACCZframeAux.push_back( Zxtar::GetACCZ() );  
	    if ( (_dtsample % _framevalue ) == (_framevalue-1)  ){
	      _vACCZframe =_vACCZframeAux ; }
  }
}

void Zxtar::ACCZFramePrint()
{

  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  for(unsigned int i=0;i<_vACCZframe.size();i++)
  {
    cout << _vACCZframe[i] << endl; 
  }
  }
}



double Zxtar::ACCZFrameAverage()
{ 
//   _ACCZframemean = 0; //Clear the last mean value
  
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
  double sum=0;
  for(unsigned int i=0;i<_vACCZframe.size();i++)
    sum+=_vACCZframe[i];
  _ACCZframemean = sum/ static_cast<double>(   _vACCZframe.size()  );
//   cout << "ACCZ mean: " << _ACCZframemean << endl;
    return _ACCZframemean; 
  }
  
}

double Zxtar::GetACCZFrameAvarage()
{
return _ACCZframemean;
}



double Zxtar::ACCZFrameStdDeviation()
{
  if ( (_dtsample % _framevalue ) == (_framevalue-1)  ) { 
    double E=0;
    // Quick Question - Can vector::size() return 0?
    double inverse = 1.0 / static_cast<double>(_vACCZframe.size());
    for(unsigned int i=0;i<_vACCZframe.size();i++)
    {
        E += pow(static_cast<double>(_vACCZframe[i]) - _ACCZframemean, 2);
    }
    _ACCZframestd = sqrt(inverse * E);
//     cout << "ACCZ Std: " << _ACCZframestd << endl;
    return _ACCZframestd;
  }
}





double Zxtar::GetACCZFrameStdDeviation()
{
    return _ACCZframestd;
}





