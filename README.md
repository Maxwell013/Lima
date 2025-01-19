# Lima
A lightweight logging library for C++.

This library is part of a long term project that aims to build a small game engine and break it down into various smaller projects.
This is the first library and may be revisited when additional features are needed.

## Version 2.0.0 - Lima release
- Major: Lima release
- Minor: Lima release
- Patch: Lima release

## Features
- Single file header only implementation
- Easy to use macros
- Thread safety
- Timestamps
- Tags and flags for versatility
- Highly customizable filtering
- Support for alternate output streams

## Requirements
This library was built using modern C++ (C++17) features and was solely tested on a macos environment using Clang++ 16.0.0, meaning using different tools may not work as intended.

## Usage
To get started with Lima, copy the `lima.hpp` file from the repository and add it to your project.
Include the header files to your cpp files and use any of the macros from the example bellow!

Example:
```C++
//test.cpp
#include "lima.hpp"

int main() {

    // Logging with different log types

    LOG_TRACE("Testing TRACE logging!");
    LOG_DEBUG("Testing DEBUG logging!");
    LOG_INFO("Testing INFO logging!");
    LOG_WARNING("Testing WARNING logging!");
    LOG_ERROR("Testing ERROR logging!");
    LOG_FATAL("Testing FATAL logging!");

    // Logging with multiple arguments to the methods

    LOG_DEBUG("Testing ", "multiple ", "arguments!");
    LOG_DEBUG("Testing ", 2, " different ", "argument types!");
    LOG_DEBUG("Testing multiple different types: ", 100, ' ', 100.00, " ", 0x64, '!');

    // Note: if you wish to use a custom class or type make sure it has the << operator defined!

    return 0;
}
```

That's it! It's as simple as that! Feel free to use this library in your personnal projects!

If you wish to keep your logs in a file rather than outputing to the console, Lima supports alternate output streams.
Simply use the `LIMA_SET_OUTPUT_STREAM()` macro.

Example:
```C++
//test.cpp
#include "lima.hpp"

#include <fstream>
#include <string>

int main() {

    std::string filePath = "log.txt";
    std::ofstream ofstream(filePath);
    LIMA_SET_OUTPUT_STREAM(&ofstream);

    LOG_DEBUG("Testing alternate output streams!");

    return 0;
}
```

For output preferences, Lima uses flags.
Simply use the `LIMA_SET_FLAG()` and `LIMA_CLEAR_FLAG()` macros.

Example:
```C++
// test.cpp
#include "lima.hpp"

int main() {

    // Note: by default, most flags are set to true! (See flag defaults below)
    LOG_DEBUG("Testing different output flags!");

    // Use LIMA_CLEAR_FLAG() to set flags to false

    LIMA_CLEAR_FLAG(lima::Flag::TIMESTAMPS_PREFIX);
    LOG_DEBUG("Testing different output flags!");

    LIMA_CLEAR_FLAG(lima::Flag::WHITESPACE_PREFIX);
    LOG_DEBUG("Testing different output flags!");

    // Use LIMA_SET_FLAGS() to set them to true

    LIMA_SET_FLAG(lima::Flag::TIMESTAMPS_PREFIX);
    LOG_DEBUG("Testing different output flags!");

    LIMA_CLEAR_FLAG(lima::Flag::LOGTYPES_PREFIX);
    LOG_DEBUG("Testing different output flags!");

    LIMA_SET_FLAG(lima::Flag::WHITESPACE_PREFIX);
    LIMA_SET_FLAG(lima::Flag::LOGTYPES_PREFIX);
    LOG_DEBUG("Testing different output flags!");

    return 0;
}
```

If you wish to specify further your logging, use the built in log tags!

Example:

```C++
//test.cpp
#include "lima.hpp"

int main() {

    // Set the log tag prefix flag
    LIMA_SET_FLAG(lima::Flag::LOGTAG_PREFIX);

    lima::LogTag testingTag("Testing"); // Create a log tag
    LOG_DEBUG(testingTag, "Testing tag specification!");

    // Note: using multiple log tags
    // or not specifying the log tag as the first argument
    // will cause unwanted behaviour when filtering
    // and will not log to the console

    return 0;
```

### Additional information about flags (NAME, default value, behaviour)
- `TIMESTAMPS_PREFIX`,  `true`,  Toggles the display of the timestamp
- `LOGTYPES_PREFIX`,    `true`,  Toggles the display of the log type
- `WHITESPACE_PREFIX`,  `true`,  Toggles the display of whitespace between the prefix and the message
- `LOGTAG_PREFIX`,      `false`, Toggles the display of the log tag
- `LOGTYPE_COLORS`,     `true`,  Toggles the color of the message based on log type
- `LOGTYPE_FILTER`,     `false`, Toggles the filtering of the message based on log type
- `LOGTAG_FILTER`,      `false`, Toggles the filtering of the message based on log tag
- `WHITELIST_FILTER`,   `true`,  Toggles the use of whitelisting for filtering (filters act as blacklists if this flag is cleared)
- `END_OF_LINE_SUFFIX`,   `true`,  Toggles the display of a end of line following the message

## Changelog

### Version 2.0.0 - Lima release
- Changed the naming and branding of the library
- Changed the LogTag and LogType implementation to avoid unwanted behaviour
- Changed macro naming for consistency

### Version 1.1.2 - Namespace convention
- Changed the namespace naming convention to lowercase for consistency

### Version 1.1.1 - Safe timestamps
- Changed the timestamp implementation to avoid unsafe functions

### Version 1.1.0 - Refactor and Cleanup
- Changed naming conventions for consistency
- Changed method naming for code clarity
- Changed README to match updates

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
