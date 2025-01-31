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

// --------------------------------------------------------------------------
//
//  Copyright (C) 2009 Christian Schlegel, Andreas Steck, Matthias Lutz
//
//        schlegel@hs-ulm.de
//        steck@hs-ulm.de
//
//        ZAFH Servicerobotik Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        D-89075 Ulm
//        Germany
//
//  This file is part of the "SmartSoft smartPlannerBreadthFirstSearch component".
//  It provides planning services based on grid maps.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------


#ifndef _PLANNERTASK_HH
#define _PLANNERTASK_HH

#include "PlannerTaskCore.hh"

#include "smartPlannerMap.hh"
	
class PlannerTask  : public PlannerTaskCore
{
private:
	GoalFifoStructPtr goalFifoPtr;
	CommBasicObjects::CommBaseState base_state;
	CommNavigationObjects::CommGridMap currentGridMap;
	CommNavigationObjects::CommPlannerGoal plannerGoal;
	CommNavigationObjects::PlannerEventType    generalstatus;
	Smart::PlannerMapClass *plannerMap;

	// not used upcall methods (instead the methods get...(input) are used)
//	virtual void on_CurMapClient(const CommNavigationObjects::CommGridMap &input);
//	virtual void on_BaseStateClient(const CommBasicObjects::CommBaseState &input);
public:
	PlannerTask(SmartACE::SmartComponent *comp);
	virtual ~PlannerTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
