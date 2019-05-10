# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

refers to a lung disease caused by silica dust. one of the longest words in the English language

also the longest word in cs50's large dictionary

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following:

RUSAGE_SELF
    Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

RUSAGE_CHILDREN
    Return resource usage statistics for all children of the calling process that have terminated and been waited for. These statistics will include the
    resources used by grandchildren, and further removed descendants, if all of the intervening descendants waited on their terminated children.

RUSAGE_THREAD
    Return resource usage statistics for the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We pass before and after by reference (instead of by value) to save time and memory

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop uses a c = fgetc(file) function call. This function gets the next character from the file and advances the position indicator in the file until the end of the file (EOF). If the character is
alphabetic, or an apostrophe that is not at index 0 of the word, the character is appended to the word array. If the word is longer than LENGTH, the word is ignored. If the character is numerical, the word
is ignored, and we skip to the next word (which is found after a space). If we hit a space or a punctuation, we have found a whole word, so we terminate the word by adding \0 to the word array.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf would include punctuation as part of a word, which could complicate things. Also it could read a longer string than we have room for in LENGTH, which could cause a segmentation fault

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Constant char pointers prevent changing the data pointed to. In this case we want to prevent changes being made to a read word, and the dictionary being used
