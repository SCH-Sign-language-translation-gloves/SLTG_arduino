#include <ArduinoJson.h>

/**
 * Converts a String into a JsonDocument of correct size.
 * In case of error, the returned `jsonDoc.isNull()` will be true.
 */
DynamicJsonDocument toJsonDocument(String str, int size = 0) {
  if (size == 0) {
    size = JSON_OBJECT_SIZE(1) + str.length();
  }
  DynamicJsonDocument jsonDoc(str.length() * 2);
  DeserializationError error = deserializeJson(jsonDoc, str);
  if (error) {
    displayError("JSON " + String(error.c_str()) + ": " + str);
    jsonDoc.clear();
  }
  return jsonDoc;
}
