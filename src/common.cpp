/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       common.h                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      1 Jan 2020                                                */
/*    Description:  Common C++ Functionality                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <sstream>
#include "common.h"

using namespace std;

template <typename T> string to_string(const T &n) {
  //for some reason unavalible in std
  ostringstream stm;
  stm << n;
  return stm.str();
}

void fn_null() {/*Does nothing*/}

int getAnswerToLifeTheUniverseAndEverything() {
  return 42; //Need to use a simulation for 1,000,000 years.
}