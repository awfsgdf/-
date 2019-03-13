#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;
void getTime();

/*------------------------------------------------�ṹ����------------------------------------------------*/
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
	unsigned int index;
}arg;
/*------------------------------------------------�ṹ����------------------------------------------------*/


/*------------------------------------------------ȫ�ֱ���------------------------------------------------*/
ifstream fin;
ofstream fout;
/*------------------------------------------------ȫ�ֱ���------------------------------------------------*/


/*------------------------------------------------�ඨ��------------------------------------------------*/
class Core {
public:
	Core();
	void print_wordlist(vector<vertex> beginword, vector<vertex> endword);
	void dfs_both(vertex p, int *distance, int *visited, int *preword, int *order, vector<vertex> *beginchar, bool enable_loop);
	void generate(char *words[], int len, int searchmethod, char head, char tail, vector<vertex> *beginchar, vector<vertex> *endchar, vector<vertex> &beginword, vector<vertex> &endword, bool enable_loop, int *distance, int *visited, int *preword, int *order, bool ischar);
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	void get_loop_list(char* words[], int len, vector<vertex> &loop_list, bool ischar);
};

Core::Core() {};

void Core::print_wordlist(vector<vertex> beginword, vector<vertex> endword) {
	vector<vertex>::iterator i;
	cout << "Begin Nodes : " << endl;
	for (i = beginword.begin(); i != beginword.end(); i++) {
		vertex n = *i;
		cout << n.word << " �±꣺" << n.index << " ���ȣ�" << n.length << " �����ʣ�" << n.is_end << endl;
	}
	cout << "End Nodes : " << endl;
	for (i = endword.begin(); i != endword.end(); i++) {
		vertex n = *i;
		cout << n.word << " �±꣺" << n.index << " ���ȣ�" << n.length << " �����ʣ�" << n.is_end << endl;
	}
	return;
}

void Core::dfs_both(vertex p, int *distance, int *visited, int *preword, int *order, vector<vertex> *beginchar, bool enable_loop) {
	if (p.is_end) {												//�ǽ�β��
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
					dfs_both(n, distance, visited, preword, order, beginchar, enable_loop);
				}
			}
		}//end for
	}
	visited[p.index] -= 1;
	return;
}

