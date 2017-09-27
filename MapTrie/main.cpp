#include "maptrie.h"
#include <time.h>
int main()
{
	trie t;
	clock_t startTime, endTime;
	startTime = clock();

	ifstream pattern_in("pattern.txt");
	if (!pattern_in.is_open())
	{
		cout << "Error opening pattern.txt";
		return 0;
	}
	string buf;
	while (pattern_in >> buf)
	{
		cout << "pattern:" << buf << endl;
		t.insert_str(buf);
	}
	pattern_in.close();

	ifstream string_in("string.txt");
	if (!string_in.is_open())
	{
		cout << "Error opening string.txt";
		return 0;
	}
	while (string_in >> buf)
	{
		cout << "string_in:" << buf << endl;
		if (t.search_str(buf) != NULL)
		{
			cout << "found" << endl;
		}
		else
		{
			cout << "not found" << endl;
		}
	}
	string_in.close();
	endTime = clock();
	cout << "Total Time:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}