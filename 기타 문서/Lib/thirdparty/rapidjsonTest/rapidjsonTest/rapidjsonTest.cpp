// rapidjsonTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
using namespace rapidjson;
typedef GenericStringBuffer<UTF16<>> StringBufferUTF16;
typedef GenericDocument<UTF16<>> DocumentUTF16;
typedef GenericValue<UTF16<>> ValueUTF16;


int main()
{
	_wsetlocale(LC_ALL, L"korean");
	StringBufferUTF16 stringJSON;
	Writer<StringBufferUTF16, UTF16LE<>, UTF16LE<>> writer(stringJSON);
	writer.StartObject(); // {
	writer.String(L"Account"); // key

	writer.StartArray(); // [ value

	writer.StartObject(); // {
	writer.String(L"AccountNo"); // key
	writer.Uint64(1111); // value
	writer.String(L"NickName"); // key
	writer.String(L"한"); // value
	writer.EndObject(); // }
	
	writer.EndArray(); // ]

	writer.EndObject(); // }

	const WCHAR * json = stringJSON.GetString();
	wprintf_s(json);
	wprintf_s(L"\n");

	DocumentUTF16 doc;
	doc.Parse(json);

	ValueUTF16 &AccountObject = doc[L"Account"];
	system("pause");


    return 0;
}

