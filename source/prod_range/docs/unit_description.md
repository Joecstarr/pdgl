---
title: Range Production
authors:
  - joe_starr
---

## Class Diagram

```mermaid
classDiagram
   prod_range --> production 
   prod_range *-- prod_range_config_t
   class prod_range{ }
    
   class prod_range_config_t{
   char* key
   int lower_bound 
   int upper_bound 
    }

   class production{<<interface>>}

```

## Interfaces

- [Production][prod_inter]

## Libraries

None

## Functionality

### Public Structures

#### Configuration Structure

The configuration structure contains the data needed for computing the positivity of an input WPTT.

This includes:

- A pointer to a read-only notation structure for a WPTT.

### Public Functions

#### Function

The configuration function sets the local configuration variable of the computation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Initialize local configuration" as Sc

    [*] --> Sc
    Sc --> [*]

```

## Validation
