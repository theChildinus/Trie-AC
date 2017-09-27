#include "maptrie.h"
void trie::insert_str(string str)
{
	if (root == NULL || str == "")
		return;
	trie_node* cur_node = root;
	for (int i = 0; i < str.size();)
	{
		int offset = getLength(str[i]);
		string sub = str.substr(i, offset);
		//cout << "sub:" << sub << endl;
		map<string, trie_node*>::iterator iter = cur_node->child.find(sub);

		if (iter == cur_node->child.end())
		{
			trie_node *tmp_node = new trie_node();
			cur_node->child.insert(pair<string, trie_node*>(sub, tmp_node));
			cur_node = tmp_node;
		}
		else
		{
			cur_node = iter->second;
		}
		i += offset;
	}
	cur_node->count++;
}

trie_node* trie::search_str(string str)
{
	if (str == "")
		return root;
	if (root == NULL)
		return NULL;
	
	trie_node* cur_node = root;
	int i;
	for (i = 0; i < str.size();)
	{
		int offset = getLength(str[i]);
		string sub = str.substr(i, offset);
		map<string, trie_node*>::iterator iter = cur_node->child.find(sub);
		if (iter == cur_node->child.end())
		{
			return NULL;
		}
		else
		{
			cur_node = iter->second;
		}
		i += offset;
	}
	if (i == str.size())
	{
		return cur_node;
	}
	else
	{
		return NULL;
	}
}

int trie::getLength(char byte)
{
	int v = byte & 0xff;
	if (v > 0xF0)
		return 4;
	else if (v > 0xE0)
		return 3;
	else if (v > 0xC0)
		return 2;
	return 1;
}


