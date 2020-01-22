#include	<stdio.h>
#include	"mcd_decode.h"

extern	fs;

loaddata ()
{
	int	offset;
	unsigned	int	n;
	char	ch1,ch2;

	printf("data, relative to G\n");
	if (fs == 0)
		error(FLER);
	else {
		getnum(&offset);
		while ( fs > 0 ) {
			getnum ( &n );
			printf("%5o:  %5oB",offset,n);
			ch1 = (char) n / 0x100;
			ch2 = (char) n % 0x100;
			if ( isvisible(ch1) && isvisible(ch2) )
				printf(" \"%c%c\"\n");
			else
				printf("\n");
			++offset;
			}
		}
	getsy();
	printf("\n");
}
