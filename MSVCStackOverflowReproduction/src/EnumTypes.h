#pragma once
#include <cstdint>

enum EnumTypeA
{
	VALUE_A,
	VALUE_B,
	VALUE_C
};

enum StorageTypeID
{
	INT_32,
	UINT_32,
	FLOAT,
	DOUBLE
};

struct StorageCollection
{
	StorageTypeID TypeID;

	union
	{
		std::int32_t Int32;
		std::uint32_t UInt32;
		float Float;
		double Double;
	};
};