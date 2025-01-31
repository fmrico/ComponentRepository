//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _COMPONENTLASERHOKUYOURGSERVER_HH
#define _COMPONENTLASERHOKUYOURGSERVER_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentLaserHokuyoURGServerCore.hh"

#include "ComponentLaserHokuyoURGServerPortFactoryInterface.hh"
#include "ComponentLaserHokuyoURGServerExtension.hh"

// forward declarations
class ComponentLaserHokuyoURGServerPortFactoryInterface;
class ComponentLaserHokuyoURGServerExtension;

// includes for ComponentLaserHokuyoURGServerROSExtension

// includes for PlainOpcUaComponentLaserHokuyoURGServerExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>
#include <CommManipulatorObjects/CommMobileManipulatorState.hh>
#include <CommManipulatorObjects/CommMobileManipulatorStateACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>

// include tasks
#include "LaserTask.hh"
#include "WatchDogTask.hh"
// include UpcallManagers
#include "BaseTimedClientUpcallManager.hh"
#include "ManipulatorTimedClientUpcallManager.hh"

// include input-handler
// include input-handler
#include "LaserQueryServerHandler.hh"

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP ComponentLaserHokuyoURGServer::instance()

class ComponentLaserHokuyoURGServer : public ComponentLaserHokuyoURGServerCore {
private:
	static ComponentLaserHokuyoURGServer *_componentLaserHokuyoURGServer;
	
	// constructor
	ComponentLaserHokuyoURGServer();
	
	// copy-constructor
	ComponentLaserHokuyoURGServer(const ComponentLaserHokuyoURGServer& cc);
	
	// destructor
	~ComponentLaserHokuyoURGServer() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ComponentLaserHokuyoURGServerPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ComponentLaserHokuyoURGServerExtension*> componentExtensionRegistry;
	
public:
	ParameterStateStruct getGlobalState() const
	{
		return paramHandler.getGlobalState();
	}
	
	ParameterStateStruct getParameters() const
	{
		return paramHandler.getGlobalState();
	}
	
	// define tasks
	Smart::TaskTriggerSubject* laserTaskTrigger;
	LaserTask *laserTask;
	Smart::TaskTriggerSubject* watchDogTaskTrigger;
	WatchDogTask *watchDogTask;
	
	// define input-ports
	// InputPort baseTimedClient
	Smart::IPushClientPattern<CommBasicObjects::CommBaseState> *baseTimedClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommBaseState> *baseTimedClientInputTaskTrigger;
	BaseTimedClientUpcallManager *baseTimedClientUpcallManager;
	// InputPort manipulatorTimedClient
	Smart::IPushClientPattern<CommManipulatorObjects::CommMobileManipulatorState> *manipulatorTimedClient;
	Smart::InputTaskTrigger<CommManipulatorObjects::CommMobileManipulatorState> *manipulatorTimedClientInputTaskTrigger;
	ManipulatorTimedClientUpcallManager *manipulatorTimedClientUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IPushServerPattern<CommBasicObjects::CommMobileLaserScan> *laserPushNewestServer;
	
	// define answer-ports
	Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommMobileLaserScan,SmartACE::QueryId> *laserQueryServer;
	Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, CommBasicObjects::CommMobileLaserScan,SmartACE::QueryId> *laserQueryServerInputTaskTrigger;
	
	// define request-handlers
	LaserQueryServerHandler *laserQueryServerHandler;
	
	// definitions of ComponentLaserHokuyoURGServerROSExtension
	
	// definitions of PlainOpcUaComponentLaserHokuyoURGServerExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ComponentLaserHokuyoURGServerPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ComponentLaserHokuyoURGServerExtension *extension);
	
	/// this method allows to access the registered component-extensions (automatically converting to the actuall implementation type)
	template <typename T>
	T* getExtension(const std::string &name) {
		auto it = componentExtensionRegistry.find(name);
		if(it != componentExtensionRegistry.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return 0;
	}
	
	/// initialize component's internal members
	void init(int argc, char *argv[]);
	
	/// execute the component's infrastructure
	void run();
	
	/// clean-up component's resources
	void fini();
	
	/// call this method to set the overall component into the Alive state (i.e. component is then ready to operate)
	void setStartupFinished();
	
	/// connect all component's client ports
	Smart::StatusCode connectAndStartAllServices();
	
	/// start all assocuated Activities
	void startAllTasks();
	
	/// start all associated timers
	void startAllTimers();
	
	Smart::StatusCode connectBaseTimedClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectManipulatorTimedClient(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static ComponentLaserHokuyoURGServer* instance()
	{
		if(_componentLaserHokuyoURGServer == 0) {
			_componentLaserHokuyoURGServer = new ComponentLaserHokuyoURGServer();
		}
		return _componentLaserHokuyoURGServer;
	}
	
	static void deleteInstance() {
		if(_componentLaserHokuyoURGServer != 0) {
			delete _componentLaserHokuyoURGServer;
		}
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		struct LaserTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} laserTask;
		struct WatchDogTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} watchDogTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct LaserPushNewestServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} laserPushNewestServer;
		struct LaserQueryServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} laserQueryServer;
	
		//--- client port parameter ---
		struct BaseTimedClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} baseTimedClient;
		struct ManipulatorTimedClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} manipulatorTimedClient;
		
		// -- parameters for ComponentLaserHokuyoURGServerROSExtension
		
		// -- parameters for PlainOpcUaComponentLaserHokuyoURGServerExtension
		
	} connections;
};
#endif
