/// Author : Bidhan Roy
/// Range Minimum Query using Frenweek Tree ( Binary indexed tree )
/// Source : https://github.com/BidhanRoy/Algorithm-Code-Library
/// 1 based
 
template < typename Int >
class rangeMinimumQuery {
	
	Int Inf; /// infinite value
	Int *Tree; /// vector containing the actual tree
	unsigned size; /// size of the tree

	public :

	rangeMinimumQuery ( unsigned _size ) : Inf ( numeric_limits< Int >::max() ) , size( _size ) { 
		/// size of tree should be double of original array
		Tree = new Int [ ( size << 1 ) + 1 ];
		fill( Tree , Tree + (size<<1) + 1 , Inf );
	}

	~rangeMinimumQuery () { 
		delete( Tree );
		size = Inf = 0;
	}

	void set( unsigned idx, Int v ) {
		
		/// Sets value of index 'idx' to v, 
		/// if the existing value is already greater.
		/// 1 Based

		if( idx == 0 ) {
			cerr << "Indexes should be 1 based." << endl;
			throw ;
		}
		
		idx += size;

		while( idx ) {
			Tree[ idx ] = min( Tree[ idx ] , v );
			idx >>= 1;
		}
	}

	Int get( unsigned L, unsigned R ) {

		/// L, R are 1 based

		Int ret = Inf;
		L += size; R += size + 1; /// +1, to make it [L,R] from [L,R)

		while( L < R ) {
			if( L & 1 ) ret = min( ret , Tree[ L++ ] ); 
			if( R & 1 ) ret = min( ret , Tree[ --R ] );
			L >>= 1, R >>= 1;
		}

		return ret;
	}

};