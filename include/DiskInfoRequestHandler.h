/*
 * SmartAllRequestHandler.h
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#ifndef SMARTALLREQUESTHANDLER_H_
#define SMARTALLREQUESTHANDLER_H_

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/ExpireCache.h"
#include <string>
#include <vector>
#include "DiskInfo.h"

#include "HDDExplorer.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerRequest;
using Poco::ExpireCache;

using std::string;
using std::vector;

class DiskInfoRequestHandler : public HTTPRequestHandler {
public:
	DiskInfoRequestHandler();
	virtual ~DiskInfoRequestHandler();

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	static ExpireCache<string, DiskInfo> smartInfoCache;
	static ExpireCache<int, HDDExplorer > hddExplorerCache;
};

#endif /* SMARTALLREQUESTHANDLER_H_ */
