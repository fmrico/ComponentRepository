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
#include "ComponentTTS.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "ComponentTTSAcePortFactory.hh"


// initialize static singleton pointer to zero
ComponentTTS* ComponentTTS::_componentTTS = 0;

// constructor
ComponentTTS::ComponentTTS()
{
	std::cout << "constructor of ComponentTTS\n";
	
	// set all pointer members to NULL
	//componentTTSParams = NULL;
	//coordinationPort = NULL;
	speechQueryHandler = NULL;
	speechQueryServiceAnsw = NULL;
	speechQueryServiceAnswInputTaskTrigger = NULL;
	speechSendHandler = NULL;
	speechSendServiceIn = NULL;
	speechSendServiceInInputTaskTrigger = NULL;
	speechSendServiceInUpcallManager = NULL;
	speechTask = NULL;
	speechTaskTrigger = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "ComponentTTS";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.speechQueryServiceAnsw.serviceName = "SpeechQueryServiceAnsw";
	connections.speechQueryServiceAnsw.roboticMiddleware = "ACE_SmartSoft";
	connections.speechSendServiceIn.serviceName = "SpeechSendServiceIn";
	connections.speechSendServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.speechTask.minActFreq = 0.0;
	connections.speechTask.maxActFreq = 0.0;
	// scheduling default parameters
	connections.speechTask.scheduler = "DEFAULT";
	connections.speechTask.priority = -1;
	connections.speechTask.cpuAffinity = -1;
	connections.speechSendHandler.prescale = 1;
	
	// initialize members of ComponentTTSROSExtension
	
	// initialize members of PlainOpcUaComponentTTSExtension
	
}

