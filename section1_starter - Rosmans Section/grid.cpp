/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "SimpleTest.h"
#include "grid.h"
#include "gridlocation.h"

using namespace std;


/**
 * @brief maxRowV1: Using a For Loop to Calculate Max of Row
 * @param grid: An indexed, two-dimensional array.
 * @param loc: A struct that contains a row and a col as integers.
 * @return
 */
int maxRowV1(Grid<int>& grid, GridLocation loc) {
    int maxRowValue = -1;
    int currRow = loc.row;
    // Iterate through the columns
    for (int col = 0; col < grid.numCols(); col++) {
        int currentValue = grid[currRow][col];
        // Update maxRowValue: We can Also use an if condition as well
        maxRowValue = max(maxRowValue, currentValue);
    }
    return maxRowValue;
}

/**
 * @brief maxRowV2: Similar to Version 1, but we're using the get method
 *          to obtain currentValue
 * @param grid: An indexed, two-dimensional array.
 * @param loc: A struct that contains a row and a col as integers.
 * @return
 */
int maxRowV2(Grid<int>& grid, GridLocation loc) {
    int maxRowValue = -1;
    int currRow = loc.row;
    for (int col = 0; col < grid.numCols(); col++) {
        int currentValue = grid.get(currRow, col);
        maxRowValue = max(maxRowValue, currentValue);
    }
    return maxRowValue;
}

/**
 * @brief maxRowV3: Similar to Version 1 and Version 2; however, we are using
 *          GridLocationRange.
 *          Per the Stanford Documentation: The range of locations extends
 *          from the corner at (StartRow, startCol) to the corner at
 *          (endRow, endCol) inclusive.
 * @param grid: An indexed, two-dimensional array.
 * @param loc: A struct that contains a row and a col as integers.
 * @return
 */
int maxRowV3(Grid<int>& grid, GridLocation loc) {
    int maxRowValue = -1;
    int startRow = loc.row;
    int startCol = 0;
    int endRow = loc.row;
    int endCol = grid.numCols() - 1;
    GridLocationRange range = GridLocationRange(startRow, startCol, endRow, endCol);
    // Iterate through range using for range loop
    for (GridLocation currLocation : range) {
        int currentValue = grid[currLocation]; // We can also use get()
        maxRowValue = max(maxRowValue, currentValue);

    }
    return maxRowValue;
}

/*
 * Max row (Code Write)
 * ----------------------------------
 * Write a function named maxRow that takes in a grid and an in
 * bounds gridLocation and returns a the maximum value in that
 * row of the grid.
 */

int maxRow(Grid<int>& grid, GridLocation loc) {
    return maxRowV3(grid, loc);
}



int avgNeighborhoodV1(Grid<int>& grid, GridLocation loc) {
    Vector<GridLocation> cardinalDirections = {
        {loc.row - 1, loc.col}, // North
        {loc.row + 1, loc.col}, // South
        {loc.row, loc.col + 1}, // East
        {loc.row, loc.col - 1} // West

    };
    int sum = 0; // This will serve as our numerator
    int validLocations = 0; // This will be our denominator (We can assume that there will be at least 1 valid location)

    // Iterate through the cardinalDirections using for range loop
    for (GridLocation current : cardinalDirections) {
        if (grid.inBounds(current)) {
            sum += grid[current]; // We can also use get()
            validLocations++;
        }

    }
    int average = sum / validLocations;
    return average;
}

/*
 * Avg neighborhood (Code Write)
 * ----------------------------------
 * Write a function named avgNeighborhood that takes in a grid and an in 
 * bounds gridLocation and returns the average value in the neighborhood
 * of the gridLocation. A neighborhood is defined as the in bounds 
 * locations in North, South, East and West of loc.
 */
int avgNeighborhood(Grid<int>& grid, GridLocation loc) {
    return avgNeighborhoodV1(grid, loc);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Test max row") {
    Grid<int> grid = {{0, 9, 1}, {1, 3, 0}, {2, 3, 1}};
    EXPECT_EQUAL(maxRow(grid, {2, 1}), 3);
    EXPECT_EQUAL(maxRow(grid, {0, 1}), 9);
}

PROVIDED_TEST("Test average neighborhood") {
    Grid<int> grid = {{0, 9, 1}, {1, 3, 0}, {2, 3, 1}};
    EXPECT_EQUAL(avgNeighborhood(grid, {0,0}), 5);
    // average is 3.33*, but we truncate to 3
    EXPECT_EQUAL(avgNeighborhood(grid, {1,1}), 3); 
}
