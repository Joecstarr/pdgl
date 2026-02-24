---
title: Building the PDGL
authors:
  - joe_starr
---

## Build from Source

### Linux

The PDGL uses the CMake toolchain for building the project. The only supported build environment is
under a Linux environment using the [Nix](https://nixos.org/guides/how-nix-works/) package manager
with the bundled `flake.nix`. From inside the development shell you can run the following command to
build all wrappers and libraries for the PDGL.

```console
just build_rel
```

> [!info] ""
>
> On Linux running Nix you can build all targets with:
>
> ```console
> just build_all
> ```

### Windows

Creating a consistent environment in Windows is quite difficult, as such a Windows build toolchain
is not supported. Not supported means we won't explicitly assist with setting up or debugging
tooling in Windows. If building source on your machine doesn't work try to make your system look
like the one configured in the `QA` and `Release` GitHub actions.

Minimally, a Windows environment will need:

- A GNU c/c++ compiler
- CMake
- Python
- Ninja
- Cython
- Lizard
- [The cp command](https://github.com/uutils/coreutils)
- [The xxd command](https://community.chocolatey.org/packages/xxd) (or just install vim)

> [!note] ""
>
> Windows binaries can also be cross compiled on Linux from within the `flake.nix` development
> shell. They can be run and tested from inside wine64.
>
> ```console
> just build_win
> ```

## Building for the Web

On Linux from within the `flake.nix` environment a JavaScript module with WASM can be compiled with
Emscripten. This is accomplished by running:

```console
just build_em
```
