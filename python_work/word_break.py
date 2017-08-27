"""
Give a string S find out if it can be segmented 
to the words present in a dictionary

S = "leetcode"

d = {"leet":1, "code":1}

Ans : True

d = {"lee":1,"code":1}

Ans: False , since the character "t" could not be associated with any word

Idea is we generate all the substrings and perform a lookup in  a hash set,
if it is found we recursively perform the test for the rest of the string 
and if all return true then everything is fine.

The above in regular recursion would be exponential time 2^len , we can use
DP to solve in n^2
"""


def wordbreak(s, words):
	n = len(s)

	#Create a dp array, one more than the length of the string 
	dp = (n+1) * [False]

	dp[0] = True #A word with 0 characters and empty dictionary is always true

	#Iterate through the letters in the string, we go to n+1 to include the last character
	for i in range(1,n+1):
		#Go through the substrings
		for j in range(0,i):
			if dp[j] and s[j:i] in words:
				dp[i] = True


	#The last entry in the array is the solution, by doing negative 1 it returns
	# the last element , if we did -2 then it would return the second last element
	# so on a so forth

	return dp[-1]


s = "leetcoder"

words = {"leet":1 , "code":1}
words2 = {"lee":1,"code":1}

print wordbreak(s,words)
print wordbreak(s,words2)