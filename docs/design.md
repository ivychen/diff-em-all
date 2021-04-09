# Diff Em All

## Design Decisions

### Background research

Our goal is to provide a robust Diff library for performing diffs. We decided to start our scope with textual diff and researched various diff algorithms. One of the most common algorithms is the [Myer's diff algorithm](https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/). Myer's diff algorithm is a greedy algorithm that models the problem of finding the shortest edit script (SES) as a graph search problem.

We also researched semantic diff algorithms for diffs on structured files such as JSON and XML and learned that performing semantic diffs follows a different paradigm compared to text diff algorithms. To simplify the scope of our project, we decided to start with text diffs.

### "Hello World" program

We started with a simple program that read in two files and printed out their contents line-by-line. Then we designed a simple templated Diff class and implemented Myer's diff algorithm using dynamic programming to diff two files line-by-line. We originally encapsulated all the program logic in the class i.e., the class contained the logic for parsing, running the diff algorithm, and producing a diff result output. However, we decided to reduce the scope of the class later on.

### Scope

We decided that the scope of our Diff library was too broad and decided to remove input parsing (reading from files) and printing out the diff output. We also wanted to be able to diff text inputs with different levels of granularity eg. char-based diff vs. line-based diff. Our current class defaults to line-based diff because we expect that users of our library will be performing diffs over multiline files, e.g., source code, plaintext, etc.


## References
- [diff-match-patch library](https://github.com/google/diff-match-patch)
- [myers-diff library](https://github.com/gritzko/myers-diff)
- [Myer's Diff Algorithm explanation](https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/)
- http://link.springer.com/article/10.1007/BF01840446
- http://alfedenzo.livejournal.com/170301.html
- https://github.com/git/git/commit/8c912eea94a2138e8bc608f7c3
- http://www.daemonology.net/bsdiff/
- https://www.chromium.org/developers/design-documents/software-updates-courgette
