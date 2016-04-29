#pragma once
#include "Utilities.h"
#include "Ospfv2LSA.h"

/************************************************************************/
/* OSPFv2报文头                                                                     */
/************************************************************************/
enum Ospfv2PacketType
{
	Hello = 1,//Hello
	DD,//Database Description
	LSR,//Link State Request
	LSU,//Link State Update
	LSA,//Link State Acknowledgment
};
class Ospfv2Header
{
public:
	Ospfv2Header();
	Ospfv2Header(Ospfv2PacketType type, const uint16_t packetLength, 
		const uint32_t routerId, const uint32_t areaId);
	virtual ~Ospfv2Header();

	uint8_t getVersion() const;
	Ospfv2PacketType getType() const;
	void setType(Ospfv2PacketType type);
	uint16_t getPacketLength() const;
	void setPacketLength(const uint16_t packetLength);
	uint32_t getRouterId() const;
	void setRouterId(const uint32_t routerId);
	uint32_t getAreaId() const;
	void setAreaId(const uint32_t areaId);
	uint16_t getCheckSum() const;
	uint16_t getAuType() const;
	uint64_t getAuthentication() const;

	void setHeader(Ospfv2PacketType type, const uint16_t packetLength, 
		const uint32_t routerId, const uint32_t areaId);

protected:
	uint8_t version;
	uint8_t type;
	uint16_t packetLength;
	uint32_t routerId;
	uint32_t areaId;
	uint16_t checkSum;
	uint16_t auType;
	uint64_t authentication;
};

/************************************************************************/
/* Hello报文                                                                     */
/************************************************************************/
class Ospfv2HelloPacket
{
public:
	Ospfv2HelloPacket();
	~Ospfv2HelloPacket();

	uint32_t getNetworkMask() const;
	void setNetworkMask(const uint32_t networkmask);
	uint16_t getHelloInterval() const;
	void setHelloInterval(const uint16_t helloInterval);
	bool getOptions(Ospfv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(Ospfv2OptionsField options);//可以用按位或连接多个Options位
	uint8_t getRouterPriority() const;
	uint32_t getRouterDeadInterval() const;
	void setRouterDeadInterval(const uint32_t routerDeadInterval);
	uint32_t getDesignateRouter() const;
	uint32_t getBackupDesignateRouter() const;

	static Ospfv2HelloPacket* CreatePacket(unsigned int nNeighbors=0);
private:
	uint32_t networkMask;
	uint16_t helloInterval;
	uint8_t options;
	uint8_t routerPriority;
	uint32_t routerDeadInterval;
	uint32_t designatedRouter;
	uint32_t backupDesignatedRouter;
};

/************************************************************************/
/* DD报文                                                                     */
/************************************************************************/
enum Ospfv2DDOptionsField
{
	I_bit=0x04,
	M_bit=0x02,
	MS_bit=0x01,
};
class Ospfv2DDPacket
{
public:
	Ospfv2DDPacket();
	~Ospfv2DDPacket();

	uint16_t getInterfaceMTU() const;
	void setInterfaceMTU(const uint16_t interfaceMTU);
	bool getOptions(Ospfv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(Ospfv2OptionsField options);//可以用按位或连接多个Options位
	bool getDDOptions(Ospfv2DDOptionsField DDOption) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setDDOptions(Ospfv2DDOptionsField DDOptions);//可以用按位或连接多个Options位
	uint32_t getDDSequenceNumber() const;
	void setDDSequenceNumber(const uint32_t DDSequenceNumber);

	static Ospfv2DDPacket* CreatePacket(unsigned int nLSAs=0);
private:
	uint16_t interfaceMTU;
	uint8_t options;
	uint8_t DDOptions;
	uint32_t DDSequenceNumber;
};