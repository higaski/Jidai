# Jidai
Jidai is a miniature single header library for generating compilation time stamps from the [standard preprocessor defines](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html) \__DATE__ and \__TIME__.

The lib comes with two different functions.

One which returns the compilation time as plain struct with integer values for date and time.

```cpp
  constexpr CompilationTime make_compilation_time();

  struct CompilationTime {
    uint8_t day{};
    uint8_t month{};
    uint16_t year{};
    uint8_t hour{};
    uint8_t minute{};
    uint8_t second{};
  };
```

And one which returns a unix time stamp since an epoch passed in. The default here is the classic unix epoch 1/1/1970.
```cpp
  inline constexpr CompilationTime default_epoch{.day = 1, .month = 1, .year = 1970};

  template<typename T = time_t>
  constexpr T make_unix_compilation_time(CompilationTime epoch = default_epoch);
```

The src/test folder contains a little test case which i checked against the unix time stamp converter on [unixtimestamp.com](https://www.unixtimestamp.com/index.php).
```cpp
  #include <iostream>
  #include "jidai.hpp"

  int main() {
    constexpr auto ct{jidai::make_compilation_time()};
    constexpr auto ut{jidai::make_unix_compilation_time()};
    
    std::cout << "Test compiled at " << (int)ct.day << "/" 
              << (int)ct.month << "/" << (int)ct.year << " " 
              << (int)ct.hour << ":" << (int)ct.minute << ":" 
              << (int)ct.second << " which equals " << ut 
              << "seconds since 1/1/1970.\n";
  }
```
