#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;
void getTime();

/*------------------------------------------------结构定义------------------------------------------------*/
typedef struct {
	string word;
	int index;
	int length;
	bool is_end;
}vertex;
typedef struct {
	string word;
	bool is_head;
}node;
typedef struct {
	bool exist = false;
	int index;
}arg;
typedef struct {
	vector<string> word_chain;	//单词链
	int len;					//单词链的长度
}chain;
/*------------------------------------------------结构定义------------------------------------------------*/


/*------------------------------------------------全局变量------------------------------------------------*/
ifstream fin;
ofstream fout;
/*------------------------------------------------全局变量------------------------------------------------*/


/*------------------------------------------------类定义------------------------------------------------*/
class Core {
private:
	vector<string> temp_list;	//dfs_loop时的缓存链
	int temp_list_length;		//缓存链的长度
	vector<chain> chain_list;
	vector<string> optimal_list;
public:
	Core();
	void print_wordlist(vector<vertex> beginword, vector<vertex> endword);
	void dfs_both(vertex p, int *distance, int *visited, int *preword, int *order, vector<vertex> *beginchar, bool enable_loop);
	void dfs_both_loop_freeend(vertex p, int *visited, vector<vertex> *beginchar, vector<string> dfs_list, int dfs_list_length, bool enable_loop);
	void dfs_both_loop_limitedend(vertex p, int *visited, vector<vertex> *beginchar, vector<string> dfs_list, int dfs_list_length, char tail, bool enable_loop);
	void generate(char *words[], int len, int searchmethod, char head, char tail, vector<vertex> *beginchar, vector<vertex> *endchar, vector<vertex> &beginword, bool enable_loop, int *distance, int *visited, int *preword, int *order, bool ischar);
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	void get_loop_list(char* words[], int len, vector<vertex> &loop_list, bool ischar);
	void print(char *result[], bool enable_loop);
};

Core::Core() {};

void Core::print_wordlist(vector<vertex> beginword, vector<vertex> endword) {
	vector<vertex>::iterator i;
	cout << "Begin Nodes : " << beginword.size() << " words" << endl;
	/*for (i = beginword.begin(); i != beginword.end(); i++) {
		vertex n = *i;
		cout << n.word << " 下标：" << n.index << " 长度：" << n.length << " 结束词：" << n.is_end << endl;
	}*/
	cout << "End Nodes : " << endword.size() << " words" << endl;
	/*for (i = endword.begin(); i != endword.end(); i++) {
		vertex n = *i;
		cout << n.word << " 下标：" << n.index << " 长度：" << n.length << " 结束词：" << n.is_end << endl;
	}*/
	return;
}

void Core::dfs_both(vertex p, int *distance, int *visited, int *preword, int *order, vector<vertex> *beginchar, bool enable_loop) {
	/*if (p.is_end) {												//是结尾词
		return;
	}*/
	visited[p.index] += 1;
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			vertex n = *item;
			if (!visited[n.index]) {
				//cout << p.word << " " << n.word << " " << distance[p.index] << " " << n.length  << " " << distance[n.index] << endl;
				if (distance[p.index] + n.length > distance[n.index]) {
					distance[n.index] = distance[p.index] + n.length;
					order[n.index] = order[p.index] + 1;
					preword[n.index] = p.index;
					dfs_both(n, distance, visited, preword, order, beginchar, enable_loop);
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}

void Core::dfs_both_loop_freeend(vertex p, int *visited, vector<vertex> *beginchar, vector<string> dfs_list, int dfs_list_length, bool enable_loop) { //loop_free
	/*if (p.is_end) {												//是结尾词
		return;
	}*/
	visited[p.index] += 1;
	dfs_list.push_back(p.word);
	dfs_list_length += p.length;
	int end = p.word.at(p.word.length() - 1) - 'a';
	bool have_next = false;
	if (beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			vertex n = *item;
			if (!visited[n.index]) {
				have_next = true;
				dfs_both_loop_freeend(n, visited, beginchar, dfs_list, dfs_list_length, enable_loop);			
			}
		}//end for
	}
	if(!have_next) {				//到达查找的终点
		if (dfs_list_length > temp_list_length) {
			temp_list = dfs_list;
			temp_list_length = dfs_list_length;
		}
	}
	visited[p.index] -= 1;
	/*vector<string>::iterator item = dfs_list.end() - 1;			//最后一个元素，即p
	dfs_list.erase(item);
	dfs_list_length -= p.length;*/
	return;
}

void Core::dfs_both_loop_limitedend(vertex p, int *visited, vector<vertex> *beginchar, vector<string> dfs_list, int dfs_list_length, char tail, bool enable_loop) { //loop_limited
	/*if (p.is_end) {												//是结尾词
		return;
	}*/
	visited[p.index] += 1;
	dfs_list.push_back(p.word);
	dfs_list_length += p.length;
	if (p.word.at(p.word.length() - 1) == tail) {
		if (dfs_list_length > temp_list_length) {
			temp_list = dfs_list;
			temp_list_length = dfs_list_length;
		}
	}
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			vertex n = *item;
			if (!visited[n.index]) {
				dfs_both_loop_limitedend(n, visited, beginchar, dfs_list, dfs_list_length, tail, enable_loop);
			}
		}//end for
	}
	visited[p.index] -= 1;
	/*vector<string>::iterator item = dfs_list.end() - 1;			//最后一个元素，即p
	dfs_list.erase(item);
	dfs_list_length -= p.length;*/
	return;
}

