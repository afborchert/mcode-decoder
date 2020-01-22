#include	<stdio.h>
#include	"mcd_decode.h"

extern	unsigned	int	sy;
extern	int	fs;

int	probablyprocnum;

loadfile ( in )
FILE	*in;
{
	initincode(in);
	getsy();
	do {
		if ( sy == CODEKEYSY )
			codekey();
		if ( sy == MODULESY ) {
			moduleheader();
			if ( sy == IMPORTSY )
				imports();
			probablyprocnum = TRUE;
			while ( sy == CTEXT || sy == DTEXT ) {
				if ( sy == CTEXT ) {
					loadcode();
					probablyprocnum = !probablyprocnum;
					}
				else
					loaddata();
				}
			if ( ! ( sy == EOFSY || sy == MODULESY || sy == CODEKEYSY ) ) {
				error(SQER);
/* salami */ printf("symbol = %o\n",sy);
				do {
					skip();
					getsy();
					}
				while ( ! (sy == EOFSY || sy == MODULESY || sy == CODEKEYSY) );
				}
			}
		else
			error(CFER);

		}
	while ( sy != EOFSY );
}

codekey()
{
	int	actcodekey;

	printf("\ncodekey    = ");
	if ( sy == CODEKEYSY )
		if ( fs == 1 ) {
			getnum ( &actcodekey );
			getsy();
			printf("%o",actcodekey);
			}
		else {
			error ( FLER );
			skip();
			sy = EOFSY;
			}
	printf("\n");
}

moduleheader()
{
	modnam	mn;
	int	modcard;
	int	datasize;
	int	i,j;

	printf("module name: ");
	if ( fs != 12 ) {
		error(FLER);
		skip();
		sy = EOFSY;
		}
	else {
		getmn ( &mn );
		printf(" %s\n",mn.id);
		getnum ( &datasize );
		getsy();
		printf("datasize   = %o\n",datasize);
		printf("key          %o %o %o\n",mn.key[0],mn.key[1],mn.key[2]);
		}
}

imports ()
{
	modnam	mn;
	int	mnr;

	printf("import ");
	mnr = 0;
	while ( fs >= 11 ) {
		getmn ( &mn );
		++mnr;
		if ( mnr != 1 )
			printf("       ");
		printf(" %s\n",mn.id);
		printf(" is # ");
		printf("%3o\n",mnr);
		}
	if ( fs != 0 ) {
		error ( FLER );
		skip();
		}
	getsy();
	printf("\n");
}

getmn ( mn )
modnam	*mn;
{
	int	c,n;
	char	ch;
	int	oddpos;

	oddpos = FALSE;
	if ( fs >= MAXMODID/sizeof(word) ) {
		for ( c = 0 ; c < MAXMODID ; ++c ) {
			if ( oddpos ) {
				ch = n % 0400;
				oddpos = FALSE;
				}
			else {
				getnum ( &n );
				ch = n / 0400;
				oddpos = TRUE;
				}
			if ( ch == ' ' )
				ch = '\0';
			mn->id[c] = ch;
			}
		mn->id[MAXMODID] = '\0';
		for ( c = 0 ; c < 3 ; ++c )
			getnum ( & mn->key[c] );
		}
	else {
		error( MNER );
		skip();
		}
}
