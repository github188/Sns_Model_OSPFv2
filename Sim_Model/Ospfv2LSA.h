#pragma once
#include "Utilities.h"

enum Ospfv2OptionsField
{
	DC_bit = 0x20,
	EA_bit = 0x10,
	NP_bit = 0x08,
	MC_bit = 0x04,
	E_bit = 0x02,
};

enum Ospfv2LSType
{
	Router = 1,
	Network,
	Summary_IPNetwork,
	Summary_ABSR,
	AS_external,
};

class Ospfv2LSAHeader
{
public:
	Ospfv2LSAHeader();
	Ospfv2LSAHeader(const uint16_t LSAge, Ospfv2OptionsField options, Ospfv2LSType LSType,
		uint32_t linkStateId, uint32_t advertisingRouter,uint32_t LSSequenceNumber,
		uint16_t length);
	virtual ~Ospfv2LSAHeader();

	Ospfv2LSType getLSAge() const;
	void setLSAge(Ospfv2LSType LSAge);
	bool getOptions(Ospfv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(Ospfv2OptionsField options);//可以用按位或连接多个Options位
	uint8_t getLSType() const;
	void setLSType(const uint8_t LSType);
	uint32_t getLinkStateId() const;
	void setLinkStateId(const uint32_t linkStateId);
	uint32_t getAdvertisingRouter() const;
	void setAdvertisingRouter(const uint32_t advertisingRouter);
	uint32_t getLSSequenceNumber() const;
	void setLSSequenceNumber(const uint32_t LSSequenceNumber);
	uint16_t getLSCheckSum() const;
	uint16_t getLength() const;
	void setLength(const uint16_t length);

	void setHeader(const uint16_t LSAge, Ospfv2OptionsField options, Ospfv2LSType LSType,
		uint32_t linkStateId, uint32_t advertisingRouter,uint32_t LSSequenceNumber,
		uint16_t length);

protected:
	uint16_t LSAge;
	uint8_t options;
	uint8_t LSType;
	uint32_t linkStateId;
	uint32_t advertisingRouter;
	uint32_t LSSequenceNumber;
	uint16_t LSCheckSum;
	uint16_t length;
};

