#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // For time()
#define GENOMELENGTH 5 // this should be the number of genes, ignoring the 0 index as last index used as terminator
#define POPSIZE 100

// Define your representation, fitness function, and other components here

typedef struct {
    char content[GENOMELENGTH+1]; // Two to allow null terminator \0
    int fitness; // Individuals fitness
} individual;

typedef struct {
    individual *individuals; // Pointer to an array of individuals
    int size; // Size of the population
} population;


void viewPop(population *pop);

int fitnessFunction (individual ind) {

    int fitness = 0;

    for (int i = 0; i < GENOMELENGTH; i++) {
        if (ind.content[i] == 'B') {
            fitness++;
        }
    }

    return fitness;
}


// Function to initialize a population of a given size
void initPopulation(population *pop, int size) {
    pop->size = size;
    pop->individuals = (individual *)malloc(size * sizeof(individual));
    if (pop->individuals == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    //Initialize the content of each individual
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < GENOMELENGTH; j++) {
            pop->individuals[i].content[j] = 'A' + (rand() % 26);
        }
        pop->individuals[i].content[GENOMELENGTH] = '\0'; // Place the null terminator
        pop->individuals[i].fitness = fitnessFunction(pop->individuals[i]);
    }

}

// Function to free the allocated memory for the population
void freePopulation(population *pop) {
    free(pop->individuals);
    pop->individuals = NULL;
    pop->size = 0;
}

int main() {
    // Initialize population
    population pop;
    initPopulation(&pop, POPSIZE); // This will also calc the initial fitnesses


    viewPop(&pop); // For Testing

    // Free allocated pop memory
    freePopulation(&pop);

    int iterations = 2000;
    //while (iterations>0) {
        // Selection
        // Crossover
        // Mutation
        // Calculate fitness for the new population
        // Replacement to form the next generation

        // Update termination_condition if necessary
        //iterations--;
    //}

    // Output the best solution found
    return 0;
}

void viewPop(population *pop) {
    for (int i = 0; i < (*pop).size; i++) {
        printf("Individual %d Content %s Fitness %d\n", i, (*pop).individuals[i].content, (*pop).individuals[i].fitness);
    }
}

