#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

void readFileFromStream(ifstream& stream, vector<int>& text1, vector<int>& text2, vector<int>& text3, vector<int>& text4, vector<int>& text5);
vector<int> diff(vector<int>& ciphertext, vector<int>& plaintext);
bool ptnCheck(vector<int>& difference);
vector<int> keyExists(vector<int>& difference);
void encode(vector<int>& v, string word);
void diffCombos(const string str[], string prefix, const int n, const int len, vector<vector<int>>& ret);
string decrypt(vector<int>& cipher, vector<int>& shifts, string words[]);
bool correctCipher(string& answer, string str[]);

int main() {
	cout << "Enter Ciphertext" << endl;
	string s, word;
	getline(cin, s);
	cout << "My plaintext guess is:" << endl;

	vector<int> text1, text2, text3, text4, text5;
	vector<vector<int>> vectorPlaintexts;
	vector<int> cipherText;
	vector<int> asciiDiff;

	//getting the ascii value of the char of the string @ i
	for (size_t i = 0; i < s.size(); i++) {
		cipherText.push_back(int(s[i]));
		//Since the Ascii Value of ' ' is different than what we wanted
		//Each time there was a ' ' we just make it a 96
		if (s[i] == ' ') {
			cipherText.pop_back();
			cipherText.push_back(96);
		}
	}

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

	int crtPlt;
	//function to find the difference
	for (int i = 0; i < 5; i++) {
		asciiDiff = diff(cipherText, vectorPlaintexts[i]);

		if (ptnCheck(asciiDiff)) {
			crtPlt = i;
			ifstream ifs("plaintext_dictionary_test1.txt");
			if (!ifs) {
				cerr << "Could not open the file.\n";
				exit(1);
			}
			ifs >> word >> word;
			char plaintextNum;
			while (ifs >> plaintextNum) {
				if (plaintextNum == char(i + 49)) {
					ifs >> word;
					while (ifs >> word && word != "Candidate") {
						cout << word << " ";
					}
				}
			}
			cout << endl;
			ifs.close();
			exit(1);
		}

	}


	int len = 3;
	string str[] = { "unconvertible ", "intuitiveness ", "hermeneutics ", "photocompose ", "miserabilia ", "faultlessly ", "awesomeness ", "attentional ", "dismissive ", "delimiting "
					, "racecourse " , "directions " , "indelicacy " , "shorelines " , "combusting " , "successors " , "postilion " , "footfalls " , "pintsized " , "courtship "
					, "aloneness " , "hearkened " , "protruded " , "proposes " , "memphis " , "rustics " , "between " , "repress " , "matures " , "pressed "
					, "ferries " , "catcher " , "bursary " , "beheld " , "swoops " , "chuted " , "wobbly " , "myrtle " , "cadgy " , "irony " };

	int n = 40;
	vector<vector<int>> possCipher;
	diffCombos(str, "", n, len, possCipher);
	/*for (size_t index = 0; index < stuff.size(); index++) {
		for (size_t inner = 0; inner < stuff[index].size(); inner++) {
			cout << char(stuff[index][inner]);
		}
		cout << endl;
	}*/
	int count = 0;
	string answer;
	string a = "";
	bool found;
	for (size_t index = 0; index < possCipher.size(); index++) {
		if (possCipher[index].size() >= 24) {
			asciiDiff = diff(cipherText, possCipher[index]);
			//Need to shorten posscipher[index], and possibly ciphertext
			//might need to pass a size parameter on methods used to decrypt them
			vector<int> temp = keyExists(asciiDiff);
			if (temp.size() != 0) {
				//count++;
				//cout << "Found it" << endl;		
				//exit(1);
				/*for (size_t index = 0; index < temp.size(); index++) {
					cout << temp[index] << " ";
				}
				cout << endl;*/
				answer = decrypt(cipherText, temp, str);
				if(correctCipher(answer, str)){
					cout << answer << endl;
				}				
				//cout << answer << endl;
				/*for (size_t index = 0; index < answer.size(); index++){
					if (correctCipher(answer, index, str)) {
						cout << answer[index];
					}*/
			}
		}
	}
	//cout << count << endl;
	ifs.close();
	return 0;
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
			stream.get(moreWords);
			stream.get(moreWords);
			for (int i = 0; i < 48; i++) {
				stream.get(moreWords);
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

}

vector<int> diff(vector<int>& ciphertext, vector<int>& plaintext) {
	vector<int> asciiDiff2;
	for (size_t i = 0; i < plaintext.size(); i++) {
		if ((ciphertext[i] - plaintext[i]) < 0) {
			int num = (ciphertext[i] - plaintext[i]);
			asciiDiff2.push_back(27 + num);
		}
		else asciiDiff2.push_back(ciphertext[i] - plaintext[i]);
	}
	return asciiDiff2;
}


bool ptnCheck(vector<int>& difference) {
	int curr = 0;
	bool inCycle = false;
	while (curr <= 24) {
		int start = 0;
		curr++;
		int beginCycle = curr;
		while (difference[curr] == difference[start] && curr < 47) {
			inCycle = true;
			curr++;
			start++;
			if (difference[curr] != difference[start]) {
				curr = 47;
				inCycle = false;
			}
		}
		if (inCycle) {
			break;
		}
		else {
			curr = beginCycle;
		}
	}
	return inCycle;
}

//check if cycle exists within the range of what we have
//this is not enough to confirm the cycle, but enough to see if one is possible
vector<int> keyExists(vector<int>& difference) {
	vector<int> key;
	int curr = 0;
	bool inCycle = false;
	while (curr < 24) {
		int start = 0;
		curr++;
		int beginCycle = curr;
		while (curr < difference.size() - 1 && difference[curr] == difference[start]) {
			inCycle = true;
			curr++;
			start++;
			if (difference[curr] != difference[start]) {
				curr = difference.size() - 1; //break outta inner loop
				inCycle = false;
			}
		}
		if (inCycle) {
			curr = beginCycle; //set curr to where cycle started
			break;
		}
		else {
			//cout << curr << endl;
			curr = beginCycle;
		}
	}
	if (inCycle) {
		//curr is key length
		for (size_t i = 0; i < curr; i++) {
			key.push_back(difference[i]);
		}
	}
	return key;
}

//takes in vector<int> (v[index]) and a word to push into the vector<int>
void encode(vector<int>& v, string word) {
	int num_form;
	for (size_t i = 0; i < word.size(); i++) {
		num_form = int(word[i]);
		if (word[i] == ' ') {
			num_form = 96;
		}
		v.push_back(num_form);
	}
}


// The main recursive method to print all possible strings of length "len"
void diffCombos(const string str[], string prefix, const int n, const int len, vector<vector<int>>& ret) {
	if (len == 1) {
		for (int j = 0; j < n; j++) {
			//cout << prefix + str[j] << endl;
			string x = prefix + str[j];
			vector<int> v;
			encode(v, x);
			ret.push_back(v);
		}
	}//Base case: len = 1, print the string "leng" times + the remaining letter
	else {
		// One by one add all characters from "str" and recursively call for "lenght" equals to "lenght"-1
		for (int i = 0; i < n; i++)
			diffCombos(str, prefix + str[i], n, len - 1, ret);
	}

}

//uses possible shifts key to either confirm or deny it as the correct key
string decrypt(vector<int>& cipher, vector<int>& shifts, string words[]) {
	string holder = "";
	for (int index = 0; index < cipher.size(); index++) {
		if (cipher[index] - shifts[index % shifts.size()] < 97) {
			if ((char(cipher[index] + (27 - shifts[index % shifts.size()]))) == '{') {
				holder += " ";
			}
			else
				holder += char(cipher[index] + (27 - shifts[index % shifts.size()]));
		}
		else {
			if ((char(cipher[index] - shifts[index % shifts.size()])) == '{') {
				holder += " ";
			}
			else
				holder += char(cipher[index] - shifts[index % shifts.size()]);
		}
	}
	return holder;
}

//answer - possible correct strings ,
bool correctCipher(string& answer, string str[]) {
	bool found = true;
	string word = "";
	//we loop through words of answer
	for(size_t i = 0; i < answer.size(); i++){
		if(answer[i] == ' '){
			word += answer[i];
			//cout << word << endl;
			if (find(str, str + 40, word) == (str + 40)) {
				//cout << "HELLO" << endl;
				found = false;
				break;//its noti a valid cipher
			}
			word = "";
		}
		else{
			word += answer[i];
		}
	}
	return found;
}
