#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

/*
 * Given a list of words we need to print out the 'k' most frequent occuring
 * words in the list.
 *
 *
 * We need to use both map and heap to solve this.
 */


//Node to maintain reverse mapping of count --> string
class freq_node {
    int count;
    string s;
public:
     freq_node() {}
     freq_node(int c , string str)
     {
         count = c;
         s = str;
     }
     void set_str (string str)
     {
         s = str;
     }
     void set_count(int c)
     {
         count = c;
     }
     int get_count(void)
     {
         return count;
     }
     string& get_str()
     {
         return s;
     }
};

//Custom comparator for the priority queue
class Compare {
public:
    bool operator() (freq_node& x, freq_node& y)
    {
       return (x.get_count() < y.get_count());  //less-than implements a max-heap
    }
};

int main (void)
{
    string words[] = {"i", "love", "leetcode", "i", "love", "coding"};
    vector<string> s(words,words + sizeof(words)/sizeof(words[0]));
    vector<string> :: iterator iter;
    unordered_map<string, int> map;
    unordered_map<string, int> :: iterator miter; 
    priority_queue<freq_node, vector<freq_node>, Compare> pq;
    freq_node f;
    int k;

    cout << s.size() << endl;

    //Throw all the words into the map

    iter = s.begin();
    while (iter != s.end())
    {
       map[*iter] += 1;
       iter++;
    }

    //Debug code to check the map if it is correct
    miter = map.begin();
    while (miter != map.end())
    {
       cout << miter->first << " " << miter->second << endl;
       miter++;
    }

    //All good , now throw them into a max-heap based on the frequency count.
    // create a structure which tracks the count --> string relation
    miter = map.begin();
    while (miter != map.end())
    {
       cout << miter->first << " " << miter->second << endl;

       //keep pushing our node into the pq and this will
       // invoke our custom comparator
       pq.push(freq_node(miter->second, miter->first));
       miter++;
    }

    cout << "Enter k :: ";
    cin >> k;

    cout << "DUMPING HEAP....." << endl;
    while (!pq.empty() && k > 0) {
	    f = pq.top(); 
	    cout << f.get_str() <<  "::" << f.get_count() << endl;
	    pq.pop();
            k--;
    }
}
