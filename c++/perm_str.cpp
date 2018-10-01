
#include <iostream>
#include <string>
using namespace std;


void
perm_helper(string& s, string& chosen)
{
   int i = 0;
   char c;

    if (s.size() == 0) {
      cout << chosen << endl;
      return;
    }

    for (i = 0; i < s.size(); i++) {

        //Chose a character
        c = s[i];
        s.erase(i,1);
        chosen += c;

        //Explore
        perm_helper(s,chosen);

        //Unchose
        chosen.erase(chosen.length()-1, 1);
        s.insert(i,1, c);
    }
}

int main (void)
{
    string s = "abc";
    string chosen;

    perm_helper(s, chosen);
}
