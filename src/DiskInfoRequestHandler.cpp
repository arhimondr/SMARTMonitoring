/*
 * SmartAllRequestHandler.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#include "DiskInfoRequestHandler.h"

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "Poco/Net/HTMLForm.h"

#include "atasmart.h"
#include <vector>
#include <string>
#include <iterator>
#include "HDDExplorer.h"
#include "SmartInfo.h"

using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::Util::Application;
using Poco::Timestamp;
using Poco::NumberFormatter;
using Poco::SharedPtr;
using Poco::URI;
using Poco::Net::HTMLForm;

using std::vector;
using std::string;
using std::iterator;

ExpireCache<string, DiskInfo> DiskInfoRequestHandler::smartInfoCache;
ExpireCache<int, HDDExplorer > DiskInfoRequestHandler::hddExplorerCache;

DiskInfoRequestHandler::DiskInfoRequestHandler() {
	// TODO Auto-generated constructor stub

}

DiskInfoRequestHandler::~DiskInfoRequestHandler() {
	// TODO Auto-generated destructor stub
}

void DiskInfoRequestHandler::handleRequest(HTTPServerRequest& request,
		HTTPServerResponse& response) {

	Application& app = Application::instance();

	app.logger().information("Start processing request from: "+request.clientAddress().toString());

	Timestamp start;

	SharedPtr<HDDExplorer> explorer = hddExplorerCache.get(0);

	if(explorer.isNull()){
		explorer = new HDDExplorer;
		hddExplorerCache.add(0, explorer);
	}

	Object responseObject;

	if((*explorer).isSuccessfullyDiscovered() && (*explorer).getAvailableHDDs().size()>0){
		responseObject.set("found", true);

		vector<string> hdds = (*explorer).getAvailableHDDs();

		Array disks;

		for(vector<string>::iterator iter = hdds.begin(); iter!=hdds.end(); iter++){

			string hddPath = *iter;

			SharedPtr<DiskInfo> info = smartInfoCache.get(hddPath);

			if(info.isNull()){
				info = new DiskInfo(hddPath);
				smartInfoCache.add(hddPath, info);
			}

			Object jsonObject = (*info).toJSONObject();

			disks.add(jsonObject);

		}

		responseObject.set("disks", disks);
	} else {
		responseObject.set("found", false);
	}

	response.setContentType("application/javascript; charset=utf-8");

	HTMLForm form(request);

	string callbackFunc = "callback";

	if(form.has("callback") && !form.get("callback").empty()){
		callbackFunc = form.get("callback");
	}

	std::stringstream ostr;

	ostr<<callbackFunc<<"("; //send callback for JSONP
	responseObject.stringify(ostr);
	ostr<<")";

	string serialized = ostr.str();

	response.sendBuffer(serialized.c_str(), serialized.size());//connection keep-alive. We need to
	//know content-length

	Timestamp end;

	string secs = NumberFormatter::format((end-start)/1000)+" msecs";

	app.logger().information("Request from: "+request.clientAddress().toString()+
			" succesfully processed in "+secs);
}

