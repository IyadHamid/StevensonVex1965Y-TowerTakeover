/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace std;
using namespace vex;

class notifier {
  public:
    notifier(controller::lcd lcd);
    ~notifier();

    void startNotifications();
    void stopNotifications();

    bool hasNotification(string nf);
    void addNotification(string nf);
    void removeNotification(string nf);
    void clearNotification();

  private:
    void shiftNotifications(int skip = 0);

    controller::lcd lcd;

    static const int nfsSize = 10;
    string nfs[nfsSize]; //nfs = notifications
    int nfsSlot = 0;
    bool running = false;
};

notifier::notifier(controller::lcd newlcd) {
  lcd = newlcd;
}

void notifier::startNotifications() {
  running = true;
  string notifications;

  for (const string& inf: nfs) {
    notifications += " | " + inf;
  }
  notifications += " | ";
  while (running) {
    lcd.setCursor(3,0);
    lcd.print(notifications);
    notifications = notifications.substr(1) + notifications[0]; //Place first character in the end
    this_thread::sleep_for(300);
  }
}

void notifier::stopNotifications() {
  running = false;
}

bool notifier::hasNotification(string nf) {
  for (const string& inf: nfs) {
    if (nf == inf) {
      return true;
    }
  }
  return false;
}

void notifier::addNotification(string nf) {
  if (nfsSlot >= nfsSize) {
    shiftNotifications();
  }
  else {
    nfsSlot++;
  }
  nfs[nfsSlot - 1] = nf;
}

void notifier::removeNotification(string nf) {
  for (int i = 0; i < nfsSize; i++) {
    if (nf == nfs[i]) {
      shiftNotifications(i);
      nfsSlot--;
    }
  }
}

void notifier::clearNotification() {
  fill_n(nfs, nfsSize, "");
}

void notifier::shiftNotifications(int skip) {
  for (int i = skip; i < nfsSize - 1; i++) {
    nfs[i] = nfs[i + 1];
  }
  nfs[nfsSize - 1] = "";
}