/*void Core::dfs_both_loop(vertex p, int *distance, int *visited, int *preword, int *order, vector<vertex> *beginchar, bool enable_loop) {
	if (p.is_end) {												//是结尾词
		return;
	}
	visited[p.index] += 1;
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = beginchar[end].begin(); item != beginchar[end].end(); item++) {
			vertex n = *item;
			if (!visited[n.index]) {
				//cout << p.word << " " << n.word << " " << distance[p.index] << " " << n.length  << " " << distance[n.index] << endl;
				if (distance[p.index] + n.length > distance[n.index]) {
					distance[n.index] = distance[p.index] + n.length;
					order[n.index] = order[p.index] + 1;
					preword[n.index] = p.index;
					dfs_both_loop(n, distance, visited, preword, order, beginchar, enable_loop);
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}*/

void Core::generate(char *words[], int len, int searchmethod, char head, char tail, vector<vertex> *beginchar, vector<vertex> *endchar, vector<vertex> &beginword, bool enable_loop, int *distance, int *visited, int *preword, int *order, bool ischar) {
	vector<vertex>::iterator item;
	vector<vertex>::iterator temp;
	vector<vertex>::iterator ans;
	vector<vertex> loop_list;								//环路点集
	if (enable_loop) {										//生成环路点集
		cout << "开始生成环路点集" << endl;
		get_loop_list(words, len, loop_list, ischar);
		cout << "完成生成环路点集" << endl;
	}
	if (head == '0' && tail == '0') {
		searchmethod = 0;
		for (int i = 0; i < 26; i++) {
			vector<vertex>::iterator item;
			if (endchar[i].size() == 0 && beginchar[i].size() != 0) {			//没有以其为结尾的单词，但有以其为开头的单词
				item = beginchar[i].begin();			//把所有以其为开始的单词加入开始集
				while (item != beginchar[i].end()) {
					vertex n = *item;
					beginword.push_back(n);
					item++;
				}
			}
			/*else if (beginchar[i].size() == 0 && endchar[i].size() != 0) {		//没有以其为开头的单词，但有以其为结尾的单词
				item = endchar[i].begin();				//把所有以其为结束的单词加入结束集
				while (item != endchar[i].end()) {
					vertex n = *item;
					//n.is_end = true;
					endword.push_back(n);
					item++;
				}
			}*/
		}//end for
		if (enable_loop) {							//环路点集加入开始集
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				beginword.push_back(*ans);
				//endword.push_back(*ans);
			}
		}
	}
	else if (head >= 'a' && head <= 'z' && tail == '0') {
		searchmethod = 1;
		int loc = head - 'a';
		vector<vertex>::iterator item;
		item = beginchar[loc].begin();								//创建开始集
		while (item != beginchar[loc].end()) {
			vertex n = *item;
			beginword.push_back(n);
			item++;
		}
		/*for (int i = 0; i < 26; i++) {								//创建结束集
			if (beginchar[i].size() == 0 && endchar[i].size() != 0) {
				item = endchar[i].begin();
				while (item != endchar[i].end()) {
					vertex n = *item;
					//n.is_end = true;
					endword.push_back(n);
					item++;
				}
			}
		}//end for*/
		/*if (enable_loop) {							//环路点集加入结束集
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				endword.push_back(*ans);
			}
		}*/
	}
	else if (head == '0' && tail >= 'a' && tail <= 'z') {
		searchmethod = 2;
		int loc = tail - 'a';
		vector<vertex>::iterator item;								//创建结束集
		/*item = endchar[loc].begin();
		while (item != endchar[loc].end()) {
			vertex n = *item;
			//n.is_end = true;
			endword.push_back(n);
			item++;
		}*/
		for (int i = 0; i < 26; i++) {								//创建开始集
			if (endchar[i].size() == 0 && beginchar[i].size() != 0) {
				item = beginchar[i].begin();
				while (item != beginchar[i].end()) {
					vertex n = *item;
					beginword.push_back(n);
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//环路点集加入开始集
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				beginword.push_back(*ans);
			}
		}
	}
	else if (head >= 'a' && head <= 'z' && tail >= 'a' && tail <= 'z') {
		searchmethod = 3;
		int loc_begin = head - 'a';
		int loc_end = tail - 'a';
		vector<vertex>::iterator item;
		item = beginchar[loc_begin].begin();						//创建开始集
		while (item != beginchar[loc_begin].end()) {
			vertex n = *item;
			beginword.push_back(n);
			item++;
		}
		/*item = endchar[loc_end].begin();							//创建结束集
		while (item != endchar[loc_end].end()) {
			vertex n = *item;
			//n.is_end = true;
			endword.push_back(n);
			item++;
		}*/
	}
	/*for (item = endword.begin(); item != endword.end(); item++) {
		for (temp = beginword.begin(); temp != beginword.end(); temp++) {			//设置开始集的结束标志位
			if ((*temp).index == (*item).index) {
				(*temp).is_end = true;
				break;
			}
		}
		int i = (*item).word.at(0) - 'a';	//第一个字母
		for (temp = beginchar[i].begin(); temp != beginchar[i].end(); temp++) {		//设置beginchar集的结束标志位
			if ((*temp).index == (*item).index) {
				(*temp).is_end = true;
				break;
			}
		}
	}*/
	for (item = beginword.begin(); item != beginword.end(); item++) {		//初始化开始集的距离
		vertex p = *item;
		distance[p.index] += p.length;
		order[p.index] += 1;
	}
	//print_wordlist(beginword, endword);
	cout << "共有 " << beginword.size() << " 个开始点" << endl;
	getTime();
	int i = 1;
	if (!enable_loop) {
		for (item = beginword.begin(); item != beginword.end(); item++) {
			vertex p = *item;
			cout << "开始执行第" << i++ << " 个开始点 " << p.word << endl;
			getTime();
			dfs_both(p, distance, visited, preword, order, beginchar, enable_loop);
		}
		int max = 0;
		int record = 0;
		if (searchmethod == 0 || searchmethod == 1) {	
			for (int i = 0; i < len; i++) {
				if (distance[i] > max) {
					max = distance[i];
					record = i;
				}
			}
		}
		else if (searchmethod == 2 || searchmethod == 3) {
			for (int i = 0; i < len; i++) {
				string word = words[i];
				if (distance[i] > max && word.at(word.length() - 1) == tail) {
					max = distance[i];
					record = i;
				}
			}
		}
		int length = order[record];
		for (int i = 0; i < length; i++) {
			optimal_list.push_back(string(words[record]));
			record = preword[record];
		}
	}
	else {
		for (item = beginword.begin(); item != beginword.end(); item++) {
			vertex p = *item;
			cout << "开始执行第" << i++ << " 个开始点 " << p.word << endl;
			getTime();
			int temp_visited[10005] = { 0 };								//单词访问记录表
			vector<string> dfs_list;
			if (searchmethod == 0 || searchmethod == 1) {
				dfs_both_loop_freeend(p, temp_visited, beginchar, dfs_list, 0, enable_loop);
			}
			else if (searchmethod == 2 || searchmethod == 3) {
				dfs_both_loop_limitedend(p, temp_visited, beginchar, dfs_list, 0, tail, enable_loop);
			}
			chain_list.push_back({ temp_list,int(temp_list.size()) });		//本次单词链加入单词链表
		}
		
		//从单词链表中寻找最长单词链作为结果
		int max_length = 0;
		int max_index = 0;
		for (unsigned int i = 0 ; i < chain_list.size() ; i++) {
			if (chain_list[i].len > max_length) {
				max_length = chain_list[i].len;
				max_index = i;
			}
		}
		optimal_list = chain_list[max_index].word_chain;
	}
	/*for (int i = 0; i < optimal_list.size(); i++) {
		cout << "yes" << optimal_list[i] << endl;
	}*/
	getTime();
}

