//Leetcode problem - 379

class PhoneDirectory {
public:
    unordered_map<int,int> m;
    queue<int> free_stack; //Can be stack as well , depending of what policy is followed to return numbers
    
    
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        int i = 0;
        
        while (i < maxNumbers)
        {
            //mark all as available
            m[i] = 1;
            
            //push them to a stack
            free_stack.push(i);
            
            i++; 
        }
        
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        
        int val = -1;
            
        //If stack is empty no more numbers are available.
        if (free_stack.empty())
            return -1;
        
        //Pop the next available number
        val = free_stack.front();
        free_stack.pop();
        
        //mark as used
        m[val] = 0;
        
        return val;  
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        
        //Check its status in the hash table.
        if (m[number] == 0)
            return false;
        
        return true;
        
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        
        if (m[number] != 0)
            return;
        
        //push it back to the stack
        free_stack.push(number);
        m[number] = 1;  
    }
};
