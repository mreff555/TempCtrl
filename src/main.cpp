#include "buttonManager.hpp"
#include "dataManager.hpp"
#include "thermocoupleReceiver.hpp"
#include "lcdScreen.hpp"
#include "buttonSubscriber.hpp"
#include "pwmController.hpp"
#include <signal.h>
#include <memory>
#include <chrono>
#include <thread>
#include <stdio.h>

/* Terminate processing flag */
bool terminate = false;
  
void sigHandler(int signum)
{
  terminate = true;
  printf("Terminated on sig %d\n", signum); 
}

int main()
{
  /* Signal traps for various inturrupts       */
  signal(SIGINT, sigHandler);  /* Ctrl + C     */
  signal(SIGQUIT, sigHandler); /* Ctrl + D     */
  signal(SIGHUP, sigHandler);  /* On pty close */
  signal(SIGTERM, sigHandler); /* On term sig  */

  /* Since multiple threads currently need     */
  /* Wiring Pi to initialize, we call it here. */
  if(wiringPiSetup() == -1) exit(1);

  ButtonManager *buttonManager = new ButtonManager;
  LcdScreen *lcdScreen = new LcdScreen();
  DataManager *dataManager = new DataManager(*buttonManager, *lcdScreen);
  ThermocoupleReceiver *thermocoupleReceiver = new ThermocoupleReceiver(*dataManager);
  ButtonSubscriber *subscriber = new ButtonSubscriber(*buttonManager);
  // PwmController *pwmController = new PwmController();
    
  /* Start event loops */
  std::thread buttonManagerThread(
    &ButtonManager::startEventLoop, buttonManager, std::ref(terminate));
  std::thread dataManagerThread(
    &DataManager::startEventLoop, dataManager, std::ref(terminate));
  std::thread thermocoupleThread(
    &ThermocoupleReceiver::startEventLoop, thermocoupleReceiver, std::ref(terminate));
  // std::thread pwmControllerThread(
  //   &PwmController::startEventLoop, pwmController, std::ref(terminate));  

  buttonManagerThread.join();
  dataManagerThread.join();
  thermocoupleThread.join();
  // pwmControllerThread.join();

  delete lcdScreen;
  delete subscriber;
  delete thermocoupleReceiver;
  delete dataManager;
  delete buttonManager;
  // delete pwmController;
}
