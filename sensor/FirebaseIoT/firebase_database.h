#include <ArduinoHttpClient.h>

bool firebaseDatabasePut(String path, DynamicJsonDocument jsonDoc, String idToken = "") {
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  displayStatus("Saving to RTDB: " + path + " = " + jsonStr);
  
  String host = String(PROJECT_ID) + ".firebaseio.com";
  WiFiSSLClient wifiClient;
  HttpClient httpClient = HttpClient(wifiClient, host, 443);
  
  String url = "/" + path + ".json";
  if (idToken != "") {
    url = url + "?auth=" + idToken;
  }
  httpClient.put(url, "application/json", jsonStr);
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();
  
  if (statusCode != 200) {
    displayError(String(statusCode) + " " + response);
    return false;
  }
  displayStatus("Saved to RTDB.");
  return true;
}
