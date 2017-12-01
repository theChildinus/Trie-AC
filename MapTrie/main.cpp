#include "ternaryTrie.h"
#include <time.h>
////////////////////////////////////////////////////////////////////////////////////////
//本程序模式串文本文件pattern.txt建立三叉trie树，然后匹配字符文件string.txt存在的模式串,///
//将匹配到的模式串和文件偏移量输出到result.txt文件，使用编码为中文gb2312                ///
//linux下命令格式为./strsearch string.txt pattern.txt result.txt                      ///
////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	ternaryTrie tt; //定义一个三叉树类
	clock_t startTime, endTime;
	startTime = clock();

	ifstream pattern_in(argv[2]); //文件读入流
	if (!pattern_in.is_open())
	{
		printf("Error opening pattern file\n");
		return 0;
	}
	printf("----- START -----\n");
	string pbuf;
	while (pattern_in >> pbuf)
	{
		tt.insert(pbuf);       //按行插入模式串,构建一棵三叉trie树
	}
	pattern_in.close();        //关闭输入流
	printf("---BUILD ternaryTrie FINISH---\n");
	endTime = clock();
	printf("Used Time:%.2fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	tt.buildFailPath();        //构建三叉trie树的每个节点的失效路径
	printf("---BUILD failpath FINISH---\n");
	FILE *string_in;           //string.txt文件读入指针
	if (!(string_in = fopen(argv[1], "r")))    //打开文件
	{
		return -1;
	}
	FILE *result_out;         //string.txt文件写入指针
	if (!(result_out = fopen(argv[3], "w+")))
	{
		return -1;
	}
	printf("----- START SEARCH ------\n");
	int line_num = 1;
	int off = 0;
	char buf[8192];         //字符缓冲区
	while (!feof(string_in))
	{
		memset(buf, 0x0, sizeof(buf));
		fgets(buf, sizeof(buf), string_in);          //读入字符到缓冲区
		tt.search_ac(buf, off, result_out);          //对缓冲区内的字符逐个匹配，并将匹配到的关键字输出到文件
		off += strlen(buf);                  //记录文件当前偏移量
		line_num++;
	}
	printf("line: %d\n", line_num);
	//tt.ans2File(result_out);
	fclose(string_in);             //释放文件读入指针
	fclose(result_out);            //释放文件写入指针
	printf("----- END SEARCH ----\n");
	endTime = clock();
	printf("Total Time:%.2fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	system("pause");
}
