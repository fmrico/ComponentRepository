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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#ifndef _PERSONDETECTIONTASK_HH
#define _PERSONDETECTIONTASK_HH

#include "PersonDetectionTaskCore.hh"
#include "visualization/PersonDetectionVisualization.hh"
#include <CommBasicObjects/CommVoid.hh>
#include <CommTrackingObjects/CommPersonDetectionEventResult.hh>
#include <CommTrackingObjects/CommPersonLostEventParameter.hh>
#include <CommTrackingObjects/CommDetectedPerson.hh>

class PersonDetectionTask  : public PersonDetectionTaskCore
{
private:
	PersonDetectionVisualization* personDetection;
	SmartACE::EventId id;
	//CommBasicObjects::CommVoid eventParameter;
	CommTrackingObjects::CommPersonLostEventParameter eventParameter;
	CommTrackingObjects::CommPersonDetectionEventResult eventResult;
public:
	PersonDetectionTask(SmartACE::SmartComponent *comp);
	virtual ~PersonDetectionTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
