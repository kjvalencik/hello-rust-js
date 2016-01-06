extern crate libc;

use std::ffi::{CStr, CString};
use libc::c_char;

pub struct Greeter {
	greeting: String,
}

impl Greeter {
	fn new(greeting: &str) -> Greeter {
		Greeter {
			greeting: greeting.to_string(),
		}
	}

	fn hello(&self, name: &str) -> String {
		format!("{}, {}!", self.greeting, name)
	}
}

#[no_mangle]
pub extern fn create_greeter(greeting: *const c_char) -> *mut Greeter {
	let greeting = unsafe {
	   CStr::from_ptr(greeting)
	};

	let greeting = greeting.to_str().unwrap();
	let greeter = Box::new(Greeter::new(greeting));

	Box::into_raw(greeter)
}

#[no_mangle]
pub extern fn greeter_hello(ptr: *mut Greeter, name: *const c_char) -> CString {
	let (greeter, name) = unsafe {
		(&*ptr, CStr::from_ptr(name))
	};

	let name = name.to_str().unwrap();

	CString::new(greeter.hello(name)).unwrap()
}

#[no_mangle]
pub extern fn destroy_greeter(ptr: *mut Greeter) {
	unsafe {
		Box::from_raw(ptr);
	};
}
