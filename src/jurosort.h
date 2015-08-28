/*
 * jurosort.h
 *
 *  Created on: Aug 7, 2015
 *      Author: paanruot
 */

#ifndef JUROSORT_H_
#define JUROSORT_H_

using namespace std;
#include <string>

#include "FillRoot.h"
#include "TDRStream.h"

FILE *infile;
const char *inputfile;
int blocksize, stop_signal;
TDRStream parsed, fsize, bsize, blocks;
FillRoot *newtree;
TStopwatch watch;

#endif /* JUROSORT_H_ */
