// Nick Tosta
// August 2015

// main.cpp
// creates a TSP and Darwin object then runs the genetic algorithm and outputs results

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <time.h>

#include "tsp.h"
#include "darwin.h"

using namespace std;

int main() {
	// For randomizing the population and the genetic mutations
	srand(time(NULL));

	// Initialize TSP object
	TSP tsp = TSP("input/points40.txt");

	// Initialize Darwin object
	Darwin darwin = Darwin(&tsp, 100, 10, 1000);

	// Get current time (for timing how long it takes the simulation to run)
	chrono::time_point<std::chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	// Run the simulation
	cout << "Running simulation..." << endl;
	darwin.run_simulation();

	// Get the end time and calculate how long the simulation ran for
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	// Print the top fitness values and output the results of the simulation
	// to a file
	darwin.print_fitnesses(10);
	darwin.output_genomes();

	cout << "Simulation duration: " << elapsed_seconds.count() << endl;
	cout << endl << "Program end" << endl;

	cin.get();
	return 0;
}