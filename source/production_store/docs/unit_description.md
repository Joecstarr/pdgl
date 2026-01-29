---
title: Production Store
authors:
  - joe_starr
---

## Class Diagram

```mermaid
classDiagram

   production_store *-- prodstr_store_t 
   prodstr_store_t *-- prodstr_obj_t 

    class production_store{
        + int add_prod(prodstr_store_t* store, const char* name,const void* config, const resolve_fptr_t res, const terminate_fptr_t term)
        + const prodstr_obj_t * find_prod(prodstr_store_t* store, char* name)
        - int hash(char* name)
        }

    
    class prodstr_obj_t{
        <<struct>>
        prodstr_obj_t *next
        char * name
        char * type 
        void * config
        const char * (*resolve_fptr_t)(const void * config) res
        const char * (*terminate_fptr_t)(const void * config) term
    }


    class prodstr_store_t{
        <<struct>>
        prodstr_obj_t prod_table[200]
        } 


```

## Libraries

None

## Functionality

### Public Structures

#### Production Store Structure

The production store holds a hash table of production objects. This requires:

- A buffer of production objects.
- A hash table of production objects.

#### Production Object Buffer Structure

The buffer structure of production objects.

#### Production Store Object Structure

The production object type holds a single production object. To ensure hash collisions are not a
problem each object holds a pointer to another object in the same hash bin. Otherwise this structure
contains:

- The name of the production. This serves as the key for the hash.
- A void pointer to a production configuration. We choose void to allow storage of arbitrary
  production types.
- A function pointer to the resolve function of the production.
- A function pointer to the terminate function of the production.

### Public Functions

#### Add Production Function

The function adds a production to the supplied hash table. The function takes the data required for
to produce a production object. The function returns a status indicator.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Get next buffer entry" as Sc
  state "Build production object" as bpo 
  state "Hash production name" as hpn 
  state "Insert object into hash table" as io

    [*] --> Sc
    Sc --> bpo
    bpo --> hpn
    hpn --> io
    io --> [*]

```

#### Get Production Function

The function retrieves a production from the supplied hash table. The function returns the requested
production or NULL in the error case.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Hash production name" as hpn 
  state "Find object in hash table" as io

    [*] --> hpn 
    hpn --> io
    io --> [*]

```

## Validation

### Add Function

#### Positive Tests

!!! test-card "A production is passed to the add function"

    A production is passed to the add function.

    **Inputs:**

    - A production is passed to the add function with an empty store.
    - A production is passed to the add function with a non-empty stores:
        - The store has a value away from the hash of the supplied production
        - The store has a value at the hash of the supplied production

    **Expected Output:**

    A positive response. The store is reflecting an additional element. New element is at the correct
    hash and matches the supplied production.

#### Negative Tests

!!! test-card "A production already in the store is passed to the store"

    A production already in the store is passed back to the store.

    **Inputs:**

    - A production and store with collision.

    **Expected Output:**

    A negative response.

!!! test-card "A NULL pointer is passed to the function"

    A NULL pointer is passed to the function.

    **Inputs:**

    - A null pointer for:
        - store
        - production

    **Expected Output:**

    A negative response.

### Find Function

#### Positive Tests

!!! test-card "A production key is passed to the find function"

    A production key is passed to the find function.

    **Inputs:**

    - A valid production which is:
        - In the store.
        - Not in the store.

    **Expected Output:**

    - A matching production.
    - A null pointer.

#### Negative Tests

!!! test-card "A NULL pointer is passed to the function"

    A NULL pointer is passed to the function.

    **Inputs:**

    - A null pointer for:
        - store
        - production key

    **Expected Output:**

    A negative response.
