#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>
#include "Chess.h"

class MyObject : public node::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit MyObject(Board b , unsigned int ai);
        ~MyObject();

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;
};

}  // namespace demo

#endif
