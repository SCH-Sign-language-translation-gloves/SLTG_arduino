#include "config.h"

#include "display.h"
#include "wifi.h"
#include "json.h"
#include "firebase_database.h"

void setup()
{
  setupDisplay();
  setupWiFi();
}

void loop()
{
  DynamicJsonDocument json(1024);
  json["hello"] = "world";
  firebaseDatabasePut(DEVICE_ID, json);
  
  displaySuspend("All done!");
}
