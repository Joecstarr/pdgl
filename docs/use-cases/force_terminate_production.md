---
title: Force Terminate Production
authors:
  - joe_starr
---

## Primary actor

None.

## Trigger:

An upstream actor needs to terminate a production.

## Goal:

The active production is terminated.

## Preconditions:

The resolution of a production is underway.

## Scenario:

1. The termination case for the active production is sent to the output.
1. The current production is popped from the stack.
