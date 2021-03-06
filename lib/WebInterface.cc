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
using v8::Integer;
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
  NODE_SET_PROTOTYPE_METHOD(tpl, "get_current_turn", get_current_turn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "set_ai_difficulty", set_ai_difficulty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "request_move", request_move);
  NODE_SET_PROTOTYPE_METHOD(tpl, "make_move", make_move);
  NODE_SET_PROTOTYPE_METHOD(tpl, "promote_pawn", promote_pawn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "retrieve_board", retrieve_board);



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

void WebInterface::get_current_turn(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    int turn = (int) obj->chessapp->get_current_turn();
    args.GetReturnValue().Set( Integer::New(isolate, turn));
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
  Result res = obj->chessapp->make_move(orig, dest);
  int result = (int) res;
  args.GetReturnValue().Set( Integer::New(isolate, result));
}


void  WebInterface::promote_pawn(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < 2) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments, promote_pawn takes 2 arguments")));
        args.GetReturnValue().Set( Boolean::New(isolate, false));
        return;
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong argument types, promote_pawn expects 2 integers")));
        args.GetReturnValue().Set( Boolean::New(isolate, false));
        return;
    }

    Square orig = (Square) args[0]->IntegerValue();
    Piece p = (Piece) args[1]->IntegerValue();
    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    bool result = obj->chessapp->promote_pawn(orig, p);
    args.GetReturnValue().Set( Boolean::New(isolate, result));
}
void  WebInterface::request_move(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() > 0) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments, request move takes no arguments")));
        args.GetReturnValue().Set( Boolean::New(isolate, false));
        return;
    }
    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    EvaluationResult result = obj->chessapp->request_move();
    Local<String> str = String::NewFromUtf8(isolate, result.to_string().c_str());
    args.GetReturnValue().Set(str);
}


void WebInterface::retrieve_board(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    WebInterface* obj = ObjectWrap::Unwrap<WebInterface>(args.Holder());
    std::vector<Piece> v =  obj->chessapp->retrieve_board();

    std::string s = "{\"board\":[";
    for(unsigned int i=0; i<v.size(); i++) {
        s += std::to_string((int)v[i]);
        if( i != v.size()-1) {
            s += ",";
        }

    }
    s += "]}";
    Local<String> str = String::NewFromUtf8(isolate, s.c_str());
    args.GetReturnValue().Set(str);
}
