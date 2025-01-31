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
#include "ComponentRealSenseV2Server.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "ComponentRealSenseV2ServerAcePortFactory.hh"


// initialize static singleton pointer to zero
ComponentRealSenseV2Server* ComponentRealSenseV2Server::_componentRealSenseV2Server = 0;

// constructor
ComponentRealSenseV2Server::ComponentRealSenseV2Server()
{
	std::cout << "constructor of ComponentRealSenseV2Server\n";
	
	// set all pointer members to NULL
	colorImageQueryHandler = NULL;
	//componentRealSenseV2ServerParams = NULL;
	//coordinationPort = NULL;
	imageQueryHandler = NULL;
	imageTask = NULL;
	imageTaskTrigger = NULL;
	urPosePushTimedClient = NULL;
	urPosePushTimedClientInputTaskTrigger = NULL;
	urPosePushTimedClientUpcallManager = NULL;
	urPoseQueryClient = NULL;
	basePushTimedClient = NULL;
	basePushTimedClientInputTaskTrigger = NULL;
	basePushTimedClientUpcallManager = NULL;
	colorImagePushNewestServer = NULL;
	colorImageQueryServer = NULL;
	colorImageQueryServerInputTaskTrigger = NULL;
	depthPushNewestServer = NULL;
	imagePushNewestServer = NULL;
	imageQueryServer = NULL;
	imageQueryServerInputTaskTrigger = NULL;
	ptuPosePushNewestClient = NULL;
	ptuPosePushNewestClientInputTaskTrigger = NULL;
	ptuPosePushNewestClientUpcallManager = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "ComponentRealSenseV2Server";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.colorImagePushNewestServer.serviceName = "colorImagePushNewestServer";
	connections.colorImagePushNewestServer.roboticMiddleware = "ACE_SmartSoft";
	connections.colorImageQueryServer.serviceName = "colorImageQueryServer";
	connections.colorImageQueryServer.roboticMiddleware = "ACE_SmartSoft";
	connections.depthPushNewestServer.serviceName = "depthPushNewestServer";
	connections.depthPushNewestServer.roboticMiddleware = "ACE_SmartSoft";
	connections.imagePushNewestServer.serviceName = "imagePushNewestServer";
	connections.imagePushNewestServer.roboticMiddleware = "ACE_SmartSoft";
	connections.imageQueryServer.serviceName = "imageQueryServer";
	connections.imageQueryServer.roboticMiddleware = "ACE_SmartSoft";
	connections.urPosePushTimedClient.wiringName = "UrPosePushTimedClient";
	connections.urPosePushTimedClient.serverName = "unknown";
	connections.urPosePushTimedClient.serviceName = "unknown";
	connections.urPosePushTimedClient.interval = 1;
	connections.urPosePushTimedClient.roboticMiddleware = "ACE_SmartSoft";
	connections.urPoseQueryClient.initialConnect = false;
	connections.urPoseQueryClient.wiringName = "UrPoseQueryClient";
	connections.urPoseQueryClient.serverName = "unknown";
	connections.urPoseQueryClient.serviceName = "unknown";
	connections.urPoseQueryClient.interval = 1;
	connections.urPoseQueryClient.roboticMiddleware = "ACE_SmartSoft";
	connections.basePushTimedClient.wiringName = "basePushTimedClient";
	connections.basePushTimedClient.serverName = "unknown";
	connections.basePushTimedClient.serviceName = "unknown";
	connections.basePushTimedClient.interval = 1;
	connections.basePushTimedClient.roboticMiddleware = "ACE_SmartSoft";
	connections.ptuPosePushNewestClient.wiringName = "ptuPosePushNewestClient";
	connections.ptuPosePushNewestClient.serverName = "unknown";
	connections.ptuPosePushNewestClient.serviceName = "unknown";
	connections.ptuPosePushNewestClient.interval = 1;
	connections.ptuPosePushNewestClient.roboticMiddleware = "ACE_SmartSoft";
	connections.imageTask.minActFreq = 0.0;
	connections.imageTask.maxActFreq = 0.0;
	connections.imageTask.trigger = "PeriodicTimer";
	connections.imageTask.periodicActFreq = 30.0;
	// scheduling default parameters
	connections.imageTask.scheduler = "DEFAULT";
	connections.imageTask.priority = -1;
	connections.imageTask.cpuAffinity = -1;
	
	// initialize members of ComponentRealSenseV2ServerROSExtension
	
	// initialize members of PlainOpcUaComponentRealSenseV2ServerExtension
	
}

