#pragma once
#include "StdAfx.h"
#include "clock.h"
#include "Utilities.h"
class OSPFv2Interface
{
public:
	OSPFv2Interface(void);

	IPv4Address getAddress() const;
	void setAddress(const IPv4Address& address);
	IPv4Mask getMask() const;
	void setMask(const IPv4Mask& mask);
	UInt32 getAreaID() const;
	void setAreaID(UInt32 areaID);
	UInt32 getOutputCost() const;
	void setOutputCost(UInt32 outputcost);
	clocktype getRxmtInterval() const;
	void setRxmtInterval(clocktype rxmtInterval);
	clocktype getInfTransDelay() const;
	void setInfTransDelay(clocktype infTransDelay);
	clocktype getHelloInterval() const;
	void setHelloInterval(clocktype helloInterval);
	clocktype getRouterDeadInterval() const;
	void setRouterDeadInterval(clocktype routerDeadInterval);
private:
	IPv4Address address;
	IPv4Address mask;
	UInt32 areaID;
	UInt32 outputCost;
	clocktype rxmtInterval;
	clocktype infTransDelay;
	UInt8 routerPriority;//unused
	clocktype helloInterval;
	clocktype routerDeadInterval;
	UInt32 auType;//unused
	UInt64 authenticationKey;//unused
};

