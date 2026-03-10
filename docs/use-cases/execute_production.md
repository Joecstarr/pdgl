---
title: Execute Production
authors:
  - joe_starr
---

[](){#execute_production}

## Primary Actor

N/A

## Trigger

An upstream actor requires the resolution of a production in the configured language.

## Goal

The resolution of a production in the configured language.

## Preconditions

A language is specified.

## Scenario

1. A production is defined.
1. The production symbol is replaced.
1. The result of the production is enqueued.
1. When fully resolved the production step is popped.
