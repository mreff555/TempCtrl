#include "tempctrl.hpp"
#include "buttonManager.hpp"
#include "buttonSubscriber.hpp"
#include <signal.h>
#include <memory>

// For now, I'm keeping this global. The loop below is not the only loop that
// needs a term signal.  I'll figure out a better way of handling this eventually.
bool terminate = false;

void sigHandler(int signum)
{
  terminate = true; 
}

int main()
{
  TempCtrl tc;

  ButtonManager *buttonManager = new ButtonManager;
  ButtonSubscriber *subscriber = new ButtonSubscriber(*buttonManager);
  
  signal(SIGINT, sigHandler); 

  tc.getTemp(0);
  // TODO: this should be void parameters.  Make a setter for
  // the scale and make this value private
  tc.printTemp(tc.tempScaleVal);

  while(!terminate)
  {
    // TODO Why do I have this here.  This should be in a loop on
    // it's own thread.  Like the button Manager
    static float previousTemp = tc.tempStruct.back().temp;
    tc.getTemp(0);
    if(previousTemp != tc.tempStruct.back().temp)
    tc.printTemp(tc.tempScaleVal);
  } 
  
  //subscriber->unsubscribe();
  delete subscriber;
  delete buttonManager;
}
