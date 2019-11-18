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

// notifier Class

notifier::notifier(controller::lcd nlcd) : lcds({nlcd}) {}

notifier::notifier(vector<controller::lcd> nlcd) : lcds(nlcd) {}

void notifier::startNotifications() {
  running = true;
  string notifications;
  motor motors[] = {frontLeft,  backLeft, frontRight, backRight,
                    intakeLift, cubeLift, intakeLeft, intakeRight};
  for (const string &inf : nfs) {
    if (inf != "")
      notifications += " | " + inf;
  }
  while (running) {
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

void notifier::stopNotifications() { running = false; }

bool notifier::hasNotification(string nf) {
  for (const string &inf : nfs) {
    if (nf == inf) {
      return true;
    }
  }
  return false;
}

void notifier::addNotification(string nf) {
  if (hasNotification(nf))
    return;
  if (nfsSlot >= nfsSize) {
    shiftNotifications();
  } else {
    nfsSlot++;
  }
  nfs[nfsSlot - 1] = nf;
}

void notifier::removeNotification(string nf) {
  if (!hasNotification(nf))
    return;
  for (int i = 0; i < nfsSize; i++) {
    if (nf == nfs[i]) {
      shiftNotifications(i);
      nfsSlot--;
    }
  }
}

void notifier::clearNotification() { fill_n(nfs, nfsSize, ""); }

void notifier::shiftNotifications(int skip) {
  for (int i = skip; i < nfsSize - 1; i++) {
    nfs[i] = nfs[i + 1];
  }
  nfs[nfsSize - 1] = "";
}

// cGUI Class

cGUI::cGUI(controller::lcd nlcd) : lcds({nlcd}) {}

cGUI::cGUI(vector<controller::lcd> nlcd) : lcds(nlcd) {}

void cGUI::update() {
  options opt = (options)index;
  for (controller::lcd ilcd : lcds) {
    ilcd.clearLine(1);
    ilcd.setCursor(1, 1);
    ilcd.print("%s:\t%s", 
               opt == Primary ? "Primary" : 
               opt == Speed ? "Speed" : 
               "Arcade",
               settings[opt] ? "True" : "False");
  }
}

void cGUI::toggle() {
  settings[index] = !settings[index];
  switch ((options)index) {
  case Primary:
    break;
  case Speed:
    break;
  case Arcade:
    break;
  }
  update();
}

void cGUI::shift(direction dir, int amount) {
  const int n = 3;
  switch (dir) {
  case right:
    index = (index + amount) % n;
    break;
  case left:
    index = (index + n - (amount % n)) % n;
    break;
  case none:
    break;
  }
  update();
}