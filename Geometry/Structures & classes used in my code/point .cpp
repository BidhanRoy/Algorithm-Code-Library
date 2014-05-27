struct point{
    #define DT int /// Datatype
    DT x,y; 
    point():x(0),y(0){} /// default constructor
    point(DT _x,DT _y):x(_x),y(_y){} /// constructor
    
    bool operator < (point b) ; /// smaller than operator
    bool operator == (point b) ; /// equal to operator
    point operator - (point b) ; /// returns a vector from `this` to `b`
    DT operator * (point b) ; /// Dot product of `this` and `b`
    DT operator ^ (point b) ; /// Cross product of `this` and `b`
	point pointBetween(point q,double m1,double m2);
	/// returns a point from the joining segment of 'this' and 'q'
	/// the distance ratio of which from 'this' and 'q' is m1:m2
};

bool point::operator < (point b) {
	/// smaller than operator
	if(!sgn(x,b.x)) return sgn(y,b.y)<0;
	return sgn(x,b.x)<0;
}

bool point::operator == (point b) {
	/// equal to operator
	return !sgn(x,b.x) && !sgn(y,b.y);
}

point point::operator - (point b){ 
	/// returns a vector from `this` to `b`
	return point(x-b.x,y-b.y);
}

__typeof(point::x) point::operator * (point b){ 
	/// Dot product
	return x*b.x+y*b.y;
}

__typeof(point::x) point::operator ^ (point b){ 
	/// Cross product
	return x*b.y-y*b.x;
}

point point::pointBetween(point q,double m1,double m2){
	/// returns a point from the joining segment of 'this' and 'q'
	/// the distance ratio of which from 'this' and 'q' is m1:m2
    return point( ( m1 * q.x + m2 * x ) / ( m1 + m2 ) , ( m1 * q.y + m2 * y ) / ( m1 + m2 ) );
}
