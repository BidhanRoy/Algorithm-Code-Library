struct segment{
	point A,B;
	segment():A(point(0,0)),B(point(0,0)){}
	segment(point _A,point _B):A(_A),B(_B){}
	bool inside(point c); /// checks if a point is inside the enclosing rectangle
	bool intersect(segment Q) ; /// checks if 'this' intersect with 'Q'
};

bool segment::inside(point c){
	/// checks if a point is inside the enclosing rectangle
	return (min(A.x,B.x)<=c.x && c.x<=max(A.x,B.x) && min(A.y,B.y)<=c.y && c.y<=max(A.y,B.y));
}

bool segment::intersect(segment Q){
	/// checks if 'this' intersect with 'Q'
	__typeof(A.x) d1=area(Q.A,Q.B,A);
	__typeof(A.x) d2=area(Q.A,Q.B,B);
	__typeof(A.x) d3=area(A,B,Q.A);
	__typeof(A.x) d4=area(A,B,Q.B);
	if( ((d1>0 && d2<0) || (d1<0 && d2>0)) && ((d3>0 && d4<0) || (d3<0 && d4>0))  ) return true;
	if(!d1 && Q.inside(A)) return true;
	if(!d2 && Q.inside(B)) return true;
	if(!d3 && inside(Q.A)) return true;
	if(!d4 && inside(Q.B)) return true;
	return false;
}
