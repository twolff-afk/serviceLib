#include "opcuaServer.h"

#include "logUtil.h"
#include "methodSaveWsdl.h"
#include "methodGetProcess.h"
#include "methodGetService.h"
#include "methodSaveProcess.h"
#include "methodGetListOf.h"
#include "methodSaveServiceOfProcess.h"
#include "methodGetServiceOfProcess.h"

#include <open62541/server_config_default.h>

opcuaServer::opcuaServer() {

	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Create Server Instance");

	server = UA_Server_new();
	UA_ServerConfig* config = UA_Server_getConfig(server);

	UA_ServerConfig_setMinimal(config, 10002, NULL);
	UA_String_clear(&config->applicationDescription.applicationUri);
	config->applicationDescription.applicationUri = UA_String_fromChars("urn:serviceLib");

	methodSaveWsdl::createMethod(server);
	methodGetService::createMethod(server);
	methodSaveProcess::createMethod(server);
	methodGetProcess::createMethod(server);
	methodGetListOf::createMethod(server);
	methodSaveServiceOfProcess::createMethod(server);
	methodGetServiceOfProcess::createMethod(server);
}

void opcuaServer::startServer() {

	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Start Server");

	UA_StatusCode status = UA_Server_run(server, &running);
}

opcuaServer::~opcuaServer() {

	logUtil::writeLogMessageToConsoleAndFile("info", typeid(opcuaServer).name(), __LINE__, "Delete Server Instance");

	UA_Server_delete(server);
}