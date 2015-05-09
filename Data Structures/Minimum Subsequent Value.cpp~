struct MyQ{
    deque<int> D, Min;

    void push(int val) {
	//Pushes in element at the back of Queue
	//Complexity - O(1), amortized

        D.push_back(val);
        
	while(!Min.empty() && Min.back() > val) Min.pop_back();
        
	Min.push_back(val);
    }

    void pop() {
	//Pops an element from the front of Queue
	//Complexity - O(1), amortized
        
	if(Min.front() == D.front())
            Min.pop_front();
         
	D.pop_front();
    }

    int getMin() {
	//Returns minimum of current existing elements of queue
	//Complexity - O(1)

	return Min.front();
    }
};
