#include "BitArray.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
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
	//unsigned seed;
	//cout << "Enter seed: ";
	//cin >> seed;
	//srand(seed);
	srand(time(NULL));

	unsigned int rows, cols, percentage;
	cout << "Number of Rows: ";
	cin >> rows;
	cout << "Number of Columns: ";
	cin >> cols;
	cout << "Percentage of blob: ";
	cin >> percentage;

	BitArray grid(genGrid(rows, cols, percentage));
	BitArray visited(rows * cols);
	string gridString = gridView(grid, rows, cols);
	int count = blobCount(grid, visited, rows, cols);

	cout << endl << gridString << endl;
	cout << "There are " << count << " blob(s) in the grid" << endl;
	system("pause");
	return 0;
}

BitArray genGrid(unsigned int rows, unsigned int cols, unsigned int percentage) {
	unsigned int size = rows*cols;
	BitArray grid(size);
	for (unsigned int i = 0; i < size; i++) {
		unsigned int randomNum = rand() % 100 + 1;
		if (randomNum < percentage) {
			grid.SetBit(i);
		}
	}
	return grid;
}

string gridView(BitArray &grid, unsigned int rows, unsigned int cols) {
	string gridString;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			if (grid[j + (i * cols)]) {
				gridString += "x";
			} else {
				gridString += "-";
			}
		}
		gridString += "\n";
	}
	return gridString;
}

int blobCount(BitArray &grid, BitArray visited, unsigned int rows, unsigned int cols) {
	int count = 0;
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j) {
			if (grid[j + (i * cols)] && !visited[j + (i * cols)]) {
				count++;
				markBlob(grid, visited, rows, cols, i, j);
			}
		}
	}
	return count;
}

void markBlob(BitArray &grid, BitArray &visited, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col) {
	unsigned int current = col + (row * cols);
	unsigned int left = current - 1;
	unsigned int right = current + 1;
	unsigned int bottom = current + cols;
	unsigned int top = current - cols;
	unsigned int size = rows * cols;
	if (grid[current]) {
		visited.SetBit(current);
		if (row + 1 < rows && bottom < size) {
			if (!visited[bottom] && grid[bottom]) {
				markBlob(grid, visited, rows, cols, row + 1, col);
			}
		}
		if (row - 1 > 0 && top < size) {
			if (!visited[top] && grid[top]) {
				markBlob(grid, visited, rows, cols, row - 1, col);
			}
		}
		if (col - 1 > 0 && left < size) {
			if (!visited[left] && grid[left]) {
				markBlob(grid, visited, rows, cols, row, col - 1);
			}
		}
		if (col + 1 < cols && right < size) {
			if (!visited[right] && grid[right]) {
				markBlob(grid, visited, rows, cols, row, col + 1);
			}
		}
	}
}