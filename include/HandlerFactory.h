/*
 * SmartRequestHandlerFactory.h
 *
 *  Created on: Sep 9, 2013
 *      Author: andy
 */

#ifndef SMARTREQUESTHANDLERFACTORY_H_
#define SMARTREQUESTHANDLERFACTORY_H_

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"

using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

class HandlerFactory : public HTTPRequestHandlerFactory {
public:
	HandlerFactory();
	virtual ~HandlerFactory();

	HTTPRequestHandler* createRequestHandler(
	        const HTTPServerRequest& request);
};

#endif /* SMARTREQUESTHANDLERFACTORY_H_ */
