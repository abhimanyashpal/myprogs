#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

class Compare {
public:
    bool operator () (int x, int y)
    {
       cout << "X :: " << x << "Y :: " << y << endl;
       return (x > y); // does a greater-than operation and implements min-heap
    }
};

//To create a more generic comparator which can decide min or max heap
class Compare2 {
    bool min_heap;
public:
    Compare2()
    {
       min_heap = 0;
    }
    Compare2(bool t)
    {
       min_heap = t;
    }
    bool operator () (int x, int y)
    {
        if (min_heap) {
            return (x > y); //Equivalent to "greater-than" in the STL
        } else {
            return (x < y);
        }
    }
};

void priority_queue_test (void)
{
    priority_queue<int> mypq; //is basically a max-heap
    //If we want a min-heap then we need to use the keyword "greater"
    priority_queue<int , vector<int> , greater<int> > min_pq;

    priority_queue<int, vector<int>, Compare> cust_pq;
    typedef priority_queue<int , vector<int>, Compare2> cust2_pq_type;
 
    cust2_pq_type cust2_pq(Compare2(true));
    //cust2_pq_type cust3_pq(Compare2(false));
    cust2_pq_type cust3_pq;

    mypq.push(30);
    mypq.push(100);
    mypq.push(25);
    mypq.push(40);

    cout << mypq.top() << endl; // The root of the tree or top of heap

    mypq.push(400);
    cout << mypq.top() << endl; // The root of the tree or top of heap

    cout << "SIZE :: " << mypq.size() << endl;

    mypq.pop();
    cout << "After doing a pop :: " << mypq.top() << endl; // The root of the tree or top of heap
    
    min_pq.push(30);
    min_pq.push(100);
    min_pq.push(25);
    min_pq.push(40);

    cout <<"MIN-HEAP" << endl;
    cout << "Top:: " << min_pq.top() << endl;
    min_pq.push(10);
    cout << "Top:: " << min_pq.top() << endl;
    min_pq.pop();
    cout << "After a pop , Top:: " << min_pq.top() << endl;

    min_pq.push(10);
    cout << "sz :: " << min_pq.size() << endl;
    min_pq.push(10);
    cout << "sz :: " << min_pq.size() << endl;

    //Customer comparator
    cust_pq.push(30);
    cust_pq.push(100);
    cust_pq.push(25);
    cust_pq.push(40);

    cout << "CUSTOM queue::" << endl;
    cout << cust_pq.top() << endl;

    cust2_pq.push(30);
    cust2_pq.push(100);
    cust2_pq.push(25);
    cust2_pq.push(40);
    cout << "CUSTOM-2 queue::" << endl;
    cout << cust2_pq.top() << endl;

    cust3_pq.push(30);
    cust3_pq.push(100);
    cust3_pq.push(25);
    cust3_pq.push(40);
    cust3_pq.push(100);
    cust3_pq.push(100);
    cust3_pq.push(100);
    cout << "CUSTOM-3 queue::" << endl;
    cout << cust3_pq.top() << endl;

    while (!cust3_pq.empty())
    {
        cout << cust3_pq.top() << endl;
        cust3_pq.pop();
    }

}
void vector_test (void)
{
   string str[] = {"abc","efg","hij","lmn"};
   vector<string> s; int i = 0;
   int num_elems = sizeof(str)/sizeof(str[0]);
   vector<string>::iterator iter; 
   vector<string>::iterator fiter; 
   vector<int> v1(3,0); //creating fixed length vector

   cout << "Size::" << v1.size() << endl; 
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
    vector_test();
    //queue_test();
    //map_test();
    //unordered_set_test();
    //priority_queue_test();
}
