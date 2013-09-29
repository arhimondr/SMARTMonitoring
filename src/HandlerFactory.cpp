/*
 * SmartRequestHandlerFactory.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#include "HandlerFactory.h"

#include "DiskInfoRequestHandler.h"

#include "Poco/URI.h"

using Poco::URI;

HandlerFactory::HandlerFactory() {
	// TODO Auto-generated constructor stub

}

HandlerFactory::~HandlerFactory() {
	// TODO Auto-generated destructor stub
}

HTTPRequestHandler* HandlerFactory::createRequestHandler(
		const HTTPServerRequest& request) {

	URI uri(request.getURI());

	if (uri.getPath() == "/status")
		return new DiskInfoRequestHandler;
	else
		return 0;

}