void Core::generate(char *words[], int len, int searchmethod, char head, char tail, vector<vertex> *beginchar, vector<vertex> *endchar, vector<vertex> &beginword, vector<vertex> &endword, bool enable_loop, int *distance, int *visited, int *preword, int *order, bool ischar) {
	vector<vertex>::iterator item;
	vector<vertex>::iterator temp;
	vector<vertex>::iterator ans;
	vector<vertex> loop_list;								//��·�㼯
	if (enable_loop) {										//���ɻ�·�㼯
		cout << "��ʼ���ɻ�·�㼯" << endl;
		get_loop_list(words, len, loop_list, ischar);
		cout << "������ɻ�·�㼯" << endl;
	}
	if (head == '0' && tail == '0') {
		searchmethod = 0;
		for (int i = 0; i < 26; i++) {
			vector<vertex>::iterator item;
			if (endchar[i].size() == 0 && beginchar[i].size() != 0) {			//û������Ϊ��β�ĵ��ʣ���������Ϊ��ͷ�ĵ���
				item = beginchar[i].begin();			//����������Ϊ��ʼ�ĵ��ʼ��뿪ʼ��
				while (item != beginchar[i].end()) {
					vertex n = *item;
					beginword.push_back(n);
					item++;
				}
			}
			else if (beginchar[i].size() == 0 && endchar[i].size() != 0) {		//û������Ϊ��ͷ�ĵ��ʣ���������Ϊ��β�ĵ���
				item = endchar[i].begin();				//����������Ϊ�����ĵ��ʼ��������
				while (item != endchar[i].end()) {
					vertex n = *item;
					//n.is_end = true;
					endword.push_back(n);
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//��·�㼯���뿪ʼ���ͽ�����
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				beginword.push_back(*ans);
				endword.push_back(*ans);
			}
		}
	}
	else if (head >= 'a' && head <= 'z' && tail == '0') {
		searchmethod = 1;
		int loc = head - 'a';
		vector<vertex>::iterator item;
		item = beginchar[loc].begin();								//������ʼ��
		while (item != beginchar[loc].end()) {
			vertex n = *item;
			beginword.push_back(n);
			item++;
		}
		for (int i = 0; i < 26; i++) {								//����������
			if (beginchar[i].size() == 0 && endchar[i].size() != 0) {
				item = endchar[i].begin();
				while (item != endchar[i].end()) {
					vertex n = *item;
					//n.is_end = true;
					endword.push_back(n);
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//��·�㼯���������
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				endword.push_back(*ans);
			}
		}
	}
	else if (head == '0' && tail >= 'a' && tail <= 'z') {
		searchmethod = 2;
		int loc = tail - 'a';
		vector<vertex>::iterator item;								//����������
		item = endchar[loc].begin();
		while (item != endchar[loc].end()) {
			vertex n = *item;
			//n.is_end = true;
			endword.push_back(n);
			item++;
		}
		for (int i = 0; i < 26; i++) {								//������ʼ��
			if (endchar[i].size() == 0 && beginchar[i].size() != 0) {
				item = beginchar[i].begin();
				while (item != beginchar[i].end()) {
					vertex n = *item;
					beginword.push_back(n);
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//��·�㼯���뿪ʼ��
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
		item = beginchar[loc_begin].begin();						//������ʼ��
		while (item != beginchar[loc_begin].end()) {
			vertex n = *item;
			beginword.push_back(n);
			item++;
		}
		item = endchar[loc_end].begin();							//����������
		while (item != endchar[loc_end].end()) {
			vertex n = *item;
			//n.is_end = true;
			endword.push_back(n);
			item++;
		}
	}
	/*if (enable_loop) {												//�л������������������Ŀ�ʼ���ͽ���������Ϊ��
		cout << "�ѻ����뿪ʼ��" << endl;
		if (beginword.size() == 0) {								//���е���뿪ʼ���������
			for (int i = 0; i < 26; i++) {
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					beginword.push_back(*item);
				}
			}
		}
		if (endword.size() == 0) {
			for (int i = 0; i < 26; i++) {
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					endword.push_back(*item);
				}
			}
		}
	}*/
	for (item = endword.begin(); item != endword.end(); item++) {
		for (temp = beginword.begin(); temp != beginword.end(); temp++) {			//���ÿ�ʼ���Ľ�����־λ
			if ((*temp).index == (*item).index) {
				(*temp).is_end = true;
				break;
			}
		}
		int i = (*item).word.at(0) - 'a';	//��һ����ĸ
		for (temp = beginchar[i].begin(); temp != beginchar[i].end(); temp++) {		//����beginchar���Ľ�����־λ
			if ((*temp).index == (*item).index) {
				(*temp).is_end = true;
				break;
			}
		}
	}
	for (item = beginword.begin(); item != beginword.end(); item++) {		//��ʼ����ʼ���ľ���
		vertex p = *item;
		distance[p.index] += p.length;
		order[p.index] += 1;
	}
	print_wordlist(beginword, endword);
	cout << "���� " << beginword.size() << " ����ʼ��" << endl;
	getTime();
	int i = 1;
	for (item = beginword.begin(); item != beginword.end(); item++) {
		vertex p = *item;
		cout << "��ʼִ�е�" << i++ << " ����ʼ��" << endl;
		getTime();
		dfs_both(p, distance, visited, preword, order, beginchar, enable_loop);
	}
	cout << "��ʼ����������" << endl;
	getTime();
}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {	//����Ĭ��wordsû���ظ�
	int visited[10005] = { 0 };								//���ʷ��ʼ�¼��
	int distance[10005] = { 0 };							//���뿪ʼλ�õľ����
	int preword[10005];									//�·��ǰһ����
	int order[10005] = { 0 };									//��¼���������ϵ�λ��
	vector<vertex> beginchar[26];								//��a-z��ͷ�ĵ���(��endcharһͬ����ͼ)
	vector<vertex> endchar[26];								//��a-z��β�ĵ���
	vector<vertex> beginword;									//��ʼ��
	vector<vertex> endword;									//������
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//���ʳ�����Ϊ1
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
	}

	generate(words, len, searchmethod, head, tail, beginchar, endchar, beginword, endword, enable_loop, distance, visited, preword, order, false);


	int max = 0;									//���������
	int record = 0;
	for (int i = 0; i < len; i++) {
		if (distance[i] > max) {
			max = distance[i];
			record = i;
		}
	}
	cout << "���������Ϊ" << max << endl;
	result[max] = (char *)malloc(sizeof(char) * 50);
	strcpy_s(result[max], 50, "16061182");
	for (int i = max - 1; i >= 0; i--) {
		result[i] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[i], 50, words[record]);
		record = preword[record];
	}
	//cout << "�K���" << endl;
	return 1;
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {			//Ĭ��wordsû���ظ�
	int visited[10005] = { 0 };								//���ʷ��ʼ�¼��
	int distance[10005] = { 0 };							//���뿪ʼλ�õľ����
	int preword[10005];									//�·��ǰһ����
	int order[10005] = { 0 };							//��¼����������ϵĵڼ�������
	vector<vertex> beginchar[26];								//��a-z��ͷ�ĵ���(��endcharһͬ����ͼ)
	vector<vertex> endchar[26];								//��a-z��β�ĵ���
	vector<vertex> beginword;									//��ʼ��
	vector<vertex> endword;									//������
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i,int(word.length()),false });
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,int(word.length()),false });
	}

	generate(words, len, searchmethod, head, tail, beginchar, endchar, beginword, endword, enable_loop, distance, visited, preword, order, true);
	print_wordlist(beginword, endword);

	int max = 0;									//�����ĸ��
	int record = 0;
	for (int i = 0; i < len; i++) {
		if (distance[i] > max) {
			max = distance[i];
			record = i;
		}
	}
	int length = order[record];						//���������
	cout << "�����ĸ��Ϊ" << max << endl;
	cout << "���������Ϊ" << length << endl;
	result[length] = (char *)malloc(sizeof(char) * 50);
	strcpy_s(result[length], 50, "16061182");
	for (int i = length - 1; i >= 0; i--) {
		result[i] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[i], 50, words[record]);
		record = preword[record];
	}
	return 1;
}

