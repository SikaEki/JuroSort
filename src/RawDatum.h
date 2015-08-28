/*
 * RawDatum.h
 *
 *  Created on: Aug 10, 2015
 *      Author: paanruot
 */

#ifndef RAWDATUM_H_
#define RAWDATUM_H_

#include <stdint.h>
#include <cstdio>

#include "FillRoot.h"

class RawDatum {
public:
	RawDatum();
	virtual ~RawDatum();

	DATA *datapackage;
	unsigned char data[128];
	int module, channel, baseline;
	uint64_t veto, id, adc, fail, ts;

	void parseadcword(uint64_t, int , int, FillRoot *);
};

#endif /* RAWDATUM_H_ */
