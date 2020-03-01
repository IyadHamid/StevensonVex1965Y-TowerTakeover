/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.cpp                                               */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  Functionality for display.h                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "display.h"
#include "common.h"

using namespace std;
using namespace vex;

// NotificationHandler Class

NotificationHandler::NotificationHandler(controller::lcd nlcd) : lcds({nlcd}) {}

NotificationHandler::NotificationHandler(vector<controller::lcd> nlcd) : lcds(nlcd) {}

void NotificationHandler::startNotifications() {
  running = true;
  string notifications;
  //Array of all the motors
  motor motors[] = {topLeft,  bottomLeft, topRight, bottomRight,
                    intakeLift, tray, intakeLeft, intakeRight};
  for (const string &inf : nfs) {
    if (inf != "")
      notifications += " | " + inf;
  }
  while (running) {
    //Adds overheated motors to the notifications
    for (int i = 0; i < sizeof(motors) / sizeof(motors[0]); i++) {
      if (motors[i].temperature(percentUnits::pct) > 50) {
        addNotification(
            to_string(motors[i].index()) + " AT " +
            to_string(motors[i].temperature(temperatureUnits::celsius)) + "C");
      }
    }

    for (controller::lcd ilcd : lcds) {
      ilcd.clearLine(3);
      ilcd.setCursor(3, 0);
      ilcd.print(notifications.c_str());
    }
    notifications = notifications.substr(1) +
                    notifications[0]; // Place first character in the end
    this_thread::sleep_for(200);
  }
}

void NotificationHandler::stopNotifications() { running = false; }

bool NotificationHandler::hasNotification(string nf) {
  for (const string &inf : nfs) {
    if (nf == inf) {
      return true;
    }
  }
  return false;
}

void NotificationHandler::addNotification(string nf) {
  if (hasNotification(nf))
    return;
  if (nfsSlot >= nfsSize) {
    shiftNotifications();
  } else {
    nfsSlot++;
  }
  nfs[nfsSlot - 1] = nf;
}

void NotificationHandler::removeNotification(string nf) {
  if (!hasNotification(nf))
    return;
  for (int i = 0; i < nfsSize; i++) {
    if (nf == nfs[i]) {
      shiftNotifications(i);
      nfsSlot--;
    }
  }
}

void NotificationHandler::clearNotification() { fill_n(nfs, nfsSize, ""); }

void NotificationHandler::shiftNotifications(int skip) {
  //Shift notifications to the left and deletes 'skip' elements
  for (int i = skip; i < nfsSize - 1; i++) {
    nfs[i] = nfs[i + 1];
  }
  nfs[nfsSize - 1] = "";
}

// ControlGui Class
ControlGui::ControlGui(controller::lcd nlcd) : lcds({nlcd}) {}

ControlGui::ControlGui(vector<controller::lcd> nlcd) : lcds(nlcd) {}

void ControlGui::update() {
  options opt = (options)index;
  for (controller::lcd ilcd : lcds) {
    ilcd.clearLine(1);
    ilcd.setCursor(1, 1);
    ilcd.print("%s:\t%s", 
               opt == Unjam ? "Unjam" : 
               opt == Speed ? "Speed" : 
               "Arcade",
               settings[opt] ? "True" : "False");
  }
}

void ControlGui::toggle() {
  settings[index] = !settings[index];
  update();
}

void ControlGui::shift(direction dir, int amount) {
  const int n = 3;
  switch (dir) {
  case right:
    //Right shift in range (add)
    index = (index + amount) % n;
    break;
  case left:
    //Left shift in range (subtract)
    index = (index + n - (amount % n)) % n;
    break;
  case none:
    break;
  }
  update();
}

void ControlGui::setOption(ControlGui::options opt, bool val) {
  settings[opt] = val;
}