void Core::get_loop_list(char* words[], int len, vector<vertex> &loop_list, bool ischar) {									//������ȡ���еĵ���
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
			beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//���ʳ�����Ϊ1
			endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
		}

	}
	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//���Ϊ0�ĵ㣨��ʼ��
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				queue.push_back({ (*item).word, true });
			}
		}
		if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//����Ϊ0�ĵ㣨������
			for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
				queue.push_back({ (*item).word, false });
			}
		}
	}
	while (queue.size() != 0) {
		ans = queue.end() - 1;								//���һ������
		int begin_loc = (*ans).word.at(0) - 'a';
		int end_loc = (*ans).word.at((*ans).word.length() - 1) - 'a';
		/*for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
			if ((*temp) == (*item)) {						//��ʼ���ҵ���ɾ���õ���
				beginchar[begin_loc].erase(temp);
				break;
			}
		}*/
		if ((*ans).is_head == true) {									//�ǿ�ͷ�ڵ�
			while (beginchar[begin_loc].size() != 0) {					//ɾ���Ը���ĸ��ͷ�����е�
				temp = beginchar[begin_loc].end() - 1;
				beginchar[begin_loc].erase(temp);
			}
			for (temp = endchar[end_loc].begin(); temp != endchar[end_loc].end(); temp++) {
				if ((*temp).word == (*ans).word) {						//�������ҵ���ɾ���õ���
					endchar[end_loc].erase(temp);
					break;
				}
			}
		}
		else {															//�ǽ����ڵ�
			for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
				if ((*temp).word == (*ans).word) {						//��ʼ���ҵ���ɾ���õ���
					beginchar[begin_loc].erase(temp);
					break;
				}
			}
			while (endchar[end_loc].size() != 0) {						//ɾ���Ը���ĸ���������е�
				temp = endchar[end_loc].end() - 1;
				endchar[end_loc].erase(temp);
			}
		}

		cout << "ɾ����" << (*ans).word << endl;
		queue.erase(ans);									//�Ӷ�����ɾ��

		for (int i = 0; i < 26; i++) {						//��������������������ӣ�ֱ�����е�ȫ�����
			if (beginchar[i].size() != 0 && endchar[i].size() == 0) {
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					queue.push_back({ (*item).word, true });
				}
			}
			if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//����Ϊ0�ĵ㣨������
				for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
					queue.push_back({ (*item).word, false });
				}
			}
		}
	}//end while

	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0) {						//��δɾ�ɾ��ĵ�
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				loop_list.push_back(*item);
			}
		}
	}
	return;
}
/*------------------------------------------------�ඨ��------------------------------------------------*/


