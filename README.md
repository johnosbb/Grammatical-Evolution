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

# Grammatical Evolution

## Introduction

This chapter introduces the main elements of Grammatical
Evolution [@ieee2001] [@ge_book]. It begins by providing an overview of
grammars, in particular, focusing on the Backus Naur form used by GE. It
also provides brief descriptions of derivation trees and parse trees,
two important conceptual tools used to describe the application and
structure of a grammar. The basic mechanism of GE is also introduced
showing a step-by-step evolution of a solution using a simple grammar.
Many of the terms associated with GE and referenced in the following
chapters are also introduced here.

## Grammars

Grammars provide a means of formally describing a language. Grammars
consist of rules, which determine the linguistic structure of sentences
in the language, terminals, which are the words or symbols of the
language, and non-terminals, which expand into one or more terminals. In
a *context free grammar* (CFG) the syntax of a symbol, terminal or
non-terminal is the same regardless of what other symbols surround it.
Where there is a single non-terminal the grammar can be described as
*closed* [@ripple].

Backus Naur Form (BNF), an example of which is shown in
Figure [\[simple_grammar\]](#simple_grammar){reference-type="ref"
reference="simple_grammar"}, is a convenient descriptive notation for
context free grammars is a notation for expressing the grammar of a
language in the form of production rules. BNF consists of *terminals*,
which are items that can appear in the language, e.g. + - \* etc. and
*non-terminals*, which can be expanded into one or more terminals and
non-terminals. A grammar can be represented by the tuple $<N,T,P,S>$ ,
where N is the set of non-terminals, T the set of terminals, P a set of
production rules used to map elements of N to T. S a start symbol is a
member of N.

+:------------------------------------------------------------------------+
|     N = {expr,op}                                                       |
|     T = {+,-,/,*,X,(,)}                                                 |
|     S = <expr>                                                          |
|     P is a set of rules:                                                |
|     <expr>     :: == <var> | <expr><op><expr> | <pre-op>(<expr>)        |
|                      | (<expr>)                                         |
|     <var>      :: == X                                                  |
|     <op>       :: == + | - | * | /                                      |
|     <pre-op>   :: == sin | cos | tan | log                              |
+-------------------------------------------------------------------------+

 

### Derivation Trees

A derivation tree is a way of showing graphically the derivation of a
sentence from a grammar. The generation of an expression in GE can be
represented in this form.
Figure [\[derivation_tree\]](#derivation_tree){reference-type="ref"
reference="derivation_tree"} shows a derivation tree for the expression
$x + sin(x)$ using the simple grammar shown above. At the top of this
tree we see the first derivation step in which the non-terminal $<expr>$
is replaced by $<expr><op><expr>$.

### Parse Trees {#parse_trees}

A parse tree concerns itself only with terminals. It assists the
breakdown of the linguistic structure of the language. The parse tree
for the expression $x + sin(x)$ is shown in
Figure [\[parse_tree\]](#parse_tree){reference-type="ref"
reference="parse_tree"}.

 

## A Description of the Method {#modulo}

