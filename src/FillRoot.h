/*
 * FillRoot.h
 *
 *  Created on: Aug 11, 2015
 *      Author: paanruot
 */

#ifndef FILLROOT_H_
#define FILLROOT_H_

#include <stdint.h>
#include <cstdio>

#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TROOT.h"
#include "TBranch.h"

#include "RawEvent.h"


class FillRoot {
public:
	FillRoot();
	virtual ~FillRoot();

	char outfilename[32];
	TFile *output;
	TH1D *ahist;
	DATA RawData;

	TFile *fOutputFile;
	TFile *testfile;
	TTree *tree;

	void FillSpectra(uint64_t energy);
	void FillAFile();
	void CloseOutputFile();
	void SetUpTree();
	void FillTree(DATA *);
	void CreateROOTFile(const char *);
};

#endif /* FILLROOT_H_ */
