#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Problem : Wall Making Game
// Author : 山崎 ( torus711 )
//
// 各領域の Grundy 数を範囲 DP
// O( H^3 W^3 log HW )

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

using VS = vector< string >;

template < typename T > inline istream& operator>>( istream &s, vector< T > &v ){ for ( T &t : v ) { s >> t; } return s; }

#define REP2( i, n ) REP3( i, 0, n )
#define REP3( i, m, n ) for ( int i = ( int )( m ); i < ( int )( n ); ++i )
#define GET_REP( a, b, c, F, ... ) F
#define REP( ... ) GET_REP( __VA_ARGS__, REP3, REP2 )( __VA_ARGS__ )
#define AALL( a, t ) ( t* )a, ( t* )a + sizeof( a ) / sizeof( t )

#define EXIST( c, e ) ( ( c ).find( e ) != ( c ).end() )

int H, W;
VS BOARD;

int dp[ 32 ][ 32 ][ 32 ][ 32 ];

int solve( const int y1, const int x1, const int y2, const int x2 )
{
	int &res = dp[ y1 ][ x1 ][ y2 ][ x2 ];

	if ( res != -1 )
	{
		return res;
	}

	set< int > S;
	REP( y, y1, y2 )
	{
		REP( x, x1, x2 )
		{
			if ( BOARD[y][x] == 'X' )
			{
				continue;
			}

			S.insert(
					solve(    y1,    x1,  y,  x ) ^
					solve(    y1, x + 1,  y, x2 ) ^
					solve( y + 1,    x1, y2,  x ) ^
					solve( y + 1, x + 1, y2, x2 )
					);
		}
	}

	for ( res = 0; EXIST( S, res ); ++res );
	return res;
}

int main()
{
	cin.tie( 0 );
	ios::sync_with_stdio( false );

	cin >> H >> W;

	BOARD.resize( H );
	cin >> BOARD;
	
	fill( AALL( dp, int ), -1 );

	cout << ( solve( 0, 0, H, W ) ? "First" : "Second" ) << endl;

	return 0;
}
