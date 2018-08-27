# Ionic

Some code that deals with what looks to be a confusion matrix.  The program finds
regions of points in the matrix that are adjacent which meet a threshold value.
Finally the program computes the center point of each of the regions discovered.
The regions, the points in the region, and the calculated center point in the region
are printed to the console.

```
Region 1 Center {1,1}
Region 1 points
	{1,1} = 210
Region 2 Center {2,4}
Region 2 points
	{1,4} = 230
	{1,5} = 220
	{2,4} = 245
	{2,3} = 250
	{3,3} = 250
Region 3 Center {5,5}
Region 3 points
	{4,5} = 250
	{5,5} = 250
```

This program was originally written on a Mac.  To build

`make ionictest`

To run

`./ionictest`

# Test

To test all input boundary conditions need to be identified.

## Threshold input
- 0
- negative
- max int

## Matrix input
- one point
- max int points
- one row
- one column

## Point Signals input
- no points above threshold
- all points above threshold
- all points equal threshold
- one point equal to max value
- one point equal to max value + 1

All combinations of the above three categories need to be tested.