/*
 * SmartInfo.h
 *
 *  Created on: Sep 29, 2013
 *      Author: andy
 */

#ifndef SMARTINFO_H_
#define SMARTINFO_H_

#include <string>
#include <vector>

#include "SmartAttribute.h"
#include "atasmart.h"

using std::string;
using std::vector;

class SmartInfo {

private:
	bool diskStatus;
	string overall;
	uint64_t badSectors;
	uint64_t poweredOnMsecs;
	uint64_t powerCycles;
	uint64_t temperatureK;
	//smart

	string attributeVerification;
	vector<SmartAttribute> attributes;

	void readSmart(SkDisk *disk);
	void readAttributes(SkDisk *disk);

	static void dumpAttributesCallback(SkDisk *d,
			const SkSmartAttributeParsedData *a, void* userdata);

public:
	SmartInfo();
	SmartInfo(SkDisk *disk);
	virtual ~SmartInfo();

	Object toJSONObject();

	inline const vector<SmartAttribute>& getAttributes() const {
		return attributes;
	}

	inline const string& getAttributeVerification() const {
		return attributeVerification;
	}

	inline uint64_t getBadSectors() const {
		return badSectors;
	}

	inline bool isDiskStatus() const {
		return diskStatus;
	}

	inline const string& getOverall() const {
		return overall;
	}

	inline uint64_t getPowerCycles() const {
		return powerCycles;
	}

	inline uint64_t getPoweredOnMsecs() const {
		return poweredOnMsecs;
	}

	inline uint64_t getTemperatureK() const {
		return temperatureK;
	}
};

#endif /* SMARTINFO_H_ */
