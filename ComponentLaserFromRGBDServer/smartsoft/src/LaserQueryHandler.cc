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

//------------------------------------------------------------------------
//
//  Copyright (C) 2018 Nayabrasul Shaik, Matthias Lutz, Matthias Rollenhagen
//
//        shaik@hs-ulm.de, lutz@hs-ulm.de, rollenhagen@hs-ulm.de
//
//        Christian Schlegel (schlegel@hs-ulm.de)
//        University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm (Germany)
//
//  This file is part of the "SmartLaserFromRGBDServer component".
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
//--------------------------------------------------------------------------
#include "LaserQueryHandler.hh"
#include "ComponentLaserFromRGBDServer.hh"

LaserQueryHandler::LaserQueryHandler(Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommMobileLaserScan, SmartACE::QueryId>* server)
:	LaserQueryHandlerCore(server)
{
	

}

LaserQueryHandler::~LaserQueryHandler()
{
	
}


void LaserQueryHandler::handleQuery(const SmartACE::QueryId &id, const CommBasicObjects::CommVoid& request) 
{
	if (COMP->getGlobalState().getScanner().getVerbose())
				std::cout << "read new laser data\n";

			// return scan
			SmartACE::SmartGuard guard(COMP->ScanLock);
			server->answer(id, COMP->global_scan);
			guard.release();
}
