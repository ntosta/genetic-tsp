// Nick Tosta
// August 2015

// darwin.cpp
// contains the implementation for the genetic algorithm

#include <algorithm>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>

#include "Darwin.h"

using namespace std;

// Constructor
// Arguments (4):
//  Pointer to an already-initialized TSP object (points have been read, distance matrix calculated)
//  Integer value to set the population size for the simulation
//  Integer value to set the number of genomes that pass from generation to generation
//  Integer value to set the number of generations for the simulation
Darwin::Darwin(TSP* tsp, int population_size, int num_passed_genomes, int num_generations) {
	set_TSP(tsp);
	set_population_size(population_size);
	set_num_passed_genomes(num_passed_genomes);
	set_num_generations(num_generations);

	max_mutations_ = num_genes_ / 10 + 3;
}

// Initialize the entire population to have completely random genomes
void Darwin::create_random_population() {

	// Create a new individual until we've filled the population
	for (int i = 0; i < population_size_; i++) {

		vector<int> new_sequence = {};
		Individual newInd;
		newInd.fitness = -1;
		newInd.generation = 0;

		// Add genes
		for (int j = 0; j < num_genes_; j++) {
			new_sequence.push_back(j);
		}
		// Randomize the order of the genes
		random_shuffle(new_sequence.begin(), new_sequence.end());

		newInd.genome = new_sequence;

		// Add the new individual to the population
		population_.push_back(newInd);
	}

	current_generation_ = 0;
}

// Setters for the simulation parameters
void Darwin::set_TSP(TSP* tsp) {
	tsp_ = tsp;
	set_num_genes(tsp->get_num_points());
}

void Darwin::set_num_genes(int num_genes) {
	num_genes_ = num_genes;
}

void Darwin::set_population_size(int population_size) {
	population_size_ = population_size;
}

void Darwin::set_num_passed_genomes(int num_passed_genomes) {
	num_passed_genomes_ = num_passed_genomes;
}

void Darwin::set_num_generations(int num_generations) {
	num_generations_ = num_generations;
}

// Calculate the fitness for the entire population
void Darwin::calculate_fitness() {
	// Iterate over all of the individuals in the population
	for (int i = 0; i < population_size_; i++) {
		// Use the tsp object to calculate the fitness then store it with the genome
		population_[i].fitness = tsp_->get_tour_length(population_[i].genome);
	}
}

// Sort the population by fitness value
void Darwin::sort_population() {
	// This uses the std::sort function and supplies a lambda function so that it knows to compare the fitness values
	// "I" < "J" so that it will sort from least to greatest
	sort(population_.begin(), population_.end(), [](Individual &i, Individual &j){return i.fitness < j.fitness; });
}

// Run the genetic algorithm
void Darwin::run_simulation() {

	create_random_population();
	calculate_fitness();
	sort_population();
	current_generation_++;

	while (current_generation_ < num_generations_) {
		mutate_genomes();
		calculate_fitness();
		sort_population();

		// Store the most fit individual for later analysis/output
		if (current_generation_ == population_[0].generation) {
		// if (current_generation_ % (num_generations_ / 50) == 0) {
			Individual mostfit;
			mostfit.fitness = population_[0].fitness;
			mostfit.generation = current_generation_;
			mostfit.genome = population_[0].genome;
			individual_store_.push_back(mostfit);
		}
		// Store the value of the most fit individual
		fitness_store_.push_back(population_[0].fitness);

		// Simulated annealing of maximum mutations
		max_mutations_ = -4 / num_generations_ * current_generation_ + 5;

		// Print out the current generation
		// Used for tracking how long a simulation is running for
		// Note: this can significantly slow down program execution, best to leave it disabled for small runs
		/*if (current_generation_ % 10 == 0) {
		 	cout << "\r" << "Current Generation: " << current_generation_;
		}*/

		current_generation_++;
	}
}

