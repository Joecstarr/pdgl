---
title: Pure Production
authors:
  - joe_starr
---

## What Is a Pure Production?

A pure production models the basic productions seen in our abstract examples. When executed a
replacement or terminal string is selected at random from the configured array of options.

## Using a Pure Production

### Configuring

A pure production contains two configurable lists one for replacement strings and one for terminal
strings. Each list must be configured with at least one string.

> [!WARNING] "Warning!"
>
> In line with the PDGL portability and memory goals the strings must be less than a fixed size of
> length [DEFS_PDGL_MAX_STRING_SIZE](/lib/pdgl__defs_8h/#define-defs_pdgl_max_string_size).

### Examples

#### Single Option

```toml
--8<-- "docs/manual/productions/pure/media/1/def.toml"
```

#### Recursive

```toml
--8<-- "docs/manual/productions/pure/media/2/def.toml"
```

#### Multiple Options

```toml
--8<-- "docs/manual/productions/pure/media/3/def.toml"
```

[](){#schema-pure}

## Production Schema

```json
--8<-- "docs/manual/productions/pure/media/schema.json"
```
