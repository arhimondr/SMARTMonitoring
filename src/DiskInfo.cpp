/*
 * SmartInfo.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#include "DiskInfo.h"
#include "Poco/Util/Application.h"

using Poco::ScopedLock;
using Poco::Util::Application;

DiskInfo::DiskInfo(const std::string & devicePath) : devicePath(devicePath) {

	SkDisk * disk = NULL;

	if (sk_disk_open(devicePath.c_str(), &disk) < 0) {
		return; //when we not able to open device - nothing to do
	}

	if (disk->name) {
		name = disk->name;
	}

	if (disk->type) {
		type = disk->type;
		typePretty = disk_type_to_human_string(disk->type);
	}

	sk_disk_get_size(disk, &size); //read the disk size

	if (disk->identify_valid) {
		identifyValid = true;
		identifyInfo = IdentifyInfo(disk);
	}

	SkBool b = FALSE;

	if (sk_disk_smart_is_available(disk, &b) < 0) {
		smartAvailable = false;
	} else {
		smartAvailable = !!b;
	}

	if (smartAvailable) {
		smartInfo = SmartInfo(disk);
	}

	sk_disk_free(disk); //close the disk
}

DiskInfo::~DiskInfo() {


}

Object DiskInfo::toJSONObject(){
	Object jsonObject;

	jsonObject.set("devicePath", devicePath);


	jsonObject.set("name", name);
	jsonObject.set("type", type);
	jsonObject.set("typePretty", typePretty);
	jsonObject.set("size", size);


	//identify
	jsonObject.set("identifyValid", identifyValid);
	jsonObject.set("identifyInfo", identifyInfo.toJSONObject());

	//S.M.A.R.T.
	jsonObject.set("smartAvailable", smartAvailable);
	jsonObject.set("smartInfo", smartInfo.toJSONObject());


	return jsonObject;
}

