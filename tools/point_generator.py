import errno
from math import sqrt, pow
import random
from random import randint
import os

##### Point generation parameters
# Minimum geometric distance between points
# Points will not be generated that are within MIN_DISTANCE radius of other
# points.
# Note that large MIN_DISTANCE values can slow point generation significantly
# or prevent the script from generating a sufficient number of points, causing
# an infinite loop.
MIN_DISTANCE = 20

# Minimum and maximum point coordinate values. The visualization was built
# with a 600x600 grid of points in mind.
MIN_POINT_VAL = 10
MAX_POINT_VAL = 590

# Generates a list of points and writes them to an output file
def generate_points_list(outdir="../input", num_points=20):

	# Create the output directory if it doesn't exist
	try:
		os.makedirs(outdir)
	except OSError as exc:  # Python >2.5
		if exc.errno == errno.EEXIST and os.path.isdir(outdir):
			pass
		else:
			raise

	# Create the output file
	outfile = open(os.path.join(outdir, "points" + str(num_points) + ".txt"), 'w')

	points = []
	i = 0	# Number of generated points
	while (i < num_points):
		# Generate a random x-y pair
		x = randint(MIN_POINT_VAL, MAX_POINT_VAL)
		y = randint(MIN_POINT_VAL, MAX_POINT_VAL)

		# Check if the point is within MIN_DISTANCE of any existing points
		flag = False
		for point in points:
			if (sqrt(pow(x-point[0], 2) + pow(y-point[1], 2)) < MIN_DISTANCE):
				flag = True
				break

		# Write the point to the file and add the point to the list
		if (flag == False):
			outfile.write(str(x) + " " + str(y) + "\n")
			points.append([x, y])
			i += 1

	outfile.close()
	print("Created input points file: " + outdir + "/points" + str(num_points) + ".txt")


if __name__ == "__main__":

	random.seed()

	print("Generating points...")

	generate_points_list(num_points=50)

	#for numPoints in range(10, 70, 10):
	#	generate_points_list(num_points=numPoints)