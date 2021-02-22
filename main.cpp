#include "tempctrl.hpp"
#include "buttonManager.hpp"
#include "buttonSubscriber.hpp"
#include <signal.h>
#include <memory>

#include <chrono>
#include <thread>

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
  
  TempCtrl tc;
  tc.getTemp(0);
  // TODO: this should be void parameters.  Make a setter for
  // the scale and make this value private
  tc.printTemp(tc.tempScaleVal);

  /* Start event loops */
  buttonManager->startEventLoop(terminate);
  //std::thread buttonManagerThread(&ButtonManager::startEventLoop, buttonManager, terminate);
  while(!terminate)
  {
    // TODO Why do I have this here.  This should be in a loop on
    // it's own thread.  Like the button Manager
    static float previousTemp = tc.tempStruct.back().temp;
    tc.getTemp(0);
    if(previousTemp != tc.tempStruct.back().temp)
    tc.printTemp(tc.tempScaleVal);
    std::this_thread::sleep_for(std::chrono::milliseconds(SCAN_RATE));
  } 
  // buttonManagerThread.join();
  delete subscriber;
  delete buttonManager;
}
