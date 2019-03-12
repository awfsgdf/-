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
vector<vertex>* wordlist = new vector<vertex>();     //û���ظ��Ķ��㼯
int map[10000][10000] = {0};
bool validinput = true;									//�����Ƿ���Ч
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
	vector<vertex>::iterator loc;                            //���һ��������
	while (read_word(word) != EOF) {
		cout << word << endl;
		string str_word = word;
		/*char startc = str_word.at(0);
		char endc = str_word.at(str_word.length() - 1);*/
		//vertex ver = { str_word, startc, endc, str_word.length() };//������Ϊ����
		
		str_loc = find(str_wordlist.begin(), str_wordlist.end(), str_word);
		if (str_loc != str_wordlist.end()) {									//�ҵ��ظ�
			cout << "�ҵ��ظ���" << str_word << endl;
			continue;
		}
		else {																		//û���ظ�
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

/*int generate_map(vector<vertex> *wordlist,int len) {                   //����ͼ
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if ((*wordlist)[i].end == (*wordlist)[j].start) {					//��β��ӣ�����һ����
				map[i][j] = 1;
				cout << "from:" << (*wordlist)[i].word << " to:" << (*wordlist)[j].word << endl;
			}
		}
	}
	return 1;
	//vector<vector<int> >vv(len, vector<int>(len));              //����len*len�ľ���
}*/

/*
* p�ǵ�ǰ����
* num�ǵ�������
* ��ͷ��β����ͷ��β
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
			if (!visited[n.index]) {				//��δ���ʹ�����ݹ����
				if (distance[p.index] + 1 > distance[n.index]) {
					distance[n.index] = distance[p.index] + 1;									//���¾���
					preword[n.index] = p.word;													//����·��
					dfs_begin(n, distance, visited, preword, beginchar, endchar, beginword, enable_loop);
				}		
			}
			else {
				if (!enable_loop) {									//�����л�������
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
* ��ͷ��β
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
* ��ͷ��β
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
	if (find) {													//�ǽ�β��
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

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {	//����Ĭ��wordsû���ظ�
	int visited[10005] = { 0 };								//���ʷ��ʼ�¼��
	int distance[10005] = { 0 };							//���뿪ʼλ�õľ����
	int preword[10005];									//�·��ǰһ����
	vector<node> beginchar[26];								//��a-z��ͷ�ĵ���(��endcharһͬ����ͼ)
	vector<node> endchar[26];								//��a-z��β�ĵ���
	vector<node> beginword;									//��ʼ��
	vector<node> endword;									//������
	int searchmethod = 0;
	for (int i = 0; i < len; i++) {
		string word = words[i];
		beginchar[word.at(0) - 'a'].push_back({ word,i });
		endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i });
		//wordlist->push_back({ str, str.at(0), str.at(str.length() - 1), int(str.length()) });
	}
	if (!enable_loop) {															//��ȡ������Ϊ��ʼ�ĵ�Ϳ�����Ϊ�����ĵ�
		if (head == '0' && tail == '0') {
			searchmethod = 0;
			for (int i = 0; i < 26; i++) {
				vector<node>::iterator item;
				if (endchar[i].size() == 0 && beginchar[i].size() != 0) {			//û������Ϊ��β�ĵ��ʣ���������Ϊ��ͷ�ĵ���
					item = beginchar[i].begin();			//����������Ϊ��ʼ�ĵ��ʼ��뿪ʼ��
					while (item != beginchar[i].end()) {
						node n = *item;
						beginword.push_back(n);
						item++;
					}
				}
				else if (beginchar[i].size() == 0 && endchar[i].size() != 0) {		//û������Ϊ��ͷ�ĵ��ʣ���������Ϊ��β�ĵ���
					item = endchar[i].begin();				//����������Ϊ�����ĵ��ʼ��������
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
			item = beginchar[loc].begin();								//������ʼ��
			while (item != beginchar[loc].end()) {
				node n = *item;
				beginword.push_back(n);
				item++;
			}
			for (int i = 0; i < 26; i++) {								//����������
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
			vector<node>::iterator item;								//����������
			item = endchar[loc].begin();
			while (item != endchar[loc].end()) {
				node n = *item;
				endword.push_back(n);
				item++;
			}
			for (int i = 0; i < 26; i++) {								//������ʼ��
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
			item = beginchar[loc_begin].begin();						//������ʼ��
			while (item != beginchar[loc_begin].end()) {
				node n = *item;
				beginword.push_back(n);
				item++;
			}
			item = endchar[loc_end].begin();							//����������
			while (item != endchar[loc_end].end()) {
				node n = *item;
				endword.push_back(n);
				item++;
			}
		}
		else {
			validinput = false;
		}
		if (beginword.size() == 0 && endword.size() == 0) {				//û����ʾ��û�н������ʣ�˵���л�����������ȫ�ų���
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
			cout << "��ʼִ�У�����" << endl;
			dfs_both(p, distance, visited, preword, beginchar, endchar, beginword, endword, enable_loop);
		}
		cout << "��ʼ����������" << endl;
		int max = 0;
		int record = 0;
		for (int i = 0; i < len; i++) {
			if (distance[i] > max) {
				max = distance[i];
				record = i;
			}
		}
		cout << "HALF �K���" << endl;
		max = max + 1;													//max�������ĸ���
		result[max] = (char *)malloc(sizeof(char) * 50);
		strcpy_s(result[max], 50, "16061182");
		for (int i = max - 1; i >= 0; i--) {
			result[i] = (char *)malloc(sizeof(char) * 50);
			strcpy_s(result[i], 50, words[record]);
			record = preword[record];
		}
		cout << "�K���" << endl;
	}
	/*switch (searchmethod)												//����dfs�����·��
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

