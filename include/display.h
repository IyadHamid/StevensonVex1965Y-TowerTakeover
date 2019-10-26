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

class notifier {
  /**
   *@brief handles and executes notifications
   */

public:
  /**
   *@brief initalize notifier object
   *@param controller::lcd single controller screen
   */
  notifier(controller::lcd);

  /**
   *@brief initalize notifier object
   *@param vector<controller::lcd> vector of screens
   */
  notifier(vector<controller::lcd>);
  ~notifier();

  /**
   *@brief Starts marquee scroll text of all present notifications
   */
  void startNotifications();

  /**
   *@brief Stops text scroll
   */
  void stopNotifications();

  /**
   *@brief Is the notification already there
   *@return boolean found?
   *@param string notification
   */
  bool hasNotification(string);

  /**
   *@brief Adds notification to list
   *@param string notification
   */
  void addNotification(string);

  /**
   *@brief Removes notification from list
   *@param string notification
   */
  void removeNotification(string);

  /**
   *@brief Clear notifcation list
   */
  void clearNotification();

private:
  void shiftNotifications(int = 0);

  vector<controller::lcd> lcds;

  static const int nfsSize = 10;
  string nfs[nfsSize]; // nfs = notifications
  int nfsSlot = 0;
  bool running;
};

class cGUI {
  /**
   *@brief Controller GUI
   */
public:
  cGUI(controller::lcd);
  cGUI(vector<controller::lcd>);
  ~cGUI();

  enum direction { right, left, none };
  enum options { Primary, Speed, Arcade };
  options opt = Primary;

  /**
   *@brief controls GUI elements
   *@param direction direction to move
   *@param bool toggle current elem?
   */
  void control(direction, bool);

  /**
   *@brief Updates the screen
   */
  void update();

  /**
   *@brief Toggle current element
   */
  void toggle();

  /**
   *@brief shifts elemnts in a direction with loop
   *@param direction shift in a
   *@param amount to shift
   */
  void shift(direction, int = 1);

private:
  vector<controller::lcd> lcds;
  int index;

  bool settings[3] = {0, 0, 0}; // false = 0
  bool running;
};