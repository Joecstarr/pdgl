---
title: Execute Range Production
authors:
  - joe_starr
---

[](){#execute_range_production}
## Primary Actor

N/A

## Trigger:

An upstream actor requires the resolution of a range production in the configured language.

## Goal:

The resolution of a range production in the configured language.

## Preconditions:

A language is specified.

## Scenario:

1. A range production symbol is removed from the current state string.
1. A decimal string representation of an integer is generated.
1. The string is set as the result string.
1. The result string is pushed onto the stack.
