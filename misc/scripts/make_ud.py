from pathlib import Path

docs_l = Path("../../source/")

for name in docs_l.glob("**/src/*.c"):
    docs = name.parent.parent / "docs"
    nn = name.stem
    with open(name.parent.parent / "mkdocs.yml", "w") as file:
        content = f"""site_name: {str(nn).replace("_", " ").title()} 
nav:
    - Description: \"unit_description.md\"
            """

        file.write(content)
        ...
    ...

    with open(docs / "index.md", "w") as file:
        content = (
            f"""---
title: {str(nn).replace("_", " ").title()}"""
            + """
authors:
    - joe_starr

---
[](<>){#{"""
            + nn
            + """}

- [Description](unit_description.md)
"""
        )
        file.write(content)
        ...
    ...

    with open(docs / "unit_description.md", "w") as file:
        content = (
            f"""---
title: {str(nn).replace("_", " ").title()}"""
            + """
authors:
    - joe_starr

---

## Class Diagram

```mermaid
classDiagram
   class comp_rlitt_positivity_flvrs_e {
    <<Enumeration>>
     uninit,
     positive,
     negative,
     neutral,
     undefined
    }


```
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

### Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "Valid Configuration"

    A valid configuration for the computation is passed to the function.

    **Inputs:**

    - A valid configuration.

    **Expected Output:**

    A positive response.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Null Configuration"

    A null configuration for the computation is passed to the function.

    **Inputs:**

    - A null configuration.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->
"""
        )
        file.write(content)
        ...
    ...
