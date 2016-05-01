#pragma once
#include "StdAfx.h"
#include "Utilities.h"
class OPSFv2AreaRangeEntry
{
public:
	enum AreaRangeEntryStatus
	{
		DoNotAdvertise = 0,
		Advertise = 1,
	};
	OPSFv2AreaRangeEntry()
		: address(IPv4Address::GetOnes())
		, mask(IPv4Address::GetOnes())
		, status(AreaRangeEntryStatus::DoNotAdvertise)
	{

	}
private:
	IPv4Address address;
	IPv4Mask mask;
	AreaRangeEntryStatus status;
};

class OSPFv2Area
{
public:
	static const UInt32 OSPFv2_SINGLE_AREA_ID = 0xFFFFFFFF;

	OSPFv2Area(void);

	UInt32 getAreaID() const;
	void setAreaID(UInt32 areaID);
	UInt32 getStubDefaultCost() const;
	void setStubDefaultCost(UInt32 stubDefaultCost);

private:
	UInt32 areaID;
	std::vector<OPSFv2AreaRangeEntry> areaRange;//unused
	bool externalRoutingCapability;//unused
	UInt32 stubDefaultCost;
};

