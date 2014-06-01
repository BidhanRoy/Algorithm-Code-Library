struct MyQ{
	deque<int> D,Min;
	void push(int val){
        D.push_back(val);
        while(!Min.empty() && Min.back()>val) Min.pop_back();
        Min.push_back(val);
    }
    void pop(){
         if(Min.front()==D.front() )
            Min.pop_front();
         D.pop_front();
    }
    int get(){
		return Min.front();
	}
};
