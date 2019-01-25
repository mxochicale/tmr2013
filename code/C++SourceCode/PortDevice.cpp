//Implementation for the PortDevice Class (PortDevice.h)
#include "PortDevice.h"

PortDevice::PortDevice()
{
 system("./usbresetapplication");  //Reset the ZSTAR USB Stick
//  for (int a=0; a <13; a++){ cout << " . "  << endl; usleep(500000); } // 6 seconds delay
//  FD = 0; // initialize File Descriptor
 PortDevice::AllocatePortDevice();
 PortDevice::ConfigPortDevice();
}

int PortDevice::AllocatePortDevice()
{
  FD = open(USBDEVICE1, O_RDWR | O_NONBLOCK);      
  if(FD == -1) // if open is unsucessful
  {
      printf("open_port: Unable to open /dev/ttyACMX. \n");
      return -1;
  }
  else
  {
  fcntl(FD, F_SETFL, O_NONBLOCK);     // make the reads non-blocking
  }     
}

//private variables for BAUDIOS SPEED
int PortDevice::ConfigPortDevice() // User Parameters (9600)
{
	struct termios options;      // structure to store the port settings in

// 	http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
	memset (&options, 0, sizeof options);

 	tcgetattr(FD, &options); // Get current terminos configuration


	// Force termios values (should not be needed, but is)
	options.c_cflag = B9600;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_iflag = IGNPAR | IGNBRK;

	//	http://www.unixwiz.net/techtips/termios-vmin-vtime.html
	//	 Understanding UNIX termios VMIN and VTIME
// 	options.c_cc[VTIME] = 0;   //original
	options.c_cc[VTIME] = 0;            // 0.5 seconds read timeout
// 	        newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */
	options.c_cc[VMIN] = 1;  // should_block ? 1 : 0;
// 	"Blocking" sets whether a read() on the port waits for the specified number of characters to arrive. 
// 	Setting no blocking means that a read() returns however many characters are available without waiting for more, up to the buffer limit.
	
	//    VMIN specifies the minimum number of characters to read.
	//    If VTIME is set to 0 (the default), reads will block (wait) indefinitely unless the NDELAY option is set on the port with open or fcntl.

	cfsetispeed(&options, B9600); // In speed
	cfsetospeed(&options, B9600); // Output speed

	// Set communication flags
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_cflag |= (CLOCAL | CREAD); // Enable the receiver and set local mode...
	options.c_cflag &= ~PARENB; // Desactive bit de parité
	options.c_cflag &= ~CSTOPB; // Desactive 2 stop bits -> Active 1 stop bits
	options.c_cflag &= ~CSIZE; // Desactive le bit "CSIZE"
	options.c_cflag |= CS8; // Communication sur 8 bits

	options.c_oflag &= ~OPOST; // Raw output is selected by resetting the OPOST option in the c_oflag member:

	// Disable flow control
	options.c_iflag &= ~(IXON | IXOFF);

	tcsetattr(FD, TCSANOW, &options);    // apply the settings to the port

	// Empty buffer
	tcflush(FD, TCIOFLUSH);
}

int PortDevice::GetPortDevice()
{
   return FD;
}

void PortDevice::ClosePortDevice()
{ 
  close(FD);
}


void PortDevice::CleanPortDevice()
{
 tcflush(FD, TCIOFLUSH);
}
