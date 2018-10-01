
def print_bin_help(digits, res):
   
   if digits == 0:
     print res
     return

   res.append(0)
   print_bin_help(digits-1,res)
   res.pop()
   res.append(1)
   print_bin_help(digits-1,res)
   res.pop()


def print_bin(digits):
   res = []
   print_bin_help(digits,res)


print_bin(3)

