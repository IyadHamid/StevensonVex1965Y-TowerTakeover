/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       display.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      5 Aug 2019                                                */
/*    Description:  Display class defintion                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <map>
#include <vector>


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
   *@param controller::lcd single controller screen
   */
  notifier(controller::lcd);

  /*
   *@brief initalize notifier object
   *@param vector<controller::lcd> vector of screens
   */
  notifier(vector<controller::lcd>);
  ~notifier();

  /*
   *@brief Starts marquee scroll text of all present notifications
   */
  void startNotifications();

  /*
   *@brief Stops text scroll
   */
  void stopNotifications();

  /*
   *@brief Is the notification already there
   *@return boolean found?
   *@param string notification
   */
  bool hasNotification(string);

  /*
   *@brief Adds notification to list
   *@param string notification
   */
  void addNotification(string);

  /*
   *@brief Removes notification from list
   *@param string notification
   */
  void removeNotification(string);

  /*
   *@brief Clear notifcation list
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
  cGUI(controller);
  ~cGUI();

  enum direction { right, left };

  void control();
  void update();
  void toggle();
  void shift(cGUI::direction, int = 1);

private:
  controller Controller;
  int index;

  string options[4] = {"Orange", "Green", "Purple", "Primary"};
  map<string, bool> settings = {{"Orange", false},
                                {"Green", false},
                                {"Purple", false},
                                {"Primary", false}};
  bool running;
};