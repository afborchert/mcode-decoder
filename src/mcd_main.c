/*
 *	Lilith Decoder
 */

#include	<stdio.h>

char	usage[] = { "Usage: %s file ..." };
FILE	*fp;

main ( argc , argv )
int	argc;
char	**argv;
{
	if ( argc == 1 )
		quit ( usage , *argv );
	while ( --argc )
		decode ( *++argv );
}

decode ( file )
char	*file;
{
	if ( (fp = fopen(file,"r")) == NULL ) {
		perror(file);
		return;
		}
	printf("decode of `%s' :\n",file);
	loadfile ( fp );
	fclose(fp);
}

quit ( string , p1 , p2 , p3 , p4 , p5 , p6 )
{
	fprintf(stderr,string,p1,p2,p3,p4,p5,p6);
	fprintf(stderr," - QUIT\n");
	exit(1);
}
