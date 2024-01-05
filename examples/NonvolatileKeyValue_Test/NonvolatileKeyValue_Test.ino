#include <NonvolatileKeyValue.h>

/* This library uses the SPI Flash Filesystem (SPIFFS.)
   You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED true

void setup()
{
  Serial.begin(115200);
  unclutterSerialPort(true);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  bool wasFileSystemMountedSuccessfully = NonvolatileKeyValue::begin(FORMAT_SPIFFS_IF_FAILED);
  if (wasFileSystemMountedSuccessfully)
  {
    Serial.println("SPIFFS mount successful. Proceeding to run the tests.");
    runTests();
  }
  else
  {
    Serial.println("SPIFFS mount failed. Cannot run the tests without a filesystem.");
  }
}

void loop()
{
  
}

/*  When running a sketch, sometimes the serial output
 *  looks like a bunch of question marks at first. The
 *  function unclutterSerialPort is meant to prevent
 *  that from happening. */
void unclutterSerialPort(bool printDots)
{
  for (int times = 10; times > 0; times--)
  {
    Serial.flush();
    if (printDots)
    {
      Serial.print('.');
    }
    delay(100);
  }
}

void runTests()
{
  testListingWithDefaultSeparator();
  testListingWithCustomSeparator();
  String testKey = "test_key";
  testExistence(testKey);
  testRead(testKey);
  testIncrement(testKey);
  testRemove(testKey);
  Serial.println("Tests complete");
}

void testListingWithDefaultSeparator()
{
  Serial.println("Listing the existing keyvalues, separated with the default (newline) separator:");
  Serial.println(NonvolatileKeyValue::list());
}

void testListingWithCustomSeparator()
{
  Serial.println("Listing the existing keyvalues with a custom (slash) separator:");
  Serial.println(NonvolatileKeyValue::list("/"));
}

void testExistence(String key)
{
  Serial.println("Testing the existence of key \"" + key + "\"");
  bool existenceTestResult = NonvolatileKeyValue(key).exists();
  Serial.println("Result: " + String(existenceTestResult));
  Serial.println("\t(1 = exists, 0 = does not exist)");
}

void testRead(String key)
{
  Serial.println("Reading the value of \"" + key + "\": \"" + NonvolatileKeyValue(key).get() + "\"");
}

void testIncrement(String key)
{
  int previousValue = NonvolatileKeyValue(key).get().toInt();
  int incrementedValue = previousValue + 1;
  testWrite(key, String(incrementedValue));
  testRead(key);
}

void testWrite(String key, String value)
{
  Serial.println("Setting the key \"" + key + "\" to the value \"" + value + "\"");
  bool wasWritingOperationSuccessful = NonvolatileKeyValue(key).set(value);
  Serial.println("Result: " + String(wasWritingOperationSuccessful));
  Serial.println("\t(1 = write successful, 0 = write unsuccessful)");
}

void testRemove(String key)
{
  testRead(key);
  String backupValue = NonvolatileKeyValue(key).get();
  Serial.println("Removing the key \"" + key + "\"");
  bool wasRemovalOperationSuccessful = NonvolatileKeyValue(key).remove();
  Serial.println("Result: " + String(wasRemovalOperationSuccessful));
  Serial.println("\t(1 = removed successfully, 0 = remove failed)");
  testExistence(key);
  testRead(key);
  testWrite(key, backupValue);
  testRead(key);
}