void Core::print(char *result[], bool enable_loop) {
	int max = optimal_list.size();
	cout << "最长链单词数为" << max << endl;
	result[max] = (char *)malloc(sizeof(char) * 50);
	strcpy_s(result[max], 50, "16061182");
	for (int i = max - 1; i >= 0; i--) {
		result[i] = (char *)malloc(sizeof(char) * 50);
		if (!enable_loop) {
			strcpy_s(result[i], 50, optimal_list[max - 1 - i].c_str());
		}
		else {
			strcpy_s(result[i], 50, optimal_list[i].c_str());
		}
	}
}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {	//这里默认words没有重复
	int visited[10005] = { 0 };								//单词访问记录表
	int distance[10005] = { 0 };							//距离开始位置的距离表
	int preword[10005] = { 0 };									//最长路径前一单词
	int order[10005] = { 0 };									//记录单词在链上的位置
	vector<vertex> beginchar[26];								//以a-z开头的单词(和endchar一同保存图)
	vector<vertex> endchar[26];								//以a-z结尾的单词
	vector<vertex> beginword;									//开始集
	vector<vertex> endword;									//结束集
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//单词长度视为1
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
		if (word.at(0) == word.at(word.length() - 1)) {								//自环单词直接加入开始集
			beginword.push_back({ word,i,1,false });
		}
	}

	generate(words, len, searchmethod, head, tail, beginchar, endchar, beginword, enable_loop, distance, visited, preword, order, false);
	print(result, enable_loop);

	/*int max = optimal_list.size();
	cout << "最长链单词数为" << max << endl;
	result[max] = (char *)malloc(sizeof(char) * 50);
	strcpy_s(result[max], 50, "16061182");
	for (int i = max - 1; i >= 0; i--) {
		result[i] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[i], 50, optimal_list[max-1-i].c_str());
	}*/
	
	return 1;
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {			//默认words没有重复
	int visited[10005] = { 0 };								//单词访问记录表
	int distance[10005] = { 0 };							//距离开始位置的距离表
	int preword[10005] = { 0 };									//最长路径前一单词
	int order[10005] = { 0 };							//记录单词是最长链上的第几个单词
	vector<vertex> beginchar[26];								//以a-z开头的单词(和endchar一同保存图)
	vector<vertex> endchar[26];								//以a-z结尾的单词
	vector<vertex> beginword;									//开始集
	vector<vertex> endword;									//结束集
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i,int(word.length()),false });
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,int(word.length()),false });
		if (word.at(0) == word.at(word.length() - 1)) {								//自环单词直接加入开始集
			beginword.push_back({ word,i,int(word.length()),false });
		}
	}

	generate(words, len, searchmethod, head, tail, beginchar, endchar, beginword, enable_loop, distance, visited, preword, order, true);
	print(result, enable_loop);

	/*int max = optimal_list.size();
	cout << "最长链单词数为" << max << endl;
	result[max] = (char *)malloc(sizeof(char) * 50);
	strcpy_s(result[max], 50, "16061182");
	for (int i = max - 1; i >= 0; i--) {
		result[i] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[i], 50, optimal_list[max-1-i].c_str());
	}*/
	return 1;
}

