#include <buttonManager.hpp>
#include <buttonSubscriber.hpp>
#include <dataManager.hpp>
#include <lcdScreen.hpp>
#include <pwmController.hpp>
#include <thermocoupleReceiver.hpp>
#include <chrono>
#include <memory>
#include <signal.h>
#include <stdio.h>
#include <thread>

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
  if (wiringPiSetup() == -1)
    exit(1);

  auto buttonManager = std::make_shared<ButtonManager>();
  auto lcdScreen = std::make_shared<LcdScreen>();
  auto dataManager = std::make_shared<DataManager>(buttonManager, lcdScreen);

  auto thermocoupleReceiver =
      std::make_shared<ThermocoupleReceiver>(dataManager);
  auto subscriber = std::make_shared<ButtonSubscriber>(buttonManager);
  auto pwmController = std::make_shared<PwmController>();

  /* Start event loops */
  std::thread buttonManagerThread(&ButtonManager::startEventLoop, buttonManager,
                                  std::ref(terminate));
  std::thread dataManagerThread(&DataManager::startEventLoop, dataManager,
                                std::ref(terminate));
  std::thread thermocoupleThread(&ThermocoupleReceiver::startEventLoop,
                                 thermocoupleReceiver, std::ref(terminate));
  std::thread pwmControllerThread(&PwmController::startEventLoop, pwmController,
                                  std::ref(terminate));

  buttonManagerThread.join();
  dataManagerThread.join();
  thermocoupleThread.join();
  pwmControllerThread.join();
}
