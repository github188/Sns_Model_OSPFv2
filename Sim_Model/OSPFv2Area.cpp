#include "OSPFv2Area.h"


OSPFv2Area::OSPFv2Area(void)
	: areaID(OSPFv2_SINGLE_AREA_ID)
	, externalRoutingCapability(false)
	, stubDefaultCost(5)
{

}

UInt32 OSPFv2Area::getAreaID() const
{
	return areaID;
}
void OSPFv2Area::setAreaID(UInt32 areaID)
{
	this->areaID=areaID;
}
UInt32 OSPFv2Area::getStubDefaultCost() const
{
	return stubDefaultCost;
}
void OSPFv2Area::setStubDefaultCost(UInt32 stubDefaultCost)
{
	this->stubDefaultCost=stubDefaultCost;
}