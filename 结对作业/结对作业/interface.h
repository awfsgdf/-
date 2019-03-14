#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

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
	int index;
}arg;
typedef struct {
	vector<int> word_chain;	//������
	int len;					//�������ĳ���
}chain;
/*------------------------------------------------�ṹ����------------------------------------------------*/


/*------------------------------------------------ȫ�ֱ���------------------------------------------------*/

/*------------------------------------------------ȫ�ֱ���------------------------------------------------*/


/*------------------------------------------------�ඨ��------------------------------------------------*/
class Core {
private:
	vector<int> temp_list;		//dfs_loopʱ�Ļ�����
	int temp_list_length;			//�������ĳ���
	vector<chain> chain_list;		//�������ı��

	int core_visited[10005] = { 0 };								//���ʷ��ʼ�¼��
	int core_distance[10005] = { 0 };							//���뿪ʼλ�õľ����
	int core_preword[10005] = { 0 };									//�·��ǰһ����
	int core_order[10005] = { 0 };									//��¼���������ϵ�λ��

	int temp_visited[10005] = { 0 };
	vector<int> dfs_list;
	int dfs_list_length;
public:
	ifstream fin;
	ofstream fout;
	vector<vertex> core_beginchar[26];								//��a-z��ͷ�ĵ���(��endcharһͬ����ͼ)
	vector<vertex> core_endchar[26];								//��a-z��β�ĵ���
	vector<vertex> core_beginword;									//��ʼ��
	vector<vertex> core_endword;									//������
	char core_head;
	char core_tail;
	int optimal_length;				//�������ĳ���
	vector<string> optimal_list;	//������
	vector<string> core_words;

	Core();
	void print_wordlist(vector<vertex> beginword, vector<vertex> endword);
	void dfs_both(vertex p);
	void dfs_both_loop_freeend(vertex p);
	void dfs_both_loop_limitedend(vertex p);
	void generate(int len, bool enable_loop, bool ischar);
	void get_loop_list(int len, vector<vertex> &loop_list, bool ischar);
	void print(char *result[], bool enable_loop);
	void to_low(int i);
	void getTime();
	int read_word(char *word);
	vector<string> read_words(char *words[]);
	int find_arg(int argc, char *argv[], arg &w, arg &c, arg &h, arg &t, arg &r, char &head, char &tail);
	vector<string> read_words_str(string wordstring, char *words[]);
	int read_word_str(char *word, int &loc, string wordstring);

	void check_h_and_t(char head, char tail, bool have_head, bool have_tail);
	void check_file();
	void check_loop(bool enable_loop, int size);
	void check_null(char *word);
	void check_char(int i);
	void check_void(int len);		//����ĵ��ʼ��ϵĵ��ʸ����Ƿ�С��2
	void check_2();					//�������е��ʸ����Ƿ�С��2
	void check_same();

};

Core::Core() {};

void Core::print_wordlist(vector<vertex> beginword, vector<vertex> endword) {
	vector<vertex>::iterator i;
	cout << "Begin Nodes : " << beginword.size() << " words" << endl;
	cout << "End Nodes : " << endword.size() << " words" << endl;
	return;
}

void Core::dfs_both(vertex p) {
	core_visited[p.index] += 1;
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (core_beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = core_beginchar[end].begin(); item != core_beginchar[end].end(); item++) {
			vertex n = *item;
			if (!core_visited[n.index]) {
				if (core_distance[p.index] + n.length > core_distance[n.index]) {
					core_distance[n.index] = core_distance[p.index] + n.length;
					core_order[n.index] = core_order[p.index] + 1;
					core_preword[n.index] = p.index;
					dfs_both(n);
				}
			}
		}//end for
	}
	core_visited[p.index] -= 1;
	return;
}

void Core::dfs_both_loop_freeend(vertex p) { //loop_free
	temp_visited[p.index] += 1;
	dfs_list.push_back(p.index);
	dfs_list_length += p.length;
	int end = p.word.at(p.word.length() - 1) - 'a';
	bool have_next = false;
	if (core_beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = core_beginchar[end].begin(); item != core_beginchar[end].end(); item++) {
			vertex n = *item;
			if (!temp_visited[n.index]) {
				have_next = true;
				dfs_both_loop_freeend(n);
			}
		}//end for
	}
	if (!have_next) {				//������ҵ��յ�
		if (dfs_list_length > temp_list_length) {
			temp_list = dfs_list;
			temp_list_length = dfs_list_length;
		}
	}
	temp_visited[p.index] -= 1;
	dfs_list.pop_back();
	dfs_list_length -= p.length;

	return;
}

