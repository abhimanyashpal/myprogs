#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

void vector_test (void)
{
   string str[] = {"abc","efg","hij","lmn"};
   vector<string> s; int i = 0;
   int num_elems = sizeof(str)/sizeof(str[0]);
   vector<string>::iterator iter; 
   vector<string>::iterator fiter; 

   //Populate the vector
   i = 0;
   while (i < num_elems) {
        s.push_back(str[i]);
        i++;
   }

   //iterating through the vector
   iter = s.begin();
   while (iter != s.end()) {
       cout << *iter <<endl;
       iter++;
   }

   //searching in the vector
   fiter = find(s.begin(), s.end(),"abc");
  

   if (fiter != s.end()) {
       cout << "FOUND ::" << *fiter << endl;
       //erasing an entry from the vector
       s.erase(fiter);
   } else {
       cout <<"NOT FOUND !!!!" << endl;
   }
    
   //iterating through the vector
   iter = s.begin();
   while (iter != s.end()) {
       cout << *iter <<endl;
       iter++;
   }
}

void queue_test (void)
{
    queue<int> q;

    cout <<"Empty:: " << q.empty() << endl;

    q.push(100);
    q.push(200);
    cout <<"Empty:: " << q.empty() << endl;

    cout <<"Front::" << q.front() <<endl;
    cout <<"Back::" << q.back() <<endl;

    cout <<"Popping" << endl;
    q.pop(); //Removes the element from the head
    cout <<"Front::" << q.front() <<endl;
    cout <<"Back::" << q.back() <<endl;
    
    q.push(300);
    q.push(400);
    q.push(500);
    q.push(600);

    cout <<"Size:: " << q.size() <<endl;

    while (!q.empty()) {
        cout << q.front () << endl;
        q.pop();
    }
}

void map_test (void)
{
    map<char, int> m;
    map<char, int>::iterator iter, fiter;

    //Although we have inserted in a random order , the map
    // will be ordered by the key , if we want the same
    // way in which we inserted we can use unordered_map
    // unordered maps are internally implemented as htables.
    m['b'] = 1; 
    m['e'] = 1; 
    m['c'] = 1; 
    m['a'] = 1; 

    iter = m.begin();
    while (iter != m.end()) {
         cout << iter->first <<" " << iter->second <<endl;
         iter++;
    }

    //Checking if something exisits in the map
    cout << m['z'] << endl; //If it does not exist then we will see 0.

    //fiter = m.find('a');
    //fiter = m.find('z');
    fiter = m.find('g');
    if (fiter != m.end()) {
      cout << fiter->first << " " << fiter->second << endl;
    } else {
      //We will never come here , because if a key is not present
      // then the map creates a key with a value of 0.
      //This is because above we have tried to access the key 'z'
      cout << "Not present" << endl;
    }

    //Remove a element from a map
    m.erase('a');

    cout <<"After erasing" << endl;
    iter = m.begin();
    while (iter != m.end()) {
         cout << iter->first <<" " << iter->second <<endl;
         iter++;
    }
}

void unordered_set_test (void)
{
    string tmp[] = {"red","green","blue"};
    unordered_set<string> s (tmp, tmp+ sizeof(tmp)/sizeof(tmp[0]));
    unordered_set<string>::iterator iter, fiter;

    iter = s.begin();
    while (iter != s.end()) {
        cout << *iter << endl;
        iter++;
    }

    //Search
    fiter = s.find("red");
    if (fiter != s.end()) {
        cout << "FOUND ::" << *fiter << endl;
    } else {
        cout << "NOT FOUND" << endl;
    }

    //removing an entity from the set
    s.erase(fiter);

    cout << "After erasing....." << endl;
    iter = s.begin();
    while (iter != s.end()) {
        cout << *iter << endl;
        iter++;
    }

    //occurenes in a set - since set has unique elements
    //this count will always be 1 and hence we can use
    // to test the presence of a string in a set.
    cout << s.count("blue") << endl;
}

int main (void)
{
    //vector_test();
    //queue_test();
    //map_test();
    unordered_set_test();
}
