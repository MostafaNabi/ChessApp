// addon.cc
#include <node.h>
#include "WebInterface.h"

namespace demo {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  WebInterface::Init(exports);
}

NODE_MODULE(ChessAddon, InitAll)

}