void Core::dfs_both_loop_limitedend(vertex p) { //loop_limited
	temp_visited[p.index] += 1;
	dfs_list.push_back(p.index);
	dfs_list_length += p.length;
	if (p.word.at(p.word.length() - 1) == core_tail) {
		if (dfs_list_length > temp_list_length) {
			temp_list = dfs_list;
			temp_list_length = dfs_list_length;
		}
	}
	int end = p.word.at(p.word.length() - 1) - 'a';
	if (core_beginchar[end].size() != 0) {
		vector<vertex>::iterator item;
		for (item = core_beginchar[end].begin(); item != core_beginchar[end].end(); item++) {
			vertex n = *item;
			if (!temp_visited[n.index]) {
				dfs_both_loop_limitedend(n);
			}
		}//end for
	}
	temp_visited[p.index] -= 1;
	dfs_list.pop_back();
	dfs_list_length -= p.length;

	return;
}

void Core::generate(int len, bool enable_loop, bool ischar) {
	vector<vertex>::iterator item;
	vector<vertex>::iterator temp;
	vector<vertex>::iterator ans;
	vector<vertex> loop_list;								//��·�㼯
	int searchmethod = 0;
	//���ɻ�·�㼯
	cout << "��ʼ���ɻ�·�㼯" << endl;
	get_loop_list(len, loop_list, ischar);
	cout << "������ɻ�·�㼯" << endl;
	check_loop(enable_loop, int(loop_list.size()));

	if (int(core_head) == 0 && int(core_tail) == 0) {
		searchmethod = 0;
		for (int i = 0; i < 26; i++) {
			vector<vertex>::iterator item;
			if (core_endchar[i].size() == 0 && core_beginchar[i].size() != 0) {			//û������Ϊ��β�ĵ��ʣ���������Ϊ��ͷ�ĵ���
				item = core_beginchar[i].begin();			//����������Ϊ��ʼ�ĵ��ʼ��뿪ʼ��
				while (item != core_beginchar[i].end()) {
					vertex n = *item;
					if (n.word.at(0) != n.word.at(n.word.length() - 1)) {
						core_beginword.push_back(n);
					}
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//��·�㼯���뿪ʼ��
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				core_beginword.push_back(*ans);
			}
		}
	}
	else if (core_head >= 'a' && core_head <= 'z' && int(core_tail) == 0) {
		searchmethod = 1;
		int loc = core_head - 'a';
		vector<vertex>::iterator item;
		item = core_beginchar[loc].begin();								//������ʼ��
		while (item != core_beginchar[loc].end()) {
			vertex n = *item;
			if (n.word.at(0) != n.word.at(n.word.length() - 1)) {
				core_beginword.push_back(n);
			}
			item++;
		}
	}
	else if (int(core_head) == 0 && core_tail >= 'a' && core_tail <= 'z') {
		searchmethod = 2;
		int loc = core_tail - 'a';
		vector<vertex>::iterator item;
		for (int i = 0; i < 26; i++) {								//������ʼ��
			if (core_endchar[i].size() == 0 && core_beginchar[i].size() != 0) {
				item = core_beginchar[i].begin();
				while (item != core_beginchar[i].end()) {
					vertex n = *item;
					if (n.word.at(0) != n.word.at(n.word.length() - 1)) {
						core_beginword.push_back(n);
					}
					item++;
				}
			}
		}//end for
		if (enable_loop) {							//��·�㼯���뿪ʼ��
			for (ans = loop_list.begin(); ans != loop_list.end(); ans++) {
				core_beginword.push_back(*ans);
			}
		}
	}
	else if (core_head >= 'a' && core_head <= 'z' && core_tail >= 'a' && core_tail <= 'z') {
		searchmethod = 3;
		int loc_begin = core_head - 'a';
		int loc_end = core_tail - 'a';
		vector<vertex>::iterator item;
		item = core_beginchar[loc_begin].begin();						//������ʼ��
		while (item != core_beginchar[loc_begin].end()) {
			vertex n = *item;
			if (n.word.at(0) != n.word.at(n.word.length() - 1)) {
				core_beginword.push_back(n);
			}
			item++;
		}
	}
	for (item = core_beginword.begin(); item != core_beginword.end(); item++) {		//��ʼ����ʼ���ľ���
		vertex p = *item;
		core_distance[p.index] += p.length;
		core_order[p.index] += 1;
	}
	cout << "���� " << core_beginword.size() << " ����ʼ��" << endl;
	getTime();
	int i = 1;
	if (!enable_loop) {
		for (item = core_beginword.begin(); item != core_beginword.end(); item++) {
			vertex p = *item;
			cout << "��ʼִ�е�" << i++ << " ����ʼ�� " << p.word << endl;
			getTime();
			dfs_both(p);
		}
		int max = 0;
		int record = 0;
		if (searchmethod == 0 || searchmethod == 1) {
			for (int i = 0; i < len; i++) {
				if (core_distance[i] > max) {
					max = core_distance[i];
					record = i;
				}
			}
		}
		else if (searchmethod == 2 || searchmethod == 3) {
			for (int i = 0; i < len; i++) {
				string word = core_words[i];
				if (core_distance[i] > max && word.at(word.length() - 1) == core_tail) {
					max = core_distance[i];
					record = i;
				}
			}
		}
		optimal_length = max;
		int length = core_order[record];
		for (int i = 0; i < length; i++) {
			optimal_list.push_back(string(core_words[record]));
			record = core_preword[record];
		}
	}
	else {
		for (item = core_beginword.begin(); item != core_beginword.end(); item++) {
			vertex p = *item;
			cout << "��ʼִ�е�" << i++ << " ����ʼ�� " << p.word << endl;
			getTime();
			if (searchmethod == 0 || searchmethod == 1) {
				dfs_both_loop_freeend(p);
			}
			else if (searchmethod == 2 || searchmethod == 3) {
				dfs_both_loop_limitedend(p);
			}
			chain_list.push_back({ temp_list, temp_list_length });		//���ε��������뵥������
		}

		//�ӵ���������Ѱ�����������Ϊ���
		int max_length = 0;
		int max_index = 0;
		for (unsigned int i = 0; i < chain_list.size(); i++) {
			if (chain_list[i].len > max_length) {
				max_length = chain_list[i].len;
				max_index = i;
			}
		}
		optimal_length = max_length;
		//optimal_list = chain_list[max_index].word_chain;
		vector<string> perhona;
		for (int i = 0; i < chain_list[max_index].word_chain.size(); i++) {
			perhona.push_back(string(core_words[chain_list[max_index].word_chain[i]]));
		}
		optimal_list = perhona;										//�������ŵ�����
	}
	getTime();
	return;
}

void Core::print(char *result[], bool enable_loop) {
	int max = int(optimal_list.size());
	cout << "���������Ϊ" << max << endl;
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

void Core::to_low(int i) {
	for (int ans = 0; ans < core_words[i].length(); ans++) {
		core_words[i][ans] = tolower(core_words[i][ans]);
	}
}

void Core::get_loop_list(int len, vector<vertex> &loop_list, bool ischar) {									//������ȡ���еĵ���
	vector<vertex> beginchar[26];
	vector<vertex> endchar[26];
	vector<vertex>::iterator item;
	vector<vertex>::iterator temp;
	vector<node>::iterator ans;
	vector<node> queue;
	for (int i = 0; i < len; i++) {
		string word = core_words[i];
		if (word.at(0) != word.at(word.length() - 1)) {
			if (ischar == true) {
				beginchar[word.at(0) - 'a'].push_back({ word,i,int(word.length()),false });
				endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,int(word.length()),false });
			}
			else {
				beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//���ʳ�����Ϊ1
				endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
			}
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
				cout << "���� " << (*item).word << " �ڻ���" << endl;
			}
		}
	}
	return;
}

