#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

/**
 * Re-initialize the WiFi driver.
 * This is currently necessary to switch from BLE to WiFi.
 */
void resetWiFi() {
  wiFiDrv.wifiDriverDeinit();
  wiFiDrv.wifiDriverInit();
}

void connectToWiFi()
{
  int status = WiFi.status();
  if (status == WL_CONNECTED)
  {
    return;
  }
  displayStatus("Connecting to WiFi...");
  WiFi.setHostname(DEVICE_ID);
  while(true) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    if (status == WL_CONNECTED) {
      break;
    }
    displayError("Retrying in 5 seconds...");
    delay(5000);
    resetWiFi();
  }
  displayStatus("Connected to WiFi.");
}

void setupWiFi()
{
  int status = WiFi.status();
  if (status == WL_NO_SHIELD)
  {
    displaySuspend("WiFi shield missing!");
  }
  if (status == WL_NO_MODULE)
  {
    displaySuspend("Communication with WiFi module failed!");
  }
  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION)
  {
    displayStatus("Please upgrade WiFi firmware!");
  }
  connectToWiFi();
}
