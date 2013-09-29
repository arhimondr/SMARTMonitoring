/*
 * ServerApp.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: andy
 */

#include <Poco/Logger.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/NumberFormatter.h>
#include <SmartDeamonApplication.h>
#include <HandlerFactory.h>
#include <iostream>
#include <new>
#include <string>
#include <vector>

using Poco::Net::HTTPServer;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPServerParams;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::NumberFormatter;

using std::cout;
using std::endl;

SmartDeamonApplication::SmartDeamonApplication() : helpRequested(false) {
	// TODO Auto-generated constructor stub

}

SmartDeamonApplication::~SmartDeamonApplication() {
	// TODO Auto-generated destructor stub
}

int SmartDeamonApplication::main(const vector<string> &){
	if (!helpRequested) {
		unsigned short port = (unsigned short) config().getInt(
				"HTTPTimeServer.port", 8080);

		ServerSocket svs(port);

		HTTPServerParams *params = new HTTPServerParams;
		params->setKeepAlive(true);
		params->setKeepAliveTimeout(60*1000*1000/*microseconds*/);

		HTTPServer srv(new HandlerFactory, svs, params);

		Application& app = Application::instance();

		srv.start();

		app.logger().information("Server started on port: "+ NumberFormatter::format(port));

		waitForTerminationRequest();

		srv.stop();

		app.logger().information("Server stopped");
	}
	return Application::EXIT_OK;
}


void SmartDeamonApplication::initialize(Application& self) {
	loadConfiguration();
	ServerApplication::initialize(self);
}

void SmartDeamonApplication::uninitialize() {
	ServerApplication::uninitialize();
}

void SmartDeamonApplication::defineOptions(OptionSet& options) {
	ServerApplication::defineOptions(options);

	Option helpOption("help", "h", "display argument help information");
	helpOption.required(false);
	helpOption.repeatable(false);
	OptionCallback<SmartDeamonApplication> helpOptionCallback(this, &SmartDeamonApplication::handleHelp);
	helpOption.callback(helpOptionCallback);
	options.addOption(helpOption);

}

void SmartDeamonApplication::handleHelp(const std::string& name, const std::string& value) {
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A web server that serves the S.M.A.R.T. statistics for available HDDs");
	helpFormatter.format(std::cout);
	stopOptionsProcessing();
	helpRequested = true;
}


