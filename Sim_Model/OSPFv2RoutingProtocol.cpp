#include "OSPFv2RoutingProtocol.h"

const clocktype OSPFv2RoutingProtocolEntry::LS_REFRESH_TIME = SNS_Second_ConvertToClock(30*60);
const clocktype OSPFv2RoutingProtocolEntry::MIN_LS_INTERVAL = SNS_Second_ConvertToClock(5);
const clocktype OSPFv2RoutingProtocolEntry::MIN_LS_ARRIVAL = SNS_Second_ConvertToClock(1);
const clocktype OSPFv2RoutingProtocolEntry::MAX_AGE = SNS_Hour_ConvertToClock(1);
const clocktype OSPFv2RoutingProtocolEntry::CHECK_AGE = SNS_Second_ConvertToClock(5*60);
const clocktype OSPFv2RoutingProtocolEntry::MAX_AGE_DIFF = SNS_Second_ConvertToClock(15*60);
const UInt32 OSPFv2RoutingProtocolEntry::LS_INFINITY = 0xFFFFFFFF;
const IPv4Address OSPFv2RoutingProtocolEntry::DEFAULT_DESTINATION=IPv4Address::GetZeros();

OSPFv2RoutingProtocolEntry::OSPFv2RoutingProtocolEntry(void)
	:routerID(0xFFFFFFFF)
{
}

UInt32 OSPFv2RoutingProtocolEntry::getRouterID() const
{
	return routerID;
}
void OSPFv2RoutingProtocolEntry::setRouterID(UInt32 routerID)
{
	this->routerID=routerID;
}