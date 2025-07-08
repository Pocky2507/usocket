#include <napi.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

Napi::Value CreateSocketPair(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    int fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) {
        Napi::TypeError::New(env, "socketpair failed: " + std::string(strerror(errno))).ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array result = Napi::Array::New(env, 2);
    result.Set((uint32_t)0, Napi::Number::New(env, fds[0]));
    result.Set((uint32_t)1, Napi::Number::New(env, fds[1]));

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("socketpair", Napi::Function::New(env, CreateSocketPair));
    return exports;
}

NODE_API_MODULE(usocket, Init)
