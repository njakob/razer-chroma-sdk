#include <windows.h>

// Depends on windows.h
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

namespace razer::chroma {
  namespace signature {
    using Init = RZRESULT (*)();

    using InitSDK = RZRESULT (*)(ChromaSDK::APPINFOTYPE* AppInfo);

    using UnInit = RZRESULT (*)();

    using CreateEffect = RZRESULT (*)(
      RZDEVICEID deviceId,
      ChromaSDK::EFFECT_TYPE effect,
      PRZPARAM parameter,
      RZEFFECTID* effectId
    );

    using CreateKeyboardEffect = RZRESULT (*)(
      ChromaSDK::Keyboard::EFFECT_TYPE effect,
      PRZPARAM parameter,
      RZEFFECTID* effectId
    );

    using CreateMouseEffect = RZRESULT (*)(
      ChromaSDK::Mouse::EFFECT_TYPE effect,
      PRZPARAM parameter,
      RZEFFECTID* effectId
    );

    using SetEffect = RZRESULT (*)(RZEFFECTID effectId);

    using DeleteEffect = RZRESULT (*)(RZEFFECTID effectId);

    using QueryDevice =
      RZRESULT (*)(RZDEVICEID deviceId, ChromaSDK::DEVICE_INFO_TYPE& deviceInfo);
  }

  class Chroma {
  public:
    static auto create() -> Chroma* {
      auto chroma = new Chroma();

      chroma->library_ = LoadLibrary("RzChromaSDK64.dll");
      if (!chroma->library_) {
        return nullptr;
      }
      if (!chroma->loadLibrary()) {
        return nullptr;
      }

      return chroma;
    }

    ~Chroma() {
      if (!library_) {
        return;
      }

      unInit();

      FreeLibrary(library_);
      library_ = nullptr;
    }

    signature::Init init = nullptr;
    signature::InitSDK initSDK = nullptr;
    signature::UnInit unInit = nullptr;
    signature::CreateEffect createEffect = nullptr;
    signature::CreateKeyboardEffect createKeyboardEffect = nullptr;
    signature::CreateMouseEffect createMouseEffect = nullptr;
    signature::SetEffect setEffect = nullptr;
    signature::DeleteEffect deleteEffect = nullptr;
    signature::QueryDevice queryDevice = nullptr;

  private:
    HMODULE library_;

    Chroma() { };

    template<typename Callable>
    auto loadLibraryFunction(Callable& function, const char* functionName)
      -> bool {
      function =
        reinterpret_cast<Callable>(GetProcAddress(library_, functionName));
      return function != nullptr;
    }

    auto loadLibrary() -> bool {
      if (!loadLibraryFunction(init, "Init")) {
        return false;
      }
      if (!loadLibraryFunction(initSDK, "InitSDK")) {
        return false;
      }
      if (!loadLibraryFunction(unInit, "UnInit")) {
        return false;
      }
      if (!loadLibraryFunction(createEffect, "CreateEffect")) {
        return false;
      }
      if (!loadLibraryFunction(createKeyboardEffect, "CreateKeyboardEffect")) {
        return false;
      }
      if (!loadLibraryFunction(createMouseEffect, "CreateMouseEffect")) {
        return false;
      }
      if (!loadLibraryFunction(setEffect, "SetEffect")) {
        return false;
      }
      if (!loadLibraryFunction(deleteEffect, "DeleteEffect")) {
        return false;
      }
      if (!loadLibraryFunction(queryDevice, "QueryDevice")) {
        return false;
      }
      return true;
    }
  };
}
