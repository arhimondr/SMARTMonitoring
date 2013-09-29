/*
 * IdentifyInfo.h
 *
 *  Created on: Sep 29, 2013
 *      Author: andy
 */

#ifndef IDENTIFYINFO_H_
#define IDENTIFYINFO_H_

#include "atasmart.h"
#include "Poco/JSON/Object.h"

#include <string>

using std::string;

using Poco::JSON::Object;

class IdentifyInfo {

private:
	string model;
	string serial;
	string firmware;

public:
	IdentifyInfo();
	IdentifyInfo(SkDisk *disk);
	virtual ~IdentifyInfo();

	Object toJSONObject();

	inline const string& getFirmware() const {
		return firmware;
	}

	inline const string& getModel() const {
		return model;
	}

	inline const string& getSerial() const {
		return serial;
	}
};

#endif /* IDENTIFYINFO_H_ */
