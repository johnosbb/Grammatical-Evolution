# Grammatical-Evolution

[Grammatical Evolution](https://en.wikipedia.org/wiki/Grammatical_evolution) (GE) is an [Evolutionary Algorithm](https://en.wikipedia.org/wiki/Evolutionary_algorithm#:~:text=In%20computational%20intelligence%20(CI)%2C,mutation%2C%20recombination%2C%20and%20selection.) (EA) that can generate programs in an abritrary language. GE employs a genotype-phenotype mapping process which uses variable length binary strings to select productions from a [Backus Naur Form Grammar](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form). To-date GE has used a [Genetic Algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) as the means of directing the search, however, its ability to separate the search space and solution space makes it suitable for use with a variety of search mechanisms.

In this research the performance and characteristics of GE are compared across a range of metaheuristics including, Random Search (RS), Hill Climbing (HC), Simulated Annealing (SA), Evolutionary Programming (EP), Evolutionary Strategies (ES) and Genetic Algorithms (GAs). The basis for this evaluation is a series of experimental trials in which GE attempts to solve a selection of benchmark problems from the field of [Evolutionary Computing](https://en.wikipedia.org/wiki/Evolutionary_computation) (EC).

We attempt to profile the problem search spaces revealing complex, noisy, discontinuous multimodal landscapes which prove difficult for the deterministic gradient following approaches of HC and SA. We see solutions to our selected problems exist as sharp isolated peaks of maximum fitness with some evidence from our use of RS suggesting that some of the problems have a high density of such peaks.

This research demonstrates GE's ability to work successfully and seamlessly with a broad range of different search approaches and identifies  distinct performance advantages for population based approaches like EP, ES and GAs. This flexibility establishes GE as a powerful and flexible mechanism for the automatic generation of grammar based code and programs. 


[Masters Thesis in full is available here](https://github.com/johnosbb/Grammatical-Evolution/blob/main/Masters_2021.pdf)