/*------------------------------------------------ȫ�ֺ�������------------------------------------------------*/
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
	vector<string> str_wordlist;
	vector<string>::iterator str_loc;
	while (read_word(word) != EOF) {
		string str_word = word;
		str_wordlist.push_back(str_word);
	}
	for (unsigned int i = 0; i < str_wordlist.size(); i++) {
		cout << str_wordlist[i] << ":" << i << endl;
	}
	cout << endl;
	return str_wordlist;
}

/*
enable_loop == false && �л� -> return false
enable_loop == true && �޻� -> return false
*/

bool check_loop(vector<string> str_wordlist, bool enable_loop) {				//��ʱ�Ѿ������ظ��Լ��
	vector<string> beginchar[26];
	vector<string> endchar[26];
	vector<string>::iterator item;
	vector<string>::iterator temp;
	vector<node>::iterator ans;
	vector<node> queue;
	for (item = str_wordlist.begin(); item != str_wordlist.end(); item++) {
		string word = *item;
		beginchar[word.at(0) - 'a'].push_back(word);
		endchar[word.at(word.length() - 1) - 'a'].push_back(word);
	}
	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//���Ϊ0�ҳ��Ȳ�Ϊ0�ĵ㣨��ʼ��
			for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
				queue.push_back({ *item, true });
			}
		}
		if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//����Ϊ0����Ȳ�Ϊ0�ĵ㣨������
			for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
				queue.push_back({ *item, false });
			}
		}
	}
	while (queue.size() != 0) {
		ans = queue.end() - 1;								//���һ������
		int begin_loc = (*ans).word.at(0) - 'a';
		int end_loc = (*ans).word.at((*ans).word.length() - 1) - 'a';
		/*for (temp = beginchar[begin_loc].begin(); temp != beginchar[begin_loc].end(); temp++) {
			if ((*temp) == (*item)) {						//��ʼ���ҵ���ɾ���õ���
				beginchar[begin_loc].erase(temp);
				break;
			}
		}*/
		if ((*ans).is_head) {
			while (beginchar[begin_loc].size() != 0) {			//ɾ���Ը���ĸ��ͷ�����е�
				temp = beginchar[begin_loc].end() - 1;
				beginchar[begin_loc].erase(temp);
			}
			for (temp = endchar[end_loc].begin(); temp != endchar[end_loc].end(); temp++) {
				if ((*temp) == (*ans).word) {						//�������ҵ���ɾ���õ���
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
		}

		cout << "ɾ����" << (*ans).word << endl;
		queue.erase(ans);									//�Ӷ�����ɾ��

		for (int i = 0; i < 26; i++) {						//��������������������ӣ�ֱ�����е�ȫ�����
			if (beginchar[i].size() != 0 && endchar[i].size() == 0) {						//���Ϊ0�ҳ��Ȳ�Ϊ0�ĵ㣨��ʼ��
				for (item = beginchar[i].begin(); item != beginchar[i].end(); item++) {
					queue.push_back({ *item, true });
				}
			}
			if (beginchar[i].size() == 0 && endchar[i].size() != 0) {						//����Ϊ0����Ȳ�Ϊ0�ĵ㣨������
				for (item = endchar[i].begin(); item != endchar[i].end(); item++) {
					queue.push_back({ *item, false });
				}
			}
		}
	}//end while
	bool last = false;
	for (int i = 0; i < 26; i++) {
		if (beginchar[i].size() != 0) {						//��δɾ�ɾ��ĵ�
			last = true;
			cout << "ͼ���л�" << endl;
			break;
		}
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
		if (h.index >= argc - 1) {
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
	if (t.exist) {
		if (t.index >= argc - 1) {
			return false;
		}
		string str_head = argv[t.index + 1];
		char char_head = str_head.at(0);
		if (str_head.length() != 1) {
			return false;
		}
		if (!((char_head >= 'a' && char_head <= 'z') || (char_head >= 'A' && char_head <= 'Z'))) {
			return false;
		}
		tail = char_head;
	}
	return true;
}
/*------------------------------------------------ȫ�ֺ�������------------------------------------------------*/