void failure(char *p,int *F,int M){
	F[0]=F[1]=0;
	for(int i=2;i<=M;i++){
		int j=F[i-1];
		for(;;){
			if(p[j]==p[i-1]) { F[i]=j+1; break; }
			if(j==0) { F[i]=0; break; }
			j=F[j];
		}
	}  
}
 
int kmp(char *text,char *pat,int *F,int N,int M){
    failure(pat,F,M);
    int i=0,j=0,ret=0;
    for(;;){
        if(j==N) break;
        if(text[j]==pat[i]){
            i++,j++;
            if(i==M) ret++;
        }
        else if(i>0) i=F[i];
        else j++;
    }
    return ret;
}
