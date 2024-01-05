/*
 * NonvolatileKeyValue.h - Library for storing key-value pairs in ESP32's flash memory
 * Created by Alexandr Bajenov on January 3, 2024
 * License: MIT
 * Built on top of, and requires, SPIFFS
 */

#include "Arduino.h"
#include "NonvolatileKeyValue.h"

NonvolatileKeyValue::NonvolatileKeyValue() {} // Constructs a placeholder for composition

NonvolatileKeyValue::NonvolatileKeyValue(String key)
{
  if (key.equals("")) { return; } // This is practically a placeholder
  _key = key;
  _wasKeyEverDefined = true;
}

bool NonvolatileKeyValue::begin(bool formatFileSystemIfFailed)
{
  return SPIFFS.begin(formatFileSystemIfFailed);
}

String NonvolatileKeyValue::list(String separator)
{
  File root = SPIFFS.open("/");
  if (!root) { return ""; }
  if (!root.isDirectory()) { return ""; }
  String result = "";
  File f = root.openNextFile();
  while (f)
  {
    if (f.isDirectory()) { continue; } // Directories do not count as keyvalues
    result += String(f.name()) + separator;
    f = root.openNextFile();
  }
  return result;
}

String NonvolatileKeyValue::list()
{
  return NonvolatileKeyValue::list("\n");
}

bool NonvolatileKeyValue::exists()
{
  if(!_wasKeyEverDefined) { return false; }
  File file = getKeyValueFile();
  if(!file) { return false; }
  if(file.isDirectory()) { return false; }
  file.close();
  return true;
}

String NonvolatileKeyValue::getKey()
{
  return String(_key);
}

String NonvolatileKeyValue::getPath()
{
  return String("/" + _key);
}

String NonvolatileKeyValue::getValue()
{
  if(!exists()) { return ""; }
  File file = getKeyValueFile();
  if(!file) { return ""; }
  String result = "";
  while(file.available())
  {
    char charBuffer = file.read();
    result += String(charBuffer);
  }
  file.close();
  return result;
}

String NonvolatileKeyValue::get()
{
  return getValue();
}

bool NonvolatileKeyValue::setValue(String newValue)
{
  if (newValue.equals(getValue())) { return true; } // no need for excess wear on flash memory
  File file = getKeyValueFileForWriting();
  if(!file) { return false; }
  bool result = file.print(newValue);
  file.close();
  return result;
}

bool NonvolatileKeyValue::set(String newValue)
{
  return setValue(newValue);
}

bool NonvolatileKeyValue::remove()
{
  if (!exists()) { return true; } // already done
  char pathCharArray[pathLength()];
  getPath().toCharArray(pathCharArray, pathLength());
  return SPIFFS.remove(pathCharArray);
}

int NonvolatileKeyValue::pathLength()
{
  return getPath().length() + 1;
}

File NonvolatileKeyValue::getKeyValueFile()
{
  char pathCharArray[pathLength()];
  getPath().toCharArray(pathCharArray, pathLength());
  return SPIFFS.open(pathCharArray);
}

File NonvolatileKeyValue::getKeyValueFileForWriting()
{
  char pathCharArray[pathLength()];
  getPath().toCharArray(pathCharArray, pathLength());
  return SPIFFS.open(pathCharArray, FILE_WRITE);
}
