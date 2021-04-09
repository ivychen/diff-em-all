# Diff Em All

The Diff library implements Myer's diff algorithm for performing text diffs.

## How to Run

run `make`

run `./main origin.txt new.txt` for testing

The Canterurbury corpus used for testing compression algoritms is used here to measure performance differences between files of varying length : https://corpus.canterbury.ac.nz/

 Used to download files > 100MB : https://fastest.fish/test-files

The test folder contains unit tests, integration tests and performance tests

The performance analysis is mainly done on files of varying sizes. The different use cases are :

- Time taken by same files of varying sizes : how does the library perform to diff same files and how does it scale with the increase in size of the input file
- Time taken by different files of varying files : how does the library perform to diff completey disparate files and how does it scale with increase in the size of the input files

The times have been represented in tabular format for better understanding.