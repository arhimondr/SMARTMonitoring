/*
 * IdentifyInfo.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: andy
 */

#include "IdentifyInfo.h"

IdentifyInfo::IdentifyInfo(){

}

IdentifyInfo::IdentifyInfo(SkDisk *disk) {
	const SkIdentifyParsedData *ipd;

	if (sk_disk_identify_parse(disk, &ipd) < 0)
		return;

	model = ipd->model;
	serial = ipd->serial;
	firmware = ipd->firmware;
}

IdentifyInfo::~IdentifyInfo() {
	// TODO Auto-generated destructor stub
}

Object IdentifyInfo::toJSONObject(){
	Object identify;

	identify.set("model", model);
	identify.set("serial", serial);
	identify.set("firmware", firmware);

	return identify;
}

