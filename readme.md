# Evolutionary Algorithm Implemented in C [Demo]

A simple EA implemented in the C programming language.

The task in this example initalises a population of individuals each with five genes that can be A-Z.
We start by initialising a population, iterating on it a preset number of times where the best two are used to breed - in this case two point crossover. Then we add random mutation on each gene with a 0.2 prob. The childs fitness is calculated and added to the population. After the iteration loop the population is printed to screen.

The example EA is optimising for the character B and so our fitness is just count of B's.

Things that could be improved:

- Better selection (and put in a method)
- Implementation of other crossovers
- Noise based random mutation (broadly seen as better performing)
- 

---
This code was just made for fun and to practice C.