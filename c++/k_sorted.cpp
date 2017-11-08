#include<iostream>
#include<vector>
#include<queue>

using namespace std;

/*
 * Merge k sorted arrays 
 */

/*
 * The K arrays will be in the form of a matrix
 * We will create a node per element which will
 * have the value , an id corresponding to the array
 * and the next index in the array that we need to 
 * consider
 */
class node {
    int val;
    int id;
    int next_idx;

public:
    node() {}

    node (int v, int i , int n)
    {
        val = v; id = i; next_idx = n;
    }

    int get_val(void) { return val;}
    int get_id(void) { return id;}
    int get_next_idx(void) { return next_idx;}
};

class Compare {
public:
    bool operator() (node x , node y)
    {
        return (x.get_val() > y.get_val()); //min-heap 
    }
};


int main (void)
{
    vector<int> tmp;
    vector<vector<int> > v;
    vector<int> result;
    priority_queue<node, vector<node> , Compare> pq;
    int k = 3; // indicates the lists
    int id, val, idx , i;
    node n;

    //First list
    tmp.push_back(1);
    tmp.push_back(3);
    tmp.push_back(5);
    v.push_back(tmp);

    //Second list
    tmp.clear();
    tmp.push_back(2);
    tmp.push_back(4);
    v.push_back(tmp);

    //Third list
    tmp.clear();
    tmp.push_back(3);
    tmp.push_back(7);
    tmp.push_back(7);
    tmp.push_back(7);
    v.push_back(tmp);

    //lets push the first element from each of the
    // k rows to a heap
    for (i = 0; i < k; i++) {
       pq.push(node(v[i][0], i, 1));
    }

    // Now since this is a min-heap the top
    // of the heap will have the minimum node
    while (!pq.empty())
    {
       n = pq.top();
       pq.pop();

       val = n.get_val();
       id  = n.get_id();
       idx = n.get_next_idx();
       //cout << "Val::" << val << " " << "ID::" << id <<  " " <<"Next ::" << idx << endl;
       result.push_back(val);

       //Nothing more to look at from this array/row and hence proceed further.
       if (v[id].size() == idx)
           continue;

       //push another element into the heap
       pq.push(node(v[id][idx],id, idx+1));
       
     }


     i = 0;
     while (i < result.size())
     {
         cout << result[i] << endl;
         i++;
     }

       
    return 0;
}

    
