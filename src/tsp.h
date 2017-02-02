// Nick Tosta
// August 2015

// tsp.h
// contains the definition for the TSP class
// TSP maintains data structures related to the traveling salesman problem
// and provides an interface for the genetic algorithm to "ask questions" about the genes/points

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef TSP_H_
#define TSP_H_

class TSP {

	//Store the x and y coordinates of the points
	vector<float> x_;
	vector<float> y_;
	int num_points_;

	//String to store the path and filename of the file of (x, y) points
	string filename_;

	//Store the distances between all of the points as an adjacency matrix
	vector< vector<float> > distances_;


public:

	//Constructor that takes the filename as an argument
	TSP(string filename);

	//Read the x and y coordinates of the points from a specified file
	void read_points(string filename);

	//Populate the distances matrix
	void calculate_distances();

	//Return the length of a tour specified by the order of the points
	float get_tour_length(const vector<int> &tour);

	//Simple getter for the number of points in the problem
	int get_num_points();

	//Check if the line segments between two pairs of points (pA-pB and pC-pD) intersect
	bool check_intersection(int pA, int pB, int pC, int pD);

	
	//Utility functions

	//Return the points as a formatted string so that it can be output
	string get_points_as_string();

};

#endif