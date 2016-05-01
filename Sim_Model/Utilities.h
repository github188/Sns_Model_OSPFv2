#pragma once
#include "StdAfx.h"
#include <assert.h>
#include "types.h"

/************************************************************************/
/* IPv4Address                                                                     */
/************************************************************************/
class IPv4Address;
typedef IPv4Address IPv4Mask;

class IPv4Address
{
public:
	IPv4Address(UInt32 address=0xffffffff)
		:m_address(address)
	{

	}
	IPv4Address(const std::string address)
	{
		set(address);
	}

	UInt32 get() const
	{
		return m_address;
	}
	void print(std::ostream& os) const
	{
		os<<((m_address>>24)&0xff)<<"."
			<<((m_address>>16)&0xff)<<"."
			<<((m_address>>8)&0xff)<<"."
			<<((m_address>>0)&0xff);
	}
	void set(UInt32 address)
	{
		m_address=address;
	}
	void set(const std::string& address)
	{
		UInt32 a,b,c,d;
		sscanf_s(address.c_str(),"%u.%u.%u.%u",&a,&b,&c,&d);
		m_address=a<<24+b<<16+c<<8+d;
	}

	static IPv4Address GetZeros()
	{
		return IPv4Address(0x00000000);
	}
	static IPv4Address GetOnes()
	{
		return IPv4Address(0xffffffff);
	}
	static IPv4Address GetBroadcast(const IPv4Address& address, const IPv4Mask& mask);
private:
	UInt32 m_address;
};

inline IPv4Address operator& (const IPv4Address& address, const IPv4Mask& mask)
{
	return IPv4Address(address.get()&mask.get());
}
inline IPv4Address operator| (const IPv4Address& address1, const IPv4Mask& address2)
{
	return IPv4Address(address1.get()|address2.get());
}
inline IPv4Address operator~ (const IPv4Address& address)
{
	return IPv4Address(~address.get());
}

inline bool operator== (const IPv4Address& address1, const IPv4Mask& address2)
{
	return address1.get()==address2.get();
}
inline bool operator!= (const IPv4Address& address1, const IPv4Mask& address2)
{
	return address1.get()!=address2.get();
}
inline std::ostream& operator<<(std::ostream& os, const IPv4Address& address)
{
	address.print(os);
	return os;
}
inline std::istream& operator>>(std::istream& is, IPv4Address address)
{
	std::string str;
	is>>str;
	address.set(str);
	return is;
}

inline IPv4Address IPv4Address::GetBroadcast(const IPv4Address& address, const IPv4Mask& mask)
{
	return (address&mask)|(~mask);
}