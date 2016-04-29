#include <malloc.h>
#include "Ospfv2Header.h"
/************************************************************************/
/* Ospfv2Header                                                                     */
/************************************************************************/
Ospfv2Header::Ospfv2Header()
	: version(2)
	, type(0)
	, packetLength(0)
	, routerId(0xffffffff)
	, areaId(0xffffffff)
	, checkSum(0)
	, auType(0)
	, authentication(0)
{

}

Ospfv2Header::Ospfv2Header(Ospfv2PacketType type, const uint16_t packetLength, 
	const uint32_t routerId, const uint32_t areaId)
	: version(2)
	, type(static_cast<uint8_t>(type))
	, packetLength(packetLength)
	, routerId(routerId)
	, areaId(areaId)
	, checkSum(0)
	, auType(0)
	, authentication(0)
{

}

Ospfv2Header::~Ospfv2Header()
{

}

uint8_t Ospfv2Header::getVersion() const
{
	return version;
}

Ospfv2PacketType Ospfv2Header::getType() const
{
	return static_cast<Ospfv2PacketType>(type);
}

void Ospfv2Header::setType(Ospfv2PacketType type)
{
	this->type=static_cast<uint8_t>(type);
}

uint16_t Ospfv2Header::getPacketLength() const
{
	return packetLength;
}

void Ospfv2Header::setPacketLength(const uint16_t packetLength)
{
	this->packetLength=packetLength;
}

uint32_t Ospfv2Header::getRouterId() const
{
	return routerId
}

void Ospfv2Header::setRouterId(const uint32_t routerId)
{
	this->routerId=routerId;
}

uint32_t Ospfv2Header::getAreaId() const
{
	return areaId;
}

void Ospfv2Header::setAreaId(const uint32_t areaId)
{
	this->areaId=areaId;
}

uint16_t Ospfv2Header::getCheckSum() const
{
	return checkSum;
}

uint16_t Ospfv2Header::getAuType() const
{
	return auType;
}

uint64_t Ospfv2Header::getAuthentication() const
{
	return authentication;
}

void Ospfv2Header::setHeader(Ospfv2PacketType type, const uint16_t packetLength, 
	const uint32_t routerId, const uint32_t areaId)
{
	this->type=static_cast<uint8_t>(type);
	this->packetLength=packetLength;
	this->routerId=routerId;
	this->areaId=areaId;
}
/************************************************************************/
/* Hello 报文                                                                     */
/************************************************************************/

Ospfv2HelloPacket::Ospfv2HelloPacket()
	: networkMask(0xffffffff)
	, helloInterval(0)
	, options(0x00)
	, routerPriority(0)
	, routerDeadInterval(0)
	, designatedRouter(0xffffffff)
	, backupDesignatedRouter(0xffffffff)
{

}

Ospfv2HelloPacket::~Ospfv2HelloPacket()
{

}

uint32_t Ospfv2HelloPacket::getNetworkMask() const
{
	return networkMask;
}
void Ospfv2HelloPacket::setNetworkMask(const uint32_t networkmask)
{
	this->networkMask=networkmask;
}
uint16_t Ospfv2HelloPacket::getHelloInterval() const
{
	return helloInterval;
}
void Ospfv2HelloPacket::setHelloInterval(const uint16_t helloInterval)
{
	this->helloInterval=helloInterval;
}
bool Ospfv2HelloPacket::getOptions(Ospfv2OptionsField option) const
{
	return option==(options&option);
}
void Ospfv2HelloPacket::setOptions(Ospfv2OptionsField options)
{
	this->options|=options;
}
uint8_t Ospfv2HelloPacket::getRouterPriority() const
{
	return routerPriority;
}
uint32_t Ospfv2HelloPacket::getRouterDeadInterval() const
{
	return routerDeadInterval;
}
void Ospfv2HelloPacket::setRouterDeadInterval(const uint32_t routerDeadInterval)
{
	this->routerDeadInterval=routerDeadInterval;
}
uint32_t Ospfv2HelloPacket::getDesignateRouter() const
{
	return designatedRouter;
}
uint32_t Ospfv2HelloPacket::getBackupDesignateRouter() const
{
	return backupDesignatedRouter;
}
Ospfv2HelloPacket* Ospfv2HelloPacket::CreatePacket(unsigned int nNeighbors)
{
	if(nNeighbors>0)
	{
		return (Ospfv2HelloPacket*)malloc(sizeof(Ospfv2HelloPacket)+nNeighbors*sizeof(uint32_t));
	}
	else
	{
		return (Ospfv2HelloPacket*)malloc(sizeof(Ospfv2HelloPacket));
	}
}

/************************************************************************/
/* DD报文                                                                     */
/************************************************************************/
Ospfv2DDPacket::Ospfv2DDPacket()
	: interfaceMTU(0)
	, options(0x00)
	, DDOptions(0x00)
	, DDSequenceNumber(0)
{

}
Ospfv2DDPacket::~Ospfv2DDPacket()
{

}

uint16_t Ospfv2DDPacket::getInterfaceMTU() const
{
	return interfaceMTU;
}
void Ospfv2DDPacket::setInterfaceMTU(const uint16_t interfaceMTU)
{
	this->interfaceMTU=interfaceMTU;
}
bool Ospfv2DDPacket::getOptions(Ospfv2OptionsField option) const//输入位名返回是否置位
{
	return option==(options&option);
}
void Ospfv2DDPacket::setOptions(Ospfv2OptionsField options)//可以用按位或连接多个Options位
{
	this->options|=options;
}
bool Ospfv2DDPacket::getDDOptions(Ospfv2DDOptionsField DDOption) const//输入位名返回是否置位
{
	return DDOption==(DDOptions&DDOption);
}
void Ospfv2DDPacket::setDDOptions(Ospfv2DDOptionsField DDOptions)//可以用按位或连接多个Options位
{
	this->DDOptions=DDOptions;
}
uint32_t Ospfv2DDPacket::getDDSequenceNumber() const
{
	return DDSequenceNumber;
}
void Ospfv2DDPacket::setDDSequenceNumber(const uint32_t DDSequenceNumber)
{
	this->DDSequenceNumber=DDSequenceNumber;
}

static Ospfv2DDPacket* CreatePacket(unsigned int nLSAs)
{
	if(nLSAs>0)
	{
		return (Ospfv2DDPacket*)malloc(sizeof(Ospfv2DDPacket)+nLSAs*sizeof(uint32_t));
	}
	else
	{
		return (Ospfv2DDPacket*)malloc(sizeof(Ospfv2DDPacket));
	}
}