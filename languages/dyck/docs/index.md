---
title: Dyck Language
authors:
  - joe_starr
---

## What?

The Dyck language[@AlgebraicTheoryContextFree1959] is a grammar that generates strings of paired
(sometimes called balanced) parentheses. Further details can be found in the
[User Guide](./manual/whatis/).

## Special Care?

There's nothing special you need to do when deriving from the Dyck language specification.

### What Happens When the Stack Is Full?

When the stack is full an empty string is produced.

## File

```TOML
--8<-- "languages/dyck/def.toml"
```
