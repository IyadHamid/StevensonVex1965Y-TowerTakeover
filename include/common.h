/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       common.h                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      6 Aug 2019                                                */
/*    Description:  Common C++ Functionality                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <sstream>

template <typename T> std::string to_string(const T &n) {
  std::ostringstream stm;
  stm << n;
  return stm.str();
}