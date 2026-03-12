---
title: Running the PDGL
authors:
  - joe_starr
---

## Run the Executable on Your Computer

The PDGL CLI wrapper takes input in two forms, first the language specification from `stdin` and
second configuration options from arguments [^1]. The PDGL CLI outputs words to `stdout`. This
allows for the PDGL CLI to be included in complex
[pipelines](<https://en.wikipedia.org/wiki/Pipeline_(Unix)>). A typical call that outputs words to
the screen looks like the following:

```console
$ cat dyck_lang.toml | ./pdgl_cli -c 4

(()())
(())
(())
((()))
```

If something goes wrong please report your issue.

[:fontawesome-solid-bug: Report!](https://github.com/Joecstarr/pdgl/issues/new/choose){ .md-button }

## Running from the Browser

An alternative option for interacting with the PDGL is by using the browser interface available at
[TODO](TODO)

[^1]: Full documentation for arguments found in the [PDGL CLI documentation.][wrap_cli_interface]
