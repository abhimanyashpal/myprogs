#include <iostream>
#include <vector>

using namespace std;

/*
 * Find the kth largest element in a unsorted array.
 *
 * One approach is to sort the array and then index
 * it using k. However we will take atleast O(nlogn) time
 *
 * Instead of that we employ the similar technique used in
 * quicksort in which we keep partitioning the array around
 * a pivot.
 */
unsigned int 
partition (vector<int> &v, int start, int end)
{
   int pidx = start;
   int i,temp;
   int pivot = v[end];

   for (i = start; i < end; i++)
   {
      if (v[i] <= pivot) {
          temp = v[i];
          v[i] = v[pidx];
          v[pidx] = temp;
          pidx++;
      }
   }

   temp = v[end];
   v[end] = v[pidx];
   v[pidx] = temp;

   return pidx;
}

int k_large_rec(vector<int> &v, int start, int end, int target)
{
    int pidx;

    if (start > end)
        return -1;

    pidx = partition(v, start, end);

    if (pidx == target)
        return v[pidx];

    if (pidx > target)
        return k_large_rec(v, start, pidx-1, target);

    return k_large_rec(v, pidx+1, end, target);
}

    

int main (void)
{
    int arr[] = {3,2,1,5,6,4};
    int k = 1; int target_idx;
    int res;
    vector<int> v(arr, arr+sizeof(arr)/sizeof(arr[0]));


    if (k > v.size() || k == 0)
        return -1;

    target_idx = v.size() - k;

    res = k_large_rec(v, 0, v.size()-1, target_idx); 

    cout << "k :: " << k << "res ::" << res << endl;
    return 0;
}
