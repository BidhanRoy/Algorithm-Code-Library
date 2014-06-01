vector< string > tokenize( string a, string b ) {
	const char *q = a.c_str();
	while( count( b.begin(), b.end(), *q ) ) q++;
	vector< string > oot;
	while( *q ) {
		const char *e = q;
		while( *e && !count( b.begin(), b.end(), *e ) ) e++;
		oot.push_back( string( q, e ) );
		q = e;
		while( count( b.begin(), b.end(), *q ) ) q++;
	}
	return oot;
}
