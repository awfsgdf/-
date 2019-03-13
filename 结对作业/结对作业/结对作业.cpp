// 结对作业.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// E:\git\Software-Engineering\结对作业\Debug\结对作业.exe -w E:\git\Software-Engineering\结对作业\结对作业\Text2.txt
//

#include "pch.h"
#include "interface.h"

using namespace std;



int main(int argc, char *argv[])
{
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
	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	for (int i = 0; i < argc; i++) {
		cout << "第 " << i << " 个参数是 " << argv[i] << endl;
	}
	find_arg(argc, argv, arg_w, arg_c, arg_h, arg_t, arg_r, head, tail);
	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	fin.open(argv[argc - 1], ios::in);
	fout.open("./solution.txt", ios::out);
	fin.unsetf(ios::skipws);								//取消忽略空白符
	vector<string> str_wordlist = read_words();
	bool enable_loop = false;

	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	cout << "开始环路检查" << endl;
	bool loop_acc = check_loop(str_wordlist, enable_loop);
	if (loop_acc) {
		cout << "环路检查正确" << endl;
	}
	else {
		cout << "环路检查错误" << endl;
	}
	cout << "环路检查结束" << endl;
	
	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	cout << "开始创建单词集" << endl;
	for (unsigned int i = 0; i < str_wordlist.size(); i++) {
		words[i] = (char *)malloc(sizeof(char) * 50);		//每个单词限50字符
		strcpy_s(words[i],50, str_wordlist[i].c_str());
		//cout << words[i] << endl;
	}
	cout << "完成创建单词集" << endl;

	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	cout << "开始查找" << endl;
	core->gen_chain_word(words, str_wordlist.size(), result, '0', '0', enable_loop);
	cout << "完成查找" << endl;

	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	cout << "开始打印结果" << endl;
	for (int i = 0; strcmp(result[i],"16061182") != 0; i++) {
		cout << result[i] << " -> " << endl;
	}
	cout << "完成打印结果" << endl;
	
	cout << "----------COYG-COYG-COYG-COYG-COYG-COYG-COYG-COYG----------" << endl;
	cout << "全て終わり" << endl;
	/*gen_chain_char(words, str_wordlist.size(), result, '0', '0', false);
	for (int i = 0; strcmp(result[i], "16061182") != 0; i++) {
		cout << result[i] << " -> " << endl;
	}
	cout << "结束" << endl;*/
	fin.close();
	fout.close();


     
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
