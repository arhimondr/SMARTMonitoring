/*
 * HDDExplorer.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#include "HDDExplorer.h"

#include "iostream"

extern "C"
{
	#include "parted/device.h"
}

HDDExplorer::HDDExplorer() {
	discoverHDDs(); //lets discover all our HDD when class constructs
}

HDDExplorer::~HDDExplorer() {
	//nothing to kill yet=))
}

void HDDExplorer::discoverHDDs() {
	ped_device_probe_all();

	PedDevice * device = NULL;

	while((device = ped_device_get_next(device))!=NULL){
		availableHDDs.push_back(device->path);
	};

	ped_device_free_all();
}

