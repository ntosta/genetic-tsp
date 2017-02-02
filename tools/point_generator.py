from math import sqrt, pow
import random
from random import randint
import os

MIN_DISTANCE = 20

def generate_points_list(num_points = 20):

	outfile = open(os.path.join("../input", "points" + str(num_points) + ".txt"), 'w')
	points = []

	i = 0
	while (i < num_points):

		x = randint(10, 590)
		y = randint(10, 590)
		flag = False

		for point in points:
			if (sqrt(pow(x-point[0], 2) + pow(y-point[1], 2)) < MIN_DISTANCE):
				flag = True
				break
		
		if (flag == False):
			outfile.write(str(x) + " " + str(y) + "\n")
			points.append([x, y])
			i += 1


	outfile.close()



if __name__ == "__main__":

	random.seed()

	print("Generating points...")

	generate_points_list(90)
	#for numPoints in range(10, 70, 10):
#		generate_points_list(numPoints)

	print("Finished")