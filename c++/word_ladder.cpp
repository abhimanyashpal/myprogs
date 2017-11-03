#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

//Transform the word "hit" to "cog" using the wordlist in 
// which we can atmost change 1 letter at a time

// Idea is to use BFS in which pick the starting word and
// test each location in the word by replacing it with
// characters from a to z.
// Example hit can become hot which exists in the word list
// and hence this new word can be considered a neighbor to 
// hit , so we will add this new word to a queue, which is
// the standard method for BFS in a graph.
// Keep testing the words in the queue till we hit the endword
// which we would have added to the wordlist.
// And then return the length

string beginWord = "hit";
string endWord = "cog";

//maintain a set of words
string tmp[] = {"hot","dot","dog","lot","log"};
unordered_set<string> s(tmp, tmp + sizeof(tmp)/sizeof(tmp[0]));

//API takes a word and keeps replacing 1 character at a time
// and checks whether this new word exists in the wordlist
// If it is found then we add the new transformed word to the
// queue and remove him from the wordlist so that we don't end 
// up in a loop.
void test_word_trans (string s, unordered_set<string>& s1, queue<string>& q)
{
  char c = 'a'; char orig;
  unordered_set<string>::iterator fiter, iter;
  int i;

  for (i = 0; i < s.size(); i++) {
	  orig = s[i];
	  //cout <<"Begin ::" << s << endl;
	  for (c = 'a';c <= 'z';c++) {
		  s[i] = c;
		  fiter = s1.find(s);

		  //cout <<"Begin ::" << s << endl;
		  if (fiter != s1.end()) {
			  cout <<"Transformation::" << *fiter << endl;
                          s1.erase(s); //transformed word has been found
                                       // remove him from the wordlist
                          q.push(s);
		  }
	  }
          s[i] = orig;
  }
}
int main (void)
{
  unordered_set<string>::iterator iter;
  queue<string> q;
  string word; int sz = 0;
  int dist = 1;

  s.insert(endWord);

  q.push(beginWord);

  while (!q.empty()) {
          sz = q.size();
	  while (sz) {
		  word = q.front();
		  q.pop();
                  if (word == endWord) {
                    cout << "TRANSFORMATION COMPLETE ::" << dist << endl;
                    return 0;
                  }
		  test_word_trans(word, s,q); //Keeping checking/adding new transformations
                  sz--;
	  }
          //Completion of the above loop indicates we have crossed a level/frontier
          // in BFS and hence increase the dist
          //cout << "DIST ::" << dist << endl; 
          dist++;
  }
#if 1
  iter = s.begin();
  while (iter != s.end()) {
      cout << *iter << endl;
      iter++;
  }
#endif
}