void Core::getTime() {
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
		now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
}


void Core::check_h_and_t(char head, char tail, bool have_head, bool have_tail) {
	try {
		if (int(head) != 0 && !have_head) {
			throw 0;
		}
		if (int(tail) != 0 && !have_tail) {
			throw 1;
		}
	}
	catch (int e) {
		if (e == 0) {
			cout << "Error : û���Բ���'head'��ͷ�ĵ���" << endl;
			exit(0);
		}
		else if (e == 1) {
			cout << "Error : û���Բ���'tail'��β�ĵ���" << endl;
			exit(0);
		}
	}
}

void Core::check_file() {
	try {
		if (!fin) {
			throw 0;
		}
	}
	catch (...) {
		cout << "Error : �򿪵����ļ�ʧ��" << endl;
		exit(0);
	}
}

void Core::check_loop(bool enable_loop, int size) {
	try {
		if (!enable_loop && size != 0) {
			throw 0;
		}
		if (enable_loop && size == 0) {
			throw 1;
		}
	}
	catch (int e) {
		if (e == 0) {
			cout << "Error : û��-r���������ǵ��ʼ����л�" << endl;
			exit(0);
		}
		else if (e == 1) {
			cout << "Error : ��-r���������ǵ��ʼ���û�л�" << endl;
			exit(0);
		}
	}
}

