#include "ternaryTrie.h"
//构建ternaryTree
void ternaryTrie::insert(string& str) 
{
	if (str == "")       //空字符返回
		return;
	insert(str, 0, root->midNode, root);

	//左右子树置为根节点的左右子树，便于遍历树
	if (root->midNode->leftNode != NULL)
		root->leftNode = root->midNode->leftNode;

	if (root->midNode->rightNode != NULL)
		root->rightNode = root->midNode->rightNode;

	root->parent = root;   //根节点的父节点指向自己，遍历是避免访问空指针
}

void ternaryTrie::insert(string& str, int pos, TSTNode*& node, TSTNode*& parent)
{
	int offset = getLength(str[pos]);			//gb2312偏移量
	string curChar = str.substr(pos, offset);   //取得字符
	if (node == NULL)						    //当前节点为空，添加字符到该节点
	{
//		cout << curChar << endl;
		node = new TSTNode();        //生成新的树节点
		node->str = curChar;
		node_count++;                //计算树的总节点
		if ((node == parent->leftNode) || (node == parent->rightNode)) //若节点插在node的左右子树，父节点为node的父节点
		{
			node->parent = parent->parent;
		} 
		else 
		{
			node->parent = parent;   //若节点插在node的中间子树，父节点为node
		}
	}
	if (compareStr(curChar, node->str) < 0)	 //当前字符小于节点字符 在左兄弟节点插入
		insert(str, pos, node->leftNode, node);
	else if (compareStr(curChar, node->str) > 0) //当前字符大于节点字符 在右兄弟节点插入
		insert(str, pos, node->rightNode, node);
	else									//当前字符等于节点字符 在中间节点插入
	{
		if (pos + offset == str.size())       //若字符都插入完毕，最后一个节点是终点节点
			node->isEnd = true;
		else
			insert(str, pos + offset, node->midNode, node);   //若还有字符没有插入树，取下一个字符插入
	}
}

//验证模式串是否存在
bool ternaryTrie::search(string& str) 
{
	if (str == "" || root == NULL)
		return false;

	TSTNode *curNode = root->midNode;
	int pos = 0;
	cout << str << endl;
	while (curNode != NULL)
	{
		int offset = getLength(str[pos]);
		string curChar = str.substr(pos, offset);
		if (curChar < curNode->str)
			curNode = curNode->leftNode;
		else if (curChar > curNode->str)
			curNode = curNode->rightNode;
		else 
		{
			if (pos + offset == str.size())
				return curNode->isEnd;
			{
				pos += offset;
//				cout << curChar << endl;
				curNode = curNode->midNode;
			}
		}
	}
	return false;
}
//计算树高
int ternaryTrie::high(TSTNode* root)
{
	int Hl = 0;
	int Hm = 0;
	int Hr = 0;
	int Max = 0;
	if (root)
	{
		Hl = high(root->leftNode);
		Hm = high(root->midNode);
		Hr = high(root->rightNode);
		int tmp = max(Hl, Hm);
		Max = max(tmp, Hr);
		return Max + 1;
	}
	else return 0;
}

//计算gb2312编码字符偏移量
int ternaryTrie::getLength(char byte) 
{
	int v = byte & 0xFF;
	if (v < 0x81) //字节小于81H 代表单字节字符 
		return 1;
	else          //字节大于等于81H 代表双字节字符
		return 2;
}
//根据gb2312比较两个字符大小
int ternaryTrie::compareStr(string& str1, string& str2)
{
	short a, b;
	if (str1.size() == 2)
		a = (str1[0] << 8) + str1[1];
	else
		a = str1[0];

	if (str2.size() == 2)
		b = (str2[0] << 8) + str2[1];
	else
		b = str2[0];

	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}
