#include <iostream>
#include <fstream>

using namespace std;

void resize(int **arrayPtr, int *capacity)
{
	// Implement the resizing logic here
	int size = *capacity;
	*capacity *= 2;

	int* newPtr = new int[*capacity];

	for (int i = 0; i < size; i++) {
		// line casuing troubles
		newPtr[i] = (*arrayPtr)[i];
	}

	delete [] *arrayPtr;

	*arrayPtr = newPtr;
}

int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		return -1;
	}

	string filename = argv[1];
	ifstream data;
	data.open(filename.c_str());

	int capacity = 10;
	int *arrayPtr;

	// Dynamically allocate space here for the array
	arrayPtr = new int[capacity];
	int numOfElement = 0;
	string temp;

	if(data.is_open())
	{
		cout<<"file is open"<<endl;
		while(getline(data, temp))
		{
			int toBeInsert = stoi(temp);
			if(numOfElement == capacity)
			{
				// Implement this function
				resize(&arrayPtr, &capacity);
				cout<<capacity<<endl;
			}
			arrayPtr[numOfElement] = toBeInsert;
			numOfElement++;
		}
		data.close();
	}

	for(int i = 0; i < numOfElement; i++)
	{
		cout << "Num: " << arrayPtr[i] << endl;
	}

	return 0;
}
