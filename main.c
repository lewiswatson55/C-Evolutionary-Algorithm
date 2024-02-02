#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // For time()
#include <stdbool.h>
#define GENOMELENGTH 50   // this should be the number of genes, ignoring the 0 index as last index used as terminator
#define POPSIZE 1000
#define MUTATEPROB 0.2
#define ITERATIONNUM 20000


// Representation definition
typedef struct {
    char content[GENOMELENGTH+1]; // Two to allow null terminator \0
    int fitness; // Individuals fitness
} Genome;

typedef struct {
    Genome *individuals; // Pointer to an array of individuals
    int size; // Size of the Population
} Population;


// Method declarations
void viewPop(Population *pop);
void sortPopulationByFitness(Population *pop);
void viewGenome(Genome genome);
void findTwoNumbers(int *num1, int *num2);
void TwoPtCx(Genome mum, Genome dad, Genome *child);
void microwaveChild(Genome *child);
void replacePop(Genome baby, Population *pop);

int fitnessFunction (Genome ind) {

    int fitness = 0;

    for (int i = 0; i < GENOMELENGTH; i++) {
        if (ind.content[i] == 'B') {
            fitness++;
        }
    }

    return fitness;
}


// Function to initialize a Population of a given size
void initPopulation(Population *pop, int size) {
    pop->size = size;
    pop->individuals = (Genome *)malloc(size * sizeof(Genome));
    if (pop->individuals == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Initialize the content of each Genome
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < GENOMELENGTH; j++) {
            pop->individuals[i].content[j] = 'A' + (rand() % 26);
        }
        pop->individuals[i].content[GENOMELENGTH] = '\0'; // Place the null terminator
        pop->individuals[i].fitness = fitnessFunction(pop->individuals[i]);
    }

    sortPopulationByFitness(pop);

}

// Function to free the allocated memory for the Population
void freePopulation(Population *pop) {
    free(pop->individuals);
    pop->individuals = NULL;
    pop->size = 0;
}

int main() {

    // Seed the random number generator with time
    srand((unsigned int)time(NULL));

    // Initialize Population
    Population pop;
    initPopulation(&pop, POPSIZE); // This will also calc the initial fitnesses

    //viewPop(&pop); // For Testing

    int iterations = ITERATIONNUM;
    while (iterations>0) {

        // Select top parents
        Genome parent1 = pop.individuals[0];
        Genome parent2 = pop.individuals[1];

        // Uncomment for verbose/debugging - will drastically slow down program.
        //viewGenome(parent1);
        //viewGenome(parent2);

        // Crossover
        Genome child;
        TwoPtCx(parent1, parent2, &child);

        // Mutation
        microwaveChild(&child);

        // Calculate Child Fitness
        child.fitness = fitnessFunction(child);

        // Check child
        //viewGenome(child); // For debugging - slows program

        // Replacement to form the next generation
        replacePop(child, &pop);

        // Update Iterations
        iterations--;
    }

    // Show full population (sorted)
    sortPopulationByFitness(&pop); // Shouldn't be required but just to be safe...
    viewPop(&pop);


    // Free allocated pop memory
    freePopulation(&pop);

    // Output the best solution found
    return 0;
}

void replacePop(Genome baby, Population *pop) {
    pop->individuals[POPSIZE - 1] = baby;
    sortPopulationByFitness(pop);
}

// Mutation Operator
void microwaveChild(Genome *child) {
    // Loop through each character in the individual's content
    for (int i = 0; i < GENOMELENGTH; i++) {
        float chance = (float)rand() / (float)RAND_MAX; // Generate a number between 0.0 and 1.0
        if (chance < MUTATEPROB) { // 20% chance to mutate
            child->content[i] = 'A' + (rand() % 26); // Random character between 'A' and 'Z'
            //printf("A child has been microwaved...\n"); // for debugging
        }
    }
}

// Two Point Crossover
void TwoPtCx(Genome mum, Genome dad, Genome *child) {
    // Split points
    int pointA;
    int pointB;
    findTwoNumbers(&pointA, &pointB);
    //printf("\n%d and %d\n", pointA, pointB); // uncomment for debugging

    // Copy from mum up to pointA
    for (int j = 0; j < pointA; j++) {
        child->content[j] = mum.content[j];
    }

    // Copy from dad from pointA to pointB
    for (int j = pointA; j < pointB; j++) {
        child->content[j] = dad.content[j];
    }

    // Copy the rest from mum or dad as needed after pointB to the end
    for (int j = pointB; j < GENOMELENGTH; j++) {
        child->content[j] = mum.content[j];
    }

    // Ensure the string is null-terminated
    child->content[GENOMELENGTH] = '\0';
}

void findTwoNumbers(int *num1, int *num2) {
    // Generate the first number
    *num1 = (rand() % GENOMELENGTH); // Not plus one because it cannot be 5
    //printf("%d",*num1); // for debugging

    do {
        // Generate the second number
        *num2 = (rand() % GENOMELENGTH) + 1;
        //printf("%d",*num2); // for debugging
    } while (*num1 >= *num2); // Ensure num2 is distinct and bigger then num1
}


void viewPop(Population *pop) {
    for (int i = 0; i < (*pop).size; i++) {
        printf("Genome Rank in pop: %d Content: %s Fitness: %d\n", i, (*pop).individuals[i].content, (*pop).individuals[i].fitness);
    }
}

void viewGenome(Genome genome) {
    printf("Genome Content %s Fitness %d\n", genome.content, genome.fitness);
}

// Function to sort the Population by fitness in descending order
void sortPopulationByFitness(Population *pop) {
    int i, j;
    bool swapped;
    for (i = 0; i < pop->size - 1; i++) {
        swapped = false;
        for (j = 0; j < pop->size - i - 1; j++) {
            if (pop->individuals[j].fitness < pop->individuals[j + 1].fitness) {
                // Swap the individuals
                Genome temp = pop->individuals[j];
                pop->individuals[j] = pop->individuals[j + 1];
                pop->individuals[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (!swapped) {
            break;
        }
    }
}
