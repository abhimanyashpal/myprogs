#include<iostream>
#include<unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

//Given a list of words we need to group the anagrams,
/*

Eg: string words[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/

int main (void)
{
    string s1 = "eat";
    string s2 = "atw";
    int ret_val = -1;
    string words[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> s(words, words+ sizeof(words)/sizeof(words[0]));

    unordered_map<string,vector<string> > m;
    unordered_map<string,vector<string> > :: iterator it;
    string t;

    vector<string> tmp_res;
    vector<vector<string> > fin_res;
    vector<string>::iterator iter;
    vector<vector<string> >::iterator row;
    vector<string>::iterator col;

    //Sort the characters in the word and use the sorted
    // string as a key into a map , the value of the map
    // is a vector of strings.
    iter = s.begin();
    while (iter != s.end()) 
    {
        t = *iter;
        sort(t.begin(), t.end());

        (m[t]).push_back(*iter);
        iter++;
    }

    //Now iterate over the map and keep saving the result
    // for each key into the final result which is a vector
    // of string vectors
    it = m.begin();
    while (it != m.end()) {
       t = it->first;
       tmp_res = it->second; // this is a list of strings
       fin_res.push_back(it->second);

       iter = tmp_res.begin();
       while (iter != tmp_res.end()) 
       {
           cout << *iter << " ";
           iter++;
       }
       cout << endl;
       it++;
    }
       

    row = fin_res.begin();
    while (row != fin_res.end())
    {
       col = (*row).begin();
       while (col != (*row).end())
       {
            cout << *col << endl;
            col++;
       }
       cout <<"==========" << endl;
       row++;
    }
}

