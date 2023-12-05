# Bottom-up-parsing

<p>
An upward parser, also known as a "bottom-up parser," represents a specific type of syntactic analyzer 
employed in compiler theory to carry out the processing and analysis of the grammatical structure of a 
source program. Instead of commencing the analysis from the initial symbol, upward parsers construct the 
syntax tree from the leaves, i.e., the terminal symbols, up to the root, represented by the language's initial symbol.

Specifically, a bottom-up parser, such as the LR(1) parser, follows a syntactic approach based on reducing 
symbols to the right-hand production of a grammar rule. The notation "LR" stands for "left-to-right," indicating 
the order in which input symbols are processed, while the "R" emphasizes the construction of the derivation 
more to the "right" in the production derivation process.  

Below is an example implemented in the C programming language, following a functional programming approach.
</p>

<div align="center">
  <img src="https://github.com/DiegoAndresRa/Bottom-up-parsing/blob/main/Documentation/parser_execution.gif" alt="parser table of LR(1) grammar" width="400">
</div>

## Lenguaje
<img src="https://github.com/devicons/devicon/blob/master/icons/c/c-plain.svg" title="C" alt="C" width="40" height="40"/>&nbsp;

## Grammar
<img src="https://github.com/DiegoAndresRa/Bottom-up-parsing/blob/main/Documentation/Grammar.png" alt="grammar LR(1) of parser" width="250">

## Parser Table
<div align = "center">
  <img src="https://github.com/DiegoAndresRa/Bottom-up-parsing/blob/main/Documentation/parser_table.png" alt="parser table of LR(1) grammar" width="600">
</div>

## Execution
```
$ cd source
$ gcc sintactico_ascendente.c -o sintactico_ascendente
$ ./sintactico_ascendente string_with_atom_string
```