void Core::get_loop_list(char* words[], int len, vector<vertex> &loop_list, bool ischar) {									//用来获取环中的单词
	vector<vertex> beginchar[26];
	vector<vertex> endchar[26];
	vector<vertex>::iterator item;
	vector<vertex>::iterator temp;
	vector<node>::iterator ans;
	vector<node> queue;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		if (ischar == true) {
			beginchar[word.at(0) - 'a'].push_back({ word,i,int(word.length()),false });
			endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,int(word.length()),false });
		}
		else {
			beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//单词长度视为1
			endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
		}

	}
	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//入度为0的点（开始）
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				queue.push_back({ (*item).word, true });
			}
		}
		if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//出度为0的点（结束）
			for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
				queue.push_back({ (*item).word, false });
			}
		}
	}
	while (queue.size() != 0) {
		ans = queue.end() - 1;								//最后一个单词
		int begin_loc = (*ans).word.at(0) - 'a';
		int end_loc = (*ans).word.at((*ans).word.length() - 1) - 'a';
		/*for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
			if ((*temp) == (*item)) {						//开始集找到，删除该单词
				beginchar[begin_loc].erase(temp);
				break;
			}
		}*/
		if ((*ans).is_head == true) {									//是开头节点
			while (beginchar[begin_loc].size() != 0) {					//删除以该字母开头的所有点
				temp = beginchar[begin_loc].end() - 1;
				beginchar[begin_loc].erase(temp);
			}
			for (temp = endchar[end_loc].begin(); temp != endchar[end_loc].end(); temp++) {
				if ((*temp).word == (*ans).word) {						//结束集找到，删除该单词
					endchar[end_loc].erase(temp);
					break;
				}
			}
		}
		else {															//是结束节点
			for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
				if ((*temp).word == (*ans).word) {						//开始集找到，删除该单词
					beginchar[begin_loc].erase(temp);
					break;
				}
			}
			while (endchar[end_loc].size() != 0) {						//删除以该字母结束的所有点
				temp = endchar[end_loc].end() - 1;
				endchar[end_loc].erase(temp);
			}
		}

		//cout << "删除了" << (*ans).word << endl;
		queue.erase(ans);									//从队列中删除

		for (int i = 0; i < 26; i++) {						//继续遍历，往队列里添加，直到所有点全部添加
			if (beginchar[i].size() != 0 && endchar[i].size() == 0) {
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					queue.push_back({ (*item).word, true });
				}
			}
			if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//出度为0的点（结束）
				for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
					queue.push_back({ (*item).word, false });
				}
			}
		}
	}//end while

	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0) {						//有未删干净的点
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				loop_list.push_back(*item);
				cout << "单词 " << (*item).word << " 在环中" << endl;
			}
		}
	}
	return;
}
/*------------------------------------------------类定义------------------------------------------------*/


