/*
 * SmartAttribute.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: andy
 */

#include "SmartAttribute.h"

SmartAttribute::SmartAttribute(const SkSmartAttributeParsedData  * const a) {

	this->id = a->id;
	this->warn = !!a->warn;
	this->name = a->name;

	this->threshold = a->threshold;
	this->threshold_valid = !!a->threshold_valid;
	this->worst_value = a->worst_value;
	this->worst_value_valid = !!a->worst_value_valid;
	this->current_value = a->current_value;
	this->current_value_valid = !!a->current_value_valid;

	this->pretty_value = a->pretty_value;

	this->raw.assign(a->raw, a->raw+6);

	this->prefailure = a->prefailure ? "prefail" : "old-age";
	this->online = !!a->online;

	this->good_now_valid = !!a->good_now_valid;
	this->good_now = !!a->good_now;

	this->good_in_the_past_valid = !!a->good_in_the_past_valid;
	this->good_in_the_past = !!a->good_in_the_past;

	this->flags = 0;

}

SmartAttribute::~SmartAttribute() {
	// TODO Auto-generated destructor stub
}

Object SmartAttribute::toJSONObject(){
	Object object;

	object.set("id",id);
	object.set("warn",warn);
	object.set("name",name);
	object.set("threshold",threshold);
	object.set("threshold_valid",threshold_valid);
	object.set("worst_value",worst_value);
	object.set("worst_value_valid",worst_value_valid);
	object.set("current_value",current_value);
	object.set("current_value_valid",current_value_valid);
	object.set("pretty_value",pretty_value);
	object.set("prefailure",prefailure);
	object.set("online",online);
	object.set("good_now_valid",good_now_valid);
	object.set("good_now",good_now);
	object.set("good_in_the_past_valid",good_in_the_past_valid);
	object.set("good_in_the_past",good_in_the_past);
	object.set("flags",flags);

	Array rawValues;

	for(vector<uint8_t>::iterator iter = raw.begin(); iter!=raw.end(); iter++){
		rawValues.add(*iter);
	}

	object.set("raw", rawValues);


	return object;
}

