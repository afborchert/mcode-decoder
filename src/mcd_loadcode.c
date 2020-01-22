#include	<stdio.h>
#include	"mcd_decode.h"

extern	int	fs;
extern	unsigned	int	sy;
extern	int	probablyprocnum;

extern	struct	tab { char *mnem; int op; } table[255];

static	int	offset;
static	int	loadaddress;
static	int	byteaddress;
static	unsigned	int	byte;
static	int	endreached;
static	int	nextcase = 0;

loadcode()
{
	int	floc,i;
	int	nr;

	if ( fs == 0 )
		error ( FLER );
	else {
		getnum ( &offset );
		if ( probablyprocnum && fs == 1 ) {
			printf("procedure  # %3o at ",offset);
			getnum ( &i );
			printf("%3o bytes relative to F\n",i);
			getsy();
			}
		else {
			printf("code at F + %3o words\n",offset);
			decode();
			getsy();
			if ( sy == FIXUP ) {
				printf("fixups at ");
				i = 0;
				while ( fs > 0 ) {
					i = (i+1) % 9;
					if ( i == 0 ) {
						printf("\n          ");
						++i;
						}
					getnum ( &floc );
					printf("%5o ",floc);
					}
				getsy();
				printf("\n");
				}
			printf("\n");
			}
		}
}

static
decode ()
{
	startat(offset);
	while ( ! endreached ) {
		if ( byteaddress == nextcase )
			casetable();
		else {
			printf("%5o %5o ",loadaddress,byteaddress);
			instruction();
			}
		printf("\n");
		getnext();
		}
}

int	newword = TRUE;
unsigned	int	lword;

getnext()
{
	++byteaddress;
	if ( newword ) {
		if ( fs > 0 )
			getnum ( &lword );
		else {
			endreached = TRUE;
			lword = 0;
			}
		byte = lword / 0x100;
		++loadaddress;
		newword = FALSE;
		}
	else {
		byte = lword % 0x100;
		newword = TRUE;
		}
}

startat ( loadadr )
int	loadadr;
{
	endreached = FALSE;
	newword = TRUE;
	byteaddress = loadadr*2-1;
	loadaddress = loadadr-1;
	getnext();
}

unsigned int
nextword ()
{
	unsigned	int	l;

	getnext();
	l = byte;
	getnext();
	return l * 0x100 + byte;
}

instruction ()
{
	int	k,l;
	short	sl;
	char	x;

	x = (char) byte;
	byte = x;
	printf("%5o       %-5s ",byte,table[byte].mnem);
	switch ( table[byte].op ) {
	case	ILLEGAL :
	case	NONE	:
			break;
	case	CASEJPX :
			k = byteaddress+1;
			printf("[");
			l = nextword();
			printf("%5o] -> ",l);
			l = k+l;
			printf("%5o",l);
			caseat(l);
			break;
	case	BYTE :
			getnext();
			printf("%5o ",byte);
			break;
	case	TWOBYTES :
			getnext();
			printf("%3o ",byte);
			getnext();
			printf("%3o ",byte);
			break;
	case	BYTEFJUMP  :
			k = byteaddress+1;
			getnext();
			printf("[%3o]   -> ",byte);
			l = k+byte;
			printf("%5o",l);
			break;
	case	BYTEBJUMP :
			k = byteaddress+1;
			getnext();
			printf("[%3o]   -> ",byte);
			l = k-byte;
			printf("%5o",l);
			break;
	case	WORD :
			l = nextword();
			printf("%5o ",l);
			break;
	case	WORDJUMP :
			k = byteaddress+1;
			l = nextword();
			printf("[%5o] -> ",l);
			l = k+l;
			printf("%5o",l);
			break;
	case	SPECIALRDS :
			getnext();
			printf("%3o ",byte);
			l = byte;
			for ( k = 0 ; k < l ; ++k ) {
				getnext();
				if ( k < 10 )
					printf("%3o ",byte);
				}
			break;
	case	TWOWORDS :
			for ( k = 0 ; k < 2 ; ++k ) {
				getnext();
				l = byte;
				getnext();
				printf("%5o ",l*0x100+byte);
				}
			break;
	case	FOR2JUMP :
			getnext();
			printf("%3o ",byte);
			k = byteaddress+1;
			sl = nextword();
			if ( sl > 0 )
				printf("[%5o] -> ",sl);
			else
				printf("[%5o] -> ",-sl);
			sl += k;
			printf("%5o",sl);
			break;
	case	ESCAPE :
			printf("unknown number of bytes");
			break;
	default :
			fprintf(stderr,"decoder error\n");
			printf("decoder error\n");
	}
}

static	int	casestack[21];
static	int	casetop = 0;

caseat ( loc )
int	loc;
{
	++casetop;
	casestack[casetop] = loc;
	nextcase = loc;
}

casetable ()
{
	unsigned int 	lower,upper,i,l;
	short	sl;

	--casetop;
	nextcase = casestack[casetop];

	lower = byte;
	getnext();
	lower = lower * 0x100 + byte;
	printf("%5o %5o %5o          %5o    Low\n",
		loadaddress,
		byteaddress-1,
		lower,
		lower);

	upper = nextword();
	printf("%5o %5o %5o          %5o    High\n",
		loadaddress,
		byteaddress-1,
		upper,
		upper);

	sl = nextword();
	printf("%5o %5o %5o          -> %5o Else",
		loadaddress,
		byteaddress-1,
		-sl,
		byteaddress-1+sl);

	for ( i = 0 ; i <= upper-lower ; ++i ) {
		printf("\n");
		sl = nextword();
		printf("%5o %5o %5o          -> %5o",
			loadaddress,
			byteaddress-1,
			-sl,
			byteaddress-1+sl);
		}
	printf(" End");
}
