"""
Given a string S find out if it can be segmented 
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


def wordbreak(s, words, index):
   n = len(s)
   i = index

   if index == n:
     return True

   print "Index ::" + str(index)
   while i < n:
       j = index
       while j <= i:
           print s[j:i+1]
           if s[j:i+1] in words:
             print "Found " + s[j:i+1]
             ret_val = wordbreak(s,words,i+1)
             if ret_val is True:
               return ret_val

           j += 1
       i += 1

   return False 


s = "leetcode"

words = {"leet":1 , "code":1}
#words2 = {"lee":1,"code":1}

ret = wordbreak(s, words, 0)

print ret
#print wordbreak(s,words)
#print wordbreak(s,words2)
