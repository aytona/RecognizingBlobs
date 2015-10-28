#include "BitArray.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

/* Create a function called genGrid with the following signature:
BitArray genGrid(unsigned int rows, unsigned int cols, unsigned int percentage)
that generates a grid, where each pixel belongs to a blob based on a random
number generated in the range 1 to 100: if the random number is less than the
percentage, the pixel belongs to some blob (that is you set the corresponding
bit to 1); otherwise the pixel does not belong to the blob (that is you set the
corresponding bit to 0). */
BitArray genGrid(unsigned int rows, unsigned int cols, unsigned int percentage);

/* Create a function gridView with the following signature:
string gridView(BitArray &grid, unsigned int rows, unsigned int cols)
that produces a string representation of the grid in a form similar to that shown
on the image above. */
string gridView(BitArray &grid, unsigned int rows, unsigned int cols);

/* In order to count the blobs, you will create a function with the
following signature: int blobCount(BitArray &grid, BitArray visited,
unsigned int rows, unsigned int cols)
where grid is the representation of the image, and visited keeps track of the
fact if your counting function has ever visited a particular element of the grid.
Note if you mark a pixel as visited, you want to check the neighbor pixels and
mark them as well if they belong to the same blob. */
int blobCount(BitArray &grid, BitArray visited, unsigned int rows, unsigned int cols);

/* The marking of pixels belonging to blobs must be done using a
recursive function with the following signature:
void markBlob(BitArray &grid, BitArray &visited, unsinged int rows,
unsigned int cols,unsigned int row, unsigned int col)
where row, col is the particular pixel that is being visited at this time. */
void markBlob(BitArray &grid, BitArray &visited, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col);

/* Your main() program must prompt the user for the number of
rows and number of columns of a grid, and also for the percentage of the blobs,
and then generate a grid, count the blobs, and show the grid and the count */
int main() {
	unsigned seed;
	cout << "Enter seed: ";
	cin >> seed;
	srand(seed);

	unsigned int rows, cols, percentage;
	cout << "Number of Rows: ";
	cin >> rows;
	cout << "Number of Columns: ";
	cin >> cols;
	cout << "Percentage of blob: ";
	cin >> percentage;

	BitArray visited(rows*cols);
	visited.ClearAllBits();
	cout << gridView(genGrid(rows, cols, percentage), rows, cols);
	cout << "There are " << blobCount(genGrid(rows, cols, percentage), visited, rows, cols) << " blob(s) in the grid" << endl;
	system("pause");
	return 0;
}

BitArray genGrid(unsigned int rows, unsigned int cols, unsigned int percentage) {
	BitArray grid(rows*cols);
	grid.ClearAllBits();
	unsigned int i = 0;
	while (i < rows*cols) {
		unsigned int randomNum = rand() % 100 + 1;
		if (randomNum < percentage)
			grid.SetBit(i);
		i++;
	}
	return grid;
}

string gridView(BitArray &grid, unsigned int rows, unsigned int cols) {
	string gridString;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			unsigned int loc = j + i * rows;
			if (grid[loc])
				gridString += "x";
			else
				gridString += "-";
		}
		gridString += "\n";
	}
	return gridString;
}

int blobCount(BitArray &grid, BitArray visited, unsigned int rows, unsigned int cols) {
	int count = 0;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			unsigned int current = j + i * rows;
			if (grid[current] && !visited[current]) {
				count++;
				markBlob(grid, visited, rows, cols, i, j);
			}
		}
	}
	return count;
}

void markBlob(BitArray &grid, BitArray &visited, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col) {
	unsigned int current = col + row * rows;
	if ((current + 1 < rows * cols) && (current + cols < rows * cols)) {
		if (grid[current] && !visited[current]) {
			visited.SetBit(current);
			if (grid[current + 1] && !visited[current + 1]) {
				visited.SetBit(current + 1);
				markBlob(grid, visited, rows, cols, row++, col);
			}
			if (grid[current + cols] && !visited[current + cols]) {
				visited.SetBit(current + cols);
				markBlob(grid, visited, rows, cols, row, col++);
			}
		}
	}
	return;
}