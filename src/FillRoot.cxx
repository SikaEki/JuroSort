/*
 * FillRoot.cxx
 *
 *  Created on: Aug 11, 2015
 *      Author: paanruot
 */
#include <string.h>
#include <string>
#include <stdio.h>

#include "FillRoot.h"

FillRoot::FillRoot() {

}

void FillRoot::FillSpectra(uint64_t adata) {
	ahist = new TH1D("ahist","Some data",16384, 0, 16384);
	ahist->Fill(adata);
}

void FillRoot::FillAFile() {
	output = new TFile("ahist.root","RECREATE");
	output->cd();
	ahist->Write();
	output->Close();
}

void FillRoot::CloseOutputFile() {
	if(fOutputFile) {
		fOutputFile->Write();
		fOutputFile->Close();
		printf("Close output file!...");
		fOutputFile = 0;
		printf("done.\n");
	}
}

void FillRoot::CreateROOTFile(const char *outputfile)	{
	sprintf(outfilename, "%s.root", outputfile);
	fOutputFile = new TFile(outfilename,"RECREATE");

	if (!fOutputFile) {
	          fprintf(stderr, "ERROR: Unable to create %s - %m\n", outfilename);
	          exit(0);
	}
	else printf("Opened output file with name:\t%s\n",outfilename);
	SetUpTree();
}

void FillRoot::SetUpTree() {
	fOutputFile->cd();
	tree = new TTree("RawEventTree","RawEventTree");
	tree->Branch("RawData",&RawData,"ts/l:energy/l:chnum/S:modnum/S:veto/S:fail/S");
}

void FillRoot::FillTree(DATA *rawevent)	{
	RawData.ts = rawevent->ts;
	RawData.energy = rawevent->energy;
	RawData.chnum = rawevent->chnum;
	RawData.modnum = rawevent->modnum;
	RawData.veto = rawevent->veto;
	RawData.fail = rawevent->fail;
	tree->Fill();
	return;
}

FillRoot::~FillRoot() {
	// TODO Auto-generated destructor stub
}
