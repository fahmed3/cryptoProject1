#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

//prototypes
void readFileFromStream(ifstream& stream, vector<int>& text1, vector<int>& text2, vector<int>& text3,
	vector<int>& text4, vector<int>& text5);
vector<int> diff(vector<int>& ciphertext, vector<int>& plaintext);
bool ptnCheck(vector<int>& difference);
vector<int> keyExists(vector<int>& difference);
void encode(vector<int>& v, string word);
void diffCombos(const string str[], string prefix, const int n, const int len, vector<vector<int>>& ret);
string decrypt(vector<int>& cipher, vector<int>& shifts, string words[]);
bool correctPlainText(string& answer, string str[]);

int main() {
	cout << "Enter Ciphertext" << endl;
	string s, word;
	getline(cin, s);
	cout << "My plaintext guess is:" << endl;

	vector<int> text1, text2, text3, text4, text5;
	vector<vector<int>> vectorPlaintexts;
	vector<int> cipherText;
	vector<int> asciiDiff;

	//pushing the ascii values of the inputed ciphertext into the vector cipherText
	for (size_t i = 0; i < s.size(); i++) {
		cipherText.push_back(int(s[i]));
		if (s[i] == ' ') {
			cipherText.pop_back();
			cipherText.push_back(96);
		}
	}

	//for test 1
	ifstream ifs("plaintext_dictionary_test1.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}

	//separating test1 plaintext into 5 different vectors
	//represented by their ASCII values
	readFileFromStream(ifs, text1, text2, text3, text4, text5);
	vectorPlaintexts.push_back(text1);
	vectorPlaintexts.push_back(text2);
	vectorPlaintexts.push_back(text3);
	vectorPlaintexts.push_back(text4);
	vectorPlaintexts.push_back(text5);

	//Loop used to see if the ciphertext was the ciphertext for
	//test one. if it is, it then attemps to output what ciphertext
	//it is
	int crtPlt;
	for (size_t i = 0; i < vectorPlaintexts.size(); i++) {
		//gets the ASCII difference between each plaintext and the ciphertext
		asciiDiff = diff(cipherText, vectorPlaintexts[i]);
		if (ptnCheck(asciiDiff)) { //if a pattern exists its Test One
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
			exit(1);
		}
	}
	ifs.close();


	//known words in the second dictionary, with a space at the end,
	//so they were hardcoded to save time. Ordered from the longest to smallest in 
	//character count
	string str[] = { "unconvertible ","intuitiveness ","hermeneutics ","photocompose ",
					"miserabilia ","faultlessly ","awesomeness ","attentional ",
					"dismissive ","delimiting ","racecourse " ,"directions ",
					"indelicacy ","shorelines " ,"combusting " ,"successors ",
					"postilion ","footfalls ","pintsized ","courtship ","aloneness ",
					"hearkened ","protruded ","proposes ","memphis ","rustics ",
					"between ","repress ","matures ","pressed ","ferries ",
					"catcher ","bursary ","beheld ","swoops ","chuted ","wobbly " ,
					"myrtle ","cadgy ", "irony " };

	int len = 3, n = 40; // 3 words per permuatation out of all the 40 words in the
						// second dictionary 

	vector<vector<int>> possCipher;
	diffCombos(str, "", n, len, possCipher);
	int count = 0;
	string answer;
	string a = "";
	bool found;
	for (size_t index = 0; index < possCipher.size(); index++) {
		//if the possible cipher has a size of 24 we can compare
		//and decrypt because the size of the key happens at least once
		if (possCipher[index].size() >= 24) {
			asciiDiff = diff(cipherText, possCipher[index]);
			//Need to shorten posscipher[index], and possibly ciphertext
			//might need to pass a size parameter on methods used to decrypt them
			vector<int> temp = keyExists(asciiDiff);
			if (temp.size() != 0) {
				answer = decrypt(cipherText, temp, str);
				if (correctPlainText(answer, str)) {
					cout << answer << endl;
					exit(1);
				}
			}
		}
		//if the size of the possible cipher is less than 24, one more word is inputed
		//to increase the chances that the full key exists in the subset of characters
		else {
			for (int i = 0; i < 40; i++) {
				vector<int> newWord = possCipher[index];
				encode(newWord, str[i]);
				asciiDiff = diff(cipherText, newWord);
				vector<int> temp = keyExists(asciiDiff);
				if (temp.size() != 0) {
					answer = decrypt(cipherText, temp, str);
					if (correctPlainText(answer, str)) {
						cout << answer << endl;
						exit(1);
					}
				}
			}
		}
	}
	//output if everything else fails
	cout << "PlainText Not found. Sorry Professor :(\n";
	return 0;
}

//function used to read from the file and place into a specific vector representing each plaintext in test 1
void readFileFromStream(ifstream& stream, vector<int>& text1, vector<int>& text2, vector<int>& text3, vector<int>& text4, vector<int>& text5) {
	void inputWordsFromStream(ifstream & ifs, vector<int> & push, char& moreWords, char& word);
	char word, moreWords;
	string w;
	string plt;
	int num;
	stream >> w >> w;
	while (stream >> word) {
		if (word == '1') {
			inputWordsFromStream(stream, text1, moreWords, word);
		}
		else if (word == '2') {
			inputWordsFromStream(stream, text2, moreWords, word);
		}
		else if (word == '3') {
			inputWordsFromStream(stream, text3, moreWords, word);
		}
		else if (word == '4') {
			inputWordsFromStream(stream, text4, moreWords, word);
		}
		else if (word == '5') {
			inputWordsFromStream(stream, text5, moreWords, word);
		}
	}

}
//used as a helper function for the readFileFromStream, to help input the words into a vector
void inputWordsFromStream(ifstream& ifs, vector<int>& push, char& moreWords, char& word) {
	ifs >> word;
	ifs.get(moreWords);
	ifs.get(moreWords);
	for (int i = 0; i < 48; i++) {
		ifs.get(moreWords);
		if (moreWords == ' ') {
			push.push_back(int(96));
		}
		else
			push.push_back(int(moreWords));
	}
}

//Function that takes in the vector representation of the cipher and plain texts
//and returns the a vector connainty the ascii diff between them.
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

//input: vector<int> that is all the shifts we found from diff
//loops through the shifts to check if there is a pattern
//if one does not begin within the first 24 ints,
// we return false since a pattern longer than 24 is not possible with a max key length of 24
//we return if we spot a pattern and it continues until the 48th character
// if it does, we confirmed our cycle
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
//converts string word into it's ascii value and pushes back into vector
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


// The main recursive method to print all possible strings of length 3
void diffCombos(const string str[], string prefix, const int n, const int len, vector<vector<int>>& ret) {
	if (len == 1) {
		for (int j = 0; j < n; j++) {
			string x = prefix + str[j];
			vector<int> v;
			//encodes the permutation to it's ASCII values and then
			//places it in the return (ret) vector
			encode(v, x);
			ret.push_back(v);
		}
	}
	else {
		for (int i = 0; i < n; i++)
			//recursive call to get all possible combinations of the string
			diffCombos(str, prefix + str[i], n, len - 1, ret);
	}

}

//uses possible shifts key to either confirm or deny it as the correct key
string decrypt(vector<int>& cipher, vector<int>& shifts, string words[]) {
	string holder = "";
	for (int index = 0; index < cipher.size(); index++) {
		//we are shifting it back, and when this is done sometimes it goes
		//past the character 'a' by 27 so the condition is needed to make sure the
		//proper shift can happen if it goes past 'a'
		if (cipher[index] - shifts[index % shifts.size()] < 97) {
			//the ' ' character appearead as the '}' so whenever the '{' character appears
			//when decrypting it is replaced with a ' '
			if ((char(cipher[index] + (27 - shifts[index % shifts.size()]))) == '{') {
				holder += " ";
			}
			else
				//decrypting a regular character
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

//answer - possible correct strings , str - array of 40 words
//loops through potential plaintext answer word by word
//checks if each word exists in our words array
bool correctPlainText(string& answer, string str[]) {
	bool found = true;
	string word = "";
	//we loop through words of answer
	for (size_t i = 0; i < answer.size(); i++) {
		if (answer[i] == ' ') {
			word += answer[i];
			if (find(str, str + 40, word) == (str + 40)) {
				found = false;
				break;//its noti a valid cipher
			}
			word = "";
		}
		else
			word += answer[i];
	}
	return found;
}
