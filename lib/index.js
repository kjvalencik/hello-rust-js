"use strict";

const neon = require("neon-bridge");

const addon = neon.load();

function Greeter(greeting) {
	const greeter = addon.createGreeter(greeting);

	function hello(name) {
		return addon.greeterHello(greeter, name);
	}

	return Object.freeze({
		hello
	});
}

module.exports = Greeter;
