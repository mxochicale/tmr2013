#include "Hridd.h"

int main() {  
  
  Hridd waltz;
  
  waltz.SetACCFrameWord(10);
  while(   !waltz.Kbhit()   )
  {
      waltz.GestureControl();
   
  }

  return 0;
}