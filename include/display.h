/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      5 Aug 2019                                                */
/*    Description:  Display class defintion                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <vector>
#include <map>

#include "vex.h"

using namespace std;
using namespace vex;

class notifier {
/*
*@brief handles and executes notifications
*/

public:

  /*
   *@brief initalize notifier object
   *@return none
   *@param controller::lcd nlcd, single controller
   */
  notifier(controller::lcd);

  /*
   *@brief initalize notifier object
   *@return none
   *@param vector<controller::lcd> nlcd, vector of screens
   */
  notifier(vector<controller::lcd>);
  ~notifier();


  /*
   *@brief Starts marquee scroll text of all present notifications
   *@return none
   *@param none
   */
  void startNotifications();

  /*
   *@brief Stops text scroll
   *@return none
   *@param none
   */
  void stopNotifications();

  /*
   *@brief Is the notification already there
   *@return boolean, found or not
   *@param string, notification
   */
  bool hasNotification(string);

  /*
   *@brief Adds notification to list
   *@return none
   *@param string, notification
   */
  void addNotification(string);
  
  /*
   *@brief Removes notification from list
   *@return none
   *@param string, notification
   */
  void removeNotification(string);

  /*
   *@brief Clear notifcation list
   *@return none
   *@param none
   */
  void clearNotification();

private:
  void shiftNotifications(int = 0);

  vector<controller::lcd> lcd;

  static const int nfsSize = 10;
  string nfs[nfsSize]; // nfs = notifications
  int nfsSlot = 0;
  bool running;
};

class cGUI {
  public:
    cGUI(controller::lcd);
    ~cGUI();

    enum direction {right, left};

    void update();
    void toggle();
    void shift(cGUI::direction, int = 1);

  private:
    controller::lcd lcd;
    int index;

    string options[4] = {"Orange", "Green", "Purple", "Primary"};
    map<string, bool> settings = { {"Orange", false}, {"Green", false}, 
                                   {"Purple", false}, {"Primary", false} };
    bool running;

};