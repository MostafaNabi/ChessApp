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
        explicit WebInterface(int game_type);
        explicit WebInterface(int game_type, int ai);

        ~WebInterface();

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void build_from_fen(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void set_ai_difficulty(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void request_move(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void make_move(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void promote_pawn(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void retrieve_board(const v8::FunctionCallbackInfo<v8::Value>& args);

        static v8::Persistent<v8::Function> constructor;
        Chess* chessapp;
};


#endif
