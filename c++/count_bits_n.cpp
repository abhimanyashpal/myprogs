#include <iostream>


using namespace std;

/*
 * Count the number of bits set on all
 * numbers from 1 to n
 *
 * We can solve it in O(n) time using DP.
 *
 */

int count_set_bits (int n)
{
    int arr[n+1];
    int idx,i, sum = 0;

    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    arr[0] = 0;
    arr[1] = 1;

    i = 2;
    while (i <= n)
    {
        if (!(i & i-1))
        {
          arr[i] = 1;
        } else {
           idx = (i & (i-1));
           arr[i] = arr[idx] + 1;
        }
        i++;
     }

     i = 0;
     while (i <= n)
     {
        cout << arr[i] << endl;
        sum += arr[i];
        i++;
     }

     return sum;
}

int main (void)
{
    int sum;

    sum = count_set_bits(3);
    cout << "SUM:: " << sum << endl;
    return 0;
}

