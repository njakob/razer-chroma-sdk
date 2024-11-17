# Razer Chroma SDK Wrapper

This repository provides a C++ wrapper around the [Razer Chroma SDK](https://www.chromargb.com/), which allows developers to easily integrate Razer Chroma RGB lighting effects into their applications. 

The [official examples](https://github.com/razerofficial/CSDK_SampleApp) provided by Razer are quite extensive and include an [animation library](https://github.com/razerofficial/CChromaEditor) on top of the low level SDK.

This wrapper aims to offer a simpler, more lightweight interface for basic integration needs with CMake support.

## Requirements

To use this SDK wrapper, ensure that you meet the following requirements:

- **Operating System**: Razer Chroma is only supported on **Windows**.
- **Runtime Libraries**: Install the Razer Chroma runtime DLLs via [Razer Synapse](https://www.razer.com/synapse).

## Usage Example

Here is a simple example that demonstrates how to use the Razer Chroma SDK wrapper to create a red keyboard effect:

```cpp
#include <cstdlib>

#include "razer-chroma-sdk/chroma.hpp"

int main() {
  // Create an instance of the Chroma SDK
  auto chroma = razer::chroma::Chroma::create();
  if (chroma == nullptr) {
    printf("Unable to load Razer Chroma SDK\n");
    return EXIT_FAILURE;
  }

  // Set up application information for the SDK
  ChromaSDK::APPINFOTYPE applicationInfo;
  wcsncpy_s(applicationInfo.Title, L"Example", 256);
  wcsncpy_s(applicationInfo.Description, L"My game", 1024);
  wcsncpy_s(applicationInfo.Author.Name, L"Studio", 256);
  wcsncpy_s(applicationInfo.Author.Contact, L"https://example.org", 256);

  applicationInfo.SupportedDevice = (0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20);
  applicationInfo.Category = 1;

  // Initialize the Chroma SDK
  auto result = chroma->initSDK(&applicationInfo);
  if (result != RZRESULT_SUCCESS) {
    printf("Unable to initialize Razer Chroma SDK. Error code: %ld\n", result);
    return EXIT_FAILURE;
  }

  // Infinite loop for demonstration purposes
  while (true) {
    RZEFFECTID effectId;

    ChromaSDK::Keyboard::STATIC_EFFECT_TYPE effect;
    effect.Color = RGB(255, 0, 0);

    auto result = chroma->createKeyboardEffect(
      ChromaSDK::Keyboard::CHROMA_STATIC,
      &effect,
      &effectId
    );
    if (result == RZRESULT_SUCCESS) {
      chroma->setEffect(effectId);
      chroma->deleteEffect(effectId);
    }

    // Adjust the effect every 50ms
    Sleep(50);
  }

  // Clean up the SDK
  delete chroma;
  chroma = nullptr;

  return EXIT_SUCCESS;
}
```

## Explanation

1. **Creating an Instance**: The `razer::chroma::Chroma::create()` function initializes the Chroma SDK. If the SDK cannot be loaded, the program exits.

2. **Setting Application Information**: The `APPINFOTYPE` structure is used to describe the application to the Razer Chroma SDK, including the name, description, author, and supported devices.

3. **Initializing the SDK**: The `initSDK()` function initializes the connection with the Chroma SDK.

4. **Creating Keyboard Effects**: This example continuously creates a red static effect for the keyboard and sets it using `createKeyboardEffect()` and `setEffect()`. The `Sleep(50)` function is used to create a loop that keeps updating the effect every 50 milliseconds.

5. **Cleanup**: Properly release the allocated memory and uninitialize the SDK using `uninitSDK()` before deleting the Chroma instance.

## Disclaimer

This repository is not affiliated with Razer Inc. All product names, trademarks, and registered trademarks are the property of their respective owners.

