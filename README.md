# Logger
A lightweight logging library for C++

## Version 1.0.1 - File extension and README update
- Major: Full release
- Minor: Full release
- Patch: File extension and README update

## Features
- Six different log types with (Trace, Debug, Info, Warning, Error, Fatal)
- Easy to use macros for convenience
- Thread safe methods
- Timestamps and log types prefixes for logged messages
- Tags and flags for customizing the output
- Highly customizable filtering for both log types and tags
- Support for different output streams
- Single file header only implementation

## Requirements
This library was built using modern C++ (C++17) features and was solely tested on a macos environment using Clang++ 16.0.0, meaning using different tools may not work as intended.

## Usage
To get started with Logger, copy the `Logger.hpp` file from the repository and add it to your project.
Include the header files to your cpp files and use any of the logging methods from the example bellow!

Example:
```C++
//test.cpp
#include "Logger.hpp"

int main() {

    // Logging with different log types

    LOGGER_TRACE("Testing TRACE logging!");
    LOGGER_DEBUG("Testing DEBUG logging!");
    LOGGER_INFO("Testing INFO logging!");
    LOGGER_WARNING("Testing WARNING logging!");
    LOGGER_ERROR("Testing ERROR logging!");
    LOGGER_FATAL("Testing FATAL logging!");

    // Logging with multiple arguments to the methods

    LOGGER_DEBUG("Testing ", "multiple ", "arguments!");
    LOGGER_DEBUG("Testing ", 2, " different ", "argument types!");
    LOGGER_DEBUG("Testing multiple different types: ", 100, ' ', 100.00, " ", 0x64, '!');

    // Note: if you wish to use a custom class or type make sure it has the << operator defined!

    return 0;
}
```

That's it! It's as simple as that! Feel free to use this library in your personnal projects!

If you wish to keep your logs in a file rather than outputing to the console, Logger supports alternate output streams.
Simply use the `LOGGER_SETOUTPUTSTREAM()` macro.

Example:
```C++
//test.cpp
#include "Logger.hpp"

#include <fstream>
#include <string>

int main() {

    std::string filePath = "log.txt";
    std::ofstream ofstream(filePath);
    LOGGER_SETOUTPUTSTREAM(&ofstream);

    LOGGER_DEBUG("Testing alternate output streams!");

    return 0;
}
```

For output preferences, Logger uses flags.
Simply use the `LOGGER_SETFLAG()` and `LOGGER_CLEARFLAG()` macros.

Example:
```C++
// test.cpp
#include "Logger.hpp"

int main() {

    // Note: by default, most flags are set to true! (See flag defaults below)
    LOGGER_DEBUG("Testing different output flags!");

    // Use LOGGER_CLEARFLAG() to set flags to false

    LOGGER_CLEARFLAG(Logger::Flag::TIMESTAMPSPREFIX);
    LOGGER_DEBUG("Testing different output flags!");

    LOGGER_CLEARFLAG(Logger::Flag::WHITESPACEPREFIX);
    LOGGER_DEBUG("Testing different output flags!");

    // Use LOGGER_SETFLAGS() to set them to true

    LOGGER_SETFLAG(Logger::Flag::TIMESTAMPSPREFIX);
    LOGGER_DEBUG("Testing different output flags!");

    LOGGER_CLEARFLAG(Logger::Flag::LOGTYPESPREFIX);
    LOGGER_DEBUG("Testing different output flags!");

    LOGGER_SETFLAG(Logger::Flag::WHITESPACEPREFIX);
    LOGGER_SETFLAG(Logger::Flag::LOGTYPESPREFIX);
    LOGGER_DEBUG("Testing different output flags!");

    return 0;
}
```

If you wish to specify further your logging, use the built in log tags!

Example:

```C++
//test.cpp
#include "Logger.hpp"

int main() {

    // Set the log tag prefix flag
    LOGGER_SETFLAG(Logger::Flag::LOGTAGPREFIX);

    Logger::LogTag testingTag("Testing"); // Create a log tag
    LOGGER_DEBUG(testingTag, "Testing tag specification!");

    // Note: using multiple log tags
    // or not specifying the log tag as the first argument
    // will cause unwanted behaviour when filtering!

    return 0;
```

### Additional information about flags (NAME, default value, behaviour)
- `TIMESTAMPSPREFIX`,  `true`,  Toggles the display of the timestamp
- `LOGTYPESPREFIX`,    `true`,  Toggles the display of the log type
- `WHITESPACEPREFIX`,  `true`,  Toggles the display of whitespace between the prefix and the message
- `LOGTAGPREFIX`,      `false`, Toggles the display of the log tag
- `LOGTYPECOLORS`,     `true`,  Toggles the color of the message based on log type
- `LOGTYPEFILTER`,     `false`, Toggles the filtering of the message based on log type
- `LOGTAGFILTER`,      `false`, Toggles the filtering of the message based on log tag
- `WHITELISTFILTER`,   `true`,  Toggles the use of whitelisting for filtering (filters act as blacklists if this flag is cleared)
- `ENDOFLINESUFFIX`,   `true`,  Toggles the display of a end of line following the message

## Changelog

### Version 1.0.1 - File extension and README update
- Added README section (Requirements)
- Changed the file extension by convention

### Version 1.0.0 - Full release
- Added macros for all class methods
- Added a namespace to the project as to avoid pollution
- Changed method implementations to reduce file size and project complexity

### Version 0.7.0 - Log tags and Filtering
- Added log tags for additional specification
- Added filtering using both tags and types
- Added flags for tags and filtering
- Changed attribute declaration for code clarity
- Changed the method implementations for code clarity

### Version 0.6.1 - Clear warnings
- Changed all possible ODR violations to proper inline methods/attributes

### Version 0.6.0 - Log type colors
- Added colors for all log types (only for console logging)
- Added an output flag for log type colors
- Added suffix flags (End of line)

### Version 0.5.0 - Output flags
- Added output flags for logging preferences (Timestamps Prefix, Log Type Prefix and Whitespace Prefix)

### Version 0.4.0 - Output streams
- Added support for alternate output streams

### Version 0.3.1 - Refactor and README update
- Added README sections (Features, Usage, Changelog)
- Changed the method implementations for code clarity

### Version 0.3.0 - Timestamps and Refactor
- Added timestamps to log methods
- Changed the method implementations for code clarity

### Version 0.2.0 - Thread safety
- Added lock_guard to all log methods for proper thread safety

### Version 0.1.0 - Basic logging
- Added Logger class
- Added log types (Trace, Debug, Info, Warning, Error, Fatal)
- Added static methods for all log types
