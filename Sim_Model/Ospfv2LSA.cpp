#include "OSPFv2LSA.h"


OSPFv2LSAHeader::OSPFv2LSAHeader()
	: LSAge(0xffff)
	, options(0x00)
	, LSType(0)
	, linkStateID(0xffffffff)
	, advertisingRouter(0xffffffff)
	, LSSequenceNumber(0)
	, LSCheckSum(0)
	, length(0)
{

}
OSPFv2LSAHeader::OSPFv2LSAHeader(UInt16 LSAge, OSPFv2OptionsField options, OSPFv2LSType LSType,
	UInt32 linkStateID, UInt32 advertisingRouter,UInt32 LSSequenceNumber,
	UInt16 length)
	: LSAge(LSAge)
	, options(options)
	, LSType(static_cast<UInt8>(LSType))
	, linkStateID(linkStateID)
	, advertisingRouter(advertisingRouter)
	, LSSequenceNumber(LSSequenceNumber)
	, LSCheckSum(0)
	, length(length)
{

}
OSPFv2LSAHeader::~OSPFv2LSAHeader()
{

}

UInt16 OSPFv2LSAHeader::getLSAge() const
{
	return LSAge;
}
void OSPFv2LSAHeader::setLSAge(UInt16 LSAge)
{
	this->LSAge=LSAge;
}
bool OSPFv2LSAHeader::getOptions(OSPFv2OptionsField option) const
{
	return option==(options&option);
}
void OSPFv2LSAHeader::setOptions(OSPFv2OptionsField options)
{
	this->options|=options;
}
OSPFv2LSType OSPFv2LSAHeader::getLSType() const
{
	return static_cast<OSPFv2LSType>(LSType);
}
void OSPFv2LSAHeader::setLSType(OSPFv2LSType LSType)
{
	this->LSType=static_cast<UInt8>(LSType);
}
UInt32 OSPFv2LSAHeader::getLinkStateID() const
{
	return linkStateID;
}
void OSPFv2LSAHeader::setLinkStateID(UInt32 linkStateID)
{
	this->linkStateID=linkStateID;
}
UInt32 OSPFv2LSAHeader::getAdvertisingRouter() const
{
	return advertisingRouter;
}
void OSPFv2LSAHeader::setAdvertisingRouter(UInt32 advertisingRouter)
{
	this->advertisingRouter=advertisingRouter;
}
UInt32 OSPFv2LSAHeader::getLSSequenceNumber() const
{
	return LSSequenceNumber;
}
void OSPFv2LSAHeader::setLSSequenceNumber(UInt32 LSSequenceNumber)
{
	this->LSSequenceNumber=LSSequenceNumber;
}
UInt16 OSPFv2LSAHeader::getLSCheckSum() const
{
	return LSCheckSum;
}
UInt16 OSPFv2LSAHeader::getLength() const
{
	return length;
}
void OSPFv2LSAHeader::setLength(UInt16 length)
{
	this->length=length;
}

void OSPFv2LSAHeader::setHeader(UInt16 LSAge, OSPFv2OptionsField options, OSPFv2LSType LSType,
	UInt32 linkStateID, UInt32 advertisingRouter,UInt32 LSSequenceNumber,
	UInt16 length)
{
	setLSAge(LSAge);
	setOptions(static_cast<OSPFv2OptionsField>(options));
	setLSType(static_cast<OSPFv2LSType>(LSType));
	setLinkStateID(linkStateID);
	setAdvertisingRouter(advertisingRouter);
	setLSSequenceNumber(LSSequenceNumber);
	setLength(length);
}
void OSPFv2LSAHeader::setHeader(const OSPFv2LSAHeader& header)
{
	setLSAge(header.LSAge);
	setOptions(static_cast<OSPFv2OptionsField>(header.options));
	setLSType(static_cast<OSPFv2LSType>(header.LSType));
	setLinkStateID(header.linkStateID);
	setAdvertisingRouter(header.advertisingRouter);
	setLSSequenceNumber(header.LSSequenceNumber);
	setLength(header.length);
}

/************************************************************************/
/* Router LSA                                                                     */
/************************************************************************/
