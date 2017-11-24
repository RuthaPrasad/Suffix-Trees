# Suffix-Trees
To build and experiment with Suffix Trees

Language Restriction: C

Given a set of documents, build a suffix tree to perform the following operations.
1.	List all the occurrences of a query-string in the set of documents.
2.	List only the first occurrence of a given query-string in every document. If the query-string is not present, find the first occurrence of the longest substring of the query-string.
3.	For a given query-string (query of words), list the documents ranked by the relevance.

Data-Set and Resources:
Data-set 1: Aesop Tales (AesopTales.txt), where each tale is a document. It's provided as a single text file with all the tales concatenated with two blank lines separating two tales. First line of the tale is the title of the tale.

1.	List all the occurrences of a query-string in the set of documents. One result per occurrence. For every occurrence, a result to have the title of the tale along with the sentence (sentences if the query-string spans over multiple sentences) having the matched text (text snippet surrounding the matched text).

2.	List only the first occurrence of a given query-string in every document. If the query-string is not present, find the first occurrence of the longest substring of the query-string. For every occurrence, a result to have the title of the tale along with the sentence (sentences if the query-string spans over multiple sentences) having the matched text (text snippet surrounding the matched text). One result per document (tale) if there is at least one character match.

3.	For a given query-string (query of words), list the documents ranked by the relevance. Define relevance. The following criteria are some guidelines for defining the relevance but you can have your own reasonable definition:
   
      a. Sequence of words in the text matching the query is more relevant than subsequence of words in the text matching the query (that is, all the words in query appear in the relative order but some other words in between is a subsequence of words).
   
      b. A subsequence with lesser number of other words is more relevant than with more number of other words.
    
      c. All the words of the query appear in the same relative order is more relevant than they appearing in any other order in the document.
   
      d.	Matching of non-stop-words is more relevant than matching of stop-words. In general, matching "important" words is more relevant than that of the other words.
   
      e.	Matching all words in the query is more relevant than matching a subset of words.
   
      f.	Matching exact words from the query is more relevant than matching a similar word (another word with same stem, possible minor typo in the word, synonym).
