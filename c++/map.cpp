#include <iostream>
#include <vector>
#include <deque>
#include <map>

using namespace std;

//string s = "abcadcbb";
//string s = "qwnfenpglqdq";
//string s = "aab";
string s= "tmmzuxt";
int max_len = -1;
int res_start = -1;

string
long_uniq_sub (string &s)
{
	map<char, int> m;
	size_t len = s.size();
	int end = 0; int start = 0;
	string res;

	while (end < len) {
		/*
		 * Lookup in the hash map,
		 * if it does not exist then
		 * just add it to the map and 
		 * move on
		 */
		if (m[s[end]] == 0) {
			cout << s[end] << " " <<end <<endl;
			m[s[end]] = end + 1;


			if (end == len -1) {
				if ((end - start + 1) > max_len) {
					cout << "max string found at" <<" start:: "<<start << " end::" << end << endl;
					max_len = end - start + 1;
					res_start = start;
				}
				break;

			}
			end++;
			continue;
		}

		cout << "Element found " << start << " " << end << endl;

		/*
		 * If we are here, that means we have found
		 * a match
		 */

		/*
		 * Although we found the key but we need to check 
		 * if it is in the range of start to end at the moment
		 */
		if (m[s[end]] < start) {
			//update the new locatiom
			m[s[end]] = end+1;

			//double check if we are at the end again
			if (end == len -1) {
				if ((end - start + 1) > max_len) {
					cout << "max string found at" <<" start:: "<<start << " end::" << end << endl;
					max_len = end - start + 1;
					res_start = start;
				}
				break;

			}
			end++;
			continue;
		} 


		if (end - start > max_len) {
			cout << "max string found at" <<" start:: "<<start << " end::" << end << endl;
			max_len = end - start;
			res_start = start;
		}


		if (m[s[end]] > start) {
			start = m[s[end]]; //start is updated only here

			//Update with the next position to start from
			m[s[end]] = end+1;
		}

		end++;

	}

	if (res_start != -1) {
		cout <<"Result :: " << res_start <<" " <<max_len<<endl;
		res = s.substr(res_start, max_len);
	}

	return res;

}

int main (void)
{
	cout << s << endl;
	cout << long_uniq_sub(s);
}
