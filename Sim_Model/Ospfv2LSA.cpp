#include "OSPFv2LSA.h"


OSPFv2LSAHeader::OSPFv2LSAHeader()
	: LSAge(0xffff)
	, options(0x00)
	, LSType(0)
	, linkStateID(0xFFFFFFFF)
	, advertisingRouter(0xFFFFFFFF)
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
OSPFv2LSAHeader::OSPFv2LSAHeader(const MetaData& metaData)
	: LSAge(metaData.LSAge)
	, options(metaData.options)
	, LSType(static_cast<UInt8>(metaData.LSType))
	, linkStateID(metaData.linkStateID)
	, advertisingRouter(metaData.advertisingRouter)
	, LSSequenceNumber(metaData.LSSequenceNumber)
	, LSCheckSum(metaData.LSCheckSum)
	, length(metaData.length)
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
OSPFv2OptionsField OSPFv2LSAHeader::getOptions(OSPFv2OptionsField option) const
{
	return static_cast<OSPFv2OptionsField>(options&option);
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
void OSPFv2LSAHeader::setHeader(const MetaData& metaData)
{
	LSAge=metaData.LSAge;
	options=metaData.options;
	LSType=metaData.LSType;
	linkStateID=metaData.linkStateID;
	advertisingRouter=metaData.advertisingRouter;
	LSSequenceNumber=metaData.LSSequenceNumber;
	LSCheckSum=metaData.LSCheckSum;
	length=metaData.length;
}
void OSPFv2LSAHeader::getMetaData(MetaData& metaData) const
{
	metaData.LSAge=LSAge;
	metaData.options=options;
	metaData.LSType=LSType;
	metaData.linkStateID=linkStateID;
	metaData.advertisingRouter=advertisingRouter;
	metaData.LSSequenceNumber=LSSequenceNumber;
	metaData.LSCheckSum=LSCheckSum;
	metaData.length=length;
}
std::ostream& operator<< (std::ostream& os, const OSPFv2LSAHeader& header)
{
	os<<"Link-State age: "<<header.getLSAge()
		<<" Options: "<<header.getOptions(OSPFv2OptionsField::ALL_bits)
		<<" Link-State type: "<<header.getLSType()
		<<" Link-State ID: "<<header.getLinkStateID()
		<<" Advertising router: "<<header.getAdvertisingRouter()
		<<" Link-State sequence number: "<<header.getLSSequenceNumber()
		<<" Length: "<<header.getLength()
		<<"\n";
	return os;
}

/************************************************************************/
/* Base LSA                                                                     */
/************************************************************************/
OSPFv2LSA::OSPFv2LSA()
{

}
OSPFv2LSA::OSPFv2LSA(const OSPFv2LSAHeader& header)
	:header(header)
{

}
OSPFv2LSAHeader OSPFv2LSA::getHeader() const
{
	return header;
}
void OSPFv2LSA::setHeader(const OSPFv2LSAHeader& header)
{
	this->header=header;
}
std::ostream& operator<< (std::ostream& os, const OSPFv2LSA& LSA)
{
	os<<LSA.getHeader();
	return os;
}

/************************************************************************/
/* Router LSA                                                                     */
/************************************************************************/
//Router Link
OSPFv2RouterLink::OSPFv2RouterLink()
	: linkID(0xFFFFFFFF)
	, linkData(0xFFFFFFFF)
	, type(0)
	, nTOS(0)
	, metric(0)
{

}
OSPFv2RouterLink::OSPFv2RouterLink(UInt32 linkID,
	UInt32 linkData,
	OSPFv2RouterLinkType type,UInt16 metric)
	: linkID(linkID)
	, linkData(linkData)
	, type(static_cast<UInt8>(type))
	, nTOS(0)
	, metric(metric)
{

}
OSPFv2RouterLink::OSPFv2RouterLink(const MetaData& metaData)
	: linkID(metaData.linkID)
	, linkData(metaData.linkData)
	, type(metaData.type)
	, nTOS(metaData.nTOS)
	, metric(metaData.metric)
{

}
UInt32 OSPFv2RouterLink::getLinkID() const
{
	return linkID;
}
void OSPFv2RouterLink::setLinkID(UInt32 linkID)
{
	this->linkID=linkID;
}
UInt32 OSPFv2RouterLink::getLinkData() const
{
	return linkData;
}
void OSPFv2RouterLink::setLinkData(UInt32 linkData)
{
	this->linkData=linkData;
}
OSPFv2RouterLinkType OSPFv2RouterLink::getType() const
{
	return static_cast<OSPFv2RouterLinkType>(type);
}
void OSPFv2RouterLink::setType(OSPFv2RouterLinkType type)
{
	this->type=static_cast<UInt8>(type);
}
UInt8 OSPFv2RouterLink::getNTOS() const
{
	return nTOS;
}
UInt16 OSPFv2RouterLink::getMetric() const
{
	return metric;
}
void OSPFv2RouterLink::setMetric(UInt16 metric)
{
	this->metric=metric;
}
void OSPFv2RouterLink::getMetaData(MetaData& metaData) const
{
	metaData.linkID=linkID;
	metaData.linkData=linkData;
	metaData.type=type;
	metaData.nTOS=nTOS;
	metaData.metric=metric;
}
void OSPFv2RouterLink::set(const MetaData& metaData)
{
	linkID=metaData.linkID;
	linkData=metaData.linkData;
	type=metaData.type;
	nTOS=metaData.nTOS;
	metric=metaData.metric;
}
std::ostream& operator<< (std::ostream& os, const OSPFv2RouterLink& routerLink)
{
	os<<"Link ID: "<<routerLink.getLinkID()
		<<" Link data: "<<routerLink.getLinkData()
		<<" Type: "<<routerLink.getType()
		<<" nTOS: "<<routerLink.getNTOS()
		<<" metric: "<<routerLink.getMetric()
		<<"\n";
	return os;
}
//Router LSA
OSPFv2RouterLSA::OSPFv2RouterLSA()
	: options(NONE_bit)
{

}

OSPFv2RouterLSA::OSPFv2RouterLSAOptionFeild OSPFv2RouterLSA::getOptions(OSPFv2RouterLSA::OSPFv2RouterLSAOptionFeild option) const//输入位名返回是否置位,可以用按位或连接多个Options位
{
	return static_cast<OSPFv2RouterLSAOptionFeild>(options&option);
}
void OSPFv2RouterLSA::setOptions(OSPFv2RouterLSA::OSPFv2RouterLSAOptionFeild options)//可以用按位或连接多个Options位
{
	this->options|=options;
}
UInt16 OSPFv2RouterLSA::getNLinks() const
{
	return routerLinks.size();
}
std::vector<OSPFv2RouterLink> OSPFv2RouterLSA::getRouterLinks() const
{
	return routerLinks;
}
void OSPFv2RouterLSA::addRouterLink(const OSPFv2RouterLink& routerLink)
{
	routerLinks.push_back(routerLink);
}
void OSPFv2RouterLSA::getMetaData(UInt8* series) const
{
	MetaData* metaData=reinterpret_cast<MetaData*>(series);
	header.getMetaData(metaData->headerMetaData);
	metaData->options=options;
	metaData->nLinks=getNLinks();
	OSPFv2RouterLink::MetaData* RouterLink=reinterpret_cast<OSPFv2RouterLink::MetaData*>(metaData+1);
	for (std::vector<OSPFv2RouterLink>::const_iterator i=routerLinks.begin();
		i!=routerLinks.end();
		i++)
	{
		i->getMetaData(*RouterLink);
	}
}
const UInt8* OSPFv2RouterLSA::set(const UInt8* series)
{
	const MetaData* metaData = reinterpret_cast<const MetaData*>(series);
	const UInt32 nRouterLinks=metaData->nLinks;
	header.setHeader(metaData->headerMetaData);
	options=metaData->options;

	const OSPFv2RouterLink::MetaData* routerLink=reinterpret_cast<const OSPFv2RouterLink::MetaData*>(metaData+1);
	for (int i=0;i<nRouterLinks;i++)
	{
		routerLinks.push_back(OSPFv2RouterLink(*routerLink));
		routerLink++;
	}
	return reinterpret_cast<const UInt8*>(routerLink);
}
std::ostream& operator<< (std::ostream& os, const OSPFv2RouterLSA& routerLSA)
{
	os<<"Options: "<<routerLSA.getOptions(OSPFv2RouterLSA::OSPFv2RouterLSAOptionFeild::ALL_bits)
		<<" nLinks: "<<routerLSA.getNLinks()
		<<"\n";
	for(std::vector<OSPFv2RouterLink>::const_iterator i=routerLSA.getRouterLinks().begin();
		i!=routerLSA.getRouterLinks().end();
		i++)
	{
		os<<*i;
	}
	return os;
}