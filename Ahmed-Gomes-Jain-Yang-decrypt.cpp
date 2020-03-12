#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

//prototyping
void readFileFromStream(ifstream& stream, vector<int>& text1, vector<int>& text2, vector<int>& text3, vector<int>& text4, vector<int>& text5);
vector<int> diff(vector<int>& ciphertext, vector<int>& plaintext);
bool ptnCheck(vector<int>& difference);

int main() {
	cout << "Enter Ciphertext" << endl;
	string s, word;
	getline(cin, s);
	//cout << s << endl;
	cout << "My plaintext guess is:" << endl;
	vector<int> text1, text2, text3, text4, text5;
	vector<vector<int>> vectorPlaintexts;
	vector<int> cipherText;
	vector<int> asciiDiff;


	//getting the ascii value of the char of the string @ i
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			cipherText.push_back(96);
		}
		else
		{
			cipherText.push_back(int(s[i]));
		}
	}
	//

	//puting the first 49 characters into a vector
	//because idk why we gotta use a map if were not counting occurances
	ifstream ifs("plaintext_dictionary_test1.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	readFileFromStream(ifs, text1, text2, text3, text4, text5);

	vectorPlaintexts.push_back(text1);
	vectorPlaintexts.push_back(text2);
	vectorPlaintexts.push_back(text3);
	vectorPlaintexts.push_back(text4);
	vectorPlaintexts.push_back(text5);
	/*for (size_t i = 0; i < text2.size(); i++) {
		cout << text2[i] << " ";
	}
	cout << endl;*/




	int crtPlt;
	//function to find the difference
	for (int i = 0; i < 5; i++) {
		//vectorPlaintexts[i];
		asciiDiff = diff(cipherText, vectorPlaintexts[i]);
	/*	for (size_t x = 0; x < asciiDiff.size(); x++) {
			cout << asciiDiff[x] << " ";
		}
		cout << endl;*/


		if (ptnCheck(asciiDiff)) {

			crtPlt = i;
			//cout << i << endl;
			ifstream ifs("plaintext_dictionary_test1.txt");
			if (!ifs) {
				cerr << "Could not open the file.\n";
				exit(1);
			}
			ifs >> word >> word;
			char plaintextNum;
			while(ifs >> plaintextNum) {
				//cout << plaintextNum << endl;
				//cout << char(i + 48);
				if (plaintextNum == char(i+ 49)) {
					//cout << char(i);
					ifs >> word;
					while (ifs >> word && word != "Candidate") {
						cout << word << " ";
					}
				}
			}
			cout << endl;
			ifs.close();
			break;
		}
		//cout << "hii" << i << endl;
		//break if we find a pattern
	}

	//if (crtPlt == 1) {
	//	cout << "Candidate plaintext 1" << endl;
	//}




}

void readFileFromStream(ifstream& stream, vector<int>& text1, vector<int>& text2, vector<int>& text3, vector<int>& text4, vector<int>& text5) {
	char word, moreWords;
	string w;
	string plt;
	int num;
	stream >> w >> w;
	while (stream >> word) {
		if (word == '1') {
			stream >> word;
			//cout << word << endl;
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
				if (moreWords == ' ') {
					text1.push_back(int(96));
				}
				else
					text1.push_back(int(moreWords));
			}
		}
		else if (word == '2') {
			stream >> word;
			//cout << word << endl;
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
				//cout << moreWords << " ";
				if (moreWords == ' ') {
					text2.push_back(int(96));
				}
				else
					text2.push_back(int(moreWords));
			}
		}
		else if (word == '3') {
			stream >> word;
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
				if (moreWords == ' ') {
					text3.push_back(int(96));
				}
				else
					text3.push_back(int(moreWords));
			}
		}
		else if (word == '4') {
			stream >> word;
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
				if (moreWords == ' ') {
					text4.push_back(int(96));
				}
				else
					text4.push_back(int(moreWords));
			}
		}
		else if (word == '5') {
			stream >> word;
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
				if (moreWords == ' ') {
					text5.push_back(int(96));
				}
				else
					text5.push_back(int(moreWords));
			}
		}
	}
	stream.seekg(0);
	stream.close();

}

vector<int> diff(vector<int>& ciphertext, vector<int>& plaintext) {
	vector<int> asciiDiff2;
	for (size_t i = 0; i < plaintext.size(); i++) {
		if ((ciphertext[i] - plaintext[i]) < 0) {
			int num = (ciphertext[i] - plaintext[i]);
			asciiDiff2.push_back(27 + num);
		}
		else {
			asciiDiff2.push_back(ciphertext[i] - plaintext[i]);
		}
	}
	return asciiDiff2;
}


bool ptnCheck(vector<int>& difference) {
	int curr = 0;
	bool inCycle = false;
	//if within 24, then repeat exists in correct plaintext
	//cout << difference.size() << endl;
	while (curr <= 24) {
		int start = 0;
		curr++;
		int beginCycle = curr;
		//cout << curr << " " << start << endl;
		while (difference[curr] == difference[start] && curr < 47) {
			//cout << curr << " " << start << endl;
			inCycle = true;
			curr++;
			start++;
			if (difference[curr] != difference[start]) {
				curr = 47;
				inCycle = false;
			}
		}
		//cout << curr << " " << start << endl;
		//if still true, we hit 48 and still in cycle so break
		if (inCycle) {
			break;
		}
		else {
			curr = beginCycle;
		}
	}
	//cout << "Incycle: " << inCycle << endl;
	return inCycle;
}

