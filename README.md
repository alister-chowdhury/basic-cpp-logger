# basic-cpp-logger

Basic C++11 logging header.

# Example useage

```cpp

#include "logger/logger.h"
using namespace logging;

void something(int a) {
    DebugLogger(std::cout, "a has a value of", a);

    if(a != 0)
        InfoLogger("a is not 0");

    if(a > 25)
        WarningLogger("Oh goodness a is greater than 25!")

    if(a > 50)
        ErrorLogger(std::cerr, "a cannot be greater than 50!")

    if(a >= 100) {
        CriticalLogger(std::cerr, "a is greater or equal to 100, shutting down!");
        exit(-1);
    }
}
```

---

When ```something``` is called with a value of 100 (so it hits all loggers).

When compiled with no specific flags you can expect to see:

    [Error] a cannot be greater than 50!
    [Critical] a is greater or equal to 100, shutting down!

When compiled with **NO_LOGGING** being defined, nothing will print and
the program will simply exit (this overrides all other flags).

When compiled with **DEBUG** or **LOG_EVERYTHING**

    [Debug] a has a value of 100
    [Info] a is not 0
    [Warning] Oh goodness a is greather than 25!
    [Error] a cannot be greater than 50!
    [Critical] a is greater or equal to 100, shutting down!

You can turn off certain loggers aswell, i.e compiling with
**LOG_EVERYTHING** and **NO_INFO_LOGGING** we get:

    [Debug] a has a value of 100
    [Warning] Oh goodness a is greather than 25!
    [Error] a cannot be greater than 50!
    [Critical] a is greater or equal to 100, shutting down!

---

This is of course intended so that if a logger isn't active, it isn't
simply skipped at run time, but is ommited at compile time, so hopefully
there shouldn't be any cost adding it to code if you aren't using it.

You can specify an ```std::ostream``` as the first argument, otherwise it
falls back to using ```std::cerr```.

The loggers can handle mulitple arguments and attempts to pass them
directly to the ```ostream``` it's trying to print to.


---

# List of flags

| Flag                   | Effect                                                                                                            |
|------------------------|-------------------------------------------------------------------------------------------------------------------|
| USE_DEBUG_LOGGER       | Turns on the **Debug** logger. And by default turns on **Info**, **Warning**, **Error** and **Critical** loggers. |
| USE_INFO_LOGGER        | Turns on the **Info** logger. And by default turns on **Warning**, **Error** and **Critical** loggers.            |
| USE_WARNING_LOGGER     | Turns on the **Warning** logger. And by default turns on **Error** and **Critical** loggers.                      |
| USE_ERROR_LOGGER       | Turns on the **Error** logger. And by default turns on the **Critical** logger. *(Enabled by default)*            |
| USE_CRITICAL_LOGGER    | Turns on the **Critical** logger. *(Enabled by default)*                                                          |
| LOG_EVERYTHING / DEBUG | Effectively **USE_DEBUG_LOGGER**                                                                                  |


| Flag                | Effect                             |
|---------------------|------------------------------------|
| NO_DEBUG_LOGGING    | Turns off the **Debug** logger.    |
| NO_INFO_LOGGING     | Turns off the **Info** logger.     |
| NO_WARNING_LOGGING  | Turns off the **Warning** logger.  |
| NO_ERROR_LOGGING    | Turns off the **Error** logger.    |
| NO_CRITICAL_LOGGING | Turns off the **Critical** logger. |
| NO_LOGGING          | Turns off all loggers.             |



