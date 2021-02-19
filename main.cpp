#include "tempctrl.hpp"
#include "buttonManager.hpp"
#include "buttonSubscriber.hpp"
#include <signal.h>
#include <memory>

/* Terminate processing flag */
bool terminate = false;
  
void sigHandler(int signum)
{
  terminate = true; 
}

int main()
{
  /* Signal traps for various inturrupts */
  signal(SIGINT, sigHandler); /* Ctrl + C */

  ButtonManager *buttonManager = new ButtonManager;
  ButtonSubscriber *subscriber = new ButtonSubscriber(*buttonManager);
  
  /* Add GPIO 26 to the list of GPIO's for the button manager to query */
  /* Since this call creates the button objects.  It must be called    */
  /* before subscribers can subscribe to the button. */
  // buttonManager->addButton(Button(26));
  
  /* Subscribe to GPIO 26 notifications                                */
  /* The whole buttonSubscriber class is temporary until it works and  */
  /* can be simplified as much as possible.  Each functional element   */
  /* will independantly subscribe to buttons that it needs.            */
  // subscriber->subscribe(26); 
   
  TempCtrl tc;
  tc.getTemp(0);
  // TODO: this should be void parameters.  Make a setter for
  // the scale and make this value private
  tc.printTemp(tc.tempScaleVal);

  /* Start event loops */
  buttonManager->startEventLoop(terminate);
  while(!terminate)
  {
    // TODO Why do I have this here.  This should be in a loop on
    // it's own thread.  Like the button Manager
    static float previousTemp = tc.tempStruct.back().temp;
    tc.getTemp(0);
    if(previousTemp != tc.tempStruct.back().temp)
    tc.printTemp(tc.tempScaleVal);
  } 
  
  delete subscriber;
  delete buttonManager;
}
