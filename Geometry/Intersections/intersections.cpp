pair<bool,point> intersectionLineLine( line L1 , line L2 ){
	__typeof(L1.a) det = L1.a * L2.b - L1.b * L2.a;
	point ret(-1,-1);
	if( !sgn ( det, 0 ) ) return mp(false,ret);
	ret.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	ret.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return mp(true,ret);
}

pair<bool,point> intersectionLineSegment( line L , segment S ){
	line L2( S.A , S.B );
	point ret(-1,-1);
	pair<bool,point> P=intersectionLineLine( L , L2 );
	if(!P.xx) return mp(false,ret);
	if( !sgn( dist(P.yy,S.A) + dist(P.yy,S.B) , dist(S.A,S.B) ) ) return mp(true,P.yy);
	return mp(false,ret);
}

