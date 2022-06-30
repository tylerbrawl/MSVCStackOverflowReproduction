/*
Summary: Initializing fields of an anonymous union declared in a header within a static member function of a struct may 
cause a stack overflow in CL.exe.

Visual Studio Version: Version 17.3 Preview 2

Detailed Description: Attempting to pass a structure containing an anonymous union by reference into a static member
function of a struct and proceeding to modify said structure may result in a stack overflow in CL.exe. However, this only
happens under a strict set of conditions:

	1. The module containing the function(s) which will modify the anonymous union is *NOT* exporting the header file
	   containing the union's definition as a header unit. Instead, it is including the header in the global module fragment.

	2. The module containing the function(s) is imported into a translation unit, *AND* the header file containing
	   the union definition *IS* #included. CL.exe will not crash if the header file is not included, even if the function
	   which modifies the union is directly or indirectly called.

This might seem like a rather strict set of conditions, but it can happen. I recently came across this issue in an actual
project while working with the D3D12 API, which uses lots of anonymous unions within structs defined in header files. It is
also interesting to note that this issue is, in fact, a regression. The latest version which I know worked was version 17.3
Preview 1.1.

Reproduction Steps:
	1. Attempt to build the MSVCStackOverflowReproduction project. Regardless of the build mode (either Debug or Release),
	   CL.exe should crash with error code -1073741571 (i.e., Win32 error STATUS_STACK_OVERFLOW/0xC00000FD), assuming that
	   none of the source files were modified.
*/

#include <format>
#include <iostream>
#include <cassert>
#include "EnumTypes.h"  // <- Comment out this #include to build the project. Note that the project still builds even if TemplatedType::GetStorageCollection() is called if this header file is not included.

import TemplatedType;

int main(const int argc, const char* const argv[])
{
	const NS::UInt32TemplatedType templatedTypeInstance{ 69 };
	const auto collection{ templatedTypeInstance.GetStorageCollection() };

	//assert(collection.TypeID == StorageTypeID::UINT_32 && "ERROR: The StorageCollection instance contained an unexpected type!");

	//std::wcout << std::format(L"Stored Value: {}\n", collection.UInt32);
	
	return 0;
}