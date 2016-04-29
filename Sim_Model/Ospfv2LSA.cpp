#include "Ospfv2LSA.h"


Ospfv2LSAHeader::Ospfv2LSAHeader()
	: LSAge(0xffff)
	, options(0x00)
	, LSType(0)
	, linkStateId(0xffffffff)
	, advertisingRouter(0xffffffff)
	, LSSequenceNumber(0)
	, LSCheckSum(0)
	, length(0)
{

}
Ospfv2LSAHeader::Ospfv2LSAHeader(const uint16_t LSAge, Ospfv2OptionsField options, Ospfv2LSType LSType,
	uint32_t linkStateId, uint32_t advertisingRouter,uint32_t LSSequenceNumber,
	uint16_t length)
	: LSAge(LSAge)
	, options(options)
	, LSType(static_cast<uint16_t>(LSType))
	, linkStateId(linkStateId)
	, advertisingRouter(advertisingRouter)
	, LSSequenceNumber(LSSequenceNumber)
	, LSCheckSum(0)
	, length(length)
{

}
Ospfv2LSAHeader::~Ospfv2LSAHeader()
{

}

Ospfv2LSType Ospfv2LSAHeader::getLSAge() const
{
	return LSAge;
}
void Ospfv2LSAHeader::setLSAge(Ospfv2LSType LSAge)
{
	this->LSAge=LSAge;
}
bool Ospfv2LSAHeader::getOptions(Ospfv2OptionsField option) const
{
	return option==(options&option);
}
void Ospfv2LSAHeader::setOptions(Ospfv2OptionsField options)
{
	this->options|=options;
}
uint8_t Ospfv2LSAHeader::getLSType() const
{
	return static_cast<Ospfv2LSType>(LSType);
}
void Ospfv2LSAHeader::setLSType(const uint8_t LSType)
{
	this->LSAge=static_cast<uint16_t>(LSType);
}
uint32_t Ospfv2LSAHeader::getLinkStateId() const
{
	return linkStateId;
}
void Ospfv2LSAHeader::setLinkStateId(const uint32_t linkStateId)
{
	this->linkStateId=linkStateId;
}
uint32_t Ospfv2LSAHeader::getAdvertisingRouter() const
{
	return advertisingRouter;
}
void Ospfv2LSAHeader::setAdvertisingRouter(const uint32_t advertisingRouter)
{
	this->advertisingRouter=advertisingRouter;
}
uint32_t Ospfv2LSAHeader::getLSSequenceNumber() const
{
	return LSSequenceNumber;
}
void Ospfv2LSAHeader::setLSSequenceNumber(const uint32_t LSSequenceNumber)
{
	this->LSSequenceNumber=LSSequenceNumber;
}
uint16_t Ospfv2LSAHeader::getLSCheckSum() const
{
	return LSCheckSum;
}
uint16_t Ospfv2LSAHeader::getLength() const
{
	return length;
}
void Ospfv2LSAHeader::setLength(const uint16_t length)
{
	this->length=length;
}

void Ospfv2LSAHeader::setHeader(const uint16_t LSAge, Ospfv2OptionsField options, Ospfv2LSType LSType,
	uint32_t linkStateId, uint32_t advertisingRouter,uint32_t LSSequenceNumber,
	uint16_t length)
{
	this->LSAge=LSAge;
	this->options|=options;
	this->LSType=LSType;
	this->linkStateId=linkStateId;
	this->advertisingRouter=advertisingRouter;
	this->LSSequenceNumber=LSSequenceNumber;
	this->LSCheckSum=0;
	this->length=length;
}