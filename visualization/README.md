# Visualization

To view the visualization run ``server.bat`` then open [`localhost:9001`](http://localhost:9001/) in a web browser (preferably Chrome).

Note that the visualization has only been tested on Chrome versions above v44, although it should work on most modern browsers.

## Server

The visualization depends on a simple Python (Flask) server which reads the output files from the genetic algorithm and parses them into a json data structure. This data structure is then injected into index.html.

Any output files must be added to the ``data/`` folder in order to be read by the server. Several sample output files are available in the ``data/`` folder so that you can run the visualization without needing to build and run the genetic algorithm itself.

## Visualization

The implementation of the visualization itself is found in ``templates/index.html``. It uses the D3.js library to render the points and traveling salesman route as an SVG.