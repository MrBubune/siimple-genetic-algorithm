#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Parameters
const int POP_SIZE = 6;          // Population size
const int CHROMOSOME_LENGTH = 5; // 5 bits for numbers 0-31
const int MAX_GENERATIONS = 20;
const double MUTATION_RATE = 0.1;

// Convert binary string to integer
int binaryToInt(const vector<int>& chromosome) {
    int value = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        value = (value << 1) | chromosome[i];
    }
    return value;
}

// Fitness function f(x) = x^2
int fitness(const vector<int>& chromosome) {
    int x = binaryToInt(chromosome);
    return x * x;
}

// Create a random chromosome
vector<int> randomChromosome() {
    vector<int> chromosome(CHROMOSOME_LENGTH);
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        chromosome[i] = rand() % 2;
    }
    return chromosome;
}

// Selection: Roulette Wheel Selection
int selectParent(const vector<vector<int>>& population, const vector<int>& fitnesses) {
    int totalFitness = 0;
    for (int f : fitnesses) totalFitness += f;
    int pick = rand() % totalFitness;
    int current = 0;
    for (int i = 0; i < POP_SIZE; ++i) {
        current += fitnesses[i];
        if (current > pick) return i;
    }
    return POP_SIZE - 1; // fallback
}

// Crossover: Single-point crossover
pair<vector<int>, vector<int>> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int point = rand() % CHROMOSOME_LENGTH;
    vector<int> child1 = parent1;
    vector<int> child2 = parent2;
    for (int i = point; i < CHROMOSOME_LENGTH; ++i) {
        swap(child1[i], child2[i]);
    }
    return {child1, child2};
}

// Mutation: flip bits with probability MUTATION_RATE
void mutate(vector<int>& chromosome) {
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        if ((rand() / (double)RAND_MAX) < MUTATION_RATE) {
            chromosome[i] = 1 - chromosome[i];
        }
    }
}

int main() {
    srand(time(0));

    // Initialize population
    vector<vector<int>> population;
    for (int i = 0; i < POP_SIZE; ++i) {
        population.push_back(randomChromosome());
    }

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        // Calculate fitness for each individual
        vector<int> fitnesses;
        for (auto& indiv : population) {
            fitnesses.push_back(fitness(indiv));
        }

        // Find best solution
        int bestFitness = *max_element(fitnesses.begin(), fitnesses.end());
        int bestIndex = distance(fitnesses.begin(), max_element(fitnesses.begin(), fitnesses.end()));
        cout << "Gen " << generation << " Best Fitness: " << bestFitness
             << " (x = " << binaryToInt(population[bestIndex]) << ")" << endl;

        // Create new population
        vector<vector<int>> newPopulation;

        while ((int)newPopulation.size() < POP_SIZE) {
            int parent1Idx = selectParent(population, fitnesses);
            int parent2Idx = selectParent(population, fitnesses);

            // Crossover
            auto [child1, child2] = crossover(population[parent1Idx], population[parent2Idx]);

            // Mutation
            mutate(child1);
            mutate(child2);

            newPopulation.push_back(child1);
            if ((int)newPopulation.size() < POP_SIZE)
                newPopulation.push_back(child2);
        }

        population = newPopulation;
    }

    return 0;
}