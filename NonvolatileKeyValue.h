/*
 * NonvolatileKeyValue.h - Library for storing key-value pairs in ESP32's flash memory
 * Created by Alexandr Bajenov on January 3, 2024
 * License: MIT
 * Built on top of, and requires, SPIFFS
 */

#ifndef NonvolatileKeyValue_h
#define NonvolatileKeyValue_h

#include "Arduino.h"
#include "FS.h"
#include "SPIFFS.h"

class NonvolatileKeyValue
{
  public:
    NonvolatileKeyValue(); // Constructs a placeholder for class composition
    NonvolatileKeyValue(String key);
    static bool begin(bool formatFileSystemIfFailed);
    static String list(String separator);
    static String list();
    bool exists();
    String getKey();
    String getPath();
    String getValue();
    String get();
    bool setValue(String newValue);
    bool set(String newValue);
    bool remove();
  
  private:
    String _key;
    bool _wasKeyEverDefined = false;
    int pathLength();
    File getKeyValueFile();
    File getKeyValueFileForWriting();
    bool canOpenKeyValueFile();
};

#endif
