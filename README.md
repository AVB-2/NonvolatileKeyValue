# NonvolatileKeyValue library

This is a library for storing keyvalues as files in ESP32's flash memory.

Designed and tested on the Adafruit HUZZAH32 – ESP32 Feather Board
https://www.adafruit.com/product/3405

Written by Alexandr Bajenov

MIT license

Requires the SPI Flash File System (SPIFFS) library.

## Manual Installation

1.  Click the downward-arrow on the "<> Code" button
2.  Click the "Download ZIP" button
3.  Uncompress the downloaded archive file
4.  Rename the uncompressed folder to `NonvolatileKeyValue`
5.  Verify that the `NonvolatileKeyValue` folder contains the files:
  *   `library.properties`
  *   `NonvolatileKeyValue.cpp`
  *   `NonvolatileKeyValue.h`

6. Open your Arduino sketch folder and find the `libraries` folder. If you cannot find the `libraries` folder in your Arduino sketch folder, then you need to create it.
7. Place the `NonvolatileKeyValue` folder into the `libraries` folder mentioned above
8. Restart the IDE