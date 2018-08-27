# Ionic

Some code that deals with what looks to be a confusion matrix.  The program finds
regions of point in the matrix that are adjacent which meet a threshold value.
Finally the program computers the center point of each of the regions discovered.
The regions, the points in the region and the calculated center point in the region
are printed to the console.

This program was originally written on a Mac.  To build

'make ionictest'

To run

'./ionictest'

# Test

To test all input boundary conditions need to be identified.

## Threshold input
- set to 0
- negative
- max int
- max int + 1

## Matrix input
- one point
- max int points
- one row
- one column

## Point Signals input
- no points above threshold
- all points above threshold
- all points equal threshold
- all points equal max value

All combinations of the above three categories need to be tested.