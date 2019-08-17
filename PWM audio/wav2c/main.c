/***************************************************************
 * Name:      wave2c, a WAV file to GBA C source converter.
 * Purpose:   translate audio binaries into AVR memory data
 * Author:    Ino Schlaucher (ino@blushingboy.org)
 * Created:   2008-07-28
 * Copyright: Ino Schlaucher (http://blushingboy.org)
 * License:   GPLv3 (upgrading previous version)
 **************************************************************
 *
 * Adapted and debugged by Paul Veldhuijzen van Zanten
 *                         20-9-2017 Windesheim
 *
 * Based on an original piece of code by Mathieu Brethes.
 *
 * Copyright (c) 2003 by Mathieu Brethes.
 *
 * Contact : thieumsweb@free.fr
 * Website : http://thieumsweb.free.fr/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "wavdata.h"
#include <stdio.h>
#include <stdlib.h>

int write_u16( unsigned short val, FILE * fp )
{
    unsigned char msb = val>>8;
    unsigned char lsb = val & 0xFF;
    fputc( lsb, fp );
    fputc( msb, fp );
}

int write_small_u32( unsigned int val, FILE * fp )
{
    unsigned char msb = (val & 0xFF00) >> 8;
    unsigned char lsb = val & 0xFF;
    fputc( lsb, fp );
    fputc( msb, fp );
    fputc( 0, fp );
    fputc( 0, fp );
}

int main(int argc, char **argv) {
	wavSound* s;
	FILE *fin;
	FILE *fout;
	FILE *ftemp;
	int i;

//	if (argc < 4 || argc > 6) {
//		printf("Usage 1: %s <file.wav> <output.c> <soundname>\n", argv[0]);
//		printf("Usage 2: %s <file.wav> <output.c> <soundname> <amount of samples>\n", argv[0]);
//		exit(0);
//	}

    printf("Typ de naam van het wav bestand (dus <naam>.wav)\n");

	char buf[1024];
	scanf( "%s", buf );
	char *wavextension = strstr(buf, ".wav");

	if (!wavextension)
    {
        printf("Please specify a 8KHz, 8-bit wav file!\n");
        exit(0);
    }

	fin = fopen(buf, "rb");    //binairy!!!
    if (!fin)
	{
		printf("Could not open input file %s!\n", buf);
	}
	s = loadWaveHeader(fin);

	if (s == NULL) {
		printf("Invalid wave !\n");
		exit(0);
	}

    //strcpy(s, ".c");
	fout = fopen("output.c", "w");

#if 0
	//make demo wav file
	ftemp = fopen("test.wav", "w");
    fprintf( ftemp, "RIFF");
    fprintf( ftemp, "    ");     //nbRead=fread(&chunkSize, sizeof(int), 1, fp);
    fprintf( ftemp, "WAVEfmt ");
    write_small_u32( 16, ftemp ); //int subChunk1Size
    write_u16( 1, ftemp );        //short int audFormat  is 1
    write_u16( 1, ftemp );        //short int nbChannels is 1
    write_small_u32( 8000, ftemp ); //int sampleRate is 8000 (1F40)
    write_small_u32( 8000, ftemp ); //int byterate   is 8000 (1F40)
    write_u16( 1, ftemp );        //short int blockalign
    write_u16( 8, ftemp );        //short int bitspersample is 8
    fprintf( ftemp, "data");
    write_small_u32( 1000, ftemp ); //int dataLength is 1000
    for ( i=0; i<1000; i++)
    {
        char c = (i & 0xFF);
        //if (c == 26) c=255;
        fputc( c, ftemp );
    }
#endif //

    saveWave(fin, s, fout, "test" );

	return 0;
}
