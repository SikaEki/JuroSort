/*
 * jurosort.cxx
 *
 *  Created on: Aug 7, 2015
 *      Author: paanruot
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include "TStopwatch.h"

#include "jurosort.h"

int main(int argc, char *argv[])	{

	//Initialize stop.
	stop_signal = 0;

	//Parses the command line arguments, which ought to be just a run file.
	inputfile = parsed.parsecmdline(argc, argv);

	//Opens the run file for operations
	infile = fopen(inputfile, "rb");
	if (!infile) {
		printf("Unable to open. File cannot be located. \n");
		exit(0);
	}
	else printf("File %s opened successfully! \n", inputfile);

	//Resolve file and block sizes. Print result with the second argument.
	//Or, if you know the block size, just give it like it it now.
		//fsize.findfilesize(infile, 1);
		//blocksize = bsize.findblocksize(infile, 1);
	blocksize = 65536;

	//Create a ROOT tree, which is going to be filled
	newtree = new FillRoot();
	newtree->CreateROOTFile(inputfile);

	//Call to initialize the data parsing.
	watch.Start();
	while((stop_signal == 0)) {
		stop_signal = blocks.parsedata(infile, blocksize, inputfile, newtree);
	}
	if(stop_signal == 1)newtree->CloseOutputFile();

	fclose(infile);
	printf("Closing run file %s! \n", inputfile);
	std::cout << inputfile << " done after " << watch.RealTime() << " seconds" << std::endl;

	if(stop_signal == 1)printf("Data parsing completed!");

	return 0;
}
