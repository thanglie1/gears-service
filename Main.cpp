#include <iostream>
#include <maf/messaging/client-server/ipc/LocalIPCServiceStub.h>
#include <maf/messaging/client-server/ipc/LocalIPCServer.h>
#include <maf/messaging/Component.h>
#include <maf/messaging/Timer.h>
#include "GearsContract.h"

using namespace maf::messaging;

class ScanServiceComp : public Component
{
public:
	void start()
	{
		this->_detached = false;
		onMessage<ipc::IPCClientRequestMsg>([this](CMessagePtr<ipc::IPCClientRequestMsg>& msg) {
			auto requestKeeper = msg->getRequestKeeper();
			if (requestKeeper->getOperationCode() == OpCode::Request && requestKeeper->getOperationID() == CSC_OpID_ScanningStatus)
			{
				//_timer.start(1000, [requestKeeper, this] {
					auto status = ScanningStatusResult::create();
					std::this_thread::sleep_for(std::chrono::seconds(1));
					status->props().set_percentage(_percentage++);
					requestKeeper->update(status);
					//});
			}
			/*else if (requestKeeper->getOperationCode() == OpCode::Abort)
			{
				_timer.stop();
			}*/
			});

		Component::start([this] {
			_serviceStub = ipc::LocalIPCServiceStub::createStub(SERVICE_ID_SCANNING_SERVICE);
			});
	}
	maf::messaging::Timer _timer;
	int _percentage = 0;
	std::shared_ptr<ipc::LocalIPCServiceStub> _serviceStub;
};

int main()
{
	ipc::LocalIPCServer::instance().init(Address{ SERVER_DOMAIN_NAME, 0 });
	ScanServiceComp comp;
	comp.start();
}