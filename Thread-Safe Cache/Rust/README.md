# Thread-Safe Cache in Rust

## Expected outcome

- Execute `cargo run hello_server`. A web server should run. If it doesn't, try changing the port used in [`main.rs:6`](../src/main.rs).
- Run `curl http://localhost:7878/alice`. It should wait for a few seconds, and return a web page.
- Run `curl http://localhost:7878/alice` again. It should instantly return a web page.
- Run `curl http://localhost:7878/bob`. It should wait for a few seconds, and return a web page.
- Press `Ctrl-C`. The web server should gracefully shut down after printing statistics.

## Organization

- `src/main.rs`: the web server.
- `src/hello_server/*.rs`: the server components. You should fill out the `todo!()` in the `cache.rs` file.

## Grading

The grader runs the `script/grade.sh` script. This script runs the tests with with various options.

## Guide

### Reading Rust book

This homework requires a good understanding of materials covered in [the Rust book §20](https://doc.rust-lang.org/book/ch20-00-final-project-a-web-server.html).
This is the minimal path for understanding §20: §1, 2, 3, 4, 5, 6, 8, 9, 10, 13.1, 13.2, **15**, **16**, **20**.

Specifically, make sure that you understand following topics.

- [`Drop`](https://doc.rust-lang.org/std/ops/trait.Drop.html) trait and [`drop`](https://doc.rust-lang.org/std/mem/fn.drop.html) function
- Type signature of [`std::thread::spawn`](https://doc.rust-lang.org/std/thread/fn.spawn.html) and the meaning of [`std::thread::JoinHandle`](https://doc.rust-lang.org/std/thread/struct.JoinHandle.html).
- The meaning and usage of [`Arc<`](https://doc.rust-lang.org/std/sync/struct.Arc.html)[`Mutex<T>>`](https://doc.rust-lang.org/std/sync/struct.Mutex.html).
- [Channels](https://doc.rust-lang.org/std/sync/mpsc/index.html).
<!-- * The fact that there is no non-trivial way to break out of `TcpListener::incoming` loop. -->

### Major differences between HW thread pool and Rust book §20 thread pool

1. We use [`crossbeam_channel`](https://docs.rs/crossbeam-channel/) instead of [<code>std::sync::<strong>mpsc</strong></code>](https://doc.rust-lang.org/std/sync/mpsc/index.html). Since crossbeam channel is **mpmc**, you don't need to wrap the `Receiver` inside a `Mutex`.
2. We do not use explicit exit message for thread pool. Instead, we disconnect the channel by `drop`ping the receiver/sender.

    - Our message type is simply the `Job` itself:

      ```rust
      struct Job(Box<dyn FnOnce() + Send + 'static>);
      ```

    - Each worker thread automatically breaks out of the loop if the channel is disconnected.

3. We `join()` each thread in the destructor of `Worker`, not in the destructor of `ThreadPool`. Since `ThreadPool` has field `workers: Vec<Worker>`, the worker destructor will be called when the pool is dropped. Note that the channel should be disconnected before `join`ning the worker threads. (Otherwise, `join` will block.) This means that the `Sender` should be dropped before `Vec<Worker>`. You can specify the drop order in many ways. In this homework, we use `ThreadPool::job_sender` of type `Option<Sender<Job>>`, content of which can be `take`n and `drop`ped explicitly in `<ThreadPool as Drop>::drop`.

### Tips

Start with `Mutex<HashMap<K, V>>`. To fully implement the specification, you will need a more complicated type. The simplest solution makes use of all the things imported in `cache.rs`.

### Testing

We'll only test the libraries.

```bash
cargo test --test cache
cargo test --test tcp
cargo test --test thread_pool
```

We will use those tests for grading, too. We may add some more tests for grading, but if your solution passes all the given tests, it's very likely that you will get the full score.
