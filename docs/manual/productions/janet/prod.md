---
title: Janet Production
authors:
  - joe_starr
---

## What Is a Janet Production?

Most production types of the PDGL are written in C and compiled into machine code. Meaning that for
most productions the scope of functionality is fixed at compile time. It's easy to see that fixing
the functional scope at compile time limits the flexibility of the PDGL. A Janet production helps
mitigate this issue by allowing the execution of arbitrary functionality during the resolution and
termination of a production. [Janet](https://janet-lang.org/) is a small Lisp style scripting
language with an interpreter embeddable into other programs. The embedded Janet interpreter is fully
featured and is what allows the incision of arbitrary functionality into a PDGL language
specification.

## Using a Janet Production

The Janet production takes in a script as the production output generator and then runs that script
in a Janet interpreter. The standard Janet print function is used to pass replacement data back to
the PDGL. This means calling:

```janet
(print "value")
```

will place the string `value` into the replacement string buffer.

> [!IMPORTANT]
>
> The Janet scripts do not maintain state between executions within the PDGL. That means if you want
> to maintain/pass state in a Janet script you must do it yourself.
>
> One easy way to do this on a PC is by creating
> [files](https://janetdocs.org/core-api/file%2fwrite). Here's an example from the linked site:
>
> ```janet
> # opens a file named filename for writing, and writes Hello World!
> (def f (file/open "filename" :w))
> (file/write f "Hello World!")
> (file/flush f)
> (file/close f)
> ```
>
> For the browser while I haven't looked into it, I suspect something similar can be done with the
> [Emscripten file I/O](https://emscripten.org/docs/api_reference/Filesystem-API.html) system.

> [!WARNING] "Warning!"
>
> In line with the PDGL portability and memory goals the output buffer for a Janet production is a
> fixed size of length
> [DEFS_PDGL_MAX_STRING_SIZE](/lib/pdgl__defs_8h/#define-defs_pdgl_max_string_size).

### Configuring

A Janet production contains two configurable scripts, the replacement script and the terminal
script. The two scripts use the same execution flow but do not run in the same interpreter instance.

### Examples

#### File I/O

```toml
--8<-- "docs/manual/productions/janet/media/1/def.toml"
```

#### Use Library

```toml
--8<-- "docs/manual/productions/janet/media/2/def.toml"
```

#### Include Library

```toml
--8<-- "docs/manual/productions/janet/media/3/def.toml"
```

Supported by `./docs/manual/productions/janet/media/3/script.janet`

```janet
--8<-- "docs/manual/productions/janet/media/3/script.janet"
```

#### Janet Entry

```toml
--8<-- "docs/manual/productions/janet/media/4/def.toml"
```

[](){#schema-janet}
## Production Schema

```json
--8<-- "docs/manual/productions/janet/media/schema.json"
```
