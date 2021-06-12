# TDAAProject
In this project, we implement various heuristics for the Bounded Degree Minimum Spanning Tree (bMST) problem which is to find a spanning tree of a given graph with minimum weight such that the maximum degree of any vertex of the output tree is less than a given value b.

We implement the additional degree 1 approximation algorithm mentioned in [this](https://drive.google.com/drive/u/1/folders/1NMQ4ei-7zAPwo7sph7Xp1hZhsFxP0jU5) paper and modify it to work on weighted graphs and have a heuristic for bMST.

We also modify Kruskal's and Prim's algorithm to get heuristcs for bMST.

## Directory Structure

- The **code** folder contains all the header files, corresponding implementations and test script used to run the three heuristics.
- The **datasets** folder contains all the datatsets that were used to evaluate the code and generate results.
- The **Results.md** file contains the results for different datasets in tabular format.


## Running the Code
 
Simply running
```
bash test_script.sh
```
in the code folder creates the required outputs.
