#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>

// ---------------------------------------------
// sets the char for Thanos and Iron Man

const char Thanos = '*';

const char IronMan = '#';

// ---------------------------------------------

using namespace std;

// prints the matrix in a nice format
void printMatrix(vector<vector<char> > matrix);

int findShortestPath(vector<vector<char> > matrix);

int main(int argc, char *argv[]) {
	// seeds the random spots where Thanos and Iron Man spawn in
	srand(clock());	

	// sets the size of the matrix
	int n = 4;
	// sets up the matrix vectors with empty spaces
	vector<vector<char> > matrix = vector<vector<char> >(n, vector<char>(n, ' '));
	
	// randomly pick a spot for Thanos
	// row
	int ThanosRandomRow = rand() % n;
	// column
	int ThanosRandomColumn = rand() % n;
	
	// randomly pick a spot for IronMan
	// row
	int IronManRandomRow = rand() % n;
	// column
	int IronManRandomColumn = rand() % n;

	// while Iron Man's spot is the same as Thano's spot, we need to pick a new spot for Iron Man
	while ((IronManRandomRow == ThanosRandomRow) && (IronManRandomColumn == ThanosRandomColumn)) {
		// randomly pick a spot for IronMan
		int IronManRandomRow = rand() % n;
		int IronManRandomColumn = rand() % n;
	}
	
	// sets the matrix spot for Thanos and then IronMan
	matrix[ThanosRandomRow][ThanosRandomColumn] = Thanos;
	matrix[IronManRandomRow][IronManRandomColumn] = IronMan;

	// prints the matrix so the user can check my function
	printMatrix(matrix);
	
	cout << endl << "Iron Man must move " << findShortestPath(matrix) << " spots!" << endl;
}	

// prints the matrix in a nice format
void printMatrix(vector<vector<char> > matrix) {
	int size = matrix.size();


	for (int i = 0; i < size; i++) {
		for (int a = 0; a < size; a++) {
			cout << "------";
		}
		cout << "-" << endl;
		
		
		for (int j = 0; j < size; j++) {
			if (j == 0) {
				cout << "|  " << matrix[i][j];
			}
			else {
				cout << "  |  " << matrix[i][j];
			}
			
			if (j == size - 1) {
				cout << "  |  ";
			}
		}
		cout << endl;
	}
	for (int a = 0; a < size; a++) {
		cout << "------";
	}
	cout << "-" << endl;
}

int findShortestPath(vector<vector<char> > matrix) {
	int totalNumSpaces = 0;
	
	int size = matrix.size();
	
	int IronManRow, IronManColumn, ThanosRow, ThanosColumn;
	IronManRow = IronManColumn = ThanosRow = ThanosColumn = 0;
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] == IronMan) {
				IronManRow = i;
				IronManColumn = j;
				break;
			}
			if (matrix[i][j] == Thanos) {
				ThanosRow = i;
				ThanosColumn = j;
				break;
			}
		}
	}
	if (ThanosColumn == IronManColumn) {
		if (IronManRow >= ThanosRow) {
			return IronManRow - ThanosRow;

		}
		return (ThanosRow - IronManRow) - 1;
	}
	if (ThanosRow == IronManRow) {
		if (IronManColumn >= ThanosColumn) {
			return IronManColumn- ThanosColumn;
		}
		return (ThanosColumn - IronManColumn) - 1; 
	}                                        
	else {
		int sum = 0;
		if (ThanosColumn > IronManColumn) {
			sum += (ThanosColumn - IronManColumn);
		}
		else {
			sum += (IronManColumn - ThanosColumn);
		}
		if (ThanosRow > IronManRow) {
			sum += (ThanosRow - IronManRow);
		}
		else {
			sum += (IronManRow - ThanosRow);
		}
		
		return sum - 1;
	}
}

