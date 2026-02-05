---
title: Execute Janet Production
authors:
  - joe_starr
---

[](){#execute_janet_production}
## Primary actor

N/A

## Trigger:

An upstream actor requires the resolution of a janet production in the configured language.

## Goal:

The resolution of a janet production in the configured language.

## Preconditions:

A language is specified.

## Scenario:

1. A janet production symbol is removed from the current state string.
1. A janet snippet is executed resulting in a string.
1. The string is set as the result string.
1. The result string is pushed onto the stack.
