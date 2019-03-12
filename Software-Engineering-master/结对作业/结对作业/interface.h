#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
typedef struct {
	string word;
	char start;
	char end;
	int length;
}vertex;
typedef struct{
	string word;
	int index;
}node;
ifstream fin;
ofstream fout;
vector<vertex>* wordlist = new vector<vertex>();     //没有重复的顶点集
int map[10000][10000] = {0};
bool validinput = true;									//输入是否有效
//vector<string>* wordmap[26][26];
/*void initmap() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			wordmap[i][j] = new vector<string>();
		}
	}
	return;
}*/
int read_word(char *word) {
	char c;
	if (fin.eof()) {
		return EOF;
	}
	do {
		fin >> c;
		c = tolower(c);
	} while (!isalpha(c) && !fin.eof());
	if (fin.eof()) {
		return EOF;
	}
	do {
		*word++ = c;
		fin >> c;
		c = tolower(c);
	} while (isalpha(c) && !fin.eof());
	*word = '\0';
	return 1;
}

vector<string> read_words() {
	char word[50];
	//initmap();
	vector<string> str_wordlist;
	vector<string>::iterator str_loc;
	vector<vertex>::iterator loc;                            //获得一个迭代器
	while (read_word(word) != EOF) {
		cout << word << endl;
		string str_word = word;
		/*char startc = str_word.at(0);
		char endc = str_word.at(str_word.length() - 1);*/
		//vertex ver = { str_word, startc, endc, str_word.length() };//单词作为顶点
		
		str_loc = find(str_wordlist.begin(), str_wordlist.end(), str_word);
		if (str_loc != str_wordlist.end()) {									//找到重复
			cout << "找到重复：" << str_word << endl;
			continue;
		}
		else {																		//没有重复
			str_wordlist.push_back(str_word);
		}
	}
	/*str_loc = str_wordlist.begin();
	while (str_loc != str_wordlist.end()) {
		string str = *str_loc;
		cout << str << endl;
		wordlist->push_back({ str, str.at(0), str.at(str.length() - 1), int(str.length()) });
		str_loc++;
	}
	loc = wordlist->begin();
	while (loc != wordlist->end()) {
		cout << "word:" << (loc->word) << "	start:" << (loc->start) << "	end:" << (loc->end) << "	length:" << (loc->length) << endl;
		loc++;
	}*/
	for (unsigned int i = 0; i < str_wordlist.size(); i++) {
		cout << str_wordlist[i] << ":" << i << " ";
	}
	cout << endl;
	return str_wordlist;
}

void print_wordlist(vector<node> beginword, vector<node> endword) {
	vector<node>::iterator i;
	cout << "Begin Nodes : " << endl;
	for (i = beginword.begin(); i != beginword.end(); i++) {
		node n = *i;
		cout << n.word << " " << n.index << endl;
	}
	cout << "End Nodes : " << endl;
	for (i = endword.begin(); i != endword.end(); i++) {
		node n = *i;
		cout << n.word << " " << n.index << endl;
	}
	return;
}

/*int generate_map(vector<vertex> *wordlist,int len) {                   //生成图
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if ((*wordlist)[i].end == (*wordlist)[j].start) {					//首尾相接，存在一条边
				map[i][j] = 1;
				cout << "from:" << (*wordlist)[i].word << " to:" << (*wordlist)[j].word << endl;
			}
		}
	}
	return 1;
	//vector<vector<int> >vv(len, vector<int>(len));              //创建len*len的矩阵
}*/

/*
* p是当前单词
* num是单词总数
* 无头无尾、有头无尾
*/
/*void dfs_begin(node p, int *distance, int *visited, string *preword, vector<node> *beginchar, vector<node> *endchar, vector<node> beginword, bool enable_loop) {
	if (!validinput) {
		return;
	}
	visited[p.index] += 1;
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (beginchar[end].size() != 0) {
		vector<node>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			node n = *item;
			if (!visited[n.index]) {				//若未访问过，则递归访问
				if (distance[p.index] + 1 > distance[n.index]) {
					distance[n.index] = distance[p.index] + 1;									//更新距离
					preword[n.index] = p.word;													//更新路径
					dfs_begin(n, distance, visited, preword, beginchar, endchar, beginword, enable_loop);
				}		
			}
			else {
				if (!enable_loop) {									//输入有环，错误
					validinput = false;
					break;
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}*/

/*
* 无头有尾
*/
/*void dfs_end(node p, int *distance, int *visited, string *preword, vector<node> *beginchar, vector<node> *endchar, vector<node> endword, bool enable_loop) {
	if (!validinput) {
		return;
	}
	visited[p.index] += 1;
	int begin = p.word.at(0) - 'a';
	if (endchar[begin].size() != 0) {
		vector<node>::iterator item;
		for (item = endchar[begin].begin(); item != endchar[begin].end(); item++) {
			node n = *item;
			if (!visited[n.index]) {
				if (distance[p.index] + 1 > distance[n.index]) {
					distance[n.index] = distance[p.index] + 1;
					preword[n.index] = p.word;
					dfs_end(n, distance, visited, preword, beginchar, endchar, endword, enable_loop);
				}	
			}
			else {
				if (!enable_loop) {
					validinput = false;
					break;
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}*/

