# ntosta/genetic-tsp

Approximates solutions to the Traveling Salesman Problem (TSP) using a genetic algorithm.

## Genetic Simulation

The algorithm creates a random population of individuals; their genomes consist of an ordered list of points, which correspond to the x-y coordinates of the stops in the traveling salesman problem. The algorithm then randomly mutates the population and selects the most fit individuals. It discards the least fit individuals then repeats the process of mutation and selection for a specified number of iterations (generations).

The genetic algorithm's implementation can be found in src/ as main.cpp, tsp.cpp, and darwin.cpp.

## Visualization

Also included is an interactive visualization! This allows you to view the progress of algorithm by displaying the most-fit individual in the population for each generation. For more information see the README in visualization/.

## Todo

- Cleanup comments, whitespace, etc.
- Add necessary visual studio files to git repository
- Add 'crossover' or 'sexual' mutations to hopefully improve results and algorithm convergence

### Credits

The genetic algorithm was created by Nick Tosta, August 2015.
The visualization was created by Nick Tosta and Brandon Duffany, August 2015.