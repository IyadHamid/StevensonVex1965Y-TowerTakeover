/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.cpp                                               */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  Function functionality for display.h                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "components.h"
#include "display.h"

using namespace std;
using namespace vex;

//notifier Class

notifier::notifier(controller::lcd nlcd) : lcd({nlcd}) {}

notifier::notifier(vector<controller::lcd> nlcd) : lcd(nlcd) {}

void notifier::startNotifications() {
  running = true;
  string notifications;

  for (const string &inf : nfs) {
    if (inf != "")
      notifications += " | " + inf;
  }
  while (running) {
    for (controller::lcd ilcd : lcd) {
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
  if (!hasNotification(nf)) return;
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

//cGUI Class

cGUI::cGUI(controller::lcd nlcd) : lcd(nlcd) {}

void cGUI::update() {
  lcd.clearLine(1);
  lcd.clearLine(2);
  lcd.setCursor(1, 1);
  lcd.print(options[index].c_str());
  lcd.setCursor(2, 1);
  lcd.print(settings[options[index]]);
}

void cGUI::toggle() {
  settings[options[index]] = !settings[options[index]];
  if (options[index] == "Orange") {
    pickOrange = settings[options[index]];
  }
  else if (options[index] == "Green") {
    pickGreen = settings[options[index]];
  }
  else if (options[index] == "Purple") {
    pickPurple  = settings[options[index]];
  }
  update();
}

void cGUI::shift(direction dir, int amount) {
  switch (dir) {
    case right:
      index = (index+amount) % settings.size();
      break;
    case left:
      index = (index+settings.size()-(amount%settings.size())) % settings.size();
      break;
  }
  update();
}