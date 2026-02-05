---
title: High Level Documentation for Low Level Libraries
authors:
  - joe_starr
---

## System Architecture

```mermaid
flowchart LR
    ep["<< External >> 
    Entry point"]
    toml["TOML Parser"]
    rsm["Resolution State Machine"]
    io["I/O"]
    log["Log"]
    ps["Production Store"]
    jp["Janet Production"]
    pure["Pure Production"]
    range["Range Production"]
    ip["<< Interface >>
    Production"]
    ep -->|1..*| rsm
    ep -->|1..1| ps 
    ep -->|1..1| toml 
    ep -->|1..1| io 
    rsm -->|1..1| toml 
    ip -->|1..1| io 
    ip -->|1..1| log 
    rsm -->|1..1| ps 
    ep -->|1..1| log 
    rsm -->|1..1| log 
    ps -->|1..*| jp
    ps -->|1..*| pure
    ps -->|1..*| range
    jp -. Implements .-> ip
    pure -. Implements .-> ip 
    range -. Implements .-> ip 
```

## General Design Considerations

##### Memory

The PDGL is to be written in C, one major consideration when using a non-memory language like C is
memory leaks. The allocation (and release) of memory at runtime is complicated and error prone. To
mitigate the risk of a memory leak we will restrict runtime memory allocation where possible.
Instead we will allocate memory at runtime or opt for passing of buffers.

##### Patterns

We will leverage the [strategy](https://refactoring.guru/design-patterns/strategy) pattern for
defining generic productions with the interface described as the
[Production Interface](./interfaces/production.md). We will also leverage the
[prototype](https://refactoring.guru/design-patterns/prototype) pattern for managing configurations
of various 'objects'. Meaning components should not maintain internal state, any state must be
passed to components.