void ComponentRealSenseV2Server::addPortFactory(const std::string &name, ComponentRealSenseV2ServerPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void ComponentRealSenseV2Server::addExtension(ComponentRealSenseV2ServerExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* ComponentRealSenseV2Server::getComponentImpl()
{
	return dynamic_cast<ComponentRealSenseV2ServerAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void ComponentRealSenseV2Server::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode ComponentRealSenseV2Server::connectUrPosePushTimedClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = urPosePushTimedClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->urPosePushTimedClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	urPosePushTimedClient->subscribe(connections.urPosePushTimedClient.interval);
	return status;
}
Smart::StatusCode ComponentRealSenseV2Server::connectUrPoseQueryClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.urPoseQueryClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = urPoseQueryClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->urPoseQueryClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}
Smart::StatusCode ComponentRealSenseV2Server::connectBasePushTimedClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = basePushTimedClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->basePushTimedClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	basePushTimedClient->subscribe(connections.basePushTimedClient.interval);
	return status;
}
Smart::StatusCode ComponentRealSenseV2Server::connectPtuPosePushNewestClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = ptuPosePushNewestClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->ptuPosePushNewestClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	ptuPosePushNewestClient->subscribe(connections.ptuPosePushNewestClient.interval);
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode ComponentRealSenseV2Server::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectUrPosePushTimedClient(connections.urPosePushTimedClient.serverName, connections.urPosePushTimedClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectUrPoseQueryClient(connections.urPoseQueryClient.serverName, connections.urPoseQueryClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectBasePushTimedClient(connections.basePushTimedClient.serverName, connections.basePushTimedClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectPtuPosePushNewestClient(connections.ptuPosePushNewestClient.serverName, connections.ptuPosePushNewestClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void ComponentRealSenseV2Server::startAllTasks() {
	// start task ImageTask
	if(connections.imageTask.scheduler != "DEFAULT") {
		ACE_Sched_Params imageTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.imageTask.scheduler == "FIFO") {
			imageTask_SchedParams.policy(ACE_SCHED_FIFO);
			imageTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.imageTask.scheduler == "RR") {
			imageTask_SchedParams.policy(ACE_SCHED_RR);
			imageTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		imageTask->start(imageTask_SchedParams, connections.imageTask.cpuAffinity);
	} else {
		imageTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void ComponentRealSenseV2Server::startAllTimers() {
}


Smart::TaskTriggerSubject* ComponentRealSenseV2Server::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "UrPosePushTimedClient") return urPosePushTimedClientInputTaskTrigger;
	if(client == "basePushTimedClient") return basePushTimedClientInputTaskTrigger;
	if(client == "ptuPosePushNewestClient") return ptuPosePushNewestClientInputTaskTrigger;
	
	return NULL;
}


void ComponentRealSenseV2Server::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of ComponentRealSenseV2ServerROSExtension
		
		// initializations of PlainOpcUaComponentRealSenseV2ServerExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		ComponentRealSenseV2ServerPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<ComponentRealSenseV2ServerAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition ComponentRealSenseV2Server is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		colorImagePushNewestServer = portFactoryRegistry[connections.colorImagePushNewestServer.roboticMiddleware]->createColorImagePushNewestServer(connections.colorImagePushNewestServer.serviceName);
		colorImageQueryServer = portFactoryRegistry[connections.colorImageQueryServer.roboticMiddleware]->createColorImageQueryServer(connections.colorImageQueryServer.serviceName);
		colorImageQueryServerInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, DomainVision::CommVideoImage,SmartACE::QueryId>(colorImageQueryServer);
		depthPushNewestServer = portFactoryRegistry[connections.depthPushNewestServer.roboticMiddleware]->createDepthPushNewestServer(connections.depthPushNewestServer.serviceName);
		imagePushNewestServer = portFactoryRegistry[connections.imagePushNewestServer.roboticMiddleware]->createImagePushNewestServer(connections.imagePushNewestServer.serviceName);
		imageQueryServer = portFactoryRegistry[connections.imageQueryServer.roboticMiddleware]->createImageQueryServer(connections.imageQueryServer.serviceName);
		imageQueryServerInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, DomainVision::CommRGBDImage,SmartACE::QueryId>(imageQueryServer);
		
		// create client ports
		urPosePushTimedClient = portFactoryRegistry[connections.urPosePushTimedClient.roboticMiddleware]->createUrPosePushTimedClient();
		urPoseQueryClient = portFactoryRegistry[connections.urPoseQueryClient.roboticMiddleware]->createUrPoseQueryClient();
		basePushTimedClient = portFactoryRegistry[connections.basePushTimedClient.roboticMiddleware]->createBasePushTimedClient();
		ptuPosePushNewestClient = portFactoryRegistry[connections.ptuPosePushNewestClient.roboticMiddleware]->createPtuPosePushNewestClient();
		
		// create InputTaskTriggers and UpcallManagers
		urPosePushTimedClientInputTaskTrigger = new Smart::InputTaskTrigger<CommManipulatorObjects::CommMobileManipulatorState>(urPosePushTimedClient);
		urPosePushTimedClientUpcallManager = new UrPosePushTimedClientUpcallManager(urPosePushTimedClient);
		basePushTimedClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommBaseState>(basePushTimedClient);
		basePushTimedClientUpcallManager = new BasePushTimedClientUpcallManager(basePushTimedClient);
		ptuPosePushNewestClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommDevicePoseState>(ptuPosePushNewestClient);
		ptuPosePushNewestClientUpcallManager = new PtuPosePushNewestClientUpcallManager(ptuPosePushNewestClient);
		
		// create input-handler
		
		// create request-handlers
		colorImageQueryHandler = new ColorImageQueryHandler(colorImageQueryServer);
		imageQueryHandler = new ImageQueryHandler(imageQueryServer);
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		if (stateSlave->defineStates("PushImage" ,"pushimage") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion PushImage.pushimage" << std::endl;
		if (stateSlave->defineStates("QueryImage" ,"queryonly") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion QueryImage.queryonly" << std::endl;
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.urPosePushTimedClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommManipulatorObjects::CommMobileManipulatorState>*>(urPosePushTimedClient)->add(wiringSlave, connections.urPosePushTimedClient.wiringName);
		}
		if(connections.urPoseQueryClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::QueryClient<CommBasicObjects::CommVoid, CommManipulatorObjects::CommMobileManipulatorState>*>(urPoseQueryClient)->add(wiringSlave, connections.urPoseQueryClient.wiringName);
		}
		if(connections.basePushTimedClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommBaseState>*>(basePushTimedClient)->add(wiringSlave, connections.basePushTimedClient.wiringName);
		}
		if(connections.ptuPosePushNewestClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommDevicePoseState>*>(ptuPosePushNewestClient)->add(wiringSlave, connections.ptuPosePushNewestClient.wiringName);
		}
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task ImageTask
		imageTask = new ImageTask(component);
		// configure input-links
		urPosePushTimedClientUpcallManager->attach(imageTask);
		basePushTimedClientUpcallManager->attach(imageTask);
		ptuPosePushNewestClientUpcallManager->attach(imageTask);
		// configure task-trigger (if task is configurable)
		if(connections.imageTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.imageTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(imageTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				imageTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task ImageTask" << std::endl;
			}
		} else if(connections.imageTask.trigger == "DataTriggered") {
			imageTaskTrigger = getInputTaskTriggerFromString(connections.imageTask.inPortRef);
			if(imageTaskTrigger != NULL) {
				imageTaskTrigger->attach(imageTask, connections.imageTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.imageTask.inPortRef << " as activation source for Task ImageTask" << std::endl;
			}
		} else
		{
			// setup default task-trigger as PeriodicTimer
			Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
			int microseconds = 1000*1000 / 30.0;
			if(microseconds > 0) {
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				triggerPtr->attach(imageTask);
				// store trigger in class member
				imageTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task ImageTask" << std::endl;
			}
		}
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void ComponentRealSenseV2Server::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void ComponentRealSenseV2Server::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	urPosePushTimedClientUpcallManager->detach(imageTask);
	basePushTimedClientUpcallManager->detach(imageTask);
	ptuPosePushNewestClientUpcallManager->detach(imageTask);
	// unlink the TaskTrigger
	if(imageTaskTrigger != NULL){
		imageTaskTrigger->detach(imageTask);
		delete imageTask;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete urPosePushTimedClientInputTaskTrigger;
	delete urPosePushTimedClientUpcallManager;
	delete basePushTimedClientInputTaskTrigger;
	delete basePushTimedClientUpcallManager;
	delete ptuPosePushNewestClientInputTaskTrigger;
	delete ptuPosePushNewestClientUpcallManager;

	// destroy client ports
	delete urPosePushTimedClient;
	delete urPoseQueryClient;
	delete basePushTimedClient;
	delete ptuPosePushNewestClient;

	// destroy server ports
	delete colorImagePushNewestServer;
	delete colorImageQueryServer;
	delete colorImageQueryServerInputTaskTrigger;
	delete depthPushNewestServer;
	delete imagePushNewestServer;
	delete imageQueryServer;
	delete imageQueryServerInputTaskTrigger;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete colorImageQueryHandler;
	delete imageQueryHandler;
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of ComponentRealSenseV2ServerROSExtension
	
	// destruction of PlainOpcUaComponentRealSenseV2ServerExtension
	
}

void ComponentRealSenseV2Server::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("ComponentRealSenseV2Server.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load ComponentRealSenseV2Server.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: ComponentRealSenseV2Server.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client UrPosePushTimedClient
		parameter.getString("UrPosePushTimedClient", "serviceName", connections.urPosePushTimedClient.serviceName);
		parameter.getString("UrPosePushTimedClient", "serverName", connections.urPosePushTimedClient.serverName);
		parameter.getString("UrPosePushTimedClient", "wiringName", connections.urPosePushTimedClient.wiringName);
		parameter.getInteger("UrPosePushTimedClient", "interval", connections.urPosePushTimedClient.interval);
		if(parameter.checkIfParameterExists("UrPosePushTimedClient", "roboticMiddleware")) {
			parameter.getString("UrPosePushTimedClient", "roboticMiddleware", connections.urPosePushTimedClient.roboticMiddleware);
		}
		// load parameters for client UrPoseQueryClient
		parameter.getBoolean("UrPoseQueryClient", "initialConnect", connections.urPoseQueryClient.initialConnect);
		parameter.getString("UrPoseQueryClient", "serviceName", connections.urPoseQueryClient.serviceName);
		parameter.getString("UrPoseQueryClient", "serverName", connections.urPoseQueryClient.serverName);
		parameter.getString("UrPoseQueryClient", "wiringName", connections.urPoseQueryClient.wiringName);
		if(parameter.checkIfParameterExists("UrPoseQueryClient", "roboticMiddleware")) {
			parameter.getString("UrPoseQueryClient", "roboticMiddleware", connections.urPoseQueryClient.roboticMiddleware);
		}
		// load parameters for client basePushTimedClient
		parameter.getString("basePushTimedClient", "serviceName", connections.basePushTimedClient.serviceName);
		parameter.getString("basePushTimedClient", "serverName", connections.basePushTimedClient.serverName);
		parameter.getString("basePushTimedClient", "wiringName", connections.basePushTimedClient.wiringName);
		parameter.getInteger("basePushTimedClient", "interval", connections.basePushTimedClient.interval);
		if(parameter.checkIfParameterExists("basePushTimedClient", "roboticMiddleware")) {
			parameter.getString("basePushTimedClient", "roboticMiddleware", connections.basePushTimedClient.roboticMiddleware);
		}
		// load parameters for client ptuPosePushNewestClient
		parameter.getString("ptuPosePushNewestClient", "serviceName", connections.ptuPosePushNewestClient.serviceName);
		parameter.getString("ptuPosePushNewestClient", "serverName", connections.ptuPosePushNewestClient.serverName);
		parameter.getString("ptuPosePushNewestClient", "wiringName", connections.ptuPosePushNewestClient.wiringName);
		parameter.getInteger("ptuPosePushNewestClient", "interval", connections.ptuPosePushNewestClient.interval);
		if(parameter.checkIfParameterExists("ptuPosePushNewestClient", "roboticMiddleware")) {
			parameter.getString("ptuPosePushNewestClient", "roboticMiddleware", connections.ptuPosePushNewestClient.roboticMiddleware);
		}
		
		// load parameters for server colorImagePushNewestServer
		parameter.getString("colorImagePushNewestServer", "serviceName", connections.colorImagePushNewestServer.serviceName);
		if(parameter.checkIfParameterExists("colorImagePushNewestServer", "roboticMiddleware")) {
			parameter.getString("colorImagePushNewestServer", "roboticMiddleware", connections.colorImagePushNewestServer.roboticMiddleware);
		}
		// load parameters for server colorImageQueryServer
		parameter.getString("colorImageQueryServer", "serviceName", connections.colorImageQueryServer.serviceName);
		if(parameter.checkIfParameterExists("colorImageQueryServer", "roboticMiddleware")) {
			parameter.getString("colorImageQueryServer", "roboticMiddleware", connections.colorImageQueryServer.roboticMiddleware);
		}
		// load parameters for server depthPushNewestServer
		parameter.getString("depthPushNewestServer", "serviceName", connections.depthPushNewestServer.serviceName);
		if(parameter.checkIfParameterExists("depthPushNewestServer", "roboticMiddleware")) {
			parameter.getString("depthPushNewestServer", "roboticMiddleware", connections.depthPushNewestServer.roboticMiddleware);
		}
		// load parameters for server imagePushNewestServer
		parameter.getString("imagePushNewestServer", "serviceName", connections.imagePushNewestServer.serviceName);
		if(parameter.checkIfParameterExists("imagePushNewestServer", "roboticMiddleware")) {
			parameter.getString("imagePushNewestServer", "roboticMiddleware", connections.imagePushNewestServer.roboticMiddleware);
		}
		// load parameters for server imageQueryServer
		parameter.getString("imageQueryServer", "serviceName", connections.imageQueryServer.serviceName);
		if(parameter.checkIfParameterExists("imageQueryServer", "roboticMiddleware")) {
			parameter.getString("imageQueryServer", "roboticMiddleware", connections.imageQueryServer.roboticMiddleware);
		}
		
		// load parameters for task ImageTask
		parameter.getDouble("ImageTask", "minActFreqHz", connections.imageTask.minActFreq);
		parameter.getDouble("ImageTask", "maxActFreqHz", connections.imageTask.maxActFreq);
		parameter.getString("ImageTask", "triggerType", connections.imageTask.trigger);
		if(connections.imageTask.trigger == "PeriodicTimer") {
			parameter.getDouble("ImageTask", "periodicActFreqHz", connections.imageTask.periodicActFreq);
		} else if(connections.imageTask.trigger == "DataTriggered") {
			parameter.getString("ImageTask", "inPortRef", connections.imageTask.inPortRef);
			parameter.getInteger("ImageTask", "prescale", connections.imageTask.prescale);
		}
		if(parameter.checkIfParameterExists("ImageTask", "scheduler")) {
			parameter.getString("ImageTask", "scheduler", connections.imageTask.scheduler);
		}
		if(parameter.checkIfParameterExists("ImageTask", "priority")) {
			parameter.getInteger("ImageTask", "priority", connections.imageTask.priority);
		}
		if(parameter.checkIfParameterExists("ImageTask", "cpuAffinity")) {
			parameter.getInteger("ImageTask", "cpuAffinity", connections.imageTask.cpuAffinity);
		}
		
		// load parameters for ComponentRealSenseV2ServerROSExtension
		
		// load parameters for PlainOpcUaComponentRealSenseV2ServerExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
