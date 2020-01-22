#include	<stdio.h>
#include	"mcd_decode.h"

unsigned	int	sy;
int	fs;

static	FILE	*in;
static	int	nextn;

initincode ( fp )
FILE	*fp;
{
	in = fp;
	readword(&nextn);
	fs = 0;
}

readword ( n )
unsigned	int	*n;
{
	word	x;

	if ( ! fread ( &x , sizeof(word) , 1 , in ) )
		sy = EOFSY;
	*n = (unsigned	int) x;
}

getnum ( n )
unsigned	int	*n;
{
	if ( fs == 0 ) {
		error ( FRER );
		*n = 0;
		}
	else {
		--fs;
		if ( feof(in) ) {
			*n = 0;
			if ( fs == 0 )
				error ( FRER );
			}
		else {
			*n = nextn;
			readword(&nextn);
			}
		}
}

skip ()
{
	unsigned	int	n;

	while ( fs > 0 )
		getnum ( &n );
}

getsy ()
{
	unsigned	int	n;

	if ( fs > 0 ) {
		error ( FRER );
		skip();
		}
	if ( feof(in) )
		sy = EOFSY;
	else {
		fs = 1;
		getnum ( &n );
		if ( 0200 <= n && n <= 0205 ) {
			sy = n;
			fs = 1;
			getnum ( &fs );
			}
		else {
			sy = EOFSY;
			error ( SYER );
			}
		}
}
