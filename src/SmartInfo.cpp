/*
 * SmartInfo.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: andy
 */

#include <Poco/Util/Application.h>
#include "SmartInfo.h"

using Poco::Util::Application;

SmartInfo::SmartInfo() {
	poweredOnMsecs = powerCycles = temperatureK = badSectors = 0;
	diskStatus = false;
}

SmartInfo::SmartInfo(SkDisk *disk) {
	SkSmartOverall ovl;
	const SkSmartParsedData *spd;
	SkBool good;

	if (sk_disk_smart_status(disk, &good) < 0) {
		diskStatus = false;
	} else {
		diskStatus = !!good;
	}

	if (sk_disk_smart_read_data(disk) < 0)
		return;

	if (sk_disk_smart_parse(disk, &spd) < 0)
		return;

	/*printf("Off-line Data Collection Status: [%s]\n"
	 "Total Time To Complete Off-Line Data Collection: %u s\n"
	 "Self-Test Execution Status: [%s]\n"
	 "Percent Self-Test Remaining: %u%%\n"
	 "Conveyance Self-Test Available: %s\n"
	 "Short/Extended Self-Test Available: %s\n"
	 "Start Self-Test Available: %s\n"
	 "Abort Self-Test Available: %s\n"
	 "Short Self-Test Polling Time: %u min\n"
	 "Extended Self-Test Polling Time: %u min\n"
	 "Conveyance Self-Test Polling Time: %u min\n",
	 sk_smart_offline_data_collection_status_to_string(
	 spd->offline_data_collection_status),
	 spd->total_offline_data_collection_seconds,
	 sk_smart_self_test_execution_status_to_string(
	 spd->self_test_execution_status),
	 spd->self_test_execution_percent_remaining,
	 yes_no(spd->conveyance_test_available),
	 yes_no(spd->short_and_extended_test_available),
	 yes_no(spd->start_test_available),
	 yes_no(spd->abort_test_available), spd->short_test_polling_minutes,
	 spd->extended_test_polling_minutes,
	 spd->conveyance_test_polling_minutes);*/

	sk_disk_smart_get_bad(disk, &badSectors);
	sk_disk_smart_get_power_on(disk, &poweredOnMsecs);
	sk_disk_smart_get_power_cycle(disk, &powerCycles);
	sk_disk_smart_get_temperature(disk, &temperatureK);

	if (sk_disk_smart_get_overall(disk, &ovl) >= 0) {
		overall = sk_smart_overall_to_string(ovl);
	}

	readAttributes(disk);

}

void SmartInfo::readAttributes(SkDisk *disk) {

	attributeVerification = disk->attribute_verification_bad ? "Bad" : "Good";

	Application::instance().logger().information("Starting reading attributes");

	sk_disk_smart_parse_attributes(disk, &dumpAttributesCallback, this);

	Application::instance().logger().information(
			"Attributes successfully readed");
}

void SmartInfo::dumpAttributesCallback(SkDisk *d,
		const SkSmartAttributeParsedData *a, void* userdata) {
	Application::instance().logger().information("Dump callback called");

	SmartInfo &smartInfo = *((SmartInfo*) userdata);

	Application::instance().logger().information("Smart info converted");

	SmartAttribute smartAttribute(a);

	Application::instance().logger().information("Smart attribute parsed");

	smartInfo.attributes.push_back(smartAttribute);

	Application::instance().logger().information(
			"Smart attribute added to a list");
}

Object SmartInfo::toJSONObject() {
	Object smart;

	smart.set("diskStatus", diskStatus);
	smart.set("overall", overall);
	smart.set("badSectors", badSectors);
	smart.set("poweredOnMsecs", poweredOnMsecs);
	smart.set("powerCycles", powerCycles);
	smart.set("temperatureK", temperatureK);
	smart.set("attributeVerification", attributeVerification);

	Array attrArray;

	for (vector<SmartAttribute>::iterator iter = attributes.begin();
			iter != attributes.end(); iter++) {
		attrArray.add((*iter).toJSONObject());
	}

	smart.set("attributes", attrArray);

	return smart;
}

SmartInfo::~SmartInfo() {
	// TODO Auto-generated destructor stub
}

