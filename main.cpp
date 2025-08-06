#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

vector<string> split(const string& line);

class Interpreter {
	bool in_loop;

public:
	Interpreter() {
		this->in_loop = false;
	}

	void interpret(const vector<string>& line, unordered_map<string, int>& varsInt) {
		if (line.size() == 0) return;
		else if (line[0] == "//") return;
		else if (line[0] == "print") {
			if (line[line.size()-1] == ";") {
				cout << varsInt[line[1]];
				return;
			}
			for (int i = 1; i < line.size(); i++) {
				cout << line[i];
				if (i == line.size()-1) {
					continue;
				} else {
					cout << " ";
				}
			}
			cout << "\n";
			return;
		} else if (line[0] == "int" && line[2] == ":=") {
			varsInt[line[1]] = stoi(line[3]);
			return;
		}
	}
};

vector<string> split(const string& line) {
	vector<string> res;
	string word;
	for (char c : line) {
		if (c == ' ') {
			res.push_back(word);
			word = "";
			continue;
		}
		word += c;
	}

	if (!word.empty()) {
		res.push_back(word);
	}
	return res;
}

int main() {
	string filename; // This is the .ff file name.
	cin >> filename;
	unordered_map<string, int> varsInt = {};
	ifstream File(filename);
	string line;
	Interpreter interpreter;
	while (getline(File, line)) {
		vector<string> l = split(line);
		interpreter.interpret(l, varsInt);
	}

	return 0;
	
}
