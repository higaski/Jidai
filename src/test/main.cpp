#include <iostream>
#include "jidai.hpp"

int main() {
  constexpr auto ct{jidai::make_compilation_time()};
  constexpr auto ut{jidai::make_unix_compilation_time()};

  std::cout << "Test compiled at " << (int)ct.day << "/" << (int)ct.month << "/"
            << (int)ct.year << " " << (int)ct.hour << ":" << (int)ct.minute
            << ":" << (int)ct.second << " which equals " << ut
            << " seconds since 1/1/1970.\n";
}