/*
* 有头有尾
*/
void dfs_both(node p, int *distance, int *visited, int *preword, vector<node> *beginchar, vector<node> *endchar, vector<node> beginword, vector<node> endword, bool enable_loop) {
	if (!validinput) {
		return;
	}
	vector<node>::iterator prev;
	bool find = false;
	for (prev = endword.begin(); prev != endword.end(); prev++) {
		if (p.index == (*prev).index) {
			find = true;
			break;
		}
	}
	if (find) {													//是结尾词
		return;
	}
	visited[p.index] += 1;
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (beginchar[end].size() != 0) {
		vector<node>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			node n = *item;
			if (!visited[n.index]) {
				if (distance[p.index] + 1 > distance[n.index]) {
					distance[n.index] = distance[p.index] + 1;
					preword[n.index] = p.index;
					dfs_both(n, distance, visited, preword, beginchar, endchar, beginword, endword, enable_loop);
				}
			}
			else {
				if (!enable_loop) {
					validinput = false;
					break;
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {	//这里默认words没有重复
	int visited[10005] = { 0 };								//单词访问记录表
	int distance[10005] = { 0 };							//距离开始位置的距离表
	int preword[10005];									//最长路径前一单词
	vector<node> beginchar[26];								//以a-z开头的单词(和endchar一同保存图)
	vector<node> endchar[26];								//以a-z结尾的单词
	vector<node> beginword;									//开始集
	vector<node> endword;									//结束集
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i });
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i });
		//wordlist->push_back({ str, str.at(0), str.at(str.length() - 1), int(str.length()) });
	}
	if (!enable_loop) {															//获取可以作为开始的点和可以作为结束的点
		if (head == '0' && tail == '0') {
			searchmethod = 0;
			for (int i = 0; i < 26; i++) {
				vector<node>::iterator item;
				if (endchar[i].size() == 0 && beginchar[i].size() != 0) {			//没有以其为结尾的单词，但有以其为开头的单词
					item = beginchar[i].begin();			//把所有以其为开始的单词加入开始集
					while (item != beginchar[i].end()) {
						node n = *item;
						beginword.push_back(n);
						item++;
					}
				}
				else if (beginchar[i].size() == 0 && endchar[i].size() != 0) {		//没有以其为开头的单词，但有以其为结尾的单词
					item = endchar[i].begin();				//把所有以其为结束的单词加入结束集
					while (item != endchar[i].end()) {
						node n = *item;
						endword.push_back(n);
						item++;
					}
				}
			}//end for
		}
		else if (head >= 'a' && head <= 'z' && tail == '0') {
			searchmethod = 1;
			int loc = head - 'a';
			vector<node>::iterator item;
			item = beginchar[loc].begin();								//创建开始集
			while (item != beginchar[loc].end()) {
				node n = *item;
				beginword.push_back(n);
				item++;
			}
			for (int i = 0; i < 26; i++) {								//创建结束集
				if (beginchar[i].size() == 0 && endchar[i].size() != 0) {
					item = endchar[i].begin();
					while (item != endchar[i].end()) {
						node n = *item;
						endword.push_back(n);
						item++;
					}
				}
			}//end for
		}
		else if (head == '0' && tail >= 'a' && tail <= 'z') {
			searchmethod = 2;
			int loc = tail - 'a';
			vector<node>::iterator item;								//创建结束集
			item = endchar[loc].begin();
			while (item != endchar[loc].end()) {
				node n = *item;
				endword.push_back(n);
				item++;
			}
			for (int i = 0; i < 26; i++) {								//创建开始集
				if (endchar[i].size() == 0 && beginchar[i].size() != 0) {
					item = beginchar[i].begin();
					while (item != beginchar[i].end()) {
						node n = *item;
						beginword.push_back(n);
						item++;
					}
				}
			}//end for
		}
		else if (head >= 'a' && head <= 'z' && tail >= 'a' && tail <= 'z') {
			searchmethod = 3;
			int loc_begin = head - 'a';
			int loc_end = tail - 'a';
			vector<node>::iterator item;
			item = beginchar[loc_begin].begin();						//创建开始集
			while (item != beginchar[loc_begin].end()) {
				node n = *item;
				beginword.push_back(n);
				item++;
			}
			item = endchar[loc_end].begin();							//创建结束集
			while (item != endchar[loc_end].end()) {
				node n = *item;
				endword.push_back(n);
				item++;
			}
		}
		else {
			validinput = false;
		}
		if (beginword.size() == 0 && endword.size() == 0) {				//没有启示或没有结束单词，说明有环（但不能完全排除）
			validinput = false;
		}
	}
	else {

	}
	print_wordlist(beginword, endword);
	if (validinput) {
		vector<node>::iterator item;
		for (item = beginword.begin(); item != beginword.end(); item++) {
			node p = *item;
			cout << "开始执行！！！" << endl;
			dfs_both(p, distance, visited, preword, beginchar, endchar, beginword, endword, enable_loop);
		}
		cout << "开始结束！！！" << endl;
		int max = 0;
		int record = 0;
		for (int i = 0; i < len; i++) {
			if (distance[i] > max) {
				max = distance[i];
				record = i;
			}
		}
		cout << "HALF 終わり" << endl;
		max = max + 1;													//max是最长链点的个数
		result[max] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[max], 50, "16061182");
		for (int i = max - 1; i >= 0; i--) {
			result[i] = (char *)malloc(sizeof(char) * 50);
			strcpy_s(result[i], 50, words[record]);
			record = preword[record];
		}
		cout << "終わり" << endl;
	}
	/*switch (searchmethod)												//调用dfs查找最长路径
	{
	case(0):
	case(1):dfs_begin(visited, preword, beginchar, endchar, beginword, enable_loop); break;
	case(2):dfs_end(visited, preword, beginchar, endchar, endword, enable_loop); break;
	case(3):dfs_both(visited, preword, beginchar, endchar, beginword, endword, enable_loop); break;
	default:
		break;
	}*/



	return 1;
}

