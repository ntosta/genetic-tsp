// Nick Tosta
// August 2015

// tsp.cpp
// contains the implementation for functions related to the traveling salesman problem

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "tsp.h"

using namespace std;

// Constructor that automatically reads the points from the file
// And automatically populates the distances array
TSP::TSP(string filename) : filename_(filename) {
	read_points(filename_);
	calculate_distances();
}

// Read the points from a file, store them in the x and y vectors
void TSP::read_points(string filename) {

	ifstream file(filename);
	string line, xVal, yVal;

	cout << "Reading points from: " << filename << endl;

	while (getline(file, line)) {
		xVal = line.substr(0, line.find_first_of(" "));
		yVal = line.substr(line.find_first_of(" "), line.length());
		x_.push_back(stof(xVal));
		y_.push_back(stof(yVal));
	}

	num_points_ = x_.size();

	if (num_points_ > 0) {
		cout << num_points_ << " points read successfully" << endl;
	}
	else {
		cout << "Error - no points were read. Ensure the points file exists in the specified path" << endl
			 << "Press any key to exit" << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}

	file.close();
}

// Calculate the distance from every point to every other point
// Store the distances in the distances matrix
void TSP::calculate_distances() {

	// Fill the distances matrix with "0"s
	for (int i = 0; i < num_points_; i++) {
		vector<float> row;
		for (int j = 0; j < num_points_; j++) {
			row.push_back(0);
		}
		distances_.push_back(row);
	}

	// For every set of points, calculate the distance
	// This just uses the standard distance formula sqrt((x1-x2)^2 + (y1-y2)^2)
	for (int i = 0; i < num_points_; i++) {
		for (int j = i + 1; j < num_points_; j++) {
			float distance = sqrt(pow(x_[i]-x_[j], 2) + pow(y_[i]-y_[j], 2));
			distances_[i][j] = distance;
			distances_[j][i] = distance;
		}
	}
}

// Return the length of a tour
float TSP::get_tour_length(const vector<int> &tour) {

	float distance = 0;

	for (int i = 0; i < num_points_-1; i++) {
		distance += distances_[tour[i]][tour[i + 1]];
	}

	distance += distances_[tour.back()][tour[0]];

	return distance;
}

// Generic getter for the number of points in the problem
int TSP::get_num_points() {
	return num_points_;
}

// Checks for an intersection between two line segments pA-pB and pC-pD
// This function works by computing the cross product and checking to see if
// each pair of points is on opposite sides of the other segment. This works
// because the segments intersect if and only if:
// ((A and B are on different sides of [CD]) and (C and D are on different sides of [AB])),
// which is checked using the XORs in the return statement.
bool TSP::check_intersection(int pA, int pB, int pC, int pD) {
	int cpC = (x_[pB] - x_[pA]) * (y_[pC] - y_[pB]) - (y_[pB] - y_[pA]) * (x_[pC] - x_[pB]);
	int cpD = (x_[pB] - x_[pA]) * (y_[pD] - y_[pB]) - (y_[pB] - y_[pA]) * (x_[pD] - x_[pB]);

	int cpA = (x_[pD] - x_[pC]) * (y_[pA] - y_[pD]) - (y_[pD] - y_[pC]) * (x_[pA] - x_[pD]);
	int cpB = (x_[pD] - x_[pC]) * (y_[pB] - y_[pD]) - (y_[pD] - y_[pC]) * (x_[pB] - x_[pD]);

	return ((cpA ^ cpB) < 0) && ((cpC ^ cpD) < 0);
}

// Returns the points in the TSP as a pre-formatted string so that it can be written directly
// to an output file
string TSP::get_points_as_string() {
	string pointString;

	for (int i = 0; i < num_points_; i++) {
		pointString += to_string((int)x_[i]);
		pointString += " ";
		pointString += to_string((int)y_[i]);
		pointString += "\n";
	}

	return pointString;
}