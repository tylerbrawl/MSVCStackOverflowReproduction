#include <format>
#include <iostream>
#include <cassert>
#include "EnumTypes.h"

import TemplatedType;

int main(const int argc, const char* const argv[])
{
	const NS::UInt32TemplatedType templatedTypeInstance{ 69 };
	const StorageCollection collection{ templatedTypeInstance.GetStorageCollection() };

	assert(collection.TypeID == StorageTypeID::UINT_32 && "ERROR: The StorageCollection instance contained an unexpected type!");

	std::wcout << std::format(L"Stored Value: {}\n", collection.UInt32);
	
	return 0;
}