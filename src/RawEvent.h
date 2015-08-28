/*
 * RawEvent.h
 *
 *  Created on: Aug 13, 2015
 *      Author: paanruot
 */

#ifndef RAWEVENT_H_
#define RAWEVENT_H_

typedef struct DATA {
	  uint64_t  ts;
	  uint64_t energy;
	  short int chnum;
	  short int modnum;
	  short int veto;
	  short int fail;
} DATA;

#endif /* RAWEVENT_H_ */
