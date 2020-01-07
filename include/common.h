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

using namespace std;

const double pi = 3.14159265;

/**
 * @brief turns everything into a string
 * @return string from input
 * @param T anything
 */
template <typename T> string to_string(const T &n);

/**
 * @brief Null function
 */
void fn_null();
