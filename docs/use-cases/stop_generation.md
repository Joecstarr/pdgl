---
title: Stop Generation
authors:
  - joe_starr
---

[](){#stop_generation}
## Primary Actor

The PDGL itself is the primary actor.

## Trigger:

The PDGL needs to terminate a generation.

## Goal:

The PDGL gracefully terminates a generation.

## Preconditions:

The generation of a word is underway.

## Scenario:

1. The PDGL detects a reason to terminate the generation of a word.
1. The PDGL terminates the active production.
1. The PDGL exits the generation.
