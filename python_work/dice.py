


def dice_helper(n, res):
   if n == 0:
     if sum(res) == 6:
       print res
     return

   for i in range(1,7):
      res.append(i);
      dice_helper(n-1, res)
      res.pop()


res = []
dice_helper(2,res)
