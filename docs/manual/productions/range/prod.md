---
title: Range Production
authors:
  - joe_starr
---

## What Is a Range Production?

A range production models the random selection of an integer from a configured range.

## Using a Range Production

### Configuring

A range production contains two configurable integer bounds a lower and upper bound.

> [!note]
>
> A production configured so the lower and upper bounds are equal is possible and will produce the
> same value on every execution.

> [!WARNING] "Warning!"
>
> In line with the PDGL portability and memory goals the output buffer for a range production is a
> fixed size of length
> [DEFS_PDGL_MAX_STRING_SIZE](/lib/pdgl__defs_8h/#define-defs_pdgl_max_string_size).

### Examples

#### Single Option

```toml
--8<-- "docs/manual/productions/range/media/1/def.toml"
```

#### Recursive

```toml
--8<-- "docs/manual/productions/range/media/2/def.toml"
```

#### Multiple Options

```toml
--8<-- "docs/manual/productions/range/media/3/def.toml"
```

[](){#schema-range}

## Production Schema

```json
--8<-- "docs/manual/productions/range/media/schema.json"
```
