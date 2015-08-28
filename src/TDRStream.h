/*
 * TDRStream.h
 *
 *  Created on: Aug 7, 2015
 *      Author: paanruot
 */

#ifndef TDRStream_H_
#define TDRStream_H_

#include <stdint.h>
#include <cstdio>
#include <fstream>
#include <string>
#include "RawDatum.h"

using namespace std;

//24 byte data block header definition. Copied from Nigell Warr.
typedef struct s_data_header {
    char       id[8];      // contains the string  EBYEDATA
    uint32_t   sequence;   // within the file
    uint16_t   stream;     // data acquisition stream number (in the range 1=>4)
    uint16_t   tape;       // =1
    uint16_t   MyEndian;   // written as a native 1 by the tape server
    uint16_t   DataEndian; // written as a native 1 in the hardware structure of the data following
    uint32_t   dataLen;    // total length of useful data following the header in bytes
} DATA_HEADER;

class TDRStream {

public:
	TDRStream();
	virtual ~TDRStream();

	RawDatum *adcword;
	uint32_t blocksize, jj, key;
	int32_t elements;
	int filesize, current_block, eof, now_adc, nob;
	string sargv;
	char infilename[32];
	unsigned char block[131072];

	const char* parsecmdline(int argc, char *argv[]);
	int findfilesize(FILE *, bool);
	int findblocksize(FILE *, bool);
	int parsedata(FILE *, uint32_t, const char*, FillRoot *);
};

#endif /* TDRStream_H_ */
