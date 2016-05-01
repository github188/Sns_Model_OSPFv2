#include "OSPFv2Interface.h"


OSPFv2Interface::OSPFv2Interface(void)
{
}

IPv4Address OSPFv2Interface::getAddress() const
{
	return address;
}
void OSPFv2Interface::setAddress(const IPv4Address& address)
{
	this->address=address;
}
IPv4Mask OSPFv2Interface::getMask() const
{
	return mask;
}
void OSPFv2Interface::setMask(const IPv4Mask& mask)
{
	this->mask=mask;
}
UInt32 OSPFv2Interface::getAreaID() const
{
	return areaID;
}
void OSPFv2Interface::setAreaID(UInt32 areaID)
{
	this->areaID=areaID;
}
UInt32 OSPFv2Interface::getOutputCost() const
{
	return outputCost;
}
void OSPFv2Interface::setOutputCost(UInt32 outputcost)
{
	this->outputCost=outputcost;
}
clocktype OSPFv2Interface::getRxmtInterval() const
{
	return rxmtInterval;
}
void OSPFv2Interface::setRxmtInterval(clocktype rxmtInterval)
{
	this->rxmtInterval=rxmtInterval;
}
clocktype OSPFv2Interface::getInfTransDelay() const
{
	return infTransDelay;
}
void OSPFv2Interface::setInfTransDelay(clocktype infTransDelay)
{
	this->infTransDelay=infTransDelay;
}
clocktype OSPFv2Interface::getHelloInterval() const
{
	return helloInterval;
}
void OSPFv2Interface::setHelloInterval(clocktype helloInterval)
{
	this->helloInterval=helloInterval;
}
clocktype OSPFv2Interface::getRouterDeadInterval() const
{
	return routerDeadInterval;
}
void OSPFv2Interface::setRouterDeadInterval(clocktype routerDeadInterval)
{
	this->routerDeadInterval=routerDeadInterval;
}
