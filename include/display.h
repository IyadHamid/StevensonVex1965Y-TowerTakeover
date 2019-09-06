/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      5 Aug 2019                                                */
/*    Description:  Display class defintion                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#pragma once

using namespace std;
using namespace vex;

//Notification handler
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
