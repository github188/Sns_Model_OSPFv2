#include <malloc.h>
#include "OSPFv2Header.h"
/************************************************************************/
/* OSPFv2Header                                                                     */
/************************************************************************/
OSPFv2CommonHeader::OSPFv2CommonHeader()
	: version(2)
	, type(0)
	, packetLength(0)
	, routerID(0xffffffff)
	, areaID(0xffffffff)
	, checkSum(0)
	, auType(0)
	, authentication(0)
{

}

OSPFv2CommonHeader::OSPFv2CommonHeader(OSPFv2PacketType type, UInt16 packetLength, 
	UInt32 routerID, UInt32 areaID)
	: version(2)
	, type(static_cast<UInt8>(type))
	, packetLength(packetLength)
	, routerID(routerID)
	, areaID(areaID)
	, checkSum(0)
	, auType(0)
	, authentication(0)
{

}

OSPFv2CommonHeader::~OSPFv2CommonHeader()
{

}

UInt8 OSPFv2CommonHeader::getVersion() const
{
	return version;
}

OSPFv2PacketType OSPFv2CommonHeader::getType() const
{
	return static_cast<OSPFv2PacketType>(type);
}

void OSPFv2CommonHeader::setType(OSPFv2PacketType type)
{
	this->type=static_cast<UInt8>(type);
}

UInt16 OSPFv2CommonHeader::getPacketLength() const
{
	return packetLength;
}

void OSPFv2CommonHeader::setPacketLength(UInt16 packetLength)
{
	this->packetLength=packetLength;
}

UInt32 OSPFv2CommonHeader::getRouterID() const
{
	return routerID
}

void OSPFv2CommonHeader::setRouterID(UInt32 routerID)
{
	this->routerID=routerID;
}

UInt32 OSPFv2CommonHeader::getAreaID() const
{
	return areaID;
}

void OSPFv2CommonHeader::setAreaID(UInt32 areaID)
{
	this->areaID=areaID;
}

UInt16 OSPFv2CommonHeader::getCheckSum() const
{
	return checkSum;
}

UInt16 OSPFv2CommonHeader::getAuType() const
{
	return auType;
}

UInt64 OSPFv2CommonHeader::getAuthentication() const
{
	return authentication;
}

void OSPFv2CommonHeader::serialize(UInt8* series) const
{
	MetaData* metaData = reinterpret_cast<MetaData*>(series);
	metaData->version=version;
	metaData->type=type;
	metaData->packetLength=packetLength;
	metaData->routerID=routerID;
	metaData->areaID=areaID;
	metaData->checkSum=checkSum;
	metaData->auType=auType;
	metaData->authentication=authentication;
}
void OSPFv2CommonHeader::deserialize(const UInt8* series, UInt32 seriesSize)
{
	assert(seriesSize==getSerializedSize(),"Series's size is wrong.");
	const MetaData* metaData = reinterpret_cast<const MetaData*>(series);
	version=metaData->version;
	type=metaData->type;
	packetLength=metaData->packetLength;
	routerID=metaData->routerID;
	areaID=metaData->areaID;
	checkSum=metaData->checkSum;
	auType=metaData->auType;
	authentication=metaData->authentication;
}
UInt32 OSPFv2CommonHeader::getSerializedSize() const
{
	return sizeof(MetaData);
}
void OSPFv2CommonHeader::setHeader(OSPFv2PacketType type, UInt16 packetLength, 
	UInt32 routerID, UInt32 areaID)
{
	setType(static_cast<OSPFv2PacketType>(type));
	setPacketLength(packetLength);
	setRouterID(routerID);
	setAreaID(areaID);
}

void OSPFv2CommonHeader::setHeader(const OSPFv2CommonHeader& header)
{
	setType(static_cast<OSPFv2PacketType>(header.type));
	setPacketLength(header.packetLength);
	setRouterID(header.routerID);
	setAreaID(header.areaID);
}

std::ostream& operator<< (std::ostream& os, const OSPFv2CommonHeader& header)
{
	os<<"Version: "<<header.getVersion()
		<<" Type: "<<header.getType()
		<<" Packet length: "<<header.getPacketLength()
		<<" Router ID: "<<header.getRouterID()
		<<" Area ID: "<<header.getAreaID()
		<<" Check Sum: "<<header.getCheckSum()
		<<" Au Type: "<<header.getAuType()
		<<" Authentication: "<<header.getAuthentication();
	return os;
}
/************************************************************************/
/* Hello 报文                                                                     */
/************************************************************************/

