#include "stdafx.h"
/*#include<stdio.h>
#include<iostream>
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
//int i=0;
class trie
{

public:
	trie * words[26] = { NULL };
	int prob;
	int id;
	string content;
	trie(string s)
	{
		content = s;
		prob = 0;
	}
};
void insert(trie* head[], string parent, int size_of = 1)
{
	string sub;
	if (parent.size() >= size_of)
	{
		sub = parent.substr(0, size_of);
		int t_p = Hash(sub);
		if (head[t_p] == NULL)
			head[t_p] = new trie(sub);
		insert(head[t_p]->words, parent, size_of + 1);
	}
}
void print(trie* words[])
{
	for (int i = 0; i<26; ++i)
	{
		if (words[i] != NULL)
		{
			g << words[i]->content << endl;
			print(words[i]->words);
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
			f >> temp;
			insert(head, temp);
		}
		print(head);
	}
}*/
/*#include<stdio.h>
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
bool full;
string content;
trie(string s)
{
content = s;
full = false;
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
::curr->full = true;
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
if (words[i] != NULL )
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
}*/
/* 
***********LATEST SUCCESSFUL BUILD
#include"stdafx.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<ctype.h>
#include<string>
#include<windows.h>
#include<algorithm>
using namespace std;
fstream g("out.txt", ios::out);
int Hash(string s)
{
int t = s.size();
return tolower(s[t - 1]) - 'a';
}
//int i=0;
class trie
{

public:
trie * words[26] = { NULL };
vector<trie* >links;
int prob;
bool complete;
string content;
trie(string s)
{
content = s;
complete = false;
prob = 0;
}
}*prev = NULL, *curr = NULL;
trie* head[26] = { NULL };
bool compare(trie* a, trie* b)
{
return (a->prob>b->prob);
}
void insert(trie* head[], string parent, int size_of = 1)
{
//cout<<parent;
string sub;
if (parent.size() >= size_of)
{
sub = parent.substr(0, size_of);
int t_p = Hash(sub);
if (head[t_p] == NULL)
head[t_p] = new trie(sub);
head[t_p]->prob++;
::curr = head[t_p];
insert(head[t_p]->words, parent, size_of + 1);
}
else
{
::curr->complete = true;
if (::prev == NULL)
{
::prev = ::curr;
}
else
{
::prev->links.push_back(::curr);
sort(::prev->links.begin(), ::prev->links.end(), compare);
::prev = ::curr;
}
//cout<<::curr->content<<' '<<::prev->content<<endl;
return;
}
}
void nextword()
{
for (int j = 0; j<::curr->links.size() && j<3; ++j)
{
cout << ::curr->links[j]->content << ' ';
}
cout << endl;
}
void print(trie* words[])
{
for (int i = 0; i<26; ++i)
{
if (words[i] != NULL)
{
if (words[i]->complete)
{
cout << words[i]->content << endl;
/*cout<<"****links********"<<endl;
for(int j=0;j<words[i]->links.size();++j)
{
cout<<words[i]->links[j]->content << ' ';
}
cout<<endl;*/
//::curr = words[i];
//			}
//			print(words[i]->words);
//			/*cout << "Links:" << endl;
//			for (int j = 0; j < words[i]->links.size(); ++j)
//			{
//			cout<< words[i]->links[j]->content << ' ';
//			}
//			cout<<endl;*/
//		}
//	}
//}
//void search(trie *words[], string s, int start = 0)
//{
//	int t = (start<s.size()) ? start : -1;
//	if (t != -1)
//	{
//		t = int(s[t] - 'a');
//		if (words[t] != NULL)
//		{
//			if (words[t]->complete)
//				cout << words[t]->content << endl;
//			search(words[t]->words, s, start + 1);
//		}
//		else
//		{
//			insert(words, s, start);
//		}
//	}
//	else
//	{
//		t = int(s[s.size() - 1] - 'a');
//		print(words);
//	}
//
//}
//void dummy()
//{
//
//
//	/* //print(head);
//	cout << "*************" << endl;
//	string t = "";
//	if (t == " ")
//	nextword();
//	cout << "*******" << t << endl;
//	search(head, t);
//	cout << "*******" << endl;
//	Sleep(40);
//	system("cls");
//	//}*/
//}
//
//extern "C"
//{
//	__declspec(dllexport) void init()
//	{
//		fstream f("train.txt", ios::in);
//		string temp;
//		while (!f.eof())
//		{
//			f >> temp;
//			insert(head, temp);
//		}
//	}
//	__declspec(dllexport) void test(const char *str)
//	{
//
//		//trie* head[26] = { NULL };
//		//fstream f("train.txt", ios::in);
//		init();
//		string temp(str);
//		//cout << temp;
//		search(head, temp);
//	}
//}
//
//*/