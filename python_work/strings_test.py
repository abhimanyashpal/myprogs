
first = "Abhiman"
last = "Karkera"

#Formatting
print "{} {}".format(first,last)


#Splicing

#print indices 1 upto 3 NOT including 3
print first[1:3]

#Print from 3rd indice till end
print first[3:]

#pinrt last 3 characters
print first[-3:]

#leave the last 3 characters
print first[:-3]

#print a substring say characters between 3 and 5
print first[3:5]

print first.capitalize()

#Counts how many times a pattern occurs in the string
print first.count("Ab")

#Searches for the substring in the string
print first.find("man")

#replace all occurrences of a subtring with another pattern
print first.replace("ma","tt")

#splits a string according to a delim
print first.split("i")

#Checks if a string or substring of a string like a sentence has
# words that start with the below pattern
print first.startswith("Ab")


s1 = "leet"
s2 = "leetcode"

#print s2.find("code")

print min(s1)

print s1[0:]

#Extended splice operator , in this we are working backwards in step of 1
print s1[::-1]

s3 = s1[::-1]

s4 = "Hello my name is Abhiman!"

l = s4.split()
print l

for x in l:
	t = x[::-1]
	l[l.index(x)] = t


print "====="
print l

s5 = ""
for x in l:
	s5 += " " + x



print s5[::-1]

