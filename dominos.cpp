#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int mark[7][8];
int mat[7][8];
int used[7][8];
int T, ways;

void domino( int x, int y ) {

	if ( y == 8 ) {	y = 0;	x++;	}
	if ( x == 7 ) {	ways++;	return;	}
	
	if ( mark[x][y] )
		domino( x, y + 1 );
	else {
		// Right
		mark[x][y] = 1;
		if ( y < 7 && !mark[x][y + 1] && !used[ mat[x][y] ][ mat[x][y + 1] ] ) {
			used[ mat[x][y] ][ mat[x][y + 1] ] = 1;
			used[ mat[x][y + 1] ][ mat[x][y] ] = 1;
			mark[x][y + 1] = 1;
			domino( x, y + 1 );
			mark[x][y + 1] = 0;
			used[ mat[x][y] ][ mat[x][y + 1] ] = 0;
			used[ mat[x][y + 1] ][ mat[x][y] ] = 0;
		}
		// Down
		if ( x < 6 && !mark[x + 1][y] && !used[ mat[x][y] ][ mat[x + 1][y] ] ) {
			used[ mat[x][y] ][ mat[x + 1][y] ] = 1;
			used[ mat[x + 1][y] ][ mat[x][y] ] = 1;
			mark[x + 1][y] = 1;
			domino( x, y + 1 );
			mark[x + 1][y] = 0;
			used[ mat[x][y] ][ mat[x + 1][y] ] = 0;
			used[ mat[x + 1][y] ][ mat[x][y] ] = 0;
		}
		mark[x][y] = 0;
	}
}

int main() {

	
	for ( int i = 0; i < 7; i++ )
		for ( int j = 0; i < 8; j++ )
			scanf( "%d", &mat[i][j] );
	
	ways = 0;
	domino( 0, 0);
	printf( "%d\n", ways );
	

	return 0;
}
