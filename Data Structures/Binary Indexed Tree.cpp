template<class T> class binaryIndexedTree{
    vector<T> tree;
    int mV;
    public:
    binaryIndexedTree(){mV=0;}
    binaryIndexedTree(int size){
        tree=vector<T>(size+1);
        mV=size;
    }
    inline void resize(int size){
        tree.clr;
        tree=vector<T>(size+1);
        mV=size;
    }
    inline void upd(int idx,T v=1){
        while(idx<=mV){
            tree[idx]+=v;
            idx+=idx&-idx;
        }
    }
    inline T get(int idx){
        T ret=0;
        while(idx){
            ret+=tree[idx];
            idx-=idx&-idx;
        }
        return ret;
    }
    inline T getS(int idx){
        T ret=tree[idx];
        if(idx){
            int z=idx-(idx&-idx);
            idx--;
            while(idx!=z){
                ret-=tree[idx];
                idx-=idx&-idx;
            }
        }
        return ret;
    }
};
