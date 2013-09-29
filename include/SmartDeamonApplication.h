/*
 * ServerApp.h
 *
 *  Created on: Sep 28, 2013
 *      Author: andy
 */

#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#include <vector>
#include <string>

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"

using std::string;
using std::vector;

using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;

class SmartDeamonApplication : public ServerApplication {
public:
	SmartDeamonApplication();
	virtual ~SmartDeamonApplication();
protected:
	int main(const vector<string> &);

	void initialize(Application& self);
	void uninitialize();
	void defineOptions(OptionSet& options);
	void handleHelp(const string& name, const string& value);

private:
	bool helpRequested;
};

#endif /* SERVERAPP_H_ */
