int minmove(char *inp,int len){
    int ret=0,l=0,idx=1;
    while(ret+l+1<len && idx<len){
        int cp=inp[ret+l]-inp[(idx+l)%len];
        if(!cp) l++;
        else if(cp<0) idx+=l+1,l=0;
        else ret=max(ret+l+1,idx), idx=ret+1, l=0;
    }
    return ret;
}
