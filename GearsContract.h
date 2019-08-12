#pragma once
#include <maf/messaging/client-server/CSContractBegin.mc.h>
#include <maf/messaging/client-server/CSContractDefines.mc.h>

#define SERVER_DOMAIN_NAME "com.opswat.agent"
#define SERVICE_ID_SCANNING_SERVICE 1


result_object_s(ScanningStatus)
	properties((int, percentage))
result_object_e(ScanningStatus)


#include <maf/messaging/client-server/CSContractEnd.mc.h>