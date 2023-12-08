# Thread-Safe Cache in C

## Expected Outcome

- Execute `make run`. A CLI application should run.
- Insert `alice`. It should wait for a few seconds, and print `alice`.
- Insert `alice` again. It should instantly print `alice`.
- Insert `bob`. It should wait for a few seconds, and print `bob`.
- Press `Ctrl-C` to close the application.

## Organization

- `src/main.c`: the CLI entrypoint.
- `src/cache.c`: the cache implementation. You should fill out the comments in this file. You will probably need to change `src/cache.h` as well.

## Grading

The grader executes `make test`. This `make` target runs various tests against your implementation.

## Guide

### `pthread` API

This homework requires a good understanding of the `pthread` API and some of its components. You are better off reading about the following types and components:

- `pthread_cond_t` and its `pthread_cond_wait` and `pthread_cond_broadcast` operations.
- `pthread_mutex_t` and its `pthread_mutex_lock` and `pthread_mutex_unlock` operations.

Specifically, make sure that you understand following topics.

We suggest reading the corresponding `man` pages.

### Testing

We will use the tests in the `test` directory for grading, too. We may add some more tests for grading, but if your solution passes all the given tests, it's very likely that you will get the full score.
