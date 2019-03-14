// 结对作业.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// E:\git\Software-Engineering\结对作业\Debug\结对作业.exe -w E:\git\Software-Engineering\结对作业\结对作业\Text2.txt
//

#include "pch.h"
#include "interface.h"
#include "ew.h"

using namespace std;



int main(int argc, char *argv[])
{
	int method = 0;


	if (method == 0) {
		char* words[10005];
		char* result[10005];
		Core* core = new Core();
		arg arg_w; //最多单词
		arg arg_c; //最多字母
		arg arg_h; //指定首字母
		arg arg_t; //指定尾字母
		arg arg_r; //允许隐含环
		char head; //开始字母
		char tail; //结束字母

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "----------开始读入参数！----------" << endl;
		cout << "Waiting···" << endl;
		for (int i = 0; i < argc; i++) {
			cout << "第 " << i << " 个参数是 " << argv[i] << endl;
		}
		int valid = core->find_arg(argc, argv, arg_w, arg_c, arg_h, arg_t, arg_r, head, tail);
		try {
			if (valid == 1) {
				throw 1;
			}
			else if (valid == 2) {
				throw 2;
			}
			else if (valid == 3) {
				throw 3;
			}
			else if (valid == 4) {
				throw 4;
			}
		}
		catch (int e) {
			if (e == 1) {
				cout << "Error : -w和-c同时存在" << endl;
				exit(0);
			}
			else if (e == 2) {
				cout << "Error : -h参数错误" << endl;
				exit(0);
			}
			else if (e == 3) {
				cout << "Error : -t参数错误" << endl;
				exit(0);
			}
			else if (e == 4) {
				cout << "Error : 没有-w或-c参数" << endl;
				exit(0);
			}
		}
		cout << "----------完成读入参数！----------" << endl;

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "----------开始读取单词列表！----------" << endl;
		cout << "Waiting···" << endl;
		core->fin.open(argv[argc - 1], ios::in);
		core->check_file();
		core->fout.open("./solution.txt", ios::out);
		core->fin.unsetf(ios::skipws);								//取消忽略空白符
		vector<string> str_wordlist = core->read_words(words);
		cout << "列表中共有 " << str_wordlist.size() << " 个单词" << endl;
		cout << "----------完成读取单词列表！----------" << endl;

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "----------开始查找最长链！----------" << endl;
		cout << "Waiting···" << endl;
		if (arg_w.exist) {
			cout << "最长单词链" << endl;
			int length = gen_chain_word(words, int(str_wordlist.size()), result, head, tail, arg_r.exist);
			cout << "最长单词链单词个数为 " << length << endl;
		}
		if (arg_c.exist) {
			cout << "最长字母链" << endl;
			int length = gen_chain_char(words, int(str_wordlist.size()), result, head, tail, arg_r.exist);
			cout << "最长字母链字母个数为 " << length << endl;
		}
		cout << "----------完成查找最长链！----------" << endl;

		cout << endl;
		cout << endl;
		cout << endl;
		cout << "----------开始打印结果！----------" << endl;
		cout << "Waiting···" << endl;
		for (int i = 0; strcmp(result[i], "16061182") != 0; i++) {
			cout << result[i] << " -> " << endl;
			core->fout << result[i] << endl;
		}
		cout << "----------完成打印结果！----------" << endl;

		core->fin.close();
		core->fout.close();
	}
	else if (method == 1) {
		Core *core = new Core();
		/*vector<string> str_wordlist = { "END", "OF", "THE", "WORLD", "TT", "ANT" };
		char *input[10];
		char *output[10];
		for (int i = 0; i < int(str_wordlist.size()); i++) {
			input[i] = (char *)malloc(sizeof(char) * 50);
			strcpy_s(input[i], 50, str_wordlist[i].c_str());
		}*/

		char *input[11] = { (char *)"Algebra",(char *)"Apple",(char *)"Zoo",(char *)"Elephant" ,
		(char *)"Under" ,(char *)"Fox" ,(char *)"Dog" ,(char *)"Moon" ,
			(char *)"Leaf",(char *)"Trick",(char *)"Pm"
		};
		char *output[11];

		int length = gen_chain_word(input, 11, output, 'a', 'n', false);
		cout << "----------开始打印结果！----------" << endl;
		for (int i = 0; strcmp(output[i], "16061182") != 0; i++) {
			cout << output[i] << " -> " << endl;
		}
		cout << "长度为 " << length << endl;
		cout << "----------完成打印结果！----------" << endl;
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
