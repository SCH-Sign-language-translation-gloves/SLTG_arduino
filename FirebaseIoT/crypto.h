#include <ArduinoECCX08.h>
#include <utility/ECCX08JWS.h>

void setupCrypto()
{
  if (!ECCX08.begin())
  {
    displaySuspend("No ECCX08 present!");
  }
  if (!ECCX08.locked())
  {
    displaySuspend("The ECCX08 on your board is not locked!");
  }
  String publicKey = ECCX08JWS.publicKey(/* slot */ 0, false);
  if (publicKey == "")
  {
    displaySuspend("Key missing. Generate a new key pair!");
  }
}