// hello.cc
#include <iostream>
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
using v8::Boolean;
using v8::Value;
using v8::Exception;

Persistent<Function> WebInterface::constructor;

WebInterface::WebInterface(int game_type) {
    GameType g = (GameType) game_type;
    this->chessapp = new Chess(g);
}


WebInterface::WebInterface(int game_type, int ai) {
//   v8::String::Utf8Value str(fen);
    //std::string f = std::string(*str);
    GameType g = (GameType) game_type;
    this->chessapp = new Chess(g, ai);
}

WebInterface::~WebInterface() {
    delete this->chessapp;
}

// Initialises wrapper
void WebInterface::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "WebInterface"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "build_from_fen", build_from_fen);
  NODE_SET_PROTOTYPE_METHOD(tpl, "set_ai_difficulty", set_ai_difficulty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "make_move", make_move);
  NODE_SET_PROTOTYPE_METHOD(tpl, "retrieve_board", make_move);



  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "WebInterface"),
               tpl->GetFunction());
}



void WebInterface::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        if(args.Length() == 1) {
            // Type check
            if(!args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong argument types, make_move expects three integers")));
                return;
            }
            int game_type = args[0]->IntegerValue();
            WebInterface* obj = new WebInterface(game_type);
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());

        } else if(args.Length() == 2) {
            // Type check
            if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong argument types, make_move expects three integers")));
                return;
            }
            int game_type = args[0]->IntegerValue();
            int ai = args[1]->IntegerValue();
            WebInterface* obj = new WebInterface(game_type, ai);
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        }

    }
}

void WebInterface::build_from_fen(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(!args[0]->IsString()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong argument types, build_from_fen expects strings")));
        return;
    }

    Local<String> fen = args[0]->ToString();
    v8::String::Utf8Value str(fen);
    std::string f = std::string(*str);

    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    obj->chessapp->build_from_fen(f);
}

void WebInterface::set_ai_difficulty(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(!args[0]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong argument types, set_ai_difficulty expects integer")));
        return;
    }
    int ai = args[0]->IntegerValue();
    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    obj->chessapp->set_ai_difficulty(ai);
}

void WebInterface::make_move(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments, make_move takes 2 arguments")));
    args.GetReturnValue().Set( Boolean::New(isolate, false));
    return;
  }

  // Check the argument types
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong argument types, make_move expects 2 integers")));
    args.GetReturnValue().Set( Boolean::New(isolate, false));
    return;
  }

  Square orig   = (Square) args[0]->IntegerValue();
  Square dest   = (Square) args[1]->IntegerValue();

  WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
  bool res = obj->chessapp->make_move(orig, dest);
  args.GetReturnValue().Set( Boolean::New(isolate, res));
}



void WebInterface::make_move(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    //args.GetReturnValue().Set( Boolean::New(isolate, res));

}