//构建每一个节点的失效路径
int ternaryTrie::buildFailPath() 
{
	if (root == NULL)
		return -1;
	root->fail = NULL;
	queue<TSTNode*> myQueue1;    //队列1遍历当前层所有节点
	queue<TSTNode*> myQueue2;    //队列2保存当前节点的孩子节点
	myQueue1.push(root);
	while (!myQueue1.empty()) 
	{
		TSTNode* tmp = myQueue1.front();  //取队头节点
		myQueue1.pop();
		if (tmp == root) //将根节点的左右节点失效指针指向root,并将根节点中间节点入队列1
		{
			if (tmp->leftNode)
				tmp->leftNode->fail = root;
			if (tmp->midNode)
				tmp->midNode->fail = root;
			if (tmp->rightNode)
				tmp->rightNode->fail = root;
			myQueue1.push(root->midNode);
		} 
		else //若当前节点不是根节点
		{
			TSTNode* p = tmp->parent->fail; //临时指针指向父节点的失效节点
			while (p != NULL) //若不为空，查找临时指针指向节点是否有与当前节点相同的字符节点
			{
				TSTNode* t = find_char(p->midNode, tmp->str);
				if (t) 
				{
					tmp->fail = t;   //若找到，当前节点的失效指针指向找到的节点
					break;
				}
				p = p->fail;     //若没有找到，沿着临时节点的失效路径继续找
			}
			if (p == NULL)    //若临时节点为空，则当前节点的失效指针指向root
				tmp->fail = root;
		}
		if (tmp != root) 
		{
			if (tmp->leftNode != NULL)
				myQueue1.push(tmp->leftNode);
			if (tmp->rightNode != NULL)
				myQueue1.push(tmp->rightNode);
			if (tmp->midNode != NULL)
				myQueue2.push(tmp->midNode);
		}
		if (myQueue1.empty()) 
		{
			while (!myQueue2.empty()) 
			{
				myQueue1.push(myQueue2.front());
				myQueue2.pop();
			}
		}
	}
	root->fail = root;
	printf("nodeCount:%d\n", node_count);
	int h = high(root);
	printf("Height:%d\n", h);
	return 0;
}
//从当前节点查找是否与当前字符匹配的子节点
TSTNode* ternaryTrie::find_char(TSTNode* p, string& str) 
{
	if (p == NULL)
		return NULL;
	while (true)
	{
		int ret = compareStr(str, p->str);
		if (ret < 0 && p->leftNode)
			p = p->leftNode;
		else if (ret > 0 && p->rightNode)
			p = p->rightNode;
		else if (ret == 0)
			return p;
		else
			return NULL;
	}
}
//输出终结字符节点代表的模式串到result文件
void ternaryTrie::display(TSTNode* root, TSTNode* temp, int i, int& off, FILE* outfile)
{
	stack<TSTNode*> mystack;  //从当前节点沿着父节点指针遍历到根节点
	while (true)
	{
		if (temp == root)
		{
			break;
		}
		mystack.push(temp);
		temp = temp->parent;
	}
	string str = "";
	while (!mystack.empty()) //从根节点到终结字符节点，输出路径遍历到的字符
	{
		str = str + mystack.top()->str;
		int offset = getLength((mystack.top()->str)[0]);
		i -= offset;
		mystack.pop();
	}
	fprintf(outfile, "%s %d\n", str.c_str(), i + off);  //把所得的模式串及位置写入result文件
}
//ac自动机的搜索函数，根据匹配字符串寻找匹配关键字，并将结果写入结果文件
int ternaryTrie::search_ac(char* str, int &off, FILE* outfile)
{
	if (root == NULL && root->midNode)
		return -1;
	TSTNode* curNode = root;    //从根节点开始匹配
	int len = strlen(str);
	for (int i = 0; i < len;) 
	{
		int offset = getLength(str[i]);   //计算当前字符所在字节，中文为2字节，英文为1字节
		char t[3] = {0};
		if (offset == 2)
		{
			t[0] = str[i];
			t[1] = str[i + 1];
		}
		else 
		{
			t[0] = str[i];
		}
		string sub(t);  //取得当前字符，并转换为string类
		TSTNode* tmp = find_char(curNode->midNode, sub);  //从当前节点查找是否与当前字符匹配的子节点
		if (tmp) 
		{
			curNode = tmp;
			TSTNode* back = tmp;
			if (curNode->isEnd == true)  //若找到节点，并且节点是终结字符，输出模式串到结果文件
			{
				display(root, curNode, i + offset, off, outfile); //输出模式串到结果文件
			}
			while (back != root)  //若找到的节点不是根节点，沿着找到的节点的失效路径遍历，若找到终结字符，输出字符
			{
				back = back->fail;
				if (back->isEnd == true)
				{
					display(root, back, i + offset, off, outfile);
				}
			}
			i += offset;
		} 
		else 
		{
			if (curNode == root)
				i += offset;
			else 
				curNode = curNode->fail;
		}
	}
	while (curNode != root)
	{
		curNode = curNode->fail;
		if (curNode->isEnd == true)    //处理完匹配串,清空ac自动机状态
		{
			display(root, curNode, len, off, outfile);
		}
	}
	return 0;
}
