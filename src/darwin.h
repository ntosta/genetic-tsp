// Nick Tosta
// August 2015

// darwin.h
// contains the definitions for the darwin class and the individual struct
// Darwin is responsible for running the genetic simulation and maintaining the data structure for the population

#include <string>
#include <vector>

#include "tsp.h"

using namespace std;

#ifndef DARWIN_H_
#define DARWIN_H_

struct Individual {
	vector<int> genome;
	float fitness;
	int generation;
};

class Darwin {

	int num_genes_; // Total number of genes per genome
	int population_size_; // Population size, or total number of genomes per generation
	int num_passed_genomes_; // Number of genomes to be passed on to the next generation
	int num_generations_;
	int current_generation_;
	int max_mutations_ = 3;

	// Store a pointer to a traveling salesman problem instance
	TSP* tsp_;

	// Store the current generation's genomes
	vector<Individual> population_;

	// Store a subset of individuals for output/visualization
	vector<Individual> individual_store_;
	// Store all of the best fitness values for output/visualization
	vector<float> fitness_store_;

public:
	Darwin(TSP* tsp, int population_size, int num_passed_genomes, int num_generations);

	// Setters
	void set_TSP(TSP*);
	void set_num_genes(int num_genes);
	void set_population_size(int population_size);
	void set_num_passed_genomes(int num_passed_genomes);
	void set_num_generations(int num_generations);

	// Simulation functions
	void create_random_population();
	void run_simulation();
	void calculate_fitness();
	void sort_population();

	void mutate_genomes();
	Individual swap_mutation(const Individual &ind);
	Individual insert_mutation(const Individual &ind);
	Individual sequence_mutation(const Individual &ind);
	Individual cross_mutation(const Individual &ind);

	// Utility functions
	void print_population();
	void print_fitnesses(int amount = -1);

	void output_genomes(string outdir);
};

#endif