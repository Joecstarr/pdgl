---
title: Resolution Machine
authors:
  - joe_starr
---

## Class Diagram

```mermaid
classDiagram
   resolution_machine  *-- resolution_stack_t
   resolution_stack_t ..|> resolution_partial_t 
   resolution_machine  *-- prodstr_store_t 
   resolution_machine  *-- prodstr_obj_t
   class resolution_machine {
    + int execute(const prodstr_store_t *prod_store, resolution_stack_t *stack )
    - const production_obj_t* next_production(resolution_partial_t* partial, const prodstr_store_t *prod_store)
    - int resolve_symbol(const prodstr_obj_t *prd, resolution_stack_t *stack)
    }

   class resolution_partial_t{
    <<struct>> 
    const char* buff
    const char* buff_end_ptr
    char * partial_ptr 
    }

   class resolution_stack_t {
    <<struct>> 
    const resolution_partial_t * partials
    const resolution_partial_t * stack_end_ptr 
    resolution_partial_t * stack_ptr 
    }
   
    class prodstr_obj_t{
        <<external>>
    } 

    class prodstr_store_t{
            <<external>>
        } 
```

## Libraries

None

## Use Cases Satisfied

- [Execute Multiple Generations][execute_multiple_generations]
- [Execute Generation of Language][execute_generation_of_language]
- [Execute Production][execute_production]
- [Report Portion of Generation String][report_portion_of_generation_string]
- [Push Production to Stack][push_production_to_stack]
- [Pop Production from Stack][pop_production_from_stack]

## Functionality

### Public Structures

#### Partial Buffer Structure

The buffer structure for partial resolutions. The buffer contains a start, end, and current pointer
for the block of memory. This is essentially a c-string.

#### Resolution Stack Structure

A stack of partial resolution objects. The stack contains a start, end, and current pointer for the
block of memory.

### Public Functions

#### Execute Function

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Push entry to stack" as pes
  state "Step resolution of string" as res  
  state is_empty <<choice>>

    [*] --> pes
    pes --> res 
    res --> is_empty
    is_empty --> res : Stack is not empty
    is_empty --> [*]: Stack is empty
```

```mermaid
stateDiagram-v2
  state "Identify next production symbol" as inps 
  state "Pop stack" as pops  
  state "Execute resolution of production symbol" as erps  
  state "Execute terminal resolution of production symbol" as etrs 
  state "Push result of production symbol" as props  
  state is_end <<choice>>
  state is_full <<choice>>

    [*] --> inps
    inps --> is_end
    is_end --> pops: symbols are exhausted 
    pops --> [*]
    is_end --> is_full: Next symbol found
    is_full --> etrs: Stack is full 
    etrs --> [*]
    is_full --> erps: Stack has room remaining 
    erps --> props 
    props --> [*]
```

### Private Functions

```mermaid
stateDiagram-v2
  state "Scan string for '%'" as ssf  
  state "Print up to found symbol" as props  
  state "Print full string" as ps 
  state "Clear symbol from string" as csfs 
  state "Identify production from store" as ipfs 
  state is_delim <<choice>>
  state is_found <<choice>>

    [*] --> ssf
    ssf --> is_found
    is_found --> is_delim : Symbol found 
    is_delim --> ssf: Is delimited 
    is_delim --> props: else 
    props --> csfs 
    csfs --> ipfs 
    ipfs --> [*] 
    is_found --> ps: else 
    ps --> [*]
```

## Validation
