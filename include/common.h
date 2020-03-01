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

//Value, Delta, Actual
#define within_tolerance(A,B,C) (C-B <= A && A <= C+B)
#define task_cast (int(*)())

using namespace std;

const double pi = 3.14159265;

/**
 * @brief turns everything into a string
 * @return string from input
 * @param T anything
 */
template <typename T> string to_string(const T &n) {
  //avalible in newer versions of c++
  ostringstream stm;
  stm << n;
  return stm.str();
}

/**
 * @brief Null function
 */
void fn_null();

/**
 * @brief gets the answer to life, the universe, and everything
 * @return int the answer
 */
int getAnswerToLifeTheUniverseAndEverything();
