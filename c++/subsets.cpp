#include <iostream>
#include <vector>


using namespace std;


void
print_list (vector<int>& v)
{
    int i = 0;
    vector<int>::iterator iter;

    cout <<"==========="<<endl;
    iter = v.begin();
    while (iter != v.end()) {
        cout << *iter << endl;
        iter++;
    }
    cout <<"==========="<<endl;
}

void
subset_r (vector<int>& v1, int idx, vector<int>& res, vector<vector<int> >& fin)
{

    if (idx == v1.size()) {
      //print_list(res);
      fin.push_back(res);
      return;
    }

    //2 possibilities , either we don't consider 
    // the element at this index and move on or
    // we consider this element at this index and
    // move on.

    //Don't consider and move on

    subset_r(v1, idx+1, res, fin);
    
    //Consider
    res.push_back(v1[idx]);
    
    subset_r(v1, idx+1, res, fin);
    res.pop_back();
}

int main (void)
{
   int arr[] = {1, 2, 3};
   vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
   vector<int> res,temp_vec;
   vector<vector<int> > fin;
   vector<vector<int> >::iterator row;
   vector<int>::iterator col;

   subset_r(v, 0, res, fin);

   
   row = fin.begin();
   while (row != fin.end()) {
       col = (*row).begin();
       while (col != (*row).end()) {
           cout << *col << endl;
           col++;
       }
       cout << "====="<<endl;
       row++;
   }
}
