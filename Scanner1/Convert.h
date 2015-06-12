#include <msclr\marshal_cppstd.h>
#include <string>


using namespace System::Runtime::InteropServices;
using namespace System;
using namespace std;

void MarshalString(String^ s, string& os)
{
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalConstChar(String^ s, const char* &oc)
{
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
}
