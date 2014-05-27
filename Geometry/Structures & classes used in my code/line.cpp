struct line{
    #define DT int /// Datatype
    DT a,b,c;
    
    line(){a=b=c=0;} /// default constructor
    line(point p,point q):a(p.y-q.y),b(q.x-p.x),c(p.x*q.y-q.x*p.y){} /// constructor
    
    bool operator < (line B); /// smaller than operator
    
    void normalize(); /// generalizes the line coefficients 'a','b','c'    
    line perpendicular(point p);
 	/// returns the perpendicular line
	/// which goes through point 'p'
};

void line::normalize(){ 
	/// generalizes the line coefficients 'a','b','c'
	__typeof(a) g=gcd(a,gcd(b,c)); 
	a/=g, b/=g, c/=g;
	int sign=(a<0 || (!a && b<0))?-1:1;
	a*=sign, b*=sign, c*=sign;
}

line line::perpendicular(point p){
	/// returns the perpendicular line
	/// which goes through point 'p'
	line ret;
	ret.a=b, ret.b=-a;
	ret.c=-p.x*ret.a-p.y*ret.b;
	return ret;
}

bool line::operator < (line B) {
	/// smaller than operator
	if(!sgn(a,B.a)) {
		return sgn(b,B.b)==0?sgn(c,B.c)<0:sgn(b,B.b)<0;
	}
	return sgn(a,B.a)<0;
}
