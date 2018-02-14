#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<ctype.h>
#include<string>
using namespace std;

fstream g("out.txt", ios::out);
int Hash(string s)
{
	int t = s.size();
	return tolower(s[t - 1]) - 'a';
}

class trie
{

public:
	trie * words[26] = { NULL };
	vector<trie*>links;
	int prob;
	string content;
	trie(string s) 
	{
		content = s;
		prob = 0;
	}
}*prev=NULL,*curr=NULL;
void insert(trie* head[], string parent, int size_of = 1)
{
	string sub;
	if (parent.size() >= size_of)
	{
		sub = parent.substr(0, size_of);
		int t_p = Hash(sub);
		if (head[t_p] == NULL)
			head[t_p] = new trie(sub);
		::curr = head[t_p];
		insert(head[t_p]->words, parent, size_of + 1);
	}
	else
	{
		if (::prev == NULL)
		{
			::prev = ::curr;
		}
		else
		{
			::curr->links.push_back(::prev);
			::prev = ::curr;
		}
		return;
	}
}
void print(trie* words[])
{
	for (int i = 0; i<26; ++i)
	{
		if (words[i] != NULL)
		{
			g<< words[i]->content << endl;
			print(words[i]->words);
			g << "Links:" << endl;
			for (int j = 0; j < words[i]->links.size(); ++j)
			{
				g << words[i]->links[j]->content << ' ';
			}
			g << endl;
		}
		

	}
}


extern "C"
{
	__declspec(dllexport) void test()
	{
		
		trie* head[26] = { NULL };
		fstream f("train.txt", ios::in);
		
		string temp;
		while (!f.eof())
		{
			f>>temp;
			insert(head, temp);
		}
		print(head);
	}
}