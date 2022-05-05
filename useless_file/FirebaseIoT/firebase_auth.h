String getDeviceToken()
{
  String header = "";
  DynamicJsonDocument json(1024);
  // ATECCx08 crypto chips only support ES256:
  // https://github.com/MicrochipTech/cryptoauthlib/blob/master/lib/jwt/atca_jwt.c
  json["alg"] = "ES256";
  json["kid"] = DEVICE_ID;
  serializeJson(json, header);

  String payload;
  json.clear();
  json["nonce"] = NONCE;
  serializeJson(json, payload);
  return ECCX08JWS.sign(/* slot */ 0, header, payload);
}

String getIdToken(String deviceToken)
{
  displayStatus("Fetching idToken...");
  
  String host = String(FUNCTIONS_REGION) + "-" + String(PROJECT_ID) + ".cloudfunctions.net";
  WiFiSSLClient wifiClient;
  HttpClient httpClient = HttpClient(wifiClient, host, 443);

  httpClient.post("/getIdToken", "text/plain", deviceToken);
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();
  httpClient.stop();

  if (statusCode != 200) {
    displayError(String(statusCode) + " " + response);
    return "";
  }

  displayStatus("Received idToken.");
  DynamicJsonDocument json = toJsonDocument(response);
  return json["idToken"].as<String>();
}