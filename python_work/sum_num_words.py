



def add_num_in_words (str):
   tmp = []
   length = len(str)
   res = 0

   for i in range(0,length):
      diff = ord(str[i]) - 48

      if diff >= 0 and diff <= 9:
        print str[i],ord(str[i])
        tmp.append(str[i])
      else:
        #print tmp
        t = ''.join(tmp)
        #print t,len(t)
        if len(t) != 0:
          print t
          res = res + int(t)
        tmp = []


   print "Result::",res
      


add_num_in_words("abcd123sssss10xxx12A")


print "==================="
#s = ''.join(z)

#print int(s) + 100
#print int(x)+y
