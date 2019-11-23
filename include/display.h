/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      5 Aug 2019                                                */
/*    Description:  Display classes defintion                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <map>
#include <vector>

#include "vex.h"

using namespace std;
using namespace vex;

/**
  * @brief handles and executes notifications
*/
class NotificationHandler {
  private:
    void shiftNotifications(int = 0);

    vector<controller::lcd> lcds;

    static const int nfsSize = 10;

    string nfs[nfsSize]; // nfs = notifications

    int nfsSlot = 0;

    bool running;

  public:
    /**
      * @brief initalize NotificationHandler object
      * @param controller::lcd single controller screen
    */
    NotificationHandler(controller::lcd);

    /**
      * @brief initalize NotificationHandler object
      * @param vector<controller::lcd> vector of screens
    */
    NotificationHandler(vector<controller::lcd>);
    ~NotificationHandler();

    /**
     * @brief Starts marquee scroll text of all present notifications
     */
    void startNotifications();

    /**
     * @brief Stops text scroll
     */
    void stopNotifications();

    /**
     * @brief Is the notification already there
     * @return boolean found?
     * @param string notification
     */
    bool hasNotification(string);

    /**
     * @brief Adds notification to list
     * @param string notification
     */
    void addNotification(string);

    /**
     * @brief Removes notification from list
     * @param string notification
     */
    void removeNotification(string);

    /**
     * @brief Clear notifcation list
     */
    void clearNotification();
};

/**
  * @brief Controller GUI
*/
class ControlGui {
  private:
    vector<controller::lcd> lcds;

    int index = 0;
    
    bool running;

  public:
    /**
      * @brief initializes ControlGui with one lcd
    */
    ControlGui(controller::lcd);

    /**
      * @brief initializes ControlGui with multiple lcds in a vector
    */
    ControlGui(vector<controller::lcd>);
    ~ControlGui();
    
    enum direction { right, left, none };

    enum options { Primary, Speed, Arcade };

    bool settings[3] = {0, 0, 0};

    /**
     * @brief Updates the screen
     */
    void update();

    /**
     * @brief Toggle current element
     */
    void toggle();

    /**
     * @brief shifts elemnts in a direction with loop
     * @param direction shift in a
     * @param amount to shift
     */
    void shift(direction, int = 1);
};