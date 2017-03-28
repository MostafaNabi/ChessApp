// hello.cc
#include <node.h>
#include "Types.h"
#include "Chess.h"

namespace WebInterface {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

Chess chess;

/*  ---------------------- TODO -------------------------------------
    Turn web interface into a class with constructor that accepts
    initial board state and an int value for AI strength (0 for no AI)

    Give Chess two constructors,
        Chess(Board b)
        Chess(Board b, int ai_strength)

    // Create tiles dynamically from BoardView constructors
        The index.html file is unreadable

    Flow:
        BoardView->Server.js.init() // create web interface

*/


void make_move(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments")
        ));
        args.GetReturnValue().Set(false);
        return;
    }

    // Check the argument types
    if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")
        ));
        args.GetReturnValue().Set(false);
        return;
    }

    // Perform the operation
    Square orig = (Square) (args[0]->NumberValue());
    Colour col  = (Colour) (args[1]->NumberValue());
    Square dest = (Square) (args[2]->NumberValue());

    bool result = chess.make_move(orig, col, dest);
    args.GetReturnValue().Set(result);
}


void get_board() {

}


void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "make_move", make_move);
    NODE_SET_METHOD(exports, "get_board", get_board);
}

NODE_MODULE(WebInterface, init)

}
