---
title: The "What" of the PDGL
authors:
  - joe_starr
---

The primary use case of the PDGL is the generation of words from an input grammar. Technically
speaking, grammars describable to the PDGL need not be context free. However, as we discuss in more
detail what the PDGL is doing we will focus on Context Free Grammars. First we will see a naive
approach to using a context free grammar to generate data. This begs the question of the existence
of probabilistic grammars. Finally, we discuss the PDGL's stochastic word generation.

## Sequentially Generating Words with a Context Free Grammar

As we saw a [context free grammar][subsec-context_free] can be applied to answer the word question.
While this is a common use for grammars we will instead apply context free grammars to different
purposes. We will instead use a context free grammar as a machine to generate words in a language.
The simplest way we accomplish this is by systematically chaining together all possible sequences of
productions.

[](){#ex-enumerate}

> [!example] "Example: "
>
> Working in the [paired parentheses language][ex-paired_paren] we have three productions on $S$. We
> can enumerate all possibilities by counting up from 0 in the ternary numeral system with the
> following correspondence:
>
> | Ternary Number | Production        |
> | -------------- | ----------------- |
> | 0              | $S\to\varepsilon$ |
> | 1              | $S\to SS$         |
> | 2              | $S\to(S)$         |
>
> We read productions from a number left to right. When we have reached the $1^{s}$ position we
> apply the $0$ production until the word contains only terminal characters.
>
> Word for 0:
>
> | Current string | Ternary Number | Next production to resolve on leftmost variable |
> | -------------- | -------------- | ----------------------------------------------- |
> | $S$            | 0              | $S\to \varepsilon$                              |
> | $\varepsilon$  |                |                                                 |
>
> Word for 1:
>
> | Current string | Ternary Number | Next production to resolve on leftmost variable |
> | -------------- | -------------- | ----------------------------------------------- |
> | $S$            | 1              | $S\to SS$                                       |
> | $SS$           | 0              | $S\to \varepsilon$                              |
> | $S$            | 0              | $S\to \varepsilon$                              |
> | $\varepsilon$  |                |                                                 |
>
> Word for 2:
>
> | Current string | Ternary Number | Next production to resolve on leftmost variable |
> | -------------- | -------------- | ----------------------------------------------- |
> | $S$            | 2              | $S\to (S)$                                      |
> | $(S)$          | 0              | $S\to \varepsilon$                              |
> | $()$           |                |                                                 |
>
> Word for 10:
>
> | Current string | Ternary Number | Next production to resolve on leftmost variable |
> | -------------- | -------------- | ----------------------------------------------- |
> | $S$            | 1              | $S\to SS$                                       |
> | $SS$           | 0              | $S\to \varepsilon$                              |
> | $S$            | 0              | $S\to \varepsilon$                              |
> | $\varepsilon$  |                |                                                 |
>
> Word for 1120222020:
>
> | Current string | Ternary Number | Next production to resolve on leftmost variable |
> | -------------- | -------------- | ----------------------------------------------- |
> | $S$            | 1              | $S\to SS$                                       |
> | $SS$           | 1              | $S\to SS$                                       |
> | $SSS$          | 2              | $S\to (S)$                                      |
> | $(S)SS$        | 0              | $S\to \varepsilon$                              |
> | $()SS$         | 2              | $S\to (S)$                                      |
> | $()(S)S$       | 2              | $S\to (S)$                                      |
> | $()((S))S$     | 2              | $S\to (S)$                                      |
> | $()((S))S$     | 0              | $S\to \varepsilon$                              |
> | $()(())S$      | 2              | $S\to (S)$                                      |
> | $()(())(S)$    | 0              | $S\to \varepsilon$                              |
> | $()(())()$     |                |                                                 |
>
> It's easy to prove that this method of generating paired parentheses attains every word in the
> language.

### Probability and Grammars

In our example we see that the numbers $0$ and $1$ produce the empty word $\varepsilon$. In fact we
can extend this to an infinite class of numbers that correspond to the empty word, namely any number
$3^n$ yields the empty string.

> [!sat] "Stop and Think:"
>
> Can you identify another infinite family that corresponds to the empty word?

At this point you might be prompted to ask yourself:

> For any given word in the language can I determine how often that word shows up on my list?

Another way to frame this question is:

> Picking a word at random can the probability of picking that specific word be measured?

For some languages the answer to this question is yes. Unfortunately for the sake of time that's as
far as we will go for these **probabilistic languages**. Further details can be found in the
literature some samples include:

- Paz's "Introduction to Probabilistic Automata"[@pazIntroductionProbabilisticAutomata1971]
- Rabin's "Probabilistic automata"[@rabinProbabilisticAutomata1963]
- Booth and Thompson's "Applying Probability Measures to Abstract Languages"
    [@boothApplyingProbabilityMeasures1973]
- Ellis' "Probabilistic languages and automata"[@ellisProbabilisticLanguagesAutomata1969]

## Stochastic Generation

A common use case for the PDGL is the stochastic generation of words from a language. In the case of
the context free grammars we've been working with this means selecting legal productions at random.

> [!EXAMPLE] "Example: "
>
> [](){#ex-random} Working in the [paired parentheses language][ex-paired_paren] we have three
> productions on $S$. We can enumerate each of the productions with a pair of values from integers
> 1-6 as:
>
> | Values | Production        |
> | ------ | ----------------- |
> | 1,2    | $S\to\varepsilon$ |
> | 3,4    | $S\to SS$         |
> | 5,6    | $S\to(S)$         |
>
> Now, to determine the next production to resolve we roll a
> [D6](https://en.wikipedia.org/wiki/Dice).
>
> Word generated from a set of dice rolls:
>
> | Current string | Dice Roll Value | Next production to resolve on leftmost variable |
> | -------------- | --------------- | ----------------------------------------------- |
> | $S$            | 6               | $S\to(S)$                                       |
> | $(S)$          | 3               | $S\to SS$                                       |
> | $(SS)$         | 3               | $S\to SS$                                       |
> | $(SSS)$        | 1               | $S\to\varepsilon$                               |
> | $(SS)$         | 5               | $S\to(S)$                                       |
> | $((S)S)$       | 2               | $S\to\varepsilon$                               |
> | $(()S)$        | 6               | $S\to(S)$                                       |
> | $(()(S))$      | 2               | $S\to\varepsilon$                               |
> | $(()())$       |                 |                                                 |

## Production Termination

In the examples we've seen so far, a common theme is that the derivation of a word appears to "use"
a stack. This is because a context free grammar can also be modeled as what is called a pushdown
automata. At a high level this is precisely how the PDGL derives words of a grammar. The resolution
of a production in a grammar pushes the replacement string onto a stack. In the theoretical world of
a pushdown automaton, the stack is infinitely large. Unfortunately, in the real world resources are
finite; this means that the stack used by the PDGL has a limited size. Which means it can reach a
state where no new productions can take place. To handle a full stack without crashing we add a
second set of replacement strings to productions in PDGL grammars, we call these replacement strings
`terminals`. Fittingly, we require that a terminal replacement contain only terminal symbols,
effectively cutting off the derivation branch.

<!-- rumdl-capture -->
<!-- rumdl-disable MD013 -->
> [!EXAMPLE] "Example: Formal description of the PDGL grammar for the
> [paired parentheses language][ex-paired_paren]:"
>
> 1. $V=\LS S\RS$.
> 1. $\Sigma=\LS (,),\varepsilon\RS$.
> 1. $R$ is the set
>    - $S\to \begin{cases}(S) \mid SS \mid \varepsilon & \text{Stack is not full}\\ \varepsilon & \text{Stack is full}\end{cases}$
> 1. $S=S$
<!-- rumdl-restore -->
> [!NOTE]
>
> We should take a second to give context to the stack design choices. The PDGL operates with a
> stack defined separately from the call stack. The alternative, which is used by the original DGL,
> is to use recursive function calls on the call stack for successive production resolutions.
>
> During simple operation this choice has no noticeable side effects. However, there are two
> important side effects in more advanced/complex usage.
>
> 1. When the stack is full in the PDGL, we can respond with an alternate path. Guaranteeing the
>    derivation of a word. When a call stack fills the program is likely to crash.
> 1. Using calls into the call stack means local and global state is a tad easier to maintain. The
>    PDGL design currently maintains state only within individual productions.

[$\leftarrow$ Last](../prelim){ .md-button } [Next $\rightarrow$](../why){ .md-button }
