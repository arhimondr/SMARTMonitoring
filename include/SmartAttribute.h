/*
 * SmartAttribute.h
 *
 *  Created on: Sep 28, 2013
 *      Author: andy
 */

#ifndef SMARTATTRIBUTE_H_
#define SMARTATTRIBUTE_H_

#include <string>
#include <vector>

#include <atasmart.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

using std::string;
using std::vector;

using Poco::JSON::Object;
using Poco::JSON::Array;

class SmartAttribute {

private:
	uint8_t id;
	string name;

	uint16_t flags;
	uint8_t threshold;

	bool threshold_valid;
	bool online;
	string prefailure;

	/* Volatile data */
	bool good_now, good_now_valid;
	bool good_in_the_past, good_in_the_past_valid;
	bool current_value_valid, worst_value_valid;
	bool warn;

	uint8_t current_value, worst_value;
	uint64_t pretty_value;
	vector<uint8_t> raw;

public:
	SmartAttribute(const SkSmartAttributeParsedData * const a);

	virtual ~SmartAttribute();

	Object toJSONObject();

	inline uint8_t getCurrentValue() const {
		return current_value;
	}

	inline bool isCurrentValueValid() const {
		return current_value_valid;
	}

	inline uint16_t getFlags() const {
		return flags;
	}

	inline bool isGoodInThePast() const {
		return good_in_the_past;
	}

	inline bool isGoodInThePastValid() const {
		return good_in_the_past_valid;
	}

	inline bool isGoodNow() const {
		return good_now;
	}

	inline bool isGoodNowValid() const {
		return good_now_valid;
	}

	inline uint8_t getId() const {
		return id;
	}

	inline const string& getName() const {
		return name;
	}

	inline bool isOnline() const {
		return online;
	}

	inline const string& getPrefailure() const {
		return prefailure;
	}

	inline uint64_t getPrettyValue() const {
		return pretty_value;
	}

	inline uint8_t getThreshold() const {
		return threshold;
	}

	inline bool isThresholdValid() const {
		return threshold_valid;
	}

	inline bool isWarn() const {
		return warn;
	}

	inline uint8_t getWorstValue() const {
		return worst_value;
	}

	inline bool isWorstValueValid() const {
		return worst_value_valid;
	}

	inline const vector<uint8_t>& getRaw() const {
		return raw;
	}
};

#endif /* SMARTATTRIBUTE_H_ */
