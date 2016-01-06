#include <nan.h>
#include <iostream>

extern "C" char * create_greeter(const char *greeting);
extern "C" void destroy_greeter(const char *ptr);
extern "C" char * greeter_hello(const char *ptr, const char *name);

void destroyGreeterCb(char *ptr, void *hint) {
	destroy_greeter(ptr);
}

void createGreeter(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Nan::HandleScope scope;
	const char *greeting = *Nan::Utf8String(args[0]);

	char *ptr = create_greeter(greeting);
	Nan::MaybeLocal<v8::Object> buf = Nan::NewBuffer(ptr, 0, destroyGreeterCb, NULL);

	args.GetReturnValue().Set(buf.ToLocalChecked());
}

void greeterHello(const v8::FunctionCallbackInfo<v8::Value>& args) {
	const char *ptr = node::Buffer::Data(args[0]->ToObject());
	const char *name = *Nan::Utf8String(args[1]);
	const char *greeting = greeter_hello(ptr, name);

	args.GetReturnValue().Set(Nan::New<v8::String>(greeting).ToLocalChecked());
}

void __node_main__(v8::Local<v8::Object> module) {
	NODE_SET_METHOD(module, "createGreeter", createGreeter);
	NODE_SET_METHOD(module, "greeterHello", greeterHello);
}

NODE_MODULE(hello_rust_js, __node_main__)
