#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
struct trie_node
{
	int count = 0;
	map<string, trie_node*> child;
};

class trie
{
public:
	trie()
	{
		root = new trie_node();
	}
	~trie() { } 
	void insert_str(string str);
	trie_node* search_str(string str);
	int getLength(char byte);
private:
	trie_node *root;
};