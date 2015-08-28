/*
 * TDRStream.cxx
 *
 *  Created on: Aug 7, 2015
 *      Author: paanruot
 */
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TDRStream.h"

TDRStream::TDRStream() {

}

//Function to parse command line input.
const char* TDRStream::parsecmdline(int argc, char *argv[]) {
	sargv = argv[1];
	if(argc < 2) {
		printf("Need to name the run file!");
			return 0;
	}
	sprintf(infilename, argv[1]);
	printf("Start to process run file: %s \n", infilename);
	return infilename;
}

//Function to resolve file size in blocks.
int TDRStream::findfilesize(FILE *infile, bool print) {
	DATA_HEADER *header = (DATA_HEADER *)block;
	if (!infile) {
			printf("ERROR: Run file is not open! Quitting...  \n");
			return 0;
	}
	for (blocksize = 0; blocksize <= sizeof(block); blocksize ++) {
	      fseek(infile, blocksize, SEEK_SET);
	      elements = fread(block, sizeof(unsigned char), blocksize, infile);
	      if (!strncmp(header->id, "EBYEDATA", 8)){
	    	  break;
	      }
	}

	filesize = 0;
	elements = (int32_t)blocksize;
	while (elements == (int32_t)blocksize) {
		fseek(infile, (filesize)*blocksize, SEEK_SET);
		elements = fread(block, sizeof(unsigned char), blocksize, infile);
		filesize+=1;
	}
	if(print)printf("Size of the current file is: %d blocks\r", filesize);
	return filesize;
}

//Function to resolve the block size. This is a bit bad design, but since it's not regularly needed, will do for now..
int TDRStream::findblocksize(FILE *infile, bool print) {
	findfilesize(infile, 0);
	if(print)printf("Block size is: %d \r", blocksize);
	return blocksize;
}


//Function to read blocks and check various data word types.
int TDRStream::parsedata(FILE *infile, uint32_t blocksize, const char* inputfile, FillRoot *treepointer) {
	DATA_HEADER *header = (DATA_HEADER *)block;
	uint64_t *data = (uint64_t *)(block + sizeof(DATA_HEADER));
	adcword = new RawDatum();
	now_adc = 0; //Calculates adc words
	eof = 0; //Variable to indicate when all data have been read.
	nob = findfilesize(infile,0); //We'll need the filesize to indicate how is the parsing progressing.

	//Rewind the infile to the start.
	fseek(infile, 0, SEEK_SET);

	printf("INFO: Reading data blocks... \n");
	for ( ; ; current_block++) {
		elements = fread(block, sizeof(unsigned char), blocksize, infile);
			if (elements != (int32_t)blocksize) {
				eof = 1;
				adcword->parseadcword(0, now_adc, eof, treepointer);
				break;
			}
			// Check header so that each block starts with string "EBYEDATA"
			if (strncmp(header->id, "EBYEDATA", 8)) {
				fprintf(stderr, "ERROR: File %s is not TDR data \n", inputfile);
				break;
			}
			// Loop over data, determine word type and do something useful with it.
			// At the moment, only adc words are parsed.
			for (jj = 0; jj < header->dataLen / sizeof(uint64_t); jj++) {
				key = (data[jj] >> 62) & 3;
				switch(key) {
					case 0: // Trace sample
						break;
					case 1: // Trace header
						break;
					case 2: // Information
						break;
					case 3: // ADC data
						now_adc ++;
						adcword->parseadcword(data[jj], now_adc, eof, treepointer);
						break;
					};
			}
			if(current_block%10000 == 0) cout << setiosflags(ios::fixed) << 100 * current_block/nob << " % complete" << "\r" << flush;
	}
	// Write a message
	if(eof) printf("Done! Found %i ADC words \n", now_adc);
	return eof;
}

TDRStream::~TDRStream() {
	// TODO Auto-generated destructor stub
}

