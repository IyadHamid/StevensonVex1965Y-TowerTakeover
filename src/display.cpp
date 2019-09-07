/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.cpp                                               */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  Function functionality for display.h                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "display.h"

using namespace std;
using namespace vex;

/*
 *@brief initalize notifier object
 *@return none
 *@param controller::lcd nlcd, single controller
 */
notifier::notifier(controller::lcd nlcd) : lcd({nlcd}) {}

/*
 *@brief initalize notifier object
 *@return none
 *@param vector<controller::lcd> nlcd, vector of screens
 */
notifier::notifier(vector<controller::lcd> nlcd) : lcd(nlcd) {}

/*
 *@brief Starts marquee scroll text of all present notifications
 *@return none
 *@param none
 */
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

/*
 *@brief Stops text scroll
 *@return none
 *@param none
 */
void notifier::stopNotifications() { running = false; }

/*
 *@brief Is the notification already there
 *@return boolean, found or not
 *@param string, notification
 */
bool notifier::hasNotification(string nf) {
  for (const string &inf : nfs) {
    if (nf == inf) {
      return true;
    }
  }
  return false;
}

/*
 *@brief Adds notification to list
 *@return none
 *@param string, notification
 */
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

/*
 *@brief Removes notification from list
 *@return none
 *@param string, notification
 */
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

/*
 *@brief Clear notifcation list
 *@return none
 *@param none
 */
void notifier::clearNotification() { fill_n(nfs, nfsSize, ""); }

/*
 *@brief Shifts elements to the left except for one
 *@return none
 *@param int, index to remove
 */
void notifier::shiftNotifications(int skip) {
  for (int i = skip; i < nfsSize - 1; i++) {
    nfs[i] = nfs[i + 1];
  }
  nfs[nfsSize - 1] = "";
}
