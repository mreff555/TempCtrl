#include "buttonManager.hpp"
#include "tempdatamanager.hpp"
#include "tempctrl.hpp"
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
  TempDataManager *tempDataManager = new TempDataManager(*buttonManager);
    
  
  TempCtrl tc;
  tc.getTemp(0);
  // TODO: this should be void parameters.  Make a setter for
  // the scale and make this value private
  tc.printTemp(tc.tempScaleVal);

  /* Start event loops */
  std::thread buttonManagerThread(&ButtonManager::startEventLoop, buttonManager, std::ref(terminate));
  std::thread tempCtrlThread(&TempCtrl::startEventLoop, &tc, std::ref(terminate));
  
  buttonManagerThread.join();
  tempCtrlThread.join();

  delete subscriber;
  delete buttonManager;
}
