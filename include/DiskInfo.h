/*
 * SmartInfo.h
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#ifndef DISKINFO_H_
#define DISKINFO_H_

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/Mutex.h>
#include <sys/types.h>
#include <string>
#include <vector>

#include "atasmart.h"
#include "SmartAttribute.h"
#include "IdentifyInfo.h"
#include "SmartInfo.h"

using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::Mutex;

using std::string;
using std::vector;

class DiskInfo {
private:

	string devicePath;

	string name;
	string type;
	string typePretty;
	uint64_t size;

	//identify
	bool identifyValid;
	IdentifyInfo identifyInfo;

	//smart
	bool smartAvailable;
	SmartInfo smartInfo;

public:

	DiskInfo(const std::string & devicePath);
	virtual ~DiskInfo();

	Object toJSONObject();

	inline const string & getName() const {
		return name;
	}

	inline const string& getDevicePath() const {
		return devicePath;
	}

	inline bool isIdentifyValid() const {
		return identifyValid;
	}

	inline int64_t getSize() const {
		return size;
	}

	inline bool isSmartAvailable() const {
		return smartAvailable;
	}

	inline const string& getType() const {
		return type;
	}

	inline const string& getTypePretty() const {
		return typePretty;
	}

	inline const IdentifyInfo& getIdentifyInfo() const {
		return identifyInfo;
	}

	inline const SmartInfo& getSmartInfo() const {
		return smartInfo;
	}
};

#endif /* DISKINFO_H_ */
