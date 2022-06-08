#include <iostream>
#include <string>
using namespace std;

int getHash(string word);

int main(int argc, char *argv[]) {
	int x = getHash("word");

	cout<<x<<endl;

	return 0;

}


int getHash(string word) {
		int hash = 5381;
		int hashTableSize = 100000;
		for (auto c : word) {
			hash = (hash * 33) + c;
		}
		hash = hash % hashTableSize;
		if (hash < 0)
				hash += hashTableSize;
		return hash;
	}
