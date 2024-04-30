# Warsaw Bus Puntuality Analysis

This is a set of modules that analyzes the positioins of the buses in Warsaw and compares it to the timetable, deriving conclusions about their punctuality.

## gather_data.sh ##
A bash script that periodically runs gather_data.py - a script that gets data regarding buses positions from API and saves them as a JSON with name given as an argument

## parse_timetable.py ##
A script that parses the timetable given in TXT file into JSON timetables for particular bus lines

## handle_bus_data.py ##
A module with functions that handle raw data from API to give real routes of buses in a particular time interval

## delay_graph.py ##
A program that generates a graph showing delays of the buses depending on hour

## delay_growth_heatmap.py ##

