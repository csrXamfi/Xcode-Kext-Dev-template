# Xcode-Kext-Dev-template
# IOKit Driver Template & Example (`kext-dev`)

Big thanks to the projects and people that made this possible:

- Xcode-IOKit-Driver-Template — https://github.com/startpenghubingzhou/Xcode-IOKit-Driver-Template — (thanks: template ideas).  
- KextRW — https://github.com/alfiecg24/KextRW — (thanks: Makefile / build tricks).

> Replace the links above with real URLs.

---

## Summary
This repository contains:
- An Xcode IOKit driver template — a starting template where you write driver code inside Xcode.  
- An example project kext-dev — same layout but with a Makefile to build outside Xcode.  
- src/kmod.cpp — shared (optional) code / entry helpers.  
- A simple userspace client for testing (open → `IOConnectCallMethod`).  
- Info.plist, Makefile template and instructions for build / install / test.

---

## Workflow — short sequence (minimum steps)

1. Write the driver in Xcode  
   - Use the Xcode IOKit driver template.  
   - Implement: IOService::start/stop, IOUserClient::initWithTask, externalMethod (dispatch table).  
   - Confirm the project builds successfully in Xcode.

2. Create the example project (`kext-dev`)  
   - Copy the template layout and create kext-dev/ with the same bundle structure (`Final.kext/Contents/...`).  
   - Add src/ and put your driver sources there (`YourKext.cpp`, YourUserClient.cpp, `kmod.cpp`).

3. Add a Makefile  
   - The Makefile should build the Mach-O binary and place it in Final.kext/Contents/MacOS/Final.  
   - Provide targets: build, install, clean, test.

4. (Optional) kmod.cpp  
   - If you use the IOService lifecycle, kmod.cpp is not required.  
   - If you need a manual entry point or helper functions, put them in src/kmod.cpp, but do not duplicate _kmod_info (avoid duplicate symbol errors).

5. Write the userspace client  
   - The client should open the service (`IOServiceGetMatchingService`), call IOServiceOpen, then call selectors via IOConnectCallMethod or IOConnectCallStructMethod.  
   - For local testing you can sign the client with your dev cert and include an entitlement if required.

6. Protection / key in plist  
   - In the driver Info.plist personality, set IOUserClientClass and CFBundleIdentifier.  
   - In initWithTask, check the client entitlement with copyClientEntitlement(owningTask, "com.example.entitlement").  
   - For local dev you can allow a test entitlement or Team ID, but never do that in production.

---
## Bypasss kextload macOS
1. Disable defenses (RecoveryOS)
```shell
bputil -k
csrutil disable
```
2. Make project
```shell
cd kext_dev
make
make install
```

## Load xctemplate
Just download and drag it into /Applications/Xcode.app/Contents/Developer/Library/Xcode/Templates/Project Templates/Mac/Other/ to replace IOKit Driver.xctemplate, then restart your Xcode app and enjoy it!
