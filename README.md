# Grammatical-Evolution

Grammatical Evolution (GE) is an Evolutionary Algorithm (EA) that can generate programs in an abritrary language. GE employs a genotype-phenotype mapping process which uses variable length binary strings to select productions from a Backus Naur Form grammar. To-date GE has used a Genetic Algorithm as the means of directing the search, however, its ability to separate the search space and solution space makes it suitable for use with a variety of search mechanisms.

In this research the performance and characteristics of GE are compared across a range of metaheuristics including, Random Search (RS), Hill Climbing (HC), Simulated Annealing (SA), Evolutionary Programming (EP), Evolutionary Strategies (ES) and Genetic Algorithms (GAs). The basis for this evaluation is a series of experimental trials in which GE attempts to solve a selection of benchmark problems from the field of Evolutionary Computing (EC).

We attempt to profile the problem search spaces revealing complex, noisy, discontinuous multimodal landscapes which prove difficult for the deterministic gradient following approaches of HC and SA. We see solutions to our selected problems exist as sharp isolated peaks of maximum fitness with some evidence from our use of RS suggesting that some of the problems have a high density of such peaks.

This research demonstrates GE's ability to work successfully and seamlessly with a broad range of different search approaches and identifies  distinct performance advantages for population based approaches like EP, ES and GAs. This flexibility establishes GE as a powerful and flexible mechanism for the automatic generation of grammar based code and programs. 


# Introduction to the Thesis

## Introduction

Grammatical Evolution (GE) is an Evolutionary Algorithm (EA) that uses
variable length binary strings to select productions from a Backus Naur
Form grammar. A feature of Grammatical Evolution is the ability to
separate the search space from the solution space. This aspect, which
allows different methods to be used to explore the search space, is
examined in this research by evaluating the performance and
characteristics of GE using a diverse range of search methods
(Metaheuristics) on a selection of benchmark problems from the field of
*Evolutionary Computation (EC)*.

## Contributions of the Thesis

The principal contribution of the thesis is the evaluation of GE with a
range of metaheuristics. In an effort to better understand the nature of
the search space presented by the GE process these metaheuristics have
been evaluated on a range of traditional Genetic Programming (GP)
benchmark problems.

This is the first time that research on GE has focused on using
different search strategies, up to this point GE had been exclusively
used with a Variable-Length Genetic Algorithm as the search engine.

The work brings together a useful practical summary of many of the key
metaheuristics in use today, providing a step-by-step guide to their
underlying algorithms and operators. The research has also resulted in
the generation of a significant body of object orientated code
implementing all of the selected metaheuristics. By using Random search
as one of the search mechanisms in this research we provide some
interesting insights into the relative difficulty of the selected
problems.

## Organisation of the Thesis

Chapter two of the thesis provides an introduction to GE, providing an
insight into the key workings of the technique. It provides some
background on the specification of grammars, introduces the Backus Naur
Form of grammar and illustrates the mapping process used by GE in
evolving programs from a grammar.

In chapter three we discuss Metaheuristics, providing an overview of the
subject before dealing in detail with each of the metaheuristics
featured in this research.

The selected problem set consisting of *The Santa Fe Trail problem*,
*Symbolic Integration* *Symbolic Regression* and *Block Stacking* is
introduced in chapter four, where we provide a description of each
problem and presents its associated grammar.

Chapters seven through to ten focus on the results from experimental
trials using the selected Metaheuristics, each chapter follows a similar
structure presenting the overall results and then attempting to analyse
and improve the performance of the Metaheuristic under consideration.

The focus of chapter eleven is a comparative overview of all of the
results provided in the previous chapters looking at relative
performance with some discussion on the characteristics that the various
Metaheuristics have in common and a contrast of those aspects that
differentiate them.

Finally, chapter twelve summarises all of the key findings and
identifies areas for future research.

## Terminology

In the context of this thesis the word *Solutions* means a potential
solution to a problem rather than the correct solution to the problem. A
solution that actually solves the problem will be referred to as a
*correct solution* or a *successful solution*.

All results have been tested for significance using a *Chi Square*
significance test at a 98% confidence level. This test compares the
difference between the actual frequencies (the observed frequencies in
the data) with those which one would expect if no factor other than
chance had been operating (the expected frequencies). The closer these
two results are to each other, the greater the probablity that the
observed frequencies are influenced by chance alone. When the text
refers to changes as being significant or not significant it is within
the context of this test.
