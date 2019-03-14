#pragma once
#include "interface.h"

int Core::find_arg(int argc, char *argv[], arg &w, arg &c, arg &h, arg &t, arg &r, char &head, char &tail) {
	w.exist = false;
	c.exist = false;
	h.exist = false;
	t.exist = false;
	r.exist = false;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-w") == 0) {
			w.exist = true;
			w.index = i;
		}
		if (strcmp(argv[i], "-c") == 0) {
			c.exist = true;
			c.index = i;
		}
		if (strcmp(argv[i], "-h") == 0) {
			h.exist = true;
			h.index = i;
		}
		if (strcmp(argv[i], "-t") == 0) {
			t.exist = true;
			t.index = i;
		}
		if (strcmp(argv[i], "-r") == 0) {
			r.exist = true;
			r.index = i;
		}
	}
	if (!w.exist && !c.exist) {
		return 4;
	}
	if (w.exist && c.exist) {
		return 1;
	}
	if (h.exist) {
		if (h.index == argc - 1) {
			return 2;
		}
		string str_head = argv[h.index + 1];
		char char_head = str_head.at(0);
		if (str_head.length() != 1) {
			return 2;
		}
		if (!((char_head >= 'a' && char_head <= 'z') || (char_head >= 'A' && char_head <= 'Z'))) {
			return 2;
		}
		head = char_head;
	}
	else {
		head = char(0);
	}
	if (t.exist) {
		if (t.index == argc - 1) {
			return 3;
		}
		string str_tail = argv[t.index + 1];
		char char_tail = str_tail.at(0);
		if (str_tail.length() != 1) {
			return 3;
		}
		if (!((char_tail >= 'a' && char_tail <= 'z') || (char_tail >= 'A' && char_tail <= 'Z'))) {
			return 3;
		}
		tail = char_tail;
	}
	else {
		tail = char(0);
	}
	return 0;
}

void Core::check_same() {
	bool valid = true;
	for (int i = 0; i < core_words.size() - 1; i++) {
		for (int j = i + 1; j < core_words.size(); j++) {
			if (core_words[i] == core_words[j]) {
				valid = false;
			}
		}
	}
	try {
		if (!valid) {
			throw 0;
		}
	}
	catch (...) {
		cout << "Error : 输入的单词列表中有重复的单词" << endl;
	}
}


int Core::read_word(char *word) {
	char c;
	if (fin.eof()) {
		return EOF;
	}
	do {
		fin >> c;
		if (fin.eof()) {
			return EOF;
		}
	} while (!isalpha(c));
	do {
		*word++ = c;
		fin >> c;
		c = tolower(c);
		if (fin.eof()) {
			return EOF;
		}
	} while (isalpha(c));
	*word = '\0';
	return 1;
}

vector<string> Core::read_words(char *words[]) {
	char word[50];
	vector<string> str_wordlist;
	int i = 0;
	while (read_word(word) != EOF) {
		string str_word = word;
		str_wordlist.push_back(str_word);
		words[i] = (char *)malloc(sizeof(char) * 50);		//每个单词限50字符
		strcpy_s(words[i], 50, str_word.c_str());
		i++;
	}
	cout << endl;
	check_void(int(str_wordlist.size()));
	return str_wordlist;
}

int Core::read_word_str(char *word, int &loc, string wordstring) {
	char c;
	if (wordstring[loc] == '\0' || loc >= 50) {					//读到结尾
		return 0;
	}
	do {
		c = wordstring[loc++];
		if (c == '\0' || loc >= 50) {					//读到结尾
			return 0;
		}
	} while (!isalpha(c));
	do {
		c = tolower(c);
		*word++ = c;
		c = wordstring[loc++];
		if (wordstring[loc + 2] == '\0' || loc + 2 >= 50) {					//读到结尾
			break;
		}
	} while (isalpha(c));
	*word = '\0';
	return 1;
}

vector<string> Core::read_words_str(string wordstring, char *words[]) {
	char word[50];
	int loc = 0;
	vector<string> str_wordlist;
	int i = 0;
	while (read_word_str(word, loc, wordstring) != 0) {
		string str_word = word;
		str_wordlist.push_back(str_word);
		words[i] = (char *)malloc(sizeof(char) * 50);		//每个单词限50字符
		strcpy_s(words[i], 50, str_word.c_str());
		i++;
	}
	check_void(int(str_wordlist.size()));
	return str_wordlist;
}
