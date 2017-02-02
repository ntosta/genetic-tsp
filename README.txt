This program uses a genetic algorithm to approximate solutions to arbitrary instances of the traveling salesman problem (TSP). 
The algorithm creates a random population of individuals (each containing an ordered list of points representing the stops in the TSP) then randomly mutates the population. It selects the most fit individuals then repeats the process of mutation and selection for a specified number of iterations (generations).
As of October 2015 the algorithms are still a work in progress. Right now the only mutations are asexual and as a result the algorithm typically requires a few attempts to produce an optimal result. The next step is to implement crossover mutations which should hopefully reduce the number of generations needed to converge while improving fitness values.

The code can be found in /genetic_TSP/ as main.cpp, tsp.h, tsp.cpp, darwin.h, and darwin.cpp. 
I've included the entire visual studio project but all that's really needed to run the program is the executable in /Release/ and the input and output folders in /genetic_TSP/

Also included is an interactive visualization in /genetic_TSP/visualization. To view the visualization run server.bat then in a web browser (preferably Chrome) go to localhost:9001/


The genetic algorithm was created by Nick Tosta, August 2015. 

The visualization was created by Nick Tosta and Brandon Duffany, August 2015.