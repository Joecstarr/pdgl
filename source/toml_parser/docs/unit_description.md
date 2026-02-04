---
title: Toml Parser
authors:
  - joe_starr
---

## Class Diagram

```mermaid
classDiagram
   class toml_parser{
    + prodstr_store_t * parse(char* toml_data )
    + prodstr_store_t * free(char* toml_data )
    - prodstr_obj_t * build_<prod_name>(char* toml_data, prodstr_store_t *store)
    - prodstr_obj_t * (*build_fptr_t)(toml_table_t* tbl ) configured_productions[] 
    }


```

## Libraries

- [tomlc17](https://github.com/cktan/tomlc17)

## Use Cases Satisfied

- [Supply Language Specification][supply_language_specification]
- [Load Language Specification][load_language_specification]
- [Language Specification is Well-defined][language_specification_is_welldefined]

## Functionality

### Public Structures

The module contains no public structures.

### Public Functions

#### Parse Function

The parse function takes TOML data passed to the module and from that data constructs a production
store and identifies the entry symbol.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Parse TOML to object" as Sc
  state "Identify entry symbol" as ies
  fep: for each production 
  state fep {
    state "Build production object" as bpo 
    state "Add production object to production store" as apo
    
    [*]--> bpo
    bpo --> apo 
    apo --> [*]

    }

    [*] --> Sc
    Sc --> ies 
    ies --> fep
    fep --> [*]

```

### Private Functions

#### Build `<<production>>` Functions

The build `<<production>>` functions take data from the given TOML and parses it into a specific
flavor of production object for storage. The implementation of each of these functions is unique and
should be documented in Doxygen comments at declaration.

## Validation
