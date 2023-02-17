/******************************************************************************
 *  main.c                                                                    *
 *  Part of Benzin                                                            *
 *  The main stuff.                                                           *
 *  Copyright (C)2009 SquidMan (Alex Marshall)        <SquidMan72@gmail.com>  *
 *  Copyright (C)2009 megazig  (Stephen Simpson)       <megazig@hotmail.com>  *
 *  Copyright (C)2009 Matt_P   (Matthew Parlane)                              *
 *  Copyright (C)2009 comex                                                   *
 *  Copyright (C)2009 booto                                                   *
 *  All Rights Reserved, HACKERCHANNEL.                                       *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brlan.h"
#include "brlyt.h"
#include "types.h"
#include "endian.h"
#include "general.h"

#ifdef DEBUGMAIN
#define dbgprintf	printf
#else
#define dbgprintf	//
#endif //DEBUGMAIN

int main(int argc, char* argv[])
{
	u8 type = 3;
	char *ext;

	if (argc == 2)
	{
		if (strcmp(argv[1], "-v") == 0)
			printf(INFORMATION_TEXT);
		exit(0);
	}

	if (argc < 4)
	{
		printf("Benzin v2.1.11 mod01 BETA\n\n");
		printf("Usage:\n");
        printf("\n");
		printf("  ./benzin <r|m> [FILE] [OUTFILE]\n");
        printf("\n");
        printf("Examples:\n");
		printf("  ./benzin r brlytfilename.brlyt xmlytfilename.xmlyt\n");
		printf("  ./benzin m xmlytfilename.xmlyt brlytfilename.brlyt\n");
		printf("  ./benzin r brlytfilename.brlan xmlytfilename.xmlan\n");
		printf("  ./benzin m brlytfilename.xmlan xmlytfilename.brlan\n");
		exit(1);
	}

	if ((strcmp(argv[1], "r") == 0) || (strcmp(argv[1], "p") == 0) || (strcmp(argv[1], "m") == 0) || (strcmp(argv[1], "w") == 0))
	{
		ext = strrchr(argv[2], '.');
	} else {
        printf("Benzin v2.1.11 mod01 BETA\n\n");
		printf("Usage:\n");
        printf("\n");
		printf("  ./benzin <r|m> [FILE] [OUTFILE]\n");
        printf("\n");
        printf("Examples:\n");
		printf("  ./benzin r brlytfilename.brlyt xmlytfilename.xmlyt\n");
		printf("  ./benzin m xmlytfilename.xmlyt brlytfilename.brlyt\n");
		printf("  ./benzin r brlytfilename.brlan xmlytfilename.xmlan\n");
		printf("  ./benzin m brlytfilename.xmlan xmlytfilename.brlan\n");
		exit(1);
	}

	if(!ext)
	{
		printf("No extension on file\n");
		printf("To see possible arguments type ./benzin\n");
		exit(1);
	} else {
		char* temp = ext;
		if(strcmp(++ext, "brlyt") == 0)
		{
			type = 1;
		}
		ext = temp;
		if(strcmp(++ext, "brlan") == 0)
		{
			type = 2;
		}
		ext = temp;
		if(strcmp(++ext, "xmlyt") == 0)
		{
			type = 1;
		}
		ext = temp;
		if(strcmp(++ext, "xmlan") == 0)
		{
			type = 2;
		}
		if(type > 2)
		{
			printf("Unknown file extension\n");
			exit(1);
		}
	}

	int brlanargread;
	int brlytargread;
	int brlanargmake;
	int brlytargmake;
	int brlanargdestmake;
	int brlytargdestmake;
	int brlanargdestread;
	int brlytargdestread;
	int currentarg = 2;

	if(type == 1)
	{
		brlytargread = currentarg;
		brlytargmake = currentarg++;
		brlytargdestread = currentarg;
		brlytargdestmake = currentarg++;
	}
	if(type == 2)
	{
		brlanargread = currentarg;
		brlanargmake = currentarg++;
		brlanargdestread = currentarg;
		brlanargdestmake = currentarg++;
	}

	printf(INFORMATION_TEXT);

	if((argv[1][0] == 'r') || (argv[1][0] == 'p')) {
		if(type == 1)
			parse_brlyt(argv[brlytargread], argv[brlytargdestread]);

		if(type == 2)
			parse_brlan(argv[brlanargread], argv[brlanargdestread]);

	} else if( (argv[1][0] == 'm') || (argv[1][0] == 'w') ) {
		if(type == 1)
			make_brlyt(argv[brlytargmake], argv[brlytargdestmake]);

		if(type == 2)
			make_brlan(argv[brlanargmake], argv[brlanargdestmake]);

	}
	return 0;
}

