#pragma once
#include "StdAfx.h"
#include "Utilities.h"

enum OSPFv2OptionsField
{
	DC_bit = 0x20,
	EA_bit = 0x10,
	NP_bit = 0x08,
	MC_bit = 0x04,
	E_bit = 0x02,
	NONE_bit = 0x00,
	ALL_bits = DC_bit|EA_bit|NP_bit|MC_bit|E_bit
};

/************************************************************************/
/* Link-State Advertisement Header                                                                     */
/************************************************************************/
enum OSPFv2LSType
{
	ROUTER = 1,
	NETWORK,
	SUMMARY_IP_NETWORK,
	SUMMARY_ABSR,
	AS_EXTERNAL,
};

class OSPFv2LSAHeader
{
public:
	struct MetaData
	{
		UInt16 LSAge;
		UInt8 options;
		UInt8 LSType;
		UInt32 linkStateID;
		UInt32 advertisingRouter;
		UInt32 LSSequenceNumber;
		UInt16 LSCheckSum;//not used
		UInt16 length;
	};
	OSPFv2LSAHeader();
	OSPFv2LSAHeader(UInt16 LSAge, OSPFv2OptionsField options, OSPFv2LSType LSType,
		UInt32 linkStateID, UInt32 advertisingRouter,UInt32 LSSequenceNumber,
		UInt16 length);
	OSPFv2LSAHeader(const MetaData& metaData);
	virtual ~OSPFv2LSAHeader();

	UInt16 getLSAge() const;
	void setLSAge(UInt16 LSAge);
	OSPFv2OptionsField getOptions(OSPFv2OptionsField option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(OSPFv2OptionsField options);//可以用按位或连接多个Options位
	OSPFv2LSType getLSType() const;
	void setLSType(OSPFv2LSType LSType);
	UInt32 getLinkStateID() const;
	void setLinkStateID(UInt32 linkStateID);
	UInt32 getAdvertisingRouter() const;
	void setAdvertisingRouter(UInt32 advertisingRouter);
	UInt32 getLSSequenceNumber() const;
	void setLSSequenceNumber(UInt32 LSSequenceNumber);
	UInt16 getLSCheckSum() const;
	UInt16 getLength() const;
	void setLength(UInt16 length);

	virtual void setHeader(UInt16 LSAge, OSPFv2OptionsField options, OSPFv2LSType LSType,
		UInt32 linkStateID, UInt32 advertisingRouter,UInt32 LSSequenceNumber,
		UInt16 length);
	virtual void setHeader(const OSPFv2LSAHeader& header);
	virtual void setHeader(const MetaData& metaData);
	virtual void getMetaData(MetaData& metaData) const;

protected:
	UInt16 LSAge;
	UInt8 options;
	UInt8 LSType;
	UInt32 linkStateID;
	UInt32 advertisingRouter;
	UInt32 LSSequenceNumber;
	UInt16 LSCheckSum;//not used
	UInt16 length;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2LSAHeader& header);

/************************************************************************/
/* Base LSA                                                                     */
/************************************************************************/
class OSPFv2LSA
{
public:
	OSPFv2LSA();
	OSPFv2LSA(const OSPFv2LSAHeader& header);
	virtual OSPFv2LSAHeader getHeader() const;
	virtual void setHeader(const OSPFv2LSAHeader& header);
protected:
	OSPFv2LSAHeader header;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2LSA& LSA);
/************************************************************************/
/* Router LSA                                                                     */
/************************************************************************/
enum OSPFv2RouterLinkType
{
	POINT_TO_POINT = 1,
	TRANSIT,
	STUB,
	VIRTUAL,
};
class OSPFv2RouterLink
{
public:
	struct MetaData
	{
		UInt32 linkID;
		UInt32 linkData;
		UInt8 type;
		UInt8 nTOS;//not used
		UInt16 metric;
	};
	OSPFv2RouterLink();
	OSPFv2RouterLink(UInt32 linkID,
		UInt32 linkData,
		OSPFv2RouterLinkType type,UInt16 metric);
	OSPFv2RouterLink(const MetaData& metaData);

	UInt32 getLinkID() const;
	void setLinkID(UInt32 linkID);
	UInt32 getLinkData() const;
	void setLinkData(UInt32 linkData);
	OSPFv2RouterLinkType getType() const;
	void setType(OSPFv2RouterLinkType type);
	UInt8 getNTOS() const;
	UInt16 getMetric() const;
	void setMetric(UInt16 metric);

	void getMetaData(MetaData& metaData) const;
	void set(const MetaData& metaData);
private:
	UInt32 linkID;
	UInt32 linkData;
	UInt8 type;
	UInt8 nTOS;//not used
	UInt16 metric;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2RouterLink& routerLink);
class OSPFv2RouterLSA: public OSPFv2LSA
{
public:
	enum OSPFv2RouterLSAOptionFeild
	{
		V_bit = 0x0400,
		E_bit = 0x0200,
		B_bit = 0x0100,
		NONE_bit = 0x0000,
		ALL_bits = V_bit|E_bit|B_bit
	};
	struct MetaData 
	{
		OSPFv2LSAHeader::MetaData headerMetaData;
		UInt16 options;
		UInt16 nLinks;
	};
	OSPFv2RouterLSA();

	OSPFv2RouterLSAOptionFeild getOptions(OSPFv2RouterLSAOptionFeild option) const;//输入位名返回是否置位,可以用按位或连接多个Options位
	void setOptions(OSPFv2RouterLSAOptionFeild options);//可以用按位或连接多个Options位
	UInt16 getNLinks() const;
	std::vector<OSPFv2RouterLink> getRouterLinks() const;
	void addRouterLink(const OSPFv2RouterLink& routerLink);

	void getMetaData(UInt8* series) const;
	const UInt8* set(const UInt8* series);
private:
	UInt16 options;
	std::vector<OSPFv2RouterLink> routerLinks;
};
std::ostream& operator<< (std::ostream& os, const OSPFv2RouterLSA& routerLSA);