class LRUCache{

    typedef list<int>:: iterator ListIterator;
    typedef pair< int , ListIterator > PairIntIt;
    typedef unordered_map< int , PairIntIt > :: iterator MapIterator;

    int capacity;
    list< int > pool;
    unordered_map< int , PairIntIt > Map;

    void makeRecent( MapIterator it ) {
        /// make the key inside iterator
        /// to most recent element
        pool.erase( it->second.second );
        pool.push_back( it->first );
        ListIterator itP = pool.end();
        it->second.second = --itP;
    }

    void reduce() {
        /// excludes the least recent element
        ListIterator it = pool.begin();
        Map.erase( *it );
        pool.erase( it );
    }

public:

    LRUCache( int _capacity ) {
        capacity = _capacity;
    }

    int get( int key ) {
        MapIterator it = Map.find( key );
        if( it == Map.end() ) return -1; /// key non existent
        makeRecent( it );
        return it->second.first;
    }

    void set( int key, int value ) {
        /// sets key = value, is key already exists, changes it's value
        MapIterator it = Map.find( key );
        if( it == Map.end() ) {
            pool.push_back( key );
            ListIterator itP = pool.end();
            Map[ key ] = { value, --itP };

            if( (int)pool.size() > capacity )
                reduce();

            return ;
        }
        it->second.first = value;
        makeRecent( it );
    }
};
