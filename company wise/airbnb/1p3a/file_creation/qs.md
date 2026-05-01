


Initially, two functions were written: `create` and `get`. `
create("/a", 1)`
`get("/a")` // Gets 1 `
create("/a/b", 2)
` `get("/a/b")` // Gets 2 `
create("/c/d", 1)` // Error because its parent directory "/c" doesn't exist
`get("/c")` // Error because "/c" doesn't exist.

The follow-up is to write a `watch` function, for example, `watch("/a", new Runnable() { System.out.println("helloword"); })`. Whenever `
create("/a/b", 1)` or other calls to directories under `/a` do not generate an error, the callback function bound to `"/a"` will be executed.

For example, `watch("/a", System.out.println("yes"))`
`watch("/a/b", System.out.println("no"))`
When `create("/a/b/c", 1)`, both callback functions will be triggered, outputting "yes". No,