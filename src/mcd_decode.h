#define	TRUE	1
#define	FALSE	0

#define	isvisible(ch)	((ch)>' '&&(ch)<'~')

#define	MAXMODID	16

typedef	struct	{
	char	id[MAXMODID+1];
	int	key[3];
	} modnam;

typedef	unsigned	short	word;

/* frame types */

#define	EOFSY		0
#define	CODEKEYSY	0200
#define	MODULESY	0201
#define	IMPORTSY	0202
#define	CTEXT		0203
#define	DTEXT		0204
#define	FIXUP		0205

/* error types */

#define	EOFER		1
#define	FRER		2
#define	SYER		3
#define	CKER		4
#define	MNER		5
#define	SQER		6
#define	CFER		7
#define	FLER		8
#define	FUER		9
#define	MSER	       10

/* operand types */

#define	NONE		1
#define	BYTE		2
#define	TWOBYTES	3
#define	WORD		4
#define	TWOWORDS	5
#define	BYTEFJUMP	6
#define	BYTEBJUMP	7
#define	WORDJUMP	8
#define	SPECIALRDS	9
#define	CASEJPX	       10
#define	FOR2JUMP       11
#define	ESCAPE	       12
#define	ILLEGAL        13
