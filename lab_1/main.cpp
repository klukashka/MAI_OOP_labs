#include <iostream>
#include "include/number_is_clear.h"

int main()
{
  long long int number;
  std::cout << "enter left value: ";
  std::cin  >> number;

  std::cout << "result: " << number_is_clear(number) << std::endl;

  return 0;
}