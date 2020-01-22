#include	<stdio.h>
#include	"mcd_decode.h"

static	int	errors = 0;

error ( er )
int	er;
{
	++errors;
	if ( errors <= 20 ) {
		printf("*** ");
		switch ( er ) {
		case EOFER:	printf("try to read past eof"); break;
		case FRER :	printf("frame error"); break;
		case SYER :	printf("illegal symbol read"); break;
		case CKER :	printf("incorrect type of code"); break;
		case MNER :	printf("illegal modulename read"); break;
		case SQER:	printf("symbol sequence error"); break;
		case CFER :	printf("file not a .RLP file"); break;
		case FLER :	printf("incorrect framelength"); break;
		case FUER :	printf("fixup error"); break;
		case MSER :	printf("top of loadable area reached"); break;
		}
		printf("\n");
		}
	else if ( errors == 21 )
		printf("*** too many errors\n");
	if ( errors == 1 )
		fprintf(stderr,"decode: errors found\n");
}
