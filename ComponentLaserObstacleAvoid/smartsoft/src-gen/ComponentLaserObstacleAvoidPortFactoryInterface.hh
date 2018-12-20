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

#ifndef COMPONENTLASEROBSTACLEAVOID_PORTFACTORYINTERFACE_HH_
#define COMPONENTLASEROBSTACLEAVOID_PORTFACTORYINTERFACE_HH_

// include communication objects
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>
#include <CommBasicObjects/CommNavigationVelocity.hh>
#include <CommBasicObjects/CommNavigationVelocityACE.hh>

#include <chrono>

// include component's main class
#include "ComponentLaserObstacleAvoid.hh"

// forward declaration
class ComponentLaserObstacleAvoid;

class ComponentLaserObstacleAvoidPortFactoryInterface {
public:
	ComponentLaserObstacleAvoidPortFactoryInterface() { };
	virtual ~ComponentLaserObstacleAvoidPortFactoryInterface() { };

	virtual void initialize(ComponentLaserObstacleAvoid *component, int argc, char* argv[]) = 0;
	virtual int onStartup() = 0;

	virtual Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> * createLaserServiceIn() = 0;
	virtual Smart::ISendClientPattern<CommBasicObjects::CommNavigationVelocity> * createNavigationVelocityServiceOut() = 0;
	

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) = 0;
	virtual void destroy() = 0;
};

#endif /* COMPONENTLASEROBSTACLEAVOID_PORTFACTORYINTERFACE_HH_ */