OSPFv2HelloPacket::OSPFv2HelloPacket()
	: networkMask(0xffffffff)
	, helloInterval(0)
	, options(0x00)
	, routerPriority(0)
	, routerDeadInterval(0)
	, designatedRouter(0xffffffff)
	, backupDesignatedRouter(0xffffffff)
{

}
IPv4Mask OSPFv2HelloPacket::getNetworkMask() const
{
	return networkMask;
}
void OSPFv2HelloPacket::setNetworkMask(const IPv4Mask& networkmask)
{
	this->networkMask=networkmask;
}
UInt16 OSPFv2HelloPacket::getHelloInterval() const
{
	return helloInterval;
}
void OSPFv2HelloPacket::setHelloInterval(UInt16 helloInterval)
{
	this->helloInterval=helloInterval;
}
bool OSPFv2HelloPacket::getOptions(OSPFv2OptionsField option) const
{
	return option==(options&option);
}
void OSPFv2HelloPacket::setOptions(OSPFv2OptionsField options)
{
	this->options|=options;
}
UInt8 OSPFv2HelloPacket::getRouterPriority() const
{
	return routerPriority;
}
UInt32 OSPFv2HelloPacket::getRouterDeadInterval() const
{
	return routerDeadInterval;
}
void OSPFv2HelloPacket::setRouterDeadInterval(UInt32 routerDeadInterval)
{
	this->routerDeadInterval=routerDeadInterval;
}
UInt32 OSPFv2HelloPacket::getDesignateRouter() const
{
	return designatedRouter;
}
UInt32 OSPFv2HelloPacket::getBackupDesignateRouter() const
{
	return backupDesignatedRouter;
}
std::vector<UInt32> OSPFv2HelloPacket::getNeighbors() const
{
	return neighbors;
}
UInt32 OSPFv2HelloPacket::getNNeighbors() const
{
	return neighbors.size();
}
void OSPFv2HelloPacket::addNeighbor(UInt32 neighborID)
{
	neighbors.push_back(neighborID);
}

void OSPFv2HelloPacket::serialize(UInt8* series) const
{
	MetaData* metaData = reinterpret_cast<MetaData*>(series);
	metaData->networkMask=networkMask.get();
	metaData->helloInterval=helloInterval;
	metaData->options=options;
	metaData->routerPriority=routerPriority;
	metaData->routerDeadInterval=routerDeadInterval;
	metaData->designatedRouter=designatedRouter;
	metaData->backupDesignatedRouter=backupDesignatedRouter;

	UInt32* neighborID=reinterpret_cast<UInt32*>(metaData+1);
	for (std::vector<UInt32>::const_iterator i=neighbors.begin();
		i!=neighbors.end();
		i++)
	{
		*neighborID=*i;
		neighborID++;
	}
}
void OSPFv2HelloPacket::deserialize(const UInt8* series, UInt32 seriesSize)
{
	const UInt32 nNeighbors=(seriesSize-sizeof(MetaData))/sizeof(UInt32);
	assert(nNeighbors>=0,"Series' size is wrong.");
	const MetaData* metaData = reinterpret_cast<const MetaData*>(series);
	networkMask.set(metaData->networkMask);
	helloInterval=metaData->helloInterval;
	options=metaData->options;
	routerPriority=metaData->routerPriority;
	routerDeadInterval=metaData->routerDeadInterval;
	designatedRouter=metaData->designatedRouter;
	backupDesignatedRouter=metaData->backupDesignatedRouter;

	const UInt32* neighborID=reinterpret_cast<const UInt32*>(metaData+1);
	for (int i=0;i<nNeighbors;i++)
	{
		neighbors.push_back(*neighborID);
	}
}
UInt32 OSPFv2HelloPacket::getSerializedSize() const
{
	return sizeof(MetaData)+sizeof(UInt32)*getNNeighbors();
}
/************************************************************************/
/* DD报文                                                                     */
/************************************************************************/
OSPFv2DDPacket::OSPFv2DDPacket()
	: interfaceMTU(0)
	, options(0x00)
	, DDOptions(0x00)
	, DDSequenceNumber(0)
{

}
UInt16 OSPFv2DDPacket::getInterfaceMTU() const
{
	return interfaceMTU;
}
void OSPFv2DDPacket::setInterfaceMTU(UInt16 interfaceMTU)
{
	this->interfaceMTU=interfaceMTU;
}
bool OSPFv2DDPacket::getOptions(OSPFv2OptionsField option) const//输入位名返回是否置位
{
	return option==(options&option);
}
void OSPFv2DDPacket::setOptions(OSPFv2OptionsField options)//可以用按位或连接多个Options位
{
	this->options|=options;
}
bool OSPFv2DDPacket::getDDOptions(OSPFv2DDOptionsField DDOption) const//输入位名返回是否置位
{
	return DDOption==(DDOptions&DDOption);
}
void OSPFv2DDPacket::setDDOptions(OSPFv2DDOptionsField DDOptions)//可以用按位或连接多个Options位
{
	this->DDOptions=DDOptions;
}
UInt32 OSPFv2DDPacket::getDDSequenceNumber() const
{
	return DDSequenceNumber;
}
void OSPFv2DDPacket::setDDSequenceNumber(UInt32 DDSequenceNumber)
{
	this->DDSequenceNumber=DDSequenceNumber;
}

std::vector<OSPFv2LSAHeader> OSPFv2DDPacket::getLSAHeaders() const
{
	return LSAHeaders;
}
UInt32 OSPFv2DDPacket::getNLSAHeaders() const
{
	return LSAHeaders.size();
}
void OSPFv2DDPacket::addLSAHeader(const OSPFv2LSAHeader& LSAHeader)
{
	LSAHeaders.push_back(LSAHeader);
}

