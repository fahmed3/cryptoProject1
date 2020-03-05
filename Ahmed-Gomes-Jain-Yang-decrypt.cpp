#include <iostream>
#include <stdlib.h>
#include <map>
#include<string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	cout << "Enter the ciphertext:" << endl;
	string s, word;
	getline(cin, s);
	cout << "My plaintext guess is:" << endl;

	map<char, int >encrypted;
	map<char, int >::iterator itr;
	for (int i = 0; i < s.length(); i++)
		encrypted[s[i]]++;

	// The for loop below is for testing purposes only to see if it counts all letters correctly
	for (itr = encrypted.begin(); itr != encrypted.end(); itr++)
		cout << itr->first << " : " << itr->second << "; ";

	ifstream ifs("plaintext_dictionary_test1.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}

	while (ifs >> word) {
		//cout << word << " ";
		if (word == "1") {
			map<char, int >text1;
			
		}

	}
}