Grammatical Evolution (GE) [@ieee2001] [@ge_book] is an evolutionary
algorithm that can evolve complete programs in an arbitrary language
using a variable-length binary string. The binary string is decoded into
a genome, which in turn is used to select production rules from a Backus
Naur Form (BNF) grammar definition. The system, illustrated in
Figure [\[ge_fig1\]](#ge_fig1){reference-type="ref"
reference="ge_fig1"}, can use any search mechanism capable of generating
a variable length sequence of integer codons. The codons, typically in
the range 0 - 255, are used to select productions from the target
grammar using the following function:
$$\emph{Rule = (Codon value) MOD(Number of Rules for the current non-terminal)}$$
A number of different codon values in the range 0 - 255 can cause
selection of the same production rule. This occurs because the number of
production rules associated with any non-terminal is generally small
relative to the 256 expressible by a codon. This
[\[sec:degeneracy\]]{#sec:degeneracy label="sec:degeneracy"} *Genetic
Code Degeneracy* [@ieee2001] permits *neutral mutation* which allows
subtle changes in the search space without necessarily impacting the
solution space (see Section [1.5](#degeneracy){reference-type="ref"
reference="degeneracy"}).

 

Wrapping[\[sec:wrapping\]]{#sec:wrapping label="sec:wrapping"} is a
technique employed by GE which allows the mapping process re-use codons
from the genome. Once all codons in a genome have been used the process
simply wraps to the start of the genome and continues the mapping
process helping to improve the probability of a complete mapping of
individuals onto programs.

The fitness associated with a solution is provided by evaluating the
phenotype (i.e.,the program) using an interpreter for the target problem
class. This fitness value is available to the generation mechanism to
influence the future direction of the search strategy. The following
example illustrates the process of GE for the following simple
expression:

$$f(x) = sin(x) + x^2 + x$$

A grammar, which can be used to derive this simple expression, is shown
below.

[\[sect:simple_grammar_bnf\]]{#sect:simple_grammar_bnf
label="sect:simple_grammar_bnf"}


    <expr>   :: == <var> | <expr><op><expr> | <pre-op>(<expr>)
                         | (<expr>) 
    <var>    :: == X                                               
    <op>     :: == + | - | * | /                            
    <pre-op> :: == sin | cos | tan | log        

We present this grammar in tabular form in
Figure [1.1](#simple_grammar_table){reference-type="ref"
reference="simple_grammar_table"} and show the mapping process that
occurs once the search engine has presented a codon to GE.

::: center
::: {#simple_grammar_table}
  Non-Terminals                Productions                                            
  --------------- ------------ ------------- -------------------- ------------------- ------------
                               0             1                    2                   3
  1\.             `<expr>`     `<var>`       `<expr><op><expr>`   `<pre-op>(<expr>`   `(<expr>)`
  2\.             `<var>`      X                                                      
  3\.             `<op>`       \+            \-                   \*                  /
  4\.             `<pre-op>`   sin           cos                  tan                 log

  : [\[simple_grammar_table\]]{#simple_grammar_table
  label="simple_grammar_table"}Simple grammar presented in table form.
:::
:::

GE can use a depth first or a breadth first approach when mapping the
codon string to an expression. The example shown in
Table [1.2](#bf_grammar_table1){reference-type="ref"
reference="bf_grammar_table1"} and
Table [1.3](#bf_grammar_table2){reference-type="ref"
reference="bf_grammar_table2"} illustrates the depth first approach
which employs expansion of the left most non-terminal as the expression
is created. Detailed commentary has been provided on the first nine
derivation steps. The expanding non-terminal is shown in bold type
through out Table [1.2](#bf_grammar_table1){reference-type="ref"
reference="bf_grammar_table1"} and
Table [1.3](#bf_grammar_table2){reference-type="ref"
reference="bf_grammar_table2"} while the genome string used is shown in
Figure [\[genome1\]](#genome1){reference-type="ref"
reference="genome1"}. Depth first expansion has been used in all of the
trials reported in later sections.

 

::: center
::: {#bf_grammar_table1}
  Step   Expression
  ------ ------------------------------------------------------
  0      $<expr>$
         Start symbol.
  1      $( \mathbf{<expr>} )$
         11 mod 4 = 3, Production 3 from row 1 was chosen.
  2      $( \mathbf{<expr>} <op> <expr> )$
         57 mod 4 = 1, Production 1 from row 1 was chosen.
  3      $(( \mathbf{<expr>}) <op> <expr> )$
         91 mod 4 = 3, Production 3 from row 1 was chosen.
  4      $((\mathbf{<var>}) <op> <expr> )$
         148 mod 4 = 0, Production 0 from row 1 was chosen.
  5      $(( X ) \mathbf{<op>} <expr> )$
         There is only one choice for $<var>$
         so no codon was used for the transition to X.
  6      $(( X ) * \mathbf{<expr>} )$
         22 mod 4 = 2, Production 2 from row 4 was chosen.
  7      $(( X ) * \mathbf{<expr>} <op> <expr> )$
         129 mod 4 = 1, Production 1 from row 1 was chosen.
  8      $(( X ) * \mathbf{<expr>} <op> <expr> <op> <expr> )$
         53 mod 4 = 1, Production 1 from row 1 was chosen.

  : [\[bf_grammar_table1\]]{#bf_grammar_table1
  label="bf_grammar_table1"}Analysis of Depth First Mapping.
:::
:::

::: center
::: {#bf_grammar_table2}
  Step   Expression
  ------ ----------------------------------------------------------
  9      $(( X ) * ( \mathbf{<expr>}) <op> <expr> <op> <expr>)$
  10     $(( X ) * (( \mathbf{<expr>})) <op> <expr> <op> <expr>)$
  11     $(( X ) * (( <var> )) \mathbf{<op>} <expr> <op> <expr>)$
  12     $(( X ) * (( X )) \mathbf{<op>} <expr> <op> <expr>)$
  13     $(( X ) * (( X )) + \mathbf{<expr>} <op> <expr>)$
  14     $(( X ) * (( X )) + \mathbf{<var>} <op> <expr>)$
  15     $(( X ) * (( X )) + X \mathbf{<op>} <expr>)$
  16     $(( X ) * (( X )) + X + \mathbf{<expr>})$
  17     $(( X ) * (( X )) + X + \mathbf{<pre-op>} (<expr>))$
  18     $(( X ) * (( X )) + X + Sin (\mathbf{<expr>}))$
  19     $(( X ) * (( X )) + X + Sin (\mathbf{<var>}))$
  20     $(( X ) * (( X )) + X + Sin (X))$

  : [\[bf_grammar_table2\]]{#bf_grammar_table2
  label="bf_grammar_table2"}Analysis of Depth First Mapping (continued).
:::
:::

## Expressed and Unexpressed Codons

A feature of GE is the ability to use only those codons which are
required to effect a successful mapping. The genome string presented to
GE could, for example, contain 30 codons, if only 15 of these are
required to map a successful solution then the remaining 15 remain
unexpressed. Though these codons are unexpressed they are not completely
redundant, because the polymorphic nature of GE means that these codons
could come in to play as that genome evolves through mutation or
recombination.

## Genetic Code Degeneracy and neutral mutation {#degeneracy}

Genetic code degeneracy is a phenomenon that can be observed in the
genetic code of biological organisms [@elseth]. It occurs where there is
redundancy in the coding required to specify aspects of the DNA. This
redundancy can neutralise the effects of mutation in cases where the
mutated bits are those that are redundant to the coding. Kimura's
neutral theory of evolution  [@kimura] suggests that it is *neutral
mutations* that are responsible for the genetic diversity found in
natural populations.

Genetic code degeneracy occurs in GE by virtue of the fact that even
though a codon can represent 256 distinct integer values, many of these
values represent the same production rule. For example using the *MOD
rule* with 4 productions would result in codon values 8, 4, 12 and 16
all selecting the same production 0. It is apparent from this that
genomes with differing codon compositions can map to the same solution.
This property of GE, which permits *neutral mutation* on redundant
codings, allows subtle changes in the search space without necessarily
impacting the solution space.

## Summary

This chapter has introduced Grammatical Evolution, showing in detail how
a variable length string of integer values can be used to derive an
expression in any language given a suitable grammar. An introduction was
provided to the subject of language grammars with particular focus on
the Backus Naur Form. The concepts of genetic code degeneracy, neutral
mutation, and expressed and unexpressed genes were also introduced.

