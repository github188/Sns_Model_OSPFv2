#pragma once
#include "StdAfx.h"
#include "Utilities.h"
#include "Ospfv2LSA.h"

class OSPFv2RoutingTableEntry
{
public:
	enum DestinationType
	{
		NETWORK,
		ROUTER,
	};
	enum PathType
	{
		INTRA_AREA,
		INTER_AREA,
		TYPE_1_EXTERNAL,
		TYPE_2_EXTERNAL,
	};
	OSPFv2RoutingTableEntry();
	~OSPFv2RoutingTableEntry();

	DestinationType getDestinationType() const;
	void setDestinationType(DestinationType destinationType);
	UInt32 getDestinationID() const;
	void setDestinationID(UInt32 destinationID);
	IPv4Mask getAddressMask() const;
	void setAddressMask(const IPv4Mask& addressMask);
	bool getOptionalCapabilities() const;
	void setOptionalCapabilities(bool optionalCapabilities);
	UInt32 getAreaID() const;
	void setAreaID(UInt32 areaID);
	PathType getPathType() const;
	void setPathType(PathType pathType);
	UInt32 getCost() const;
	void setCost(UInt32 cost);
	UInt32 getType2Cost() const;
	OSPFv2LSA* getLSOrigin() const;
	void setLSOrigin(const OSPFv2LSA* LSOrigin);
	UInt32 getNextHop() const;
	void setNextHop(UInt32 nextHop);
	UInt32 getAdvertisingRouter() const;
	
private:
	DestinationType destinationType;
	UInt32 destinationID;
	IPv4Mask addressMask;
	bool optionalCapabilities;
	UInt32 areaID;
	PathType pathType;//INTRA_AREA
	UInt32 cost;
	UInt32 type2Cost;//unused
	OSPFv2LSA* LSOrigin;
	UInt32 nextHop;
	UInt32 advertisingRouter;//unused
};
std::ostream& operator<< (std::ostream& os, const OSPFv2RoutingProtocolEntry& entry);

class OSPFv2RoutingTable
{
public:
	OSPFv2RoutingTable(void);
	~OSPFv2RoutingTable(void);
private:
	std::map<UInt32, OSPFv2RoutingProtocolEntry> routingTable;
};

