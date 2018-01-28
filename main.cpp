#include <stdio.h>
#include <typeinfo>
#include "template_array.h"

using namespace template_array;

int main() {

  static_assert(
    std::is_same<SetElem<1, 5, Array<1,2,3>>, Array<1,5,3>>(),
    "Set failed.");

  static_assert(
    GetElem<2, Array<1, 32, 1337>>() == 1337,
    "Get failed.");

  static_assert(
    std::is_same<Append<4, Array<1,2,3>>, Array<1,2,3,4>>(),
    "Append failed.");

  static_assert(
    std::is_same<Prepend<4, Array<1,2,3>>, Array<4,1,2,3>>(),
    "Prepend failed.");

  static_assert(
    Size<Array<1,2,3>>() == 3,
    "Size failed.");

  return 0;

}
