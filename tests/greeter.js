"use strict";

const assert = require("assert");

const Greeter = require("../lib");

function testGreeter() {
	const greeter = Greeter("Ｈｅｌｌｏ");
	const greeting = greeter.hello("World ♫");

	assert.strictEqual(greeting, "Ｈｅｌｌｏ, World ♫!");
}

testGreeter();
