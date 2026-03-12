---
title: Pronounceable Word Language
authors:
  - joe_starr
---

## What?

Some research disciplines dealing with human perception use English words as a base dataset for
study. Unfortunately, simply selecting English words from the OED can introduce bias in a study. In
these cases bias can be controlled by ensuring that words in the base dataset are sampled from the
language of pronounceable in English but non-dictionary words (PEND).The task of deriving words in
the PEND language isn't straight forward. There are two issues that arise when you attempt this
task. First, how do you ensure that the derived word is actually pronounceable? Second, how do you
ensure the word is not a bonafide English dictionary word?

The first issue is probably best addressed by some grammar based on phonetics pronounce ability.
Unfortunately, at this point phonetics are beyond my knowledge base. Instead, we use a less
sophisticated approach taken from an answer on Stack Overflow[^so][@Wordle]. This approach uses
bigrams (two Latin letters) and trigrams (three Latin letters) as the basis for forming words in the
target language. In our grammar a word always starts with a bigram, transitions in the grammar then
convert that bigram into a trigram. The conversion happens by selecting biased random choice a third
character. Naturally the bigrams and trigrams found in English are not equally likely. We will use
this difference in frequency as an integer weight representing its frequency in the Google n-gram
dataset[@juolaGoogleBooksNgrams2022]. If we continue to derive from this grammar we arrive at
infinitely long "pronounceable" strings. To control the length of the word we control the size of
the stack. A stack of size $n$ will produce a word of length $n+1$. This combined with a calling
script that randomly selects a length from the Google word length data [@juolaGoogleBooksNgrams2022]
again weighted by frequency.

|Length|Frequency|
|--|--|
|0 | 0|
|1 |26|
| 2|622|
|3 |4615|
| 4|6977|
|5 |10541|
| 6|13341|
| 7|14392|
| 8|13284|
| 9|11079|
| 10|8468|
| 11|5769|
| 12|3700|
| 13|2272|
| 14|1202|
| 15|668|
| 16|283|
| 17|158|
| 18|64|
| 19|40|
| 20|16|
| 21|1|
| 22|5|
| 23|2|

The second issue is much simpler to solve. Unfortunately, actually implementing the solution must be
done in a postprocessing step by a separate tool. Once we have derived a word we simply check if
it's in an (or many) dictionaries.  

## Special Care?

As described above special needs to be taken when configuring the stack size.

### What Happens When the Stack Is Full?

When the stack is full an empty string is produced a string containing the current bigram.

## File

The file containing this grammar is rather large but can be found on [GitHub](https://github.com/Joecstarr/pdgl/tree/main/languages/words/def.toml).

[^so]: [https://stackoverflow.com/questions/25966526/how-can-i-generate-a-random-logical-word](https://stackoverflow.com/questions/25966526/how-can-i-generate-a-random-logical-word)
