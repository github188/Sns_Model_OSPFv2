#pragma once
#include "Utilities.h"
#include "clock.h"
#include "OSPFv2Area.h"
#include "Ospfv2Header.h"
#include "OSPFv2Interface.h"
#include "Ospfv2LSA.h"
/************************************************************************/
/* OSPFv2 Parameters                                                                     */
/************************************************************************/
class OSPFv2RoutingProtocolEntry
{
public:
	//Architectural Constants
	static const clocktype LS_REFRESH_TIME;
	static const clocktype MIN_LS_INTERVAL;
	static const clocktype MIN_LS_ARRIVAL;
	static const clocktype MAX_AGE;
	static const clocktype CHECK_AGE;
	static const clocktype MAX_AGE_DIFF;
	static const UInt32 LS_INFINITY;
	static const IPv4Address DEFAULT_DESTINATION;
	//Contructors
	OSPFv2RoutingProtocolEntry(void);

	UInt32 getRouterID() const;
	void setRouterID(UInt32 routerID);
private:
	UInt32 routerID;
};

/************************************************************************/
/* OSPFv2 Routing Protocl                                                                     */
/************************************************************************/