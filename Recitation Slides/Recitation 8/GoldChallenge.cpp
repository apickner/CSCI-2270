#include <iostream>
#include <string>
#include <map>

using namespace std;


char commonChar(std::string input) {
	std::map<char,int> charMap;
	for (auto c : input) {
		charMap[c]++;
//		cout<<charMap[c]<<endl;
	}
	int max = 0;
	char char1 = 'a';
	for (auto c : input) {
		if (charMap[c] > max) {
			max = charMap[c];
			char1 = c;
		}
	}
	return char1;
}

int main(int argc, char *argv[]) {
	
	cout<<commonChar("bbcccdddAAaaefghia")<<endl;
	
	return 0;
	
}