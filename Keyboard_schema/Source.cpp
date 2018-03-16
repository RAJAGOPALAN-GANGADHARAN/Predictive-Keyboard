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
using namespace std;

fstream f("train.txt", ios::in|ios::out);
//multimap<int,string,greater<int>> link_next;
//multimap<int,string> ::iterator it;
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
bool compare(pair<trie*, int> a, pair<trie*, int> b)
{
	return(a.second>b.second);
}
void insert(trie* head[], string parent, int size_of = 1)
{
	string sub;
	if (parent.size() >= size_of)
	{
		sub = parent.substr(0, size_of);
		int t_p = Hash(sub);
		if (head[t_p] == NULL)
			head[t_p] = new trie(sub);
		else
		{
			head[t_p]->prob++;
		}
		::curr = head[t_p];
		//cout<<::curr->content<<endl;
		insert(head[t_p]->words, parent, size_of + 1);
	}
	else
	{
		::curr->complete = true;
		//cout<<::curr->content<<" "<<::curr->point<<" "<<::curr->prob<<endl; 
		if (::prev == NULL)
		{
			::prev = ::curr;
		}
		else
		{
			int f = 0;
			for (int i = 0; i<::prev->links.size(); i++)
			{
				if (::curr->content == ::prev->links[i].first->content)
				{
					f = i;
					break;
				}
			}
			if (f)
			{
				::prev->links[f].second++;
			}
			else
			{
				::prev->links.push_back(pair<trie*, int>(::curr, 1));
			}
			sort(::prev->links.begin(), ::prev->links.end(), compare);
			::prev = ::curr;
			//return;
		}
	}
}
vector<trie*>final;
void Print( char *str1, char *str2, char *str3)
{
	int t = (dict.size()<3) ? dict.size() : 3;
	int z = 0,l;
	for (auto it = dict.begin(); z < t; z++, it++)
	{
		//l = Hash(it->second->content);
		cout << it->second<<endl;
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
				dict.insert(pair<int,trie*>(words[i]->prob, words[i]));
				//::curr=words[i];
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
				cout << words[t]->content << endl;
			::curr = words[t];
			search(words[t]->words, s, start + 1);
		}
		else
		{
			insert(words, s, start);
			f << s <<' ';
		}
	}
	else
	{
		t = int(s[s.size() - 1] - 'a');
		Sort(words);
	}

}
void nextword(char *str1, char *str2, char *str3,int choice=0)
{
	cout << "Check:"<<::curr->content << endl;
	::curr = final[choice];
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
		//cout << ::curr->links[i].first->content << ' ' << ::curr->links[i].second << endl;
	}
}
void dummy()
{
	insert(head, "rushvi");
	insert(head, "hi");
	insert(head, "rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	insert(head, "junnuri");
	insert(head, "rushvi");
	insert(head, "cool");
	insert(head, "rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	//insert(head,"rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	insert(head, "raj");
	insert(head, "rushvi");
	insert(head, "cool");
	insert(head, "rushvi");
	insert(head, "cool");
	insert(head, "rushvi");
	insert(head, "shah");
	insert(head, "rushvi");
	insert(head, "shah");
	insert(head, "rushvi");
	insert(head, "shah");
	insert(head, "rushvi");
	cout << "*************" << endl;
	string t = "";
	while (1)
	{
		cin >> t;
		if (t == "space")
		{
			cout << "******* " << ::curr->content << endl;
			//nextword();
		}
		else
		{
			cout << "******* " << t << endl;
			search(head, t);
			cout << endl << "*******" << endl;
			//Print();
		}
		Sleep(2040);
		system("cls");
	}

}
extern "C"
{
	__declspec(dllexport) void init()
	{
		
		string temp;
		while (!f.eof())
		{
			f >> temp;
			insert(head, temp);
		}
		
	}
	__declspec(dllexport) void test(const char *str,
		char *str1, char *str2, char *str3,int choice=0
	)
	{
		string temp(str);	
		if (temp == " ")
			nextword(str1, str2, str3,choice);
		else
		{
			search(head, temp);
			Print(str1, str2, str3);
		}
	}
}