void ComponentTTS::addPortFactory(const std::string &name, ComponentTTSPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void ComponentTTS::addExtension(ComponentTTSExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* ComponentTTS::getComponentImpl()
{
	return dynamic_cast<ComponentTTSAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void ComponentTTS::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode ComponentTTS::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void ComponentTTS::startAllTasks() {
	// start task SpeechTask
	if(connections.speechTask.scheduler != "DEFAULT") {
		ACE_Sched_Params speechTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.speechTask.scheduler == "FIFO") {
			speechTask_SchedParams.policy(ACE_SCHED_FIFO);
			speechTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.speechTask.scheduler == "RR") {
			speechTask_SchedParams.policy(ACE_SCHED_RR);
			speechTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		speechTask->start(speechTask_SchedParams, connections.speechTask.cpuAffinity);
	} else {
		speechTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void ComponentTTS::startAllTimers() {
}


Smart::TaskTriggerSubject* ComponentTTS::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "SpeechSendServiceIn") return speechSendServiceInInputTaskTrigger;
	
	return NULL;
}


void ComponentTTS::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of ComponentTTSROSExtension
		
		// initializations of PlainOpcUaComponentTTSExtension
		
		
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
		
		ComponentTTSPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<ComponentTTSAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition ComponentTTS is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		speechQueryServiceAnsw = portFactoryRegistry[connections.speechQueryServiceAnsw.roboticMiddleware]->createSpeechQueryServiceAnsw(connections.speechQueryServiceAnsw.serviceName);
		speechQueryServiceAnswInputTaskTrigger = new Smart::QueryServerTaskTrigger<DomainSpeech::CommSpeechOutputMessage, CommBasicObjects::CommPropertySet,SmartACE::QueryId>(speechQueryServiceAnsw);
		speechSendServiceIn = portFactoryRegistry[connections.speechSendServiceIn.roboticMiddleware]->createSpeechSendServiceIn(connections.speechSendServiceIn.serviceName);
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		speechSendServiceInInputTaskTrigger = new Smart::InputTaskTrigger<DomainSpeech::CommSpeechOutputMessage>(speechSendServiceIn);
		speechSendServiceInUpcallManager = new SpeechSendServiceInUpcallManager(speechSendServiceIn);
		
		// create input-handler
		speechSendHandler = new SpeechSendHandler(speechSendServiceIn, connections.speechSendHandler.prescale);
		
		// create request-handlers
		speechQueryHandler = new SpeechQueryHandler(speechQueryServiceAnsw);
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task SpeechTask
		speechTask = new SpeechTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.speechTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.speechTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(speechTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				speechTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task SpeechTask" << std::endl;
			}
		} else if(connections.speechTask.trigger == "DataTriggered") {
			speechTaskTrigger = getInputTaskTriggerFromString(connections.speechTask.inPortRef);
			if(speechTaskTrigger != NULL) {
				speechTaskTrigger->attach(speechTask, connections.speechTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.speechTask.inPortRef << " as activation source for Task SpeechTask" << std::endl;
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
void ComponentTTS::run()
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
void ComponentTTS::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(speechTaskTrigger != NULL){
		speechTaskTrigger->detach(speechTask);
		delete speechTask;
	}

	// destroy all input-handler
	delete speechSendHandler;

	// destroy InputTaskTriggers and UpcallManagers
	delete speechSendServiceInInputTaskTrigger;
	delete speechSendServiceInUpcallManager;

	// destroy client ports

	// destroy server ports
	delete speechQueryServiceAnsw;
	delete speechQueryServiceAnswInputTaskTrigger;
	delete speechSendServiceIn;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete speechQueryHandler;
	
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
	
	// destruction of ComponentTTSROSExtension
	
	// destruction of PlainOpcUaComponentTTSExtension
	
}

void ComponentTTS::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("ComponentTTS.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load ComponentTTS.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: ComponentTTS.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		
		// load parameters for server SpeechQueryServiceAnsw
		parameter.getString("SpeechQueryServiceAnsw", "serviceName", connections.speechQueryServiceAnsw.serviceName);
		if(parameter.checkIfParameterExists("SpeechQueryServiceAnsw", "roboticMiddleware")) {
			parameter.getString("SpeechQueryServiceAnsw", "roboticMiddleware", connections.speechQueryServiceAnsw.roboticMiddleware);
		}
		// load parameters for server SpeechSendServiceIn
		parameter.getString("SpeechSendServiceIn", "serviceName", connections.speechSendServiceIn.serviceName);
		if(parameter.checkIfParameterExists("SpeechSendServiceIn", "roboticMiddleware")) {
			parameter.getString("SpeechSendServiceIn", "roboticMiddleware", connections.speechSendServiceIn.roboticMiddleware);
		}
		
		// load parameters for task SpeechTask
		parameter.getDouble("SpeechTask", "minActFreqHz", connections.speechTask.minActFreq);
		parameter.getDouble("SpeechTask", "maxActFreqHz", connections.speechTask.maxActFreq);
		parameter.getString("SpeechTask", "triggerType", connections.speechTask.trigger);
		if(connections.speechTask.trigger == "PeriodicTimer") {
			parameter.getDouble("SpeechTask", "periodicActFreqHz", connections.speechTask.periodicActFreq);
		} else if(connections.speechTask.trigger == "DataTriggered") {
			parameter.getString("SpeechTask", "inPortRef", connections.speechTask.inPortRef);
			parameter.getInteger("SpeechTask", "prescale", connections.speechTask.prescale);
		}
		if(parameter.checkIfParameterExists("SpeechTask", "scheduler")) {
			parameter.getString("SpeechTask", "scheduler", connections.speechTask.scheduler);
		}
		if(parameter.checkIfParameterExists("SpeechTask", "priority")) {
			parameter.getInteger("SpeechTask", "priority", connections.speechTask.priority);
		}
		if(parameter.checkIfParameterExists("SpeechTask", "cpuAffinity")) {
			parameter.getInteger("SpeechTask", "cpuAffinity", connections.speechTask.cpuAffinity);
		}
		if(parameter.checkIfParameterExists("SpeechSendHandler", "prescale")) {
			parameter.getInteger("SpeechSendHandler", "prescale", connections.speechSendHandler.prescale);
		}
		
		// load parameters for ComponentTTSROSExtension
		
		// load parameters for PlainOpcUaComponentTTSExtension
		
		
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
