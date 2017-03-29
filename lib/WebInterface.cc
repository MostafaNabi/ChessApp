// hello.cc
#include "WebInterface.h"


using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Exception;

namespace Addon {

    Persistent<Function> WebInterface::constructor;

    WebInterface::WebInterface(std::string fen, int ai) {
        this->chessapp = Chess(fen, ai);
    }

    WebInterface::~WebInterface() {

    }

    // Initialises wrapper
    void WebInterface::Init(Local<Object> exports) {
      Isolate* isolate = exports->GetIsolate();

      // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "WebInterface"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "make_move", make_move);

      constructor.Reset(isolate, tpl->GetFunction());
      exports->Set(String::NewFromUtf8(isolate, "WebInterface"),
                   tpl->GetFunction());
    }



    void WebInterface::New(const FunctionCallbackInfo<Value>& args) {
      Isolate* isolate = args.GetIsolate();

      if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        if(!args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "WebInterface constructor expacts (string, int).")));
            return;
        }

        if(!args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "WebInterface constructor expacts (string, int).")));
            return;
        }

        std::string fen = args[0]->ToString();
        int ai = args[1]->IntegerValue();

        WebInterface* obj = new WebInterface(fen, ai);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
      } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 2;
        Local<Value> argv[argc] = { args[0], args[1] };
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result = cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(result);
      }
    }

    bool WebInterface::make_move(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

      // Check the number of arguments passed.
      if (args.Length() < 3) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments, make_move takes 3 arguments")));
        return false;
      }

      // Check the argument types
      if (!args[0]->IsNumber() || !args[1]->IsNumber() !args[2]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong argument types, make_move expects three integers")));
        return false;
      }

      int orig   = (Square) args[0]->IntegerValue();
      int colour = (Square) args[1]->IntegerValue();
      int dest   = (Square) args[2]->IntegerValue();

      return this->chessapp.make_move(orig, colour, dest);
    }

}
