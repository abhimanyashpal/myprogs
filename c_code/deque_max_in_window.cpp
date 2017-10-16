#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void test_deque (void)
{
	deque<int> d;
	deque<int>::iterator iter;
	deque<int>::reverse_iterator riter;
	int is_empty;

	d.push_back(10);
	d.push_back(20);
	d.push_front(30);

    //Foward iteration
	iter = d.begin();

	while (iter != d.end()) {
		cout << *iter <<endl;
		iter++;
	}

    cout <<"BACKWARD Iterator" << endl;
	//Backward iteration
	riter = d.rbegin();

	while (riter != d.rend()) {
		cout << *riter << endl;
		riter++;
	}

    //Testing whether it is empty
	is_empty = d.empty();

	cout << is_empty << endl;
}


vector<int>
max_sliding_window (int arr[], int n, int k)
{
	int i = 0;
	vector<int> result;
	deque<int> d;
	deque<int>::iterator iter; //forward iterator
	unsigned int start_of_window = 0;

	/*
	 * Stage-1 , look at the first window and keep
	 * only the relevant indices in the deque.
	 *
	 * The front of the queue will always hold the indice
	 * of the max element in the window
	 */

	for (i = 0; i < k; i++)
	{
		/*
		 * Compare the current element from the back 
		 * of the queue.
		 *
		 * If the element pointed to by the indice at the
		 * back of the queue is smaller than the currect
		 * element then it can never be the largest in the
		 * window and hence get rid of it from the queue.
		 */
		while (!d.empty() && arr[d.back()] < arr[i]) {
			/*
			 * We don't need such elements which are less than the
			 * current element
			 */
			d.pop_back();
		}

		/*
		 * Push my current element indice into the queue
		 */
		d.push_back(i);
	}

#if TESTING
	iter = d.begin();
	while (iter != d.end()) {
		cout << *iter << endl;
		iter++;
	}
#endif

	/*
	 * Stage-2 , look at the rest of the elements.
	 * The first indice in the dequeue is the max
	 * in the current window.
	 *
	 * We will print it and then pop out all the
	 * indices from the the front that would not be
	 * part of the current window
	 */

	for (i = k; i < n; i++) {
		/*
		 * Print the first element
		 */
		result.push_back(arr[d.front()]);

		/*
		 * Compute what would be the start of the window
		 * and remove elements in the deque that are not part
		 * of the start of the window
		 */
		start_of_window = (i - k + 1);

		while (!d.empty() && d.front() < start_of_window) {
			d.pop_front(); //Remove from the front
		}

        // Repeat same procedure as stage-1
		while (!d.empty() && arr[d.back()] < arr[i]) {
			/*
			 * We don't need such elements which are less than the
			 * current element
			 */
			d.pop_back();
		}

		d.push_back(i);
	}

	//Edge case - consider the last window
	result.push_back(arr[d.front()]);

	return result;

}

int main (void)
{
	int arr[] = {22, 15,19, 35,33};
	vector<int> res;
	vector<int>::iterator iter;
	int num = 0;
	//test_deque();

    num = sizeof(arr)/sizeof(int);
	res = max_sliding_window(arr,num, 3);

	iter = res.begin();
	while (iter != res.end()) {
		cout << *iter << endl;
		iter++;
	}

	return 0;
}