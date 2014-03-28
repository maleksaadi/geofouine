#include <iostream>
#include <csv-ostream>


int main()
{
  csv::csv_ostream test(std::cout);

  test << "ta\"t\",a" << 3 << true << 33 << std::endl;

  return 0;
}
