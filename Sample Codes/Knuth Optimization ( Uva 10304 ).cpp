/*
 * Bidhan Roy
 * University of Dhaka
 * Problem : Uva - 10304 Optimal Binary Search Tree
 */

#include <cstdio>

#define mx 260
#define inf 1<<28

int a[mx];

int dp[mx][mx]; /// contains the optimal costs of intervals
int p[mx][mx]; /// contains the points by partitioning where we can get minimum cost
int sum[mx]; /// contains cumulative sum of the array

int main(){
	int n;
	while( scanf("%d",&n)==1 ){
		for(int i=0; i<n; i++) {
			scanf("%d",&a[i]);
			sum[i]=a[i];
			if(i) sum[i]+=sum[i-1];
		}
		for(int L=1; L<=n; L++){
			for(int i=0; i<n; i++){
				int j=i+L-1;
				if(L==1) dp[i][j]=0, p[i][j]=i; /// if the length is 1, there is only one possible index
				else{
					dp[i][j]=inf;
					for(int k=p[i][j-1]; k<=p[i+1][j]; k++) {
						/// optimal point of interval [i,j] will be between 
						/// the optimal points of intervals
						/// [i,j-1] and [i+1,j]
						int cost=0;
						cost+=dp[i][k-1];
						cost+=dp[k+1][j];
						cost+=sum[j]-sum[k];
						cost+=sum[k-1]-(i?sum[i-1]:0);
						/// 'cost' contains the cost of interval [i,j] if the partition was made
						/// at index 'k'
						if(cost<dp[i][j]) 
							dp[i][j]=cost, p[i][j]=k; /// if 'k' is optimal for now, then store it in p[i][j]
					}
				}
			}
		}
		printf("%d\n",dp[0][n-1]);
	}
	return 0;
}
