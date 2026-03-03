---
title: Weighted Production
authors:
  - joe_starr
---

## What Is a Weighted Production?

A weighted production is a simple extension of a [pure production][prod_pure]. The production
extends the random selection of replacement (or terminal) strings by allowing arbitrary production
ratios to be enforced when selecting.

> [!Example]
>
> Consider first the simple case where all weights are identical.
>
> | String | Weight |
> | ------ | ------ |
> | A      | 1      |
> | B      | 1      |
> | C      | 1      |
> | D      | 1      |
>
> In this case the behavior is identical to the [pure production][prod_pure]. To model the sampling
> of the set we can roll a D4 (four sided die). With a roll landing on a 1 corresponding to sampling
> an A, 2 a B, 3 a C, and 4 a D.
>
> Now take the case where weights are not identical.
>
> | String | Weight |
> | ------ | ------ |
> | A      | 1      |
> | B      | 2      |
> | C      | 2      |
> | D      | 1      |
>
> In this case we should expect different behavior when compared to the pure production case. When
> these are sampled from we should expect to see twice as many B and C as we see A and D. To model
> sampling we roll a D6. With a roll landing on a 1 corresponding to a sampling an A, 2 or 3 a B, 4
> or 5 a C, and 6 a D.

## Using a Weighted Production

### Configuring

A weighted production contains two configurable lists one for replacement strings and one for
terminal strings. Each list contains pairs of a string called `string` and an integer weight called
`weight`. Each list must be configured with at least one string.

> [!WARNING] "Warning!"
>
> In line with the PDGL portability and memory goals the strings must be less than a fixed size of
> length [DEFS_PDGL_MAX_STRING_SIZE](/lib/pdgl__defs_8h/#define-defs_pdgl_max_string_size).

### Examples

#### Single Option

```toml
--8<-- "docs/manual/productions/weighted/media/1/def.toml"
```

#### Recursive

```toml
--8<-- "docs/manual/productions/weighted/media/2/def.toml"
```

#### Multiple Options

```toml
--8<-- "docs/manual/productions/weighted/media/3/def.toml"
```

[](){#schema-weighted}
## Production Schema

```json
--8<-- "docs/manual/productions/weighted/media/schema.json"
```
