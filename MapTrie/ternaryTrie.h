#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

struct TSTNode
{
	TSTNode* leftNode = NULL;   //左兄弟节点
	TSTNode* midNode = NULL;    //匹配节点
	TSTNode* rightNode = NULL;  //右兄弟节点
	TSTNode* parent = NULL;		//父节点
	TSTNode* fail = NULL;       //失效节点
	bool isEnd = false;         //模式串结尾标志
	string str = "";			//节点存储字符
};

class ternaryTrie
{
public:
	ternaryTrie() {	root = new TSTNode(); }
	~ternaryTrie() { }
	//构建ternaryTree
	void insert(string& str);
	//验证模式串是否存在
	bool search(string& str);
	//计算树高
	int high(TSTNode* root);
	//计算gb2312编码字符偏移量
	int getLength(char type);
	//根据gb2312比较两个字符大小
	int compareStr(string& str1, string& str2);
	//失效函数
	int buildFailPath();
	//ac自动机搜索函数
	int search_ac(char* str, int &off, FILE* outfile);
	//匹配单个字符
	TSTNode* find_char(TSTNode* p, string& str);
	//输出字符到文件
    void display(TSTNode* root, TSTNode* temp, int i, int& off, FILE* outfile);
	
private:
	//插入模式串到trie树中
	void insert(string& str, int pos, TSTNode*& node, TSTNode*& parent);
	TSTNode* root; // 树的根节点
	int node_count = 0; //trie树节点总数
};
