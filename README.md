Here's a detailed `README.md` for your Genetic Algorithm project, ideal for a GitHub repository:

---

# Genetic Algorithm in C++

This project is a simple and educational implementation of a **Genetic Algorithm (GA)** written in C++. It uses binary-encoded chromosomes to evolve solutions for maximizing the function:

$$
f(x) = x^2
$$

Where $x$ is an integer in the range \[0, 31], represented using a 5-bit binary string.

---

## Features

* Binary encoding (5 bits → values 0 to 31)
* Roulette wheel selection
* Single-point crossover
* Bit-flip mutation
* Elitism (optional enhancement)
* Console output showing progress by generation

---

## How It Works

### Objective

The GA evolves a population of binary strings to find the integer $x$ that **maximizes $f(x) = x^2$**.

---

### Components

#### 1. **Chromosome Representation**

* Each chromosome is a vector of 5 binary digits (0 or 1), e.g., `[1, 0, 0, 1, 1]`
* This binary string is converted to an integer using:

```cpp
int binaryToInt(const vector<int>& chromosome);
```

---

#### 2. **Fitness Function**

* The fitness of a chromosome is computed as:

```cpp
int fitness(const vector<int>& chromosome) {
    int x = binaryToInt(chromosome);
    return x * x;
}
```

---

#### 3. **Initial Population**

* A population of `POP_SIZE` random chromosomes is generated.

```cpp
vector<int> randomChromosome();
```

---

#### 4. **Selection: Roulette Wheel**

* Individuals are selected probabilistically based on fitness.
* Higher fitness → higher probability of selection.

```cpp
int selectParent(const vector<vector<int>>& population, const vector<int>& fitnesses);
```

---

#### 5. **Crossover: Single-point**

* A random point is chosen, and children swap tails:

```cpp
pair<vector<int>, vector<int>> crossover(const vector<int>& parent1, const vector<int>& parent2);
```

Example:

```
Parent1: 110|01
Parent2: 011|10
Children: 11010, 01101
```

---

#### 6. **Mutation**

* Each bit has a small chance (`MUTATION_RATE`) of flipping.

```cpp
void mutate(vector<int>& chromosome);
```

---

#### 7. **Evolution Loop**

* The population evolves for `MAX_GENERATIONS`.
* In each generation:

  * Fitnesses are computed
  * Best solution is logged
  * A new population is generated through selection, crossover, and mutation

---

## Output Example

```bash
Gen 0 Best Fitness: 841 (x = 29)
Gen 1 Best Fitness: 961 (x = 31)
...
Gen 19 Best Fitness: 961 (x = 31)
```

---

## File Structure

```
genetic_algorithm/
├── genetic_algorithm.cpp       # All the code lives here
├── README.md                   # This file
```

---

## How to Run

### Prerequisites

* A C++ compiler (e.g., `g++`)
* C++11 or later

### Compile and Run

```bash
g++ -o ga main.cpp
./ga
```

---

## Experiment Parameters

You can tweak the following constants in the code:

```cpp
const int POP_SIZE = 6;           // Population size
const int CHROMOSOME_LENGTH = 5;  // 5 bits to represent 0–31
const int MAX_GENERATIONS = 20;
const double MUTATION_RATE = 0.1;
```

---

## Possible Extensions

* Add **elitism** to preserve the best solution each generation
* Try **tournament selection**
* Implement **multi-point crossover**
* Use **real-valued chromosomes** for continuous problems
* Change the **fitness function** (e.g., `x * sin(x)`)

---

## Educational Value

This project is ideal for:

* Understanding the mechanics of genetic algorithms
* Learning how evolutionary processes optimize solutions
* Experimenting with genetic operators and evolutionary dynamics

---

## License

This project is open-source and free to use under the [MIT License](LICENSE).

---

## Author

Daryl Narh
Feel free to reach out for contributions or questions!

---
