# TDAAProject
This repository contains implementation of various heuristics for the Bounded Degree Minimum Spanning Tree (bMST) problem, which is to find a spanning tree of a given graph with minimum weight such that the maximum degree of any vertex of the output tree is less than a given value b, as a part of our project for the CS6100: Topics in Design and Analysis of Algorithms, Spring 2021 course. This project was implemented by Arjun Bharat (CS17B006), C Shriram (CS18B007), Pragyan Chakraborty (CS18B038) and Sarthak Kapoor (CS18B066).

As a part of this project, we have implemented a greedy modification of an [additional degree 1 approximation algorithm](https://drive.google.com/drive/u/1/folders/1NMQ4ei-7zAPwo7sph7Xp1hZhsFxP0jU5) to produce a bMST. We have also modified Kruskal's and Prim's standard algorithm by adding heuristcs for bMST.

## Directory Structure

- The **code** folder contains all the header files, corresponding implementations and test script used to run the three heuristics.
- The **datasets** folder contains all the datatsets that were used to evaluate the code and generate results.
- The **Results.md** file contains the results of evaluation of the different algorithms on different datasets in tabular format.

## Running the Code
 
Simply running
```
bash test_script.sh
```
in the code folder creates the required outputs.
