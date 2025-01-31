//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain Version 0.10.2
// The SmartSoft Toolchain has been developed by:
//
// ZAFH Servicerobotic Ulm
// Christian Schlegel (schlegel@hs-ulm.de)
// University of Applied Sciences
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// smart-robotics.sourceforge.net
//
// This file is generated once. Modify this file to your needs.
// If you want the toolchain to re-generate this file, please
// delete it before running the code generator.
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//
//  Copyright (C) 	2009-2012 Andreas Steck
//
//      steck@hs-ulm.de
//		schlegel@hs-ulm.de
//
//      ZAFH Servicerobotic Ulm
//      Christian Schlegel
//      University of Applied Sciences
//      Prittwitzstr. 10
//      89075 Ulm
//      Germany
//
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
//--------------------------------------------------------------------------

#include "HandlerTimerService.hh"
#include "ComponentTCLSequencer.hh"

#include <iostream>

void HandlerTimerService::timerExpired(const std::chrono::system_clock::time_point &abs_time, const void * arg)
{
	long *currCounter = (long*)arg;
	TimerParam param = ids[*currCounter];

	std::cout << "expired: " << param.param << " id: " << *currCounter << std::endl;

	char eventResult[LISP_STRING];
	sprintf(eventResult,"((timer timer %s %d) nil)",param.param.c_str(), (int)*currCounter);
	COMP->eventInterface->append(eventResult);

	delete currCounter;
}

long HandlerTimerService::scheduleTimer(const std::string &param, const ACE_Time_Value & absolute_time)
{
	counter++;
	ids[counter].param = param;

	long *counterParam = new long;
	*counterParam = counter;

	ids[counter].internalId = COMP->getComponentImpl()->getTimerManager()->scheduleTimer(this, (void*)counterParam, SmartACE::convertToStdDurFrom(absolute_time));

	return counter;
}

int HandlerTimerService::cancelTimer(long id)
{
	if(ids.find(id) == ids.end())
	{
		// illegal id
		return -1;
	}

	COMP->getComponentImpl()->getTimerManager()->cancelTimer(ids[id].internalId);

	ids.erase(ids.find(id));

	return 0;
}
