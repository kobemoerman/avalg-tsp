# KTH DD2440 TSP 

Implementation of the Chritofides algorithm for an approximation solution for the 2D TSP problem for the course advanced algorithms at KTH (P2/2021).

* Kobe Moerman
* Paul Moosbrugger
* Frederick van der Windt
* Nikolai Tobias Limbrunner

## Build

```bash 
make
```

## Run

```bash 
./tsp < data/1.in
```

## Analysis 

In the order scripts are scripts to create new input data for testing. Also in the main.cpp the value KATTIS can be set to false. Then the current costs are written to a file which can be plotted and analyzed with the script plot_costs.py.