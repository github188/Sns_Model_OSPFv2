#pragma once
#include "StdAfx.h"
#include "Utilities.h"
#include "OSPFv2LSA.h"

/************************************************************************/
/* OSPFv2����ͷ                                                                     */
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
	UInt8 version;//2
	UInt8 type;
	UInt16 packetLength;
	UInt32 routerID;
	UInt32 areaID;//0xffffffff
	UInt16 checkSum;//not used
	UInt16 auType;//not used
	UInt64 authentication;//not used
};
std::ostream& operator<< (std::ostream& os, const OSPFv2CommonHeader& header);

/************************************************************************/
/* Hello����                                                                     */
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
	OSPFv2OptionsField getOptions(OSPFv2OptionsField option) const;//����λ�������Ƿ���λ,�����ð�λ�����Ӷ��Optionsλ
	void setOptions(OSPFv2OptionsField options);//�����ð�λ�����Ӷ��Optionsλ
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
	UInt8 routerPriority;//not used
	UInt32 routerDeadInterval;
	UInt32 designatedRouter;//not used
	UInt32 backupDesignatedRouter;//not used

	std::vector<UInt32> neighbors;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2HelloPacket& packet);

/************************************************************************/
/* DD����                                                                     */
/************************************************************************/
class OSPFv2DDPacket
{
public:
	enum OSPFv2DDOptionsField
	{
		I_bit=0x04,
		M_bit=0x02,
		MS_bit=0x01,
		NONE_bit=0x00,
		ALL_bits=I_bit|M_bit|MS_bit
	};
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
	OSPFv2OptionsField getOptions(OSPFv2OptionsField option) const;//����λ�������Ƿ���λ,�����ð�λ�����Ӷ��Optionsλ
	void setOptions(OSPFv2OptionsField options);//�����ð�λ�����Ӷ��Optionsλ
	OSPFv2DDOptionsField getDDOptions(OSPFv2DDOptionsField DDOption) const;//����λ�������Ƿ���λ,�����ð�λ�����Ӷ��Optionsλ
	void setDDOptions(OSPFv2DDOptionsField DDOptions);//�����ð�λ�����Ӷ��Optionsλ
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
std::ostream& operator<< (std::ostream& os, const OSPFv2DDPacket& packet);

/************************************************************************/
/* LSR����                                                                     */
/************************************************************************/
class OSPFv2LSRequest
{
public:
	struct MetaData
	{
		UInt32 LSType;
		UInt32 linkStateID;
		UInt32 advertisingRouter;
	};
	OSPFv2LSRequest();
	OSPFv2LSRequest(OSPFv2LSType LSType,UInt32 linkStateID,UInt32 advertisingRouter);
	OSPFv2LSRequest(const MetaData& metaData);

	OSPFv2LSType getLSType()const;
	void setLSType(OSPFv2LSType LSType);
	UInt32 getLinkStateID()const;
	void setLinkStateID(UInt32 linkStateID);
	UInt32 getAdvertisingRouter()const;
	void setAdvertisingRouter(UInt32 advertisingRouter);

	void getMetaData(MetaData& metaData) const;
	void set(const MetaData& metaData);
private:
	UInt32 LSType;
	UInt32 linkStateID;
	UInt32 advertisingRouter;

};
std::ostream& operator<< (std::ostream& os, const OSPFv2LSRequest& request);
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
std::ostream& operator<< (std::ostream& os, const OSPFv2LSRPacket& packet);


/************************************************************************/
/* LSU����                                                                     */
/************************************************************************/
template <class T=OSPFv2RouterLSA>
class OSPFv2LSUPacket
{
public:
	struct MetaData
	{
		UInt32 nLSAs;
	};
	OSPFv2LSUPacket();

	std::vector<T> getLSAs() const;
	UInt32 getNLSAs() const;
	void addLSA(const T& LSRequest);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;
private:
	std::vector<T> LSAs;
};
//ģ���ඨ��
template<class T>
OSPFv2LSUPacket<T>::OSPFv2LSUPacket()
{

}
template<class T>
std::vector<T> OSPFv2LSUPacket<T>::getLSAs() const
{
	return LSAs;
}
template<class T>
UInt32 OSPFv2LSUPacket<T>::getNLSAs() const
{
	return LSAs.size();
}
template<class T>
void OSPFv2LSUPacket<T>::addLSA(const T& LSA)
{
	LSAs.push_back(LSA);
}
template<class T>
void OSPFv2LSUPacket<T>::serialize(UInt8* series) const
{
	MetaData* metaData = reinterpret_cast<MetaData*>(series);
	metaData->nLSAs=getNLSAs();

	T::MetaData* LSAMetaData=reinterpret_cast<T::MetaData*>(metaData+1);
	for (std::vector<T>::const_iterator i=LSAs.begin();
		i!=LSAs.end();
		i++)
	{
		i->getMetaData(*LSAMetaData);
		LSAMetaData++;
	}
}
template<class T>
void OSPFv2LSUPacket<T>::deserialize(const UInt8* series, UInt32 seriesSize)
{
	UInt32 nLSAs=(seriesSize-sizeof(MetaData))/sizeof(T::MetaData);
	assert(nLSAs>=0,"Series' size is wrong.");
	const MetaData* metaData = reinterpret_cast<const MetaData*>(series);
	assert(nLSAs==metaData->nLSAs,"nLSAs is wrong.");

	const T::MetaData* LSAMetaData=reinterpret_cast<const T::MetaData*>(metaData+1);
	for (int i=0;i<nLSAs;i++)
	{
		T LSA;
		LSA.set(LSAMetaData);
		LSAs.push_back(LSA);
		LSAMetaData++;
	}
}
template<class T>
UInt32 OSPFv2LSUPacket<T>::getSerializedSize() const
{
	return sizeof(MetaData)+sizeof(T::MetaData)*getNLSAs();
}

template<class T>
std::ostream& operator<< (std::ostream& os, const OSPFv2LSUPacket<T>& packet)
{
	for (std::vector<T>::const_iterator i=packet.getLSAs().begin();
		i!=packet.getLSAs().end();
		i++)
	{
		os<<*i;
	}
	return os;
}

/************************************************************************/
/* LSA����                                                                     */
/************************************************************************/
class OSPFv2LSAPacket
{
public:
	OSPFv2LSAPacket();
	std::vector<OSPFv2LSAHeader> getLSAHeaders() const;
	UInt32 getNLSAHeaders() const;
	void addLSAHeader(const OSPFv2LSAHeader& LSAHeader);

	void serialize(UInt8* series) const;
	void deserialize(const UInt8* series, UInt32 seriesSize);
	UInt32 getSerializedSize() const;
private:
	std::vector<OSPFv2LSAHeader> LSAHeaders;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2LSAPacket& packet);