// WebInterface.h
#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <string>
#include <node.h>
#include <node_object_wrap.h>
#include "Chess.h"

class WebInterface : public node::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit WebInterface(v8::Local<v8::String> fen, int ai);
        ~WebInterface();

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void make_move(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;
        Chess chessapp;
};


#endif
