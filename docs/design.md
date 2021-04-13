# Diff Em All Design Doc

## Background

Our goal is to provide a robust Diff library for performing diffs. The motivation is that software developers routinely use tools to diff source code (as in version control systems such as git) as well as other types of files: protobufs, JSON, etc. Diffs are also critical in production systems to evaluate and diagnose changes to content.

## Introduction

DiffEmAll is a diff library for performing textual diffs.

### Diff Algorithms

There are generally two classes of diff: textual and semantic.

Textual diff algorithms compare text to find the difference between text files. One of the most common algorithms is the [Myer's diff algorithm](https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/). Myer's diff algorithm is a greedy algorithm that models the problem of finding the shortest edit script (SES) as a graph search problem. Myer's diff is the default diff used by Git. Other common diff algorithms include Patience diff which uses patience sorting algorithm and Histogram diff


Semantic diff performs a "context-aware" analysis of the differences between two files. Since the analysis is semantic rather than syntactic, meaning-preserving transformations (such as renaming variables) are correctly determined to have no visible effect. We researched semantic diff algorithms for diffs on structured data objects such as JSON and XML, but semantic diffs on structured data objects generally follow a different paradigm and would require our library to take a dependency on parsers for these file formats. We decided to reduce the scope of the library to textual diffs as an initial implementation.

## "Hello World" program

We started with a simple program that read in two files and printed out their contents line-by-line. Then we designed a simple templated Diff class and implemented Myer's diff algorithm using dynamic programming to diff two files line-by-line. We originally encapsulated all the program logic in the class i.e., the class contained the logic for parsing, running the diff algorithm, and producing a diff result output. However, we decided to reduce the scope of the class later on.

## Implementation

We decided that the scope of our Diff library was too broad and decided to remove input parsing (reading from files) and printing out the diff output. We also wanted to be able to diff text inputs with different levels of granularity eg. char-based diff vs. line-based diff. As a result, our class is a templated class that allows performing diffs over different types. Our current class defaults to line-based diff because we expect that users of our library will be performing diffs over multiline files, e.g., source code, plaintext, etc.

Since we have a templated class, we needed to account for C++ `undefined reference to` compiler error at linking. There are normally 3 ways to resolve this issue:
- Explicitly instantiate the template. This would require us to specify all the needed templates.
- Move the implementation code into the header file.
- Move the implementation code into a new header file and include it in the original header file.

We opted to move our implementation into the header to create a header-only library. While this increases compilation time, we decided that it would also offer the most flexibility for future development (eg. automatically supporting new data types) and would be easiet for the end user's build process.

## Future Work

### Support semantic diffs
Supporting semantic diffs using off-the-shelf parsers requires taking a dependency on parsers for file formats such as JSON and XML. To reduce this dependency, we would consider adding a preprocessing step to `Diff` that generates a file-format-agnostic intermediate representation that our diff library can execute over.

### Benchmark performance with other diff libraries
Benchmark performance with other diff libraries such as LibXDiff in C.

### C++20 Concepts
The current Myer's diff algorithm assumes the data type is comparable. We can add C++20 concepts to enforce that the template data type must be a type that is comparable (eg. using the `==` and `!=` operators). This allows us to enforce a compile-time check to ensure that the data type is one our algorithm can run over rather than discover an error at runtime.

## References
- [diff-match-patch library](https://github.com/google/diff-match-patch)
- [myers-diff library](https://github.com/gritzko/myers-diff)
- [Myer's Diff Algorithm explanation](https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/)
- http://link.springer.com/article/10.1007/BF01840446
- http://alfedenzo.livejournal.com/170301.html
- https://github.com/git/git/commit/8c912eea94a2138e8bc608f7c3
- http://www.daemonology.net/bsdiff/
- https://www.chromium.org/developers/design-documents/software-updates-courgette
- https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
- https://github.com/isocpp/CppCoreGuidelines