void Core::check_char(int i) {
	int length = int(core_words[i].length());
	for (int ans = 0; ans < length; ans++) {
		char c = core_words[i][ans];
		try {
			if (!((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))) {
				throw 0;
			}
		}
		catch (...) {
			cout << "Error : �����а����Ƿ��ַ�" << endl;
			exit(0);
		}
	}
}

void Core::check_null(char *word) {
	try {
		if (word == NULL) {
			throw 0;
		}
	}
	catch (...) {
		cout << "Error : �����б��д��ڿյ�ָ��" << endl;
		exit(0);
	}
}

void Core::check_void(int len) {
	try {
		if (len < 2) {
			throw 0;
		}
	}
	catch (...) {
		cout << "Error : ����ĵ�������С��2�����޷��ҳ��Ϸ��ĵ�����" << endl;
		exit(0);
	}
}

void Core::check_2() {
	try {
		if (optimal_list.size() < 2) {
			throw 0;
		}
	}
	catch (...) {
		cout << "Error : ����ĵ�����С��2" << endl;
		exit(0);
	}
}



/*------------------------------------------------ȫ�ֺ�������------------------------------------------------*/

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {	//����Ĭ��wordsû���ظ�
	Core *core = new Core();
	core->check_void(len);
	for (int i = 0; i < len; i++) {
		core->check_null(words[i]);
		string word = words[i];
		core->core_words.push_back(word);
		core->to_low(i);
		/*for (int k = 0; k < i; k++) {
			if (core->core_words[i] == core->core_words[k]) {
				cout << "Error : ����ĵ����б������ظ���" << endl;
				cout << core->core_words[i] << " " << i << endl;
				cout << core->core_words[k] << " " << k << endl;
				exit(0);
			}
		}*/
	}
	core->core_head = head;
	core->core_tail = tail;
	int searchmethod = 0;
	bool have_head = false;
	bool have_tail = false;
	for (int i = 0; i < len; i++) {
		core->check_char(i);
		//core->to_low(i);
		string word = core->core_words[i];
		if (word.at(0) == head) {
			have_head = true;
		}
		if (word.at(word.length() - 1) == tail) {
			have_tail = true;
		}
		core->core_beginchar[word.at(0) - 'a'].push_back({ word,i,1,false });					//���ʳ�����Ϊ1
		core->core_endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,1,false });
		if (word.at(0) == word.at(word.length() - 1)) {								//�Ի�����ֱ�Ӽ��뿪ʼ��
			core->core_beginword.push_back({ word,i,1,false });
		}
	}

	core->check_h_and_t(head, tail, have_head, have_tail);

	core->generate(len, enable_loop, false);
	core->check_2();
	core->print(result, enable_loop);

	return int(core->optimal_list.size());
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {			//Ĭ��wordsû���ظ�
	Core *core = new Core();
	core->check_void(len);
	for (int i = 0; i < len; i++) {
		core->check_null(words[i]);
		string word = words[i];
		core->core_words.push_back(word);
		core->to_low(i);
		/*for (int k = 0; k < i; k++) {
			if (core->core_words[i] == core->core_words[k]) {
				cout << "Error : ����ĵ����б������ظ���" << endl;
				cout << core->core_words[i] << " " << i << endl;
				cout << core->core_words[k] << " " << k << endl;
				exit(0);
			}
		}*/
	}
	core->core_head = head;
	core->core_tail = tail;
	int searchmethod = 0;
	bool have_head = false;
	bool have_tail = false;
	for (int i = 0; i < len; i++) {
		core->check_char(i);
		//core->to_low(i);
		string word = core->core_words[i];
		if (word.at(0) == head) {
			have_head = true;
		}
		if (word.at(word.length() - 1) == tail) {
			have_tail = true;
		}
		core->core_beginchar[word.at(0) - 'a'].push_back({ word,i,int(word.length()),false });
		core->core_endchar[word.at(word.length() - 1) - 'a'].push_back({ word,i,int(word.length()),false });
		if (word.at(0) == word.at(word.length() - 1)) {								//�Ի�����ֱ�Ӽ��뿪ʼ��
			core->core_beginword.push_back({ word,i,int(word.length()),false });
		}
	}

	core->check_h_and_t(head, tail, have_head, have_tail);

	core->generate(len, enable_loop, true);
	core->check_2();
	core->print(result, enable_loop);

	return int(core->optimal_list.size());
}