# Nick Tosta
# Based on code by Brandon Duffany
# August 2015

# Parses the genetic algorithm's output data 
# Creates a web server with Flask and injects the data as JSON into the index.html file

import os
import json

from flask import Flask
from flask import Markup
from flask import render_template


app = Flask(__name__)


DATA_DIR = 'data'


def _parse_genome_line(line):
    genome_list = line.split(" ")
    return {
      "generation": int(genome_list[0]),
      "fitness": float(genome_list[1]),
      "indices": list(map(int, genome_list[2:])),
    }


def get_input_data():
    #Get the filenames for all of the algorithm data output files
    filenames = os.listdir(DATA_DIR)
    data = [] #list to store dictionaries containing the data from each file

    for fname in filenames:
        with open(os.path.join(DATA_DIR, fname)) as f:
            lines = map(lambda s: s.strip(), f.read().splitlines())

        #The data files concatenate 3 different kinds of data:
        #the points in the TSP, a selection of genomes, and the best fitness value from each generation
        #The start of each kind of data is denoted by a keyword
        points_index = lines.index("points")
        genomes_index = lines.index("genomes")
        fitnesses_index = lines.index("fitnesses")

        point_lines = lines[points_index+1:genomes_index]
        genome_lines = lines[genomes_index+1:fitnesses_index]
        fitnesses = lines[fitnesses_index+1:]

        point_dicts = [dict(zip(["x", "y"], map(int, line.split(" ")))) for line in point_lines]

        genome_dicts = [_parse_genome_line(line) for line in genome_lines]

        data.append({
            "name": fname,
            "points": point_dicts,
            "genomes": genome_dicts,
            "fitnesses": fitnesses,
        })

    return data


@app.route('/')
def index():
    return render_template('index.html', data=Markup(json.dumps(get_input_data())))


if __name__ == "__main__":
    app.run(port=9001, debug=True, threaded=True)
