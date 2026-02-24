---
title: Configuring a Grammar
authors:
  - joe_starr
---

For the PDGL to derive a word in a grammar it must be presented to the PDGL in a machine readable
format, a **language specification**. For the PDGL command line tool as well as the browser
interface this means a TOML file. These TOML files can't just be in any format you want they must be
written in a way that the PDGL can understand. The PDGL can parse TOML files written in the
following [format (schema)](#schema-pdgl).

## Language Specification for the [Paired Parentheses Grammar][ex-paired_paren]

```TOML
--8<-- "languages/paren/def.toml"
```

## Parts of a PDGL Language Specification

By construction we know that a language specification must map onto the definition of an
[abstract grammars][def-grammar]. We will walk point by point through the definition of a grammar
and see how they have been mapped onto a TOML file.

### The Terminals ($\Sigma$)

The terminals of every and all PDGL language specifications are the ASCII characters.

| hex | char | hex | char  |
| --- | ---- | --- | ----- |
| 00  | NUL  | 20  | SPACE |
| 01  | SOH  | 21  | !     |
| 02  | STX  | 22  | "     |
| 03  | ETX  | 23  | #     |
| 04  | EOT  | 24  | $     |
| 05  | ENQ  | 25  | %     |
| 06  | ACK  | 26  | &     |
| 07  | BEL  | 27  | '     |
| 08  | BS   | 28  | (     |
| 09  | HT   | 29  | )     |
| 0a  | LF   | 2a  | \*    |
| 0b  | VT   | 2b  | +     |
| 0c  | FF   | 2c  | ,     |
| 0d  | CR   | 2d  | -     |
| 0e  | SO   | 2e  | .     |
| 0f  | SXI  | 2f  | /     |
| 10  | DLE  | 30  | 0     |
| 11  | DC1  | 31  | 1     |
| 12  | DC2  | 32  | 2     |
| 13  | DC3  | 33  | 3     |
| 14  | DC4  | 34  | 4     |
| 15  | NAK  | 35  | 5     |
| 16  | SYN  | 36  | 6     |
| 17  | ETB  | 37  | 7     |
| 18  | CAN  | 38  | 8     |
| 19  | EM   | 39  | 9     |
| 1a  | SUB  | 3a  | :     |
| 1b  | ESC  | 3b  | ;     |
| 1c  | FS   | 3c  | $<$   |
| 1d  | GS   | 3d  | =     |
| 1e  | RS   | 3e  | $>$   |
| 1f  | US   | 3f  | ?     |

| hex | char | hex | char |
| --- | ---- | --- | ---- |
| 40  | @    | 60  | \`   |
| 41  | A    | 61  | a    |
| 42  | B    | 62  | b    |
| 43  | C    | 63  | c    |
| 44  | D    | 64  | d    |
| 45  | E    | 65  | e    |
| 46  | F    | 66  | f    |
| 47  | G    | 67  | g    |
| 48  | H    | 68  | h    |
| 49  | I    | 69  | i    |
| 4a  | J    | 6a  | j    |
| 4b  | K    | 6b  | k    |
| 4c  | L    | 6c  | l    |
| 4d  | M    | 6d  | m    |
| 4e  | N    | 6e  | n    |
| 4f  | O    | 6f  | o    |
| 50  | P    | 70  | p    |
| 51  | Q    | 71  | q    |
| 52  | R    | 72  | r    |
| 53  | S    | 73  | s    |
| 54  | T    | 74  | t    |
| 55  | U    | 75  | u    |
| 56  | V    | 76  | v    |
| 57  | W    | 77  | w    |
| 58  | X    | 78  | x    |
| 59  | Y    | 79  | y    |
| 5a  | Z    | 7a  | z    |
| 5b  | \[   | 7b  | {    |
| 5c  | \\   | 7c  | \|   |
| 5d  | \]   | 7d  | }    |
| 5e  | ^    | 7e  | ~    |
| 5f  | \_   | 7f  | DEL  |

### The Productions ($R$)

The productions of a language specification map to elements of the `production` list. Each element
of the `production` list contains two functional paths the resolution path and the terminal path.
The specific logical execution that happens on these paths, as well as what additional data is
required, is determined by the `type` configured for the production.

#### Production Types

- [Pure Production](./pure/prod.md)
- [Range Production](./range/prod.md)
- [Janet Production](./janet/prod.md)

### The Variables ($V$)

The variables of the PDGL consist of the set of configured `name` fields of the productions. Notice
that the variables are words over the terminal, this causes some headaches for parsing the variables
out of a string that is being resolved. To mitigate this issue we modify the variables (when found
in a partially derived string) with the delimiters `%`,`{`, and `}` as `%{<variable>}`.

### The Start Variable ($S$)

The PDGL elects to define the variable `entry` as the start variable for every language
specification. Meaning every language specification must have a production configured with the name
`entry`. Defining this as a constant means the TOML files are slightly easier to read.

[](){#schema-pdgl}
## Schema

```json
--8<-- "docs/manual/media/pdgl-schema.json"
```

### Schema for Production Types

- [Pure Production][schema-pure]
- [Range Production][schema-range]
- [Janet Production][schema-janet]

### Validating a Grammar

To validate a grammar against the PDGL schema follow these steps from inside the `flake.nix`
development shell:

1. Convert the grammar TOML into JSON:
    ```fish
    toml2json gramar_file.toml > .build/temp.json
    ```
1. Validate the generated JSON:
    ```fish
    jsonschema-cli docs/manual/media/schema/pdgl-schema.json -i .build/temp.json
    ```

If your grammar passes this validation it should successfully parse in both the PDGL command line
and browser interfaces.

> [!IMPORTANT]
>
> In many of the examples in this document the entry symbol has been "pure". There is no reason the
> entry symbol needs to be "pure". The PDGL will accept any production type as the entry symbol.
