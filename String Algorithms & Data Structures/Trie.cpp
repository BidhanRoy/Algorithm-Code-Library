struct Trie{
	Trie *next[alphabet+1];
	
	Trie(){ for(int i=0; i<=alphabet; i++) next[i]=NULL; }
	~Trie(){ for(int i=0; i<=alphabet; i++) delete(next[i]); }
	
	void insert(char *str){
		/// inserting character array
		Trie *curr=this;
		for(int i=0; str[i]; i++){
			if(!curr->next[str[i]-'a'])
				curr->next[str[i]-'a']=new Trie;
			curr=curr->next[str[i]-'a']; 
			/// assuming, all the letters are in lowercase, 
			/// needs to be changed if otherwise
		}
		if(!curr->next[alphabet]) curr->next[alphabet]=new Trie;
	}
	
	bool find(char *str){
		/// returns 'true' is string 'str' has been inserted in the trie
		/// returns 'false' otherwise
		Trie *curr=this;
		for(int i=0; str[i]; i++){
			if(!curr->next[str[i]-'a']) return false;
			curr=curr->next[str[i]-'a'];
		}
		return curr->next[alphabet];
	}
};
