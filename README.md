# hello-rust-js

## Example

```js
const assert = require("assert");

const Greeter = require("hello-rust-js");

const greeter = Greeter("Hello");

assert.equal(greeter.hello("World"), "Hello, World!");
```