/*------------------------------------------------全局函数定义------------------------------------------------*/
void getTime() {
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
		now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
}

int read_word(char *word) {
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

vector<string> read_words() {
	char word[50];
	vector<string> str_wordlist;
	vector<string>::iterator str_loc;
	while (read_word(word) != EOF) {
		string str_word = word;
		//cout << str_word << endl;
		str_wordlist.push_back(str_word);
	}
	/*for (unsigned int i = 0; i < str_wordlist.size(); i++) {
		cout << str_wordlist[i] << ":" << i << endl;
	}*/
	cout << endl;
	return str_wordlist;
}

/*
enable_loop == false && 有环 -> return false
enable_loop == true && 无环 -> return false
*/

bool check_loop(vector<string> str_wordlist, bool enable_loop) {						//此时已经经过重复性检查
	vector<string> beginchar[26];
	vector<string> endchar[26];
	vector<string>::iterator item;
	vector<string>::iterator temp;
	vector<node>::iterator ans;
	vector<node> queue;
	for (item = str_wordlist.begin(); item != str_wordlist.end(); item++) {
		string word = *item;
		if (word.at(0) != word.at(word.length() - 1)) {									//自环点不算在内，检查时应该忽略
			beginchar[word.at(0) - 'a'].push_back(word);
			endchar[word.at(word.length() - 1) - 'a'].push_back(word);
		}
	}
	/*for (int i = 0; i < 26; i++) {		//自环点不算在内
		if (beginchar[i].size() != 0) {
			for (item = beginchar[i].begin(); item != beginchar[i].end(); ) {
				string str = *item;
				if (str.at(0) == str.at(str.length() - 1)) {
					temp = item;
					cout << 2333 << endl;
					item++;
					beginchar[i].erase(temp);
				}
			}
		}
		if (endchar[i].size() != 0) {
			for (item = endchar[i].begin(); item != endchar[i].end(); ) {
				string str = *item;
				if (str.at(0) == str.at(str.length() - 1)) {
					temp = item;
					cout << 4666 << endl;
					item++;
					endchar[i].erase(temp);
				}
			}
		}
		
	}*/
	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//入度为0且出度不为0的点（开始）
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				queue.push_back({ *item, true });
			}
		}
		/*if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//出度为0且入度不为0的点（结束）
			for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
				queue.push_back({ *item, false });
			}
		}*/
	}
	while (queue.size() != 0) {
		ans = queue.end() - 1;								//最后一个单词
		int begin_loc = (*ans).word.at(0) - 'a';
		int end_loc = (*ans).word.at((*ans).word.length() - 1) - 'a';
		while (beginchar[begin_loc].size() != 0) {			//删除以该字母开头的所有点
			temp = beginchar[begin_loc].end() - 1;
			beginchar[begin_loc].erase(temp);
		}
		for (temp = endchar[end_loc].begin(); temp != endchar[end_loc].end(); temp++) {
			if ((*temp) == (*ans).word) {						//结束集找到，删除该单词
				endchar[end_loc].erase(temp);
				break;
			}
		}
		/*if ((*ans).is_head) {
			while (beginchar[begin_loc].size() != 0) {			//删除以该字母开头的所有点
				temp = beginchar[begin_loc].end() - 1;
				beginchar[begin_loc].erase(temp);
			}
			for (temp = endchar[end_loc].begin(); temp != endchar[end_loc].end(); temp++) {
				if ((*temp) == (*ans).word) {						//结束集找到，删除该单词
					endchar[end_loc].erase(temp);
					break;
				}
			}
		}
		else {
			for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
				if ((*temp) == (*ans).word) {
					beginchar[begin_loc].erase(temp);
					break;
				}
			}
			while (endchar[end_loc].size() != 0) {
				temp = endchar[end_loc].end() - 1;
				endchar[end_loc].erase(temp);
			}
		}*/

		//cout << "删除了" << (*ans).word << endl;
		queue.erase(ans);									//从队列中删除

		for (int i = 0; i < 26; i++) {						//继续遍历，往队列里添加，直到所有点全部添加
			if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//入度为0且出度不为0的点（开始）
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					queue.push_back({ *item, true });
				}
			}
			/*if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//出度为0且入度不为0的点（结束）
				for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
					queue.push_back({ *item, false });
				}
			}*/
		}
	}//end while
	bool last = false;
	for (int i = 0; i < 26 && last == false; i++) {
		if (beginchar[i].size() != 0) {
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				string str = *item;
				if (!(str.at(0) == str.at(str.length() - 1))) {				//有除了自环之外的点
					last = true;
					cout << "图里有环" << endl;
					break;
				}
			}
		}
		
		/*if (beginchar[i].size() != 0) {						//有未删干净的点（未必所有未删除的点都在环中）
			last = true;
			cout << "图里有环" << endl;
			break;
		}*/
	}
	if ((enable_loop == false && last == true) || (enable_loop == true && last == false)) {
		return false;
	}
	return true;
}

bool find_arg(int argc, char *argv[], arg &w, arg &c, arg &h, arg &t, arg &r, char &head, char &tail) {
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
	if (w.exist && c.exist) {
		return false;
	}
	if (h.exist) {
		if (h.index == argc - 1) {
			return false;
		}
		string str_head = argv[h.index + 1];
		char char_head = str_head.at(0);
		if (str_head.length() != 1) {
			return false;
		}
		if (!((char_head >= 'a' && char_head <= 'z') || (char_head >= 'A' && char_head <= 'Z'))) {
			return false;
		}
		head = char_head;
	}
	else {
		head = '0';
	}
	if (t.exist) {
		if (t.index == argc - 1) {
			return false;
		}
		string str_tail = argv[t.index + 1];
		char char_tail = str_tail.at(0);
		if (str_tail.length() != 1) {
			return false;
		}
		if (!((char_tail >= 'a' && char_tail <= 'z') || (char_tail >= 'A' && char_tail <= 'Z'))) {
			return false;
		}
		tail = char_tail;
	}
	else {
		tail = '0';
	}
	return true;
}
/*------------------------------------------------全局函数定义------------------------------------------------*/