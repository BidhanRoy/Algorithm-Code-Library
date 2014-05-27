double polygonArea( vector<point> &P ) {
	double area = 0;
	int n=P.size();
	for( int i = 0, j = n - 1; i < n; j = i++ ) area += P[j].x * P[i].y - P[j].y * P[i].x;
	return fabs(area)/2;
}
