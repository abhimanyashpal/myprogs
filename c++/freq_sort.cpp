#include<iostream>
#include<unordered_map>
#include <queue>

using namespace std;

//Given a string sort it in the decreasing order of count of characeters
// Eg: tree , result = eert
// Eg: aaccc , result = cccaa

class freq_node
{
    int count;
    unsigned char c;
public:
     freq_node() {}
     ~freq_node() { }

     freq_node(int cnt, char chr)
     {
         count = cnt;
         c = chr;
     }
     int get_count()
     {
        return count;
     }

     unsigned char get_chr()
     {
        return c;
     }

};

class Compare
{
public:
    bool operator() (freq_node x, freq_node y)
    {
         return (x.get_count() < y.get_count());
    }
};


string freq_sort (string s)
{
   freq_node f;
   string res;
   int i;
   unordered_map<unsigned char , int> map;
   unordered_map<unsigned char , int>:: iterator miter;
   int chr_cnt = 0;
   char chr;

   priority_queue<freq_node, vector<freq_node> , Compare> pq;

   i = 0;
   while (i < s.size()) 
   {
      map[s[i]] += 1;
      i++;
   }

   miter = map.begin();
   while (miter != map.end())
   {
       pq.push(freq_node(miter->second, miter->first));
       miter++;
   }

   while (!pq.empty())
   {
       f = pq.top();
       chr_cnt = f.get_count();
       chr = f.get_chr();
       while (chr_cnt > 0) {
           res += chr;
           chr_cnt--;
       }
       pq.pop();
   }

   return res;
}

int main (void)
{
   string s1 = "tree";
   string s2 = "Aabb";
   string s3= "cccaaa";
   string r;

   r = freq_sort(s1);
   cout << "Result::" << r << endl;
   r = freq_sort(s2);
   cout << "Result::" << r << endl;
   r = freq_sort(s3);
   cout << "Result::" << r << endl;
}
