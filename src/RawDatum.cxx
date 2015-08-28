/*
 * RawDatum.cxx
 *
 *  Created on: Aug 10, 2015
 *      Author: paanruot
 */
#include <stdio.h>
#include <stdlib.h>
#include "RawDatum.h"

RawDatum::RawDatum() {

}

void RawDatum::parseadcword(uint64_t datum, int data_index, int stop, FillRoot *treepointer) {

	veto = (datum >> 60) & 1;      // Veto bit (contains ADC range setting 0 = low, 1 = high)
	id   = (datum >> 48) & 0xFFF;  // ID of ADC
	adc  = (datum >> 32) & 0xFFFF; // ADC conversion value
	fail = (datum >> 61) & 1;      // Failure bit
	ts   = datum & 0xFFFFFFF;      // Timestamp

	module      = id / 32;     // module numbering starts from 1
	channel     = id % 16 + 1; //channel numbering starts from 1
	baseline    = (id % 32)/16;
	//printf("ADC data: \t ts = 0x%012llX ID=%-4lld MOD=%d CHAN=%-3d BL=%-3d ADC=%-5lld veto=%lld fail=%lld \n", ts, id, module, channel, baseline, adc, veto, fail);

	//Wrap the information into a package and send to a root tree.
	datapackage = (struct DATA*) data;
	datapackage->ts = ts;
	datapackage->energy = adc;
	datapackage->chnum = channel;
	datapackage->modnum = module;
	datapackage->veto = veto;
	datapackage->fail = fail;
	if(stop == 0)treepointer->FillTree(datapackage);

	return;
}

RawDatum::~RawDatum() {
	// TODO Auto-generated destructor stub
}
