/*
 * Author : Bidhan Roy
 * Required Headers : <vector>,<algorithm>;
 * Complexity : O (|N|)
 * If you find any bug report at : mail2bidhan@gmail.com
 */

int call(char *inp,char *str,int *F,vector< pair<int,int> > &vec){
    //inp is the actual string
    //str is the modified string with double size of inp
    //F[i] contains the length of the palindrome centered at index i
    //Every element of vec cointains starting and ending positions of palindromes
    int len=0;
    str[len++]='*';
    for(int i=0; inp[i]; i++){
        str[len++]=inp[i];
        str[len++]='*';
    }
    str[len]='\0';
    int c=0,r=0,ans=0;
    for(int i=1; i&lt;len-1; i++){
        int _i=c-(i-c);
        if(r&gt;i) F[i]=min(F[_i],r-i);
        else F[i]=0;
        while(i-1-F[i]&gt;=0 &amp;&amp; str[i-1-F[i]]==str[i+1+F[i]]) {
            F[i]++;
        }
        if(i+F[i]&gt;r) r=i+F[i],c=i;
        ans=max(ans,F[i]);
        vec.push_back(make_pair(i-F[i],i+F[i]));
    }
    return ans;
}
