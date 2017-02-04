# ntosta/genetic-tsp

Approximates solutions to the Traveling Salesman Problem (TSP) using a genetic algorithm.

## Genetic Simulation

The algorithm creates a random population of individuals; their genomes consist of an ordered list of points, which correspond to the x-y coordinates of the stops in the traveling salesman problem. The algorithm then randomly mutates the population and selects the most fit individuals. It discards the least fit individuals then repeats the process of mutation and selection for a specified number of iterations (generations).

The genetic algorithm's implementation can be found in ``src/`` as ``main.cpp``, ``tsp.cpp``, and ``darwin.cpp``.

## Environment and Building

The genetic simulation itself was created in Visual Studio C++ as a Win32 Console Application. The necessary Visual Studio project files can be found in ``genetic-tsp/``.

## Visualization

Also included is an interactive visualization! This allows you to view the progress of algorithm by displaying the most-fit individual in the population for each generation. For more information see the README in ``visualization/``.

## Todo

- Usability improvements (command-line input for simulation parameters)
- Performance improvements
- Fix filesystem/environment assumptions; maybe add GNU Makefiles and modify the code to be completely cross-platform.

Algorithm Ideas:
- Add 'crossover' or 'sexual' mutations to hopefully improve results and algorithm convergence
- Make num_passed_genomes_ vary
  - Pass a number of genomes within some percentage (like 10%) of the most fit individual
  - Pass fewer genomes as the number of generations increases

Longer-term ideas:
- Clustering of points to create sub-problems (to tackle large graphs)
- Mutate some number of genomes completely separately, then around when they begin to converge combine them with some sort of crossover or mate function and then continue normally (essentially create parallel sub-simulations)

### Credits

The genetic algorithm was created by Nick Tosta, August 2015.
The visualization was created by Nick Tosta and Brandon Duffany, August 2015.