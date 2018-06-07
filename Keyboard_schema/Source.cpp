#include"stdafx.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<ctype.h>
#include<string>
#include<windows.h>
#include<map>
#include<functional>
#include<algorithm>
#include<sstream>
#include<thread>

using namespace std;
string file_name="train2.txt";
fstream f(file_name, ios::in);
class trie
{
public:
	trie * words[26] = { NULL };
	vector<pair<trie*, int> > links;
	int prob;
	bool complete;
	string content;
	trie(string s)
	{
		content = s;
		complete = false;
		prob = 1;
	}
}*prev = NULL, *curr = NULL;

trie* head[26] = { NULL };
multimap<int, trie*, greater<int>> dict;
vector<trie*>final;

int Hash(string s)
{
	int t = s.size();
	return tolower(s[t - 1]) - 'a';
}
bool compare(pair<trie*, int> a, pair<trie*, int> b)
{
	return(a.second>b.second);
}
void insert(trie* head[], string parent, int type,int size_of = 1)
{
	string sub;
	if (parent.size() >= size_of)
	{
		sub = parent.substr(0, size_of);
		if (!isalpha(sub[sub.size() - 1]))
		{
			::curr = NULL;
		}
		else
		{
			int t_p = Hash(sub);
			if (head[t_p] == NULL)
				head[t_p] = new trie(sub);
			else
			{
				head[t_p]->prob++;
			}
			::curr = head[t_p];
			insert(head[t_p]->words, parent, type, size_of + 1);
		}
	}
	else
	{
		::curr->complete = true;
		/*fstream err("error.txt", ios::out|ios::app);
		err << "Check insert head:" << parent << endl;
		err.close();*/
		if (type)
		{
			fstream g(file_name, ios::out | ios::app);
			g << parent << ' ';
			g.close();
		}
		if (::prev == NULL)
		{
			::prev = ::curr;
		}
		else
		{
			int f = -1;
			fstream err("error.txt", ios::out | ios::app);
			//err << "currentword:" << ::curr->content << endl;
			
			for (int i = 0; i < ::prev->links.size() && f==-1; i++)
			{
				//err << ::curr << ' ' << ::prev->links[i].first << ' ' << ::prev->links[i].first->content << endl;
				if (::curr == ::prev->links[i].first)
					f = i;
			}
			if (f!=-1)
			{
				::prev->links[f].second++;
			}
			else
			{
				::prev->links.push_back(pair<trie*, int>(::curr, 1));
			}
			sort(::prev->links.begin(), ::prev->links.end(), compare);
			::prev = ::curr; 
			err.close();
		}
	}
}
void Print(char *str1, char *str2, char *str3)
{
	int t = (dict.size()<3) ? dict.size() : 3;
	int z = 0, l;
	for (auto it = dict.begin(); z < t; z++, it++)
	{
		if (z == 0)
		{
			strcpy_s(str1, 30, it->second->content.c_str());
		}
		if (z == 1)
		{
			strcpy_s(str2, 30, it->second->content.c_str());
		}
		if (z == 2) 
		{
			strcpy_s(str3, 30, it->second->content.c_str());
		}
		final.push_back(it->second);
	}
	dict.clear();
}

void Sort(trie* words[])
{
	for (int i = 0; i<26; ++i)
	{
		if (words[i] != NULL)
		{
			if (words[i]->complete)
			{
				dict.insert(pair<int, trie*>(words[i]->prob, words[i]));
			}
			Sort(words[i]->words);
		}
	}
}
void search(trie *words[], string s, int start = 0)
{
	int t = (start<s.size()) ? start : -1;
	if (t != -1)
	{
		t = int(s[t] - 'a');
		if (words[t] != NULL)
		{
			if (words[t]->complete)
				dict.insert(pair<int, trie*>(words[t]->prob, words[t]));
			search(words[t]->words, s, start + 1);
		}
	}
	else
	{
		t = int(tolower(s[s.size() - 1]) - 'a');
		Sort(words);
	}
}
void nextword(char *str1, char *str2, char *str3,int choice=0)
{
	::curr = (final.size() != 0) ? final[choice] : ::curr;
	final.clear();
	int t = (::curr->links.size()>3) ? 3 : (::curr->links.size());
	for (int i = 0; i<t; i++)
	{
		if (i == 0)
		{
			strcpy_s(str1, 30, ::curr->links[i].first->content.c_str());
		}
		if (i == 1)
		{
			strcpy_s(str2, 30, ::curr->links[i].first->content.c_str());
		}
		if (i == 2)
		{
			strcpy_s(str3, 30, ::curr->links[i].first->content.c_str());
		}
		final.push_back(::curr->links[i].first);
	}
}
extern "C"
{
	__declspec(dllexport) void init()
	{
		string temp, line;
		while (!f.eof())
		{
			getline(f, line);
			stringstream ls(line);
			::prev = NULL;
			while (ls >> temp)
			{
				insert(head, temp,0);
			}
		}
		fstream g(file_name, ios::out | ios::app);
		g << endl;
		g.close();
	}
	__declspec(dllexport) void Space(const char*prev,char*str1,char*str2,char*str3,int choice)
	{
		insert(head,prev,1);
		nextword(str1,str2,str3,choice);
	}
	__declspec(dllexport) void Search(const char *text, char*str1,char*str2,char*str3)
	{
		string to_search(text);
		search(head, to_search);
		Print(str1,str2,str3);
	}
	__declspec(dllexport) void Enter()
	{
		fstream g(file_name, ios::out | ios::app);
		g << endl;
		::curr = NULL;
		g.close();
	}

}