void OSPFv2DDPacket::serialize(UInt8* series) const
{
	MetaData* metaData = reinterpret_cast<MetaData*>(series);
	metaData->interfaceMTU=interfaceMTU;
	metaData->options=options;
	metaData->DDOptions=DDOptions;
	metaData->DDSequenceNumber=DDSequenceNumber;

	OSPFv2LSAHeader* LSAHeader=reinterpret_cast<OSPFv2LSAHeader*>(metaData+1);
	for (std::vector<OSPFv2LSAHeader>::const_iterator i=LSAHeaders.begin();
		i!=LSAHeaders.end();
		i++)
	{
		*LSAHeader=*i;
		LSAHeader++;
	}
}
void OSPFv2DDPacket::deserialize(const UInt8* series, UInt32 seriesSize)
{
	const UInt32 nLSAHeaders=(seriesSize-sizeof(MetaData))/sizeof(OSPFv2LSAHeader);
	assert(nLSAHeaders>=0,"Series' size is wrong.");
	const MetaData* metaData = reinterpret_cast<const MetaData*>(series);
	interfaceMTU=metaData->interfaceMTU;
	options=metaData->options;
	DDOptions=metaData->DDOptions;
	DDSequenceNumber=metaData->DDSequenceNumber;

	const OSPFv2LSAHeader* LSAHeader=reinterpret_cast<const OSPFv2LSAHeader*>(metaData+1);
	for (int i=0;i<nLSAHeaders;i++)
	{
		LSAHeaders.push_back(*LSAHeader);
	}
}
UInt32 OSPFv2DDPacket::getSerializedSize() const
{
	return sizeof(MetaData)+sizeof(OSPFv2LSAHeader)*getNLSAHeaders();
}

/************************************************************************/
/* LSR报文                                                                     */
/************************************************************************/
//LSR Info
OSPFv2LSRequest::OSPFv2LSRequest()
	: LSType(0)
	, linkStateID(0xffffffff)
	, advertisingRouter(0xffffffff)
{

}
UInt32 OSPFv2LSRequest::getLSType()const
{
	return LSType;
}
void OSPFv2LSRequest::setLSType(UInt32 LSType)
{
	this->LSType=LSType;
}
UInt32 OSPFv2LSRequest::getLinkStateID()const
{
	return linkStateID;
}
void OSPFv2LSRequest::setLinkStateID(UInt32 linkStateID)
{
	this->linkStateID=linkStateID;
}
UInt32 OSPFv2LSRequest::getAdvertisingRouter()const
{
	return advertisingRouter;
}
void OSPFv2LSRequest::setAdvertisingRouter(UInt32 advertisingRouter)
{
	this->advertisingRouter=advertisingRouter;
}
//LSR Packet
OSPFv2LSRPacket::OSPFv2LSRPacket()
{

}

std::vector<OSPFv2LSRequest> OSPFv2LSRPacket::getLSRequests() const
{
	return LSRequests;
}
UInt32 OSPFv2LSRPacket::getNLSRequests() const
{
	return LSRequests.size();
}
void OSPFv2LSRPacket::addLSRequest(const OSPFv2LSRequest& LSRequest)
{
	LSRequests.push_back(LSRequest);
}

void OSPFv2LSRPacket::serialize(UInt8* series) const
{
	OSPFv2LSRequest* LSRequest=reinterpret_cast<OSPFv2LSRequest*>(series);
	for (std::vector<OSPFv2LSRequest>::const_iterator i=LSRequests.begin();
		i!=LSRequests.end();
		i++)
	{
		*LSRequest=*i;
		LSRequest++;
	}
}
void OSPFv2LSRPacket::deserialize(const UInt8* series, UInt32 seriesSize)
{
	const UInt32 nLSRequests=seriesSize/sizeof(OSPFv2LSRequest);
	assert(nLSRequests>=0,"Series' size is wrong.");
	
	const OSPFv2LSRequest* LSRequest=reinterpret_cast<const OSPFv2LSRequest*>(series+1);
	for (int i=0;i<nLSRequests;i++)
	{
		LSRequests.push_back(*LSRequest);
	}
}
UInt32 OSPFv2LSRPacket::getSerializedSize() const
{
	return sizeof(OSPFv2LSRequest)*getNLSRequests();
}

/************************************************************************/
/* LSU报文                                                                     */
/************************************************************************/
OSPFv2LSUPacket::OSPFv2LSUPacket()
	:nLSAs(0)
{

}

UInt32 OSPFv2LSUPacket::getNLSAs() const
{
	return nLSAs;
}
void OSPFv2LSUPacket::setNLSAs(UInt32 nLSAs)
{
	this->nLSAs=nLSAs;
}

/************************************************************************/
/* LSA报文                                                                     */
/************************************************************************/
OSPFv2LSAPacket::OSPFv2LSAPacket()
{

}