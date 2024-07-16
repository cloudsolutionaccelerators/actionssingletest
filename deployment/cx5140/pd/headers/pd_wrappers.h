/**
* @brief This file contains pd wrappers for read
*        and write to isolate the low level read
*        and writes from the container.
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#ifndef __PD_HEADERS_PD_WRAPPERS_H__
#define __PD_HEADERS_PD_WRAPPERS_H__

#include <functional>

namespace pd::wrappers {
enum class Std_ReturnType { READ_OK, READ_FAILED };

template <typename T>
inline bool readData(std::function<Std_ReturnType(T)> read_func, T output) {
  const Std_ReturnType result = read_func(output);
  bool success = true;

  if (result != Std_ReturnType::READ_OK)
    success = false;

  return success;
}

template <typename T>
inline bool writeData(std::function<Std_ReturnType(T&)> write_func, T& input) {
  const Std_ReturnType result = write_func(input);
  bool success = true;

  if (result != Std_ReturnType::READ_OK)
    success = false;

  return success;
}
}  // namespace pd::wrappers
#endif