from pathlib import Path

names = [
    "Supply Language Specification",
    "Verify Language Specification",
    "Language Specification Exists",
    "Load Language Specification",
    "Language Specification is Well-defined",
    "Language Specification Support Files Exist",
    "Log State Information",
    "Load Language Specification Support Files",
    "Execute Generation of Language",
    "Execute Multiple Generations",
    "Report Portion of Generation String",
    "Execute Production",
    "Push Production to Stack",
    "Pop Production from Stack",
    "Execute Pure Production",
    "Execute Janet Production",
    "Execute Range Production",
    "Stop Generation",
]
docs = Path("../../docs/use-cases/")
docs_l = Path("./use-cases/")

for name in names:
    nn = name.replace(" ", "_").replace("-", "").lower()
    nn = f"{nn}.md"
    print(f"- [{name}]({docs_l / nn})")
for name in names:
    nn = name.replace(" ", "_").replace("-", "").lower()
    nn = f"{nn}.md"
    print(f'- "{docs_l / nn}"')
    ...
    with open(docs / nn, "w") as file:
        content = f"""---
title: {name}
authors:
    - joe_starr

---

## Primary actor:

_Actor that initiates usecase._

## Trigger:

_What does the actor do to "start" the usecase?_

## Goal:

_What is the usecase trying to accomplish?_

## Preconditions:

_What assumptions are made when executing usecase?_

## Scenario:

_What happens in the usecase?_

"""
        file.write(content)
        ...
    ...
