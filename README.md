# FenwickTree
A new method of range update and range query using fenwick tree
While traversing the tree, it utilizes the distance of the current node to the starting node to calculate sums or update values.

I wrote the code for these a few years ago when I had less knowledge about C++, but i plan to go over them again and maybe fix some mistakes.
The struct in MD_fenwick_tree allow you to make a fenwick tree with any number of dimentions still supporting range update and range query.
How ever if you wanted it to be faster you would want to implement it the same way just not in a template way and without recursive functions for the for loops.
The code in main tests the 1D, 2D and 3D versions of the fenwick tree with random numbers and it turns out be running with good results, but I haven't tested it with higher number of dimentions.

The code will seem pretty confusing but I will try to write how it works soon, but the main idea is to keep track of the distance from the first node when traversing the trees and using that in the calculations.

Thanks.
