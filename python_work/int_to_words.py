class Solution:
    def __init__(self):
        self.to19 = 'One Two Three Four Five Six Seven Eight Nine Ten Eleven Twelve Thirteen Fourteen Fifteen Sixteen Seventeen Eighteen Nineteen'.split()
        self.tens = ["Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"]

    def words(self, n):
        if n == 0: return []
        if n < 20:
            return [self.to19[n - 1]]
        if n < 100:
            return [self.tens[n / 10 - 2]] + self.words(n % 10)
        else:
            return [self.to19[n / 100 - 1]] + ['Hundred'] + self.words(n % 100)

    def numberToWords(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "Zero"

        unit = ["", "Thousand", "Million", "Billion"]
        count = 0
        rlst = []
        while num > 0:
            n = num % 1000
            if n != 0:
                tmp = self.words(n)
                if count > 0: tmp = tmp + [unit[count]]
                rlst = tmp + rlst
            num = num / 1000
            count += 1
        return ' '.join(rlst)




s = Solution()
print s.numberToWords(51214)
