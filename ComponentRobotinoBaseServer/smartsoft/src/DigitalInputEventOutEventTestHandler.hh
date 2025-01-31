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
#ifndef _DIGITALINPUTEVENTOUT_EVENT_TEST_HANDLER_USER_HH
#define _DIGITALINPUTEVENTOUT_EVENT_TEST_HANDLER_USER_HH
		
#include "DigitalInputEventOutEventTestHandlerCore.hh"

class DigitalInputEventOutEventTestHandler : public DigitalInputEventOutEventTestHandlerCore
{
public:
	virtual bool testEvent(
		CommRobotinoObjects::CommDigitalInputEventParameter &p,
		CommRobotinoObjects::CommDigitalInputEventResult &r,
		const CommRobotinoObjects::CommDigitalInputEventState &s
	) throw();
};
#endif
