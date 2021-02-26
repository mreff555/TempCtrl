#include "buttonManager.hpp"
#include "dataManager.hpp"
#include "thermocoupleReceiver.hpp"
#include "lcdScreen.hpp"
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
  LcdScreen *lcdScreen = new LcdScreen();
  DataManager *dataManager = new DataManager(*buttonManager, *lcdScreen);
  ThermocoupleReceiver *thermocoupleReceiver = new ThermocoupleReceiver(*dataManager);
  ButtonSubscriber *subscriber = new ButtonSubscriber(*buttonManager);
    
  /* Start event loops */
  std::thread buttonManagerThread(
    &ButtonManager::startEventLoop, buttonManager, std::ref(terminate));
  std::thread dataManagerThread(
    &DataManager::startEventLoop, dataManager, std::ref(terminate));
  std::thread thermocoupleThread(
    &ThermocoupleReceiver::startEventLoop, thermocoupleReceiver, std::ref(terminate));
  
  buttonManagerThread.join();
  dataManagerThread.join();
  thermocoupleThread.join();

  delete lcdScreen;
  delete subscriber;
  delete thermocoupleReceiver;
  delete dataManager;
  delete buttonManager;
}
