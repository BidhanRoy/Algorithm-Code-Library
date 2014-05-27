/* Author : Bidhan Roy
 * Complexity : O (Nlog(N))
 * Handles Collinear points and duplicate points
 * Report at `mail2bidhan@gmail.com` if you find any buf
 */


point p0;
bool comp(point a,point b){
    i64 d=area(p0,a,b);
    if(d<0) return false;
    if(d) return true;
    return sqDist(p0,a)<sqDist(p0,b);
}
void convex(vector<point> &points,vector<point> &ans){
    int pos=0;
    rep(i,sz(points))
    if(points[pos].y>points[i].y || (points[pos].y==points[i].y && points[pos].x>points[i].x)) pos=i;
    p0=points[pos];
    sort(all(points),comp);
    int i=0;
    while(p0==points[i]) {
        i++;
        if(i==sz(points)) return ;
    }
    int start=i;
    ans.pb(points[i-1]);
    while(!area(ans[0],points[start],points[i])) {
        i++;
        if(i==sz(points)) return ;
    }
    i--;
    int sec=i;
    ans.pb(points[i]); bool one=1;
    while(!area(ans[0],ans[1],points[i])){
        i++;
        if(i==sz(points)) { if(one) return ; else break; }
        one=0;
    }
    if(i-1>sec) i--;
    if(i==sz(points)) return ;
    ans.pb(points[i]);
    i++;
    for(; i<sz(points); i++){
        while(area(ans[sz(ans)-2],ans[sz(ans)-1],points[i])<=0) ans.erase(ans.begin()+sz(ans)-1);
        ans.pb(points[i]);
    }
}
