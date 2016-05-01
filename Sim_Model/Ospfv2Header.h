#pragma once
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "OSPFv2LSA.h"

/************************************************************************/
/* OSPFv2报文头                                                                     */
/************************************************************************/
enum OSPFv2PacketType
{
	HELLO = 1,//Hello
	DD,//Database Description
	LSR,//Link State Request
	LSU,//Link State Update
	LSA,//Link State Acknowledgment
};

class OSPFv2CommonHeader
{
public:
	struct MetaData
	{
		UInt8 version;
		UInt8 type;
		UInt16 packetLength;
		UInt32 routerID;
		UInt32 areaID;
		UInt16 checkSum;
		UInt16 auType;
		UInt64 authentication;
	};
	OSPFv2CommonHeader();
	OSPFv2CommonHeader(OSPFv2PacketType type, UInt16 packetLength, 
		UInt32 routerID, UInt32 areaID);
	virtual ~OSPFv2CommonHeader();

	UInt8 getVersion() const;
	OSPFv2PacketType getType() const;
	void setType(OSPFv2PacketType type);
	UInt16 getPacketLength() const;
	void setPacketLength(UInt16 packetLength);
	UInt32 getRouterID() const;
	void setRouterID(UInt32 routerID);
	UInt32 getAreaID() const;
	void setAreaID(UInt32 areaID);
	UInt16 getCheckSum() const;
	UInt16 getAuType() const;
	UInt64 getAuthentication() const;

	virtual void serialize(UInt8* series) const;
	virtual void deserialize(const UInt8* series, UInt32 seriesSize);
	virtual UInt32 getSerializedSize() const;

	virtual void setHeader(OSPFv2PacketType type, UInt16 packetLength, 
		UInt32 routerID, UInt32 areaID);
	virtual void setHeader(const OSPFv2CommonHeader& header);
protected:
	UInt8 version;
	UInt8 type;
	UInt16 packetLength;
	UInt32 routerID;
	UInt32 areaID;
	UInt16 checkSum;
	UInt16 auType;
	UInt64 authentication;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2CommonHeader& header);

/************************************************************************/
/* Hello报文                                                                     */
/************************************************************************/
class OSPFv2HelloPacket
{
public:
	struct MetaData
	{
		UInt32 networkMask;
		UInt16 helloInterval;
		UInt8 options;
		UInt8 routerPriority;
		UInt32 routerDeadInterval;
		UInt32 designatedRouter;
		UInt32 backupDesignatedRouter;
	};
	OSPFv2HelloPacket();

	IPv4Mask getNetworkMask() const;
	void setNetworkMask(const IPv4Mask& networkmask);
	UInt16 getHelloInterval() const;
	void setHelloInterval(UInt16 helloInterval);
	bool getOptions(OSPFv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(OSPFv2OptionsField options);//可以用按位或连接多个Options位
	UInt8 getRouterPriority() const;
	UInt32 getRouterDeadInterval() const;
	void setRouterDeadInterval(UInt32 routerDeadInterval);
	UInt32 getDesignateRouter() const;
	UInt32 getBackupDesignateRouter() const;
	std::vector<UInt32> getNeighbors() const;
	UInt32 getNNeighbors() const;
	void addNeighbor(UInt32 neighborID);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;

private:
	IPv4Mask networkMask;
	UInt16 helloInterval;
	UInt8 options;
	UInt8 routerPriority;
	UInt32 routerDeadInterval;
	UInt32 designatedRouter;
	UInt32 backupDesignatedRouter;

	std::vector<UInt32> neighbors;
};

/************************************************************************/
/* DD报文                                                                     */
/************************************************************************/
enum OSPFv2DDOptionsField
{
	I_bit=0x04,
	M_bit=0x02,
	MS_bit=0x01,
	NONE_bit=0x00,
	ALL_bits=I_bit|M_bit|MS_bit
};
class OSPFv2DDPacket
{
public:
	struct MetaData
	{
		UInt16 interfaceMTU;
		UInt8 options;
		UInt8 DDOptions;
		UInt32 DDSequenceNumber;
	};
	OSPFv2DDPacket();

	UInt16 getInterfaceMTU() const;
	void setInterfaceMTU(UInt16 interfaceMTU);
	bool getOptions(OSPFv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(OSPFv2OptionsField options);//可以用按位或连接多个Options位
	bool getDDOptions(OSPFv2DDOptionsField DDOption) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setDDOptions(OSPFv2DDOptionsField DDOptions);//可以用按位或连接多个Options位
	UInt32 getDDSequenceNumber() const;
	void setDDSequenceNumber(UInt32 DDSequenceNumber);
	std::vector<OSPFv2LSAHeader> getLSAHeaders() const;
	UInt32 getNLSAHeaders() const;
	void addLSAHeader(const OSPFv2LSAHeader& LSAHeader);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;
private:
	UInt16 interfaceMTU;
	UInt8 options;
	UInt8 DDOptions;
	UInt32 DDSequenceNumber;
	std::vector<OSPFv2LSAHeader> LSAHeaders;
};

/************************************************************************/
/* LSR报文                                                                     */
/************************************************************************/
class OSPFv2LSRequest
{
public:
	OSPFv2LSRequest();

	UInt32 getLSType()const;
	void setLSType(UInt32 LSType);
	UInt32 getLinkStateID()const;
	void setLinkStateID(UInt32 linkStateID);
	UInt32 getAdvertisingRouter()const;
	void setAdvertisingRouter(UInt32 advertisingRouter);

private:
	UInt32 LSType;
	UInt32 linkStateID;
	UInt32 advertisingRouter;

};
class OSPFv2LSRPacket
{
public:
	OSPFv2LSRPacket();
	std::vector<OSPFv2LSRequest> getLSRequests() const;
	UInt32 getNLSRequests() const;
	void addLSRequest(const OSPFv2LSRequest& LSRequest);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;
private:
	std::vector<OSPFv2LSRequest> LSRequests;
};

/************************************************************************/
/* LSU报文                                                                     */
/************************************************************************/
class OSPFv2LSUPacket
{
public:
	OSPFv2LSUPacket();

	UInt32 getNLSAs() const;
	void setNLSAs(UInt32 nLSAs);
	std::vector<OSPFv2LSA> getLSAs() const;
	UInt32 getNLSAs() const;
	void addLSA(const OSPFv2LSA& LSRequest);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;
private:
	UInt32 nLSAs;
	std::vector<OSPFv2LSA> LSAs;
};

/************************************************************************/
/* LSA报文                                                                     */
/************************************************************************/
class OSPFv2LSAPacket
{
public:
	OSPFv2LSAPacket();
};