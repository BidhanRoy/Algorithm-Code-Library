/*
 * Author : Bidhan Roy
 * Required Headers : <vector>
 * If you find any bug report at : mail2bidhan@gmail.com
 * Solves equations of the format x % mods[i] = r[i], ( 0<=i<n, where n is the number of equations )
 */

long long CRT(const vector< long long > &r,const vector< long long > &mods){
    long long M=1;
    for(int i=0; i<int(mods.size()); i++) M*=mods[i];
    vector< long long > m, s;
    for(int i=0; i<int(mods.size()); i++){
        m.push_back(M/mods[i]);
        long long temp=m[i]%mods[i];
        long long k=0;
        /* if there is a possibility of k being very big, then prime factorize m[i],
         * find modular inverse of 'temp' of each of the factors
         * 'k' equals to the multiplication ( modular mods[i] ) of modular inverses
         */
        while(true){
            if((k*temp)%mods[i]==1) break;
            k++;
        }
        s.push_back(k);
    }
    long long ret=0;
    for(int i=0; i<int(s.size()); i++) {
        ret+=( (m[i]*s[i])%M *r[i] )%M;
        if(ret>=M) ret-=M;
    }
    return ret;
}