// Discard the least fit genomes, then mutate the best fit genomes until the population has been rebuilt
// Randomly decides which mutations to apply to each genome
void Darwin::mutate_genomes() {

	int gi = 0; // index of genome to be passed on to next generation
	int pi = num_passed_genomes_; // index of individual in the population that we're replacing

	// Iterate over the population and replace all of the least-fit individuals
	//   with new individuals based on the most-fit genomes
	while (pi < population_size_) {

		int random = rand() % 1000;

		if (random < 650) {
			population_[pi] = swap_mutation(population_[gi]);
		}
		else if (random < 700) {
			population_[pi] = insert_mutation(population_[gi]);
		}
		else if (random > 990) {
			population_[pi] = cross_mutation(population_[gi]);
		}
		else {
			population_[pi] = sequence_mutation(population_[gi]);
		}

		gi++;
		if (gi >= num_passed_genomes_) { gi = 0; }
		pi++;
	}
}

// Swaps the positions of two genes in the genome
// Can perform up to max_mutations_ number of swaps
Individual Darwin::swap_mutation(const Individual &ind) {
	Individual newInd;
	newInd.genome = ind.genome;
	newInd.fitness = -1;
	newInd.generation = current_generation_;

	int mutations = (rand() % max_mutations_) + 1;

	for (int i = 0; i < mutations; i++) {
		int rand1 = rand() % num_genes_;
		int rand2 = rand() % num_genes_;
		if (rand1 == rand2) {
			rand2++;
			if (rand2 == num_genes_) { rand2 = 0; }
		}
		swap(newInd.genome[rand1], newInd.genome[rand2]);
	}

	return newInd;
}

// Moves a single gene to a different part of the genome
Individual Darwin::insert_mutation(const Individual &ind) {
	Individual newInd;
	newInd.fitness = -1;
	newInd.generation = current_generation_;

	// int mutations = (rand() % max_mutations_) + 1;
	int mutations = 1;

	for (int i = 0; i < mutations; i++) {
		int gene = rand() % num_genes_;
		int location = rand() % num_genes_;

		int j = 0;
		while (newInd.genome.size() < location) {
			if (ind.genome[j] != gene) {
				newInd.genome.push_back(ind.genome[j]);
			}
			j++;
		}
		newInd.genome.push_back(gene);
		while (newInd.genome.size() < num_genes_) {
			if (ind.genome[j] != gene) {
				newInd.genome.push_back(ind.genome[j]);
			}
			j++;
		}
	}
	return newInd;
}

// Moves a sequence of several genes to a different part of the genome
Individual Darwin::sequence_mutation(const Individual &ind) {
	Individual newInd;
	// vector<int> newGenome = {};
	// newInd.genome = newGenome;
	newInd.fitness = -1;
	newInd.generation = current_generation_;

	// Create valid random numners
	int start = 0, length = 0, new_start = 0;
	while (start == new_start || new_start > (num_genes_ - length)) { // Make sure the random numbers are valid
		start = rand() % (num_genes_ - 1);
		length = rand() % (num_genes_ - start - 1) + 1;
		new_start = rand() % num_genes_;
	}

	// Create a temporary vector containing all of the numbers NOT in the sequence to be moved
	vector<int> temp = {};
	for (int i = 0; i < start; i++) {
		temp.push_back(ind.genome[i]);
	}
	for (int i = start + length; i < num_genes_; i++) {
		temp.push_back(ind.genome[i]);
	}

	// Fill the new vector with the numbers not in the sequence, then the sequence, then the rest of the numbers not in the sequence
	for (int i = 0; i < new_start; i++) {
		newInd.genome.push_back(temp[i]);
	}
	for (int i = 0; i < length; i++) {
		newInd.genome.push_back(ind.genome[start + i]);
	}
	for (int i = new_start; i < temp.size(); i++) {
		newInd.genome.push_back(temp[i]);
	}

	return newInd;
}

