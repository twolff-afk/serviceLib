#include "methodGetService.h"

#include "logUtil.h"
#include "util.h"
#include "configFileUtil.h"
#include "open62541Util.h"

static UA_StatusCode getService(
    UA_Server* server, const UA_NodeId* sessionId,
    void* sessionHandle, const UA_NodeId* methodId,
    void* methodContext, const UA_NodeId* objectId,
    void* objectContext, size_t inputSize,
    const UA_Variant* input, size_t outputSize,
    UA_Variant* output) {

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetService).name(), __LINE__, "getService was called");

    UA_String* Input = (UA_String*)input->data;
    std::string serviceName = open62541Util::uaStringPtrToStdString(Input);

    logUtil::writeLogMessageToConsoleAndFile("info", typeid(methodGetService).name(), __LINE__, "Get Service: " + serviceName);

    configFileUtil::confParam config = configFileUtil::readConfig();

    std::string serviceAsString = util::getFile(config.pathToServices + serviceName);
    const char* service = serviceAsString.c_str();

    UA_String result;
    UA_String_init(&result);

    result.length = strlen(service);
    result.data = (UA_Byte*)service;

    UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

void methodGetService::createMethod(UA_Server* server) {

    char inputText[] = "Get Service";
    UA_Argument inputArgument = createStringArgument(inputText);

    char outputText[] = "Result";
    UA_Argument outputArgument = createStringArgument(outputText);

    char methodeName[] = "Get Service";
    UA_MethodAttributes methodAttributes = createMethodAttributes(methodeName);

    UA_Server_addMethodNode (
        server, UA_NODEID_STRING(1, methodeName),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, methodeName),
        methodAttributes, &getService,
        1, &inputArgument, 1, &outputArgument, NULL, NULL
    );
}