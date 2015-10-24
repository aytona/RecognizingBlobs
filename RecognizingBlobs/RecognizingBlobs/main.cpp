#include "BitArray.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

/* Generates a grid, where each pixel belongs to a blob based on a random num gen in the range 1 to 100:
if the random number is less than the percentage, the pixel belongs to some blob;
otherwise the pixel does not belong to the blob. */
BitArray genGrid(unsigned int rows, unsigned int cols, unsigned int percentage)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int randomNum = rand() % 100 + 1;
			if (randomNum > percentage)
				return 1;
			else
				return 0;
		}
	}
}

/* Produces a string representation of the grid in a form. */
string gridView(BitArray &grid, unsigned int rows, unsigned int cols)
{

}

/* grid is the representation of the image, and visited keeps track of the fact if your counting
function has ever visited a particular element of the grid. */
int blobCount(BitArray &grid, BitArray visited, unsigned int rows, unsigned int cols)
{

}

/* where row, col is the particular pixel that is being visited at this time. */
void markBlob(BitArray &grid, BitArray &visited, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col)
{

}

int main()
{
	unsigned seed;
	cout << "Enter seed: ";
	cin >> seed;
	srand(seed);		// TODO: Always have current seed # show.

	unsigned int rows, cols, percentage;
	cout << "Number of Rows: ";
	cin >> rows;
	cout << "Number of Columns: ";
	cin >> cols;
	cout << "Percentage of blob: ";
	cin >> percentage;
	genGrid(rows, cols, percentage);

	/* prompt user for the number of rows and columns for the grid.
	Also the percent of the blos.
	Then generate a grid, count the blobs, and show the grid and the count.*/
	return 0;
}