// Looks for edges that cross (a suboptimal configuration)
// and then randomly swaps the edges to eliminate the cross
Individual Darwin::cross_mutation(const Individual &ind) {
	for (int i = 0; i < num_genes_ - 2; i++) {
		for (int j = i + 2; j < num_genes_; j++) { // i + 2 because adjacent edges cannot intersect
			if (tsp_->check_intersection(i, i + 1, j, j + 1)) {
				Individual newInd;
				newInd.genome = ind.genome;
				newInd.fitness = -1;
				newInd.generation = current_generation_;
				int randbit = rand() % 2;
				swap(newInd.genome[i + randbit], newInd.genome[j + 1 - randbit]);
				return newInd;
			}
		}
		// Check the edge from the last gene to the first
		if (tsp_->check_intersection(i, i + 1, num_genes_ - 1, 0)) {
			Individual newInd;
			newInd.genome = ind.genome;
			newInd.fitness = -1;
			newInd.generation = current_generation_;
			if (rand() % 2 == 0) {
				swap(newInd.genome[i], newInd.genome[0]);
			}
			else {
				swap(newInd.genome[i+1], newInd.genome.back());
			}
			return newInd;
		}
	}

	// If there aren't any intersections we can just default to a swap mutation instead
	return swap_mutation(ind);
}

// Print the population to cout (includes both fitnesses and the genomes)
void Darwin::print_population() {
	cout << "Printing current population (generation: " << current_generation_ << ")" << endl;
	for (int i = 0; i < population_size_; i++) {
		cout << "F: " << population_[i].fitness << " -- P: {";
		for (int j = 0; j < num_genes_; j++) {
			cout << population_[i].genome[j] << ",";
		}
		cout << "}" << endl;
	}
	cout << endl;
}

// Print the top fitness values to cout
// Arguments (1, optional):
//  Amount: number of fitness values to print
void Darwin::print_fitnesses(int amount) {
	if (amount == -1) {
		amount = population_size_;
	}

	cout << "Printing top " << amount << " fitness values for generation " << current_generation_ << endl;
	for (int i = 0; i < amount; i++) {
		cout << population_[i].fitness << endl;
	}

	cout << endl;
}

// Output the results of the genetic algorithm to an output file
// Arguments (1):
//  outdir: a string containing the directory to output the file to
void Darwin::output_genomes(string outdir) {

	// Check that the outdir exists, if not create it
	namespace fs = std::tr2::sys;
	fs::path outpath = outdir;
	if (!fs::exists(outpath)) {
		fs::create_directory(outpath);
	}

	// Generate a filename based on the current date/time
	time_t t = time(0);
	struct tm * now = localtime(&t);
	ostringstream ss;
	ss << "out_" << num_genes_ << "_" << put_time(now, "%y-%m-%d_%H-%M-%S") << ".txt";
	string outfile_name(ss.str());

	// Create the output file
	ofstream outfile(outdir + outfile_name);
	cout << "Writing output data to: " << outfile_name << " in " << outdir << endl;

	// Write the points to the output file
	outfile << "points\n"; //  spacer for parsing the data
	outfile << tsp_->get_points_as_string();

	// Write the genomes to the output file
	outfile << "genomes\n";
	for (int i = 0; i < individual_store_.size(); i++) {

		outfile << to_string(individual_store_[i].generation) << " ";
		outfile << to_string(individual_store_[i].fitness) << " ";
		for (int j = 0; j < num_genes_ - 1; j++) {
			outfile << to_string(individual_store_[i].genome[j]) << " ";
		}
		outfile << to_string(individual_store_[i].genome.back()) << "\n";
	}

	// Write the fitnesses for all of the generations to the file
	outfile << "fitnesses\n";
	for (int i = 0; i < num_generations_ - 1; i++) {
		outfile << fitness_store_[i] << "\n";
	}
	outfile << fitness_store_.back();

	outfile.close();
}