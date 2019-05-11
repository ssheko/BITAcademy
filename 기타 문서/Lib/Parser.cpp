#include "pch.h"
#include "Parser.h"

Parser::Parser()
{
	for (auto & box : _box)
	{
		box = 0;
	}
	_blockCount = 0;
	_fileSize = 0;
	_flag = 0;
}

void Parser::PrintAll()
{
	char a[3]; 
	a[0] = *_curPointer;
	a[1] = '2';
	a[2] = '\0';
	printf("%s",a);
}

bool Parser::OpenFile(const char * fileName)
{
	if (fopen_s(&_file, fileName, "rb") != 0)
		return false;

	int fd = _fileno(_file);
	_fileSize = _filelength(fd);
	_filePointer = (char *)malloc(_fileSize);
	fread_s(_filePointer, _fileSize, _fileSize, 1, _file);
	_curPointer = _filePointer;
	_fileEndPointer = _filePointer + _fileSize;

	_checkChar[0] = _filePointer;
	_checkChar[1] = _filePointer + 1; 
	//���� �α��ڵ� �ȵǳ�?
	fclose(_file);
	if (_checkChar[1] >= _fileEndPointer)
		return false;
	UpdateFlag();
	CheckBlock();
	return true;
}

void Parser::CheckBlock()
{
	Block block;
	char buffer[2];
	while (_checkChar[1] != _fileEndPointer)
	{
		memset(buffer, 0, 2);
		int bufPos = 0;
		if (*_checkChar[0] == ':')
		{
			buffer[bufPos] = ':';
			bufPos = (bufPos + 1) % 2;
		}
	
		while (_checkChar[1] != _fileEndPointer)
		{
			if (buffer[0] == ':' && buffer[1] == ':')
				break;
	
			Read();
			UpdateFlag();
			if (IsComment())
				continue;
	
			if (*_checkChar[0] == ':')
			{
				buffer[bufPos] = ':';
				bufPos = (bufPos + 1) % 2;
				continue;
			}
		}
		// ���� *_checkChar�� [:][?] ����

		if (!GetNextWord(block._name,_fileEndPointer))
			return;
		// ���� *_checkChar�� [x][] ����
		while (_checkChar[1] != _fileEndPointer)
		{
			if (*_checkChar[0] == '{')
				break;
			Jump();
		}
		if (_checkChar[1] == _fileEndPointer)
			return;
		block._startPoint = _checkChar[0];
	
		while (_checkChar[1] != _fileEndPointer)
		{
			if (*_checkChar[0] == '}')
				break;
			Jump();
		}
		if (*_checkChar[0] != '}' && _checkChar[1] == _fileEndPointer )
			return;
		block._endPoint = _checkChar[0];
		_block[_blockCount++] = block;
	}
}

bool Parser::CloseFile()
{
	free(_filePointer);
	for (auto & box : _box)
	{
		box = 0;
	}
	_blockCount = 0;
	_fileSize = 0;
	_flag = 0;
	return true;
}

void Parser::Read()
{
	_checkChar[0]++;
	_checkChar[1]++;
	/*
	_box[0] = _box[1];
	_box[1] = *_curPointer++;
	*/
}

void Parser::UpdateFlag()
{
	//�÷��� ���� Ȯ��
	// �ּ� ����ϰ��
	if (GetFlag() & (BLOCKCOMMENT | LINECOMMENT))
	{
		// �ּ�����
		if (*_checkChar[0] == CARRIAGE_RETURN && *_checkChar[1] == LINE_FEED)
			OffFlag(LINECOMMENT);
		if (*_checkChar[0] == '*' && *_checkChar[1] == '/')
		{
			Read();
			Read();
			UpdateFlag();
			OffFlag(BLOCKCOMMENT);
		}
	}
	// �ּ���尡 �ƴҶ�
	else
	{
		// �ּ����� 
		if (*_checkChar[0] == '/' && *_checkChar[1] == '/')
			SetFlag(LINECOMMENT);

		if (*_checkChar[0] == '/' && *_checkChar[1] == '*')
		{
			SetFlag(BLOCKCOMMENT);
			Read();
			Read();
		}

		// ���ڿ� ����϶� 
		if (GetFlag() & STRINGMODE)
		{
			// Ư��ó������϶�
			if (GetFlag() & SPECIALMODE)
			{
				Read();
				OffFlag(SPECIALMODE); //����
			}
			// �ƴҶ� 
			else
			{
				if (*_checkChar[0] == '\\')
					SetFlag(SPECIALMODE);
				// ���ڿ���� ����
				if (*_checkChar[0] == '"')
					SetFlag(STRINGMODE);
			}
		}
		// ���ڿ��� ����
		else
		{
			if (*_checkChar[0] == '"')
			{
				SetFlag(STRINGMODE);
				Read();
			}
		}
	}
}

bool Parser::GetEqual()
{
	while (_checkChar[1] != _fileEndPointer)
	{
		if (*_checkChar[0] == '=')
			return true;
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (*_checkChar[0] == '=')
			return true;
	}
	return false;
}
// �ܾ��� ���üũ
bool Parser::CheckBlank()
{
	if (*_checkChar[0] == ',')
		return true;
	if (*_checkChar[0] == ' ')
		return true;
	if (*_checkChar[0] == SPACE) // �����̽�
		return true;
	if (*_checkChar[0] == BACK_SPACE) // �齺���̽�
		return true;
	if (*_checkChar[0] == TAB) // ��
		return true;
	if (*_checkChar[0] == LINE_FEED) // �����ǵ�
		return true;
	if (*_checkChar[0] == CARRIAGE_RETURN) // ĳ��������
		return true;
	if (*_checkChar[0] == '=')
		return true;
	
	return false;
}
// ����� ���´� [x][?] ���� ���� , Jump�� ���´� NonComment Mode �� [y][?]
bool Parser::Jump()
{
	while (_checkChar[1] != _fileEndPointer)
	{
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (!CheckBlank())
			return true;
	}
	return false;
}

// ������ ����� [x][] , ã���ܾ��� ���κ�
bool Parser::GetNextWord(char * buffer, char * blockEndPoint)
{
	if (_checkChar[1] == blockEndPoint)
		return false;
	
	char buf[64];
	int length = 0;
	if (!Jump())
		return false;
	// Jump()�� ���� *_checkChar[0]�� �ּ��� �ƴѱ������� ����
	buf[length++] = *_checkChar[0]; 
	while (_checkChar[1] != _fileEndPointer)
	{
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (CheckBlank())
			break;
		buf[length++] = *_checkChar[0];
	}
	buf[length] = '\0';
	memcpy(buffer, buf, sizeof(buf));
	return true;
}

bool Parser::GetValue_BYTE(const char * word, BYTE & outBYTE, const char * blockName)
{

	// ��� ������, ����
	char *blockEndPoint = _fileEndPointer;
	for (auto block : _block)
	{
		if (strcmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	char buffer[64];
	while (GetNextWord(buffer, blockEndPoint))
	{
		if (strcmp(buffer, word) != 0)
			continue;

		if (!GetEqual())
			return false;

		GetNextWord(buffer, blockEndPoint);
		outBYTE = (BYTE)atoi(buffer);
		return true;
	}
	return false;
}

bool Parser::GetValue_Int(const char * word, int & outInt, const char * blockName)
{
	
	// ��� ������, ����
	char *blockEndPoint = _fileEndPointer;
	for (auto & block : _block)
	{
		if (strcmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	char buffer[64];
	while (GetNextWord(buffer, blockEndPoint))
	{
		if (strcmp(buffer, word) != 0)
			continue;

		if (!GetEqual())
			return false;

		GetNextWord(buffer,blockEndPoint);
		outInt = atoi(buffer);
		return true;
	}
	return false;
}

bool Parser::GetValue_Str(const char * word, char * outString, const char * blockName)
{
	char *blockEndPoint = _fileEndPointer;
	for (auto block : _block)
	{
		if (strcmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	char buffer[64];
	int bufPos = 0;
	while (GetNextWord(buffer, blockEndPoint))
	{
		// �� �ܾ �ƴϴ�
		if (strcmp(buffer, word) != 0)
			continue;

		// GetEqual �����ϸ� [=][?]
		if (!GetEqual())
			return false;

		while (_checkChar[1] != blockEndPoint)
		{
			// �����ϸ� checkChar = ["][?]
			if (!IsString())
			{
				Read();
				UpdateFlag();
				continue;
			}
			else
			{
				buffer[bufPos++] = *_checkChar[0];
				Read();
				UpdateFlag();
			}
			if (!IsString())
			{
				buffer[bufPos] = '\0';
				memcpy(outString, buffer, strlen(buffer) + 1);
				return true;
			}
		}
		return false;
	}
	return false;
}

unsigned char Parser::GetFlag()
{
	return _flag;
}

void Parser::SetFlag(Flag flag)
{
	_flag ^= flag;
}

void Parser::OffFlag(Flag flag)
{
	_flag &= ~flag;
}

bool Parser::IsComment()
{
	return _flag & (LINECOMMENT | BLOCKCOMMENT);
}

bool Parser::IsString()
{
	return _flag & (STRINGMODE);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



ParserUNI::ParserUNI()
{
	for (auto& box : _box)
	{
		box = 0;
	}
	_blockCount = 0;
	_fileSize = 0;
	_flag = 0;
}

void ParserUNI::PrintAll()
{
	WCHAR a[3];
	a[0] = *_curPointer;
	a[1] = '2';
	a[2] = '\0';
	wprintf(L"%s", a);
}

bool ParserUNI::OpenFile(const WCHAR* fileName)
{
	if (_wfopen_s(&_file, fileName, L"r, ccs=UNICODE") != 0)
		return false;

	int fd = _fileno(_file);
	_fileSize = _filelength(fd);
	_filePointer = (WCHAR*)malloc(_fileSize);
	fread_s(_filePointer, _fileSize, _fileSize, 1, _file);
	_curPointer = _filePointer;
	_fileEndPointer = _filePointer + _fileSize / 2;


	_checkChar[0] = _filePointer;
	_checkChar[1] = _filePointer + 1;
	//���� �α��ڵ� �ȵǳ�?
	fclose(_file);
	if (_checkChar[1] >= _fileEndPointer)
		return false;
	UpdateFlag();
	CheckBlock();
	return true;
}

void ParserUNI::CheckBlock()
{
	BlockUNI block;
	WCHAR buffer[2];
	while (_checkChar[1] != _fileEndPointer)
	{
		memset(buffer, 0, 4);
		int bufPos = 0;
		if (*_checkChar[0] == L':')
		{
			buffer[bufPos] = L':';
			bufPos = (bufPos + 1) % 2;
		}

		while (_checkChar[1] != _fileEndPointer)
		{
			if (buffer[0] == L':' && buffer[1] == L':')
				break;

			Read();
			UpdateFlag();
			if (IsComment())
				continue;

			if (*_checkChar[0] == L':')
			{
				buffer[bufPos] = L':';
				bufPos = (bufPos + 1) % 2;
				continue;
			}
		}
		// ���� *_checkChar�� [:][?] ����

		if (!GetNextWord(block._name, _fileEndPointer))
			return;
		// ���� *_checkChar�� [x][] ����
		while (_checkChar[1] != _fileEndPointer)
		{
			if (*_checkChar[0] == L'{')
				break;
			Jump();
		}
		if (_checkChar[1] == _fileEndPointer)
			return;
		block._startPoint = _checkChar[0];

		while (_checkChar[1] != _fileEndPointer)
		{
			if (*_checkChar[0] == L'}')
				break;
			Jump();
		}
		if (*_checkChar[0] != L'}' && _checkChar[1] == _fileEndPointer)
			return;
		block._endPoint = _checkChar[0];
		_block[_blockCount++] = block;
	}
}

bool ParserUNI::CloseFile()
{
	free(_filePointer);
	for (auto& box : _box)
	{
		box = 0;
	}
	_blockCount = 0;
	_fileSize = 0;
	_flag = 0;
	return true;
}

void ParserUNI::Read()
{
	_checkChar[0]++;
	_checkChar[1]++;
	/*
	_box[0] = _box[1];
	_box[1] = *_curPointer++;
	*/
}

void ParserUNI::UpdateFlag()
{
	//�÷��� ���� Ȯ��
	// �ּ� ����ϰ��
	if (GetFlag() & (BLOCKCOMMENT | LINECOMMENT))
	{
		// �ּ�����
		if (/**_checkChar[0] == BLANKUNI::CARRIAGE_RETURN &&*/ *_checkChar[0] == BLANKUNI::LINE_FEED)
			OffFlag(LINECOMMENT);
		if (*_checkChar[0] == L'*' && *_checkChar[1] == L'/')
		{
			Read();
			Read();
			UpdateFlag();
			OffFlag(BLOCKCOMMENT);
		}
	}
	// �ּ���尡 �ƴҶ�
	else
	{
		// �ּ����� 
		if (*_checkChar[0] == L'/' && *_checkChar[1] == L'/')
			SetFlag(LINECOMMENT);

		if (*_checkChar[0] == L'/' && *_checkChar[1] == L'*')
		{
			SetFlag(BLOCKCOMMENT);
			Read();
			Read();
		}

		// ���ڿ� ����϶� 
		if (GetFlag() & STRINGMODE)
		{
			// Ư��ó������϶�
			if (GetFlag() & SPECIALMODE)
			{
				Read();
				OffFlag(SPECIALMODE); //����
			}
			// �ƴҶ� 
			else
			{
				if (*_checkChar[0] == L'\\')
					SetFlag(SPECIALMODE);
				// ���ڿ���� ����
				if (*_checkChar[0] == L'"')
					SetFlag(STRINGMODE);
			}
		}
		// ���ڿ��� ����
		else
		{
			if (*_checkChar[0] == L'"')
			{
				SetFlag(STRINGMODE);
				Read();
			}
		}
	}
}

bool ParserUNI::GetEqual()
{
	while (_checkChar[1] != _fileEndPointer)
	{
		if (*_checkChar[0] == L'=')
			return true;
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (*_checkChar[0] == L'=')
			return true;
	}
	return false;
}
// �ܾ��� ���üũ
bool ParserUNI::CheckBlank()
{
	if (*_checkChar[0] == L',')
		return true;
	if (*_checkChar[0] == L' ')
		return true;
	if (*_checkChar[0] == BLANKUNI::SPACE) // �����̽�
		return true;
	if (*_checkChar[0] == BLANKUNI::BACK_SPACE) // �齺���̽�
		return true;
	if (*_checkChar[0] == BLANKUNI::TAB) // ��
		return true;
	if (*_checkChar[0] == BLANKUNI::LINE_FEED) // �����ǵ�
		return true;
	if (*_checkChar[0] == BLANKUNI::CARRIAGE_RETURN) // ĳ��������
		return true;
	if (*_checkChar[0] == L'=')
		return true;

	return false;
}
// ����� ���´� [x][?] ���� ���� , Jump�� ���´� NonComment Mode �� [y][?]
bool ParserUNI::Jump()
{
	while (_checkChar[1] != _fileEndPointer)
	{
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (!CheckBlank())
			return true;
	}
	return false;
}

// ������ ����� [x][] , ã���ܾ��� ���κ�
bool ParserUNI::GetNextWord(WCHAR* buffer, WCHAR* blockEndPoint)
{
	if (_checkChar[1] == blockEndPoint)
		return false;

	WCHAR buf[64];
	int length = 0;
	if (!Jump())
		return false;
	// Jump()�� ���� *_checkChar[0]�� �ּ��� �ƴѱ������� ����
	buf[length++] = *_checkChar[0];
	while (_checkChar[1] != _fileEndPointer)
	{
		Read();
		UpdateFlag();
		if (IsComment())
			continue;
		if (CheckBlank())
			break;
		buf[length++] = *_checkChar[0];
	}
	buf[length] = L'\0';
	memcpy(buffer, buf, sizeof(buf));
	return true;
}

bool ParserUNI::GetValue_BYTE(const WCHAR* word, BYTE & outBYTE, const WCHAR* blockName)
{

	// ��� ������, ����
	WCHAR* blockEndPoint = _fileEndPointer;
	for (auto block : _block)
	{
		if (wcscmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	WCHAR buffer[64];
	while (GetNextWord(buffer, blockEndPoint))
	{
		if (wcscmp(buffer, word) != 0)
			continue;

		if (!GetEqual())
			return false;

		GetNextWord(buffer, blockEndPoint);
		outBYTE = (BYTE)_wtoi(buffer);
		return true;
	}
	return false;
}

bool ParserUNI::GetValue_Int(const WCHAR* word, int& outInt, const WCHAR* blockName)
{

	// ��� ������, ����
	WCHAR* blockEndPoint = _fileEndPointer;
	for (auto& block : _block)
	{
		if (wcscmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	WCHAR buffer[64];
	while (GetNextWord(buffer, blockEndPoint))
	{
		if (wcscmp(buffer, word) != 0)
			continue;

		if (!GetEqual())
			return false;

		GetNextWord(buffer, blockEndPoint);
		outInt = _wtoi(buffer);
		return true;
	}
	return false;
}

bool ParserUNI::GetValue_Str(const WCHAR* word, WCHAR* outString, const WCHAR* blockName)
{
	WCHAR* blockEndPoint = _fileEndPointer;
	for (auto block : _block)
	{
		if (wcscmp(block._name, blockName) == 0)
		{
			_checkChar[0] = block._startPoint;
			_checkChar[1] = _checkChar[0] + 1;
			blockEndPoint = block._endPoint;
			break;
		}
	}
	// ����� ������? ó���� ���� ����.
	// �ϴ� ����� ã�Ҵٰ� ����
	WCHAR buffer[64];
	int bufPos = 0;
	while (GetNextWord(buffer, blockEndPoint))
	{
		// �� �ܾ �ƴϴ�
		if (wcscmp(buffer, word) != 0)
			continue;

		// GetEqual �����ϸ� [=][?]
		if (!GetEqual())
			return false;

		while (_checkChar[1] != blockEndPoint)
		{
			// �����ϸ� checkChar = ["][?]
			if (!IsString())
			{
				Read();
				UpdateFlag();
				continue;
			}
			else
			{
				buffer[bufPos++] = *_checkChar[0];
				Read();
				UpdateFlag();
			}
			if (!IsString())
			{
				buffer[bufPos] = L'\0';
				memcpy(outString, buffer, wcslen(buffer) * 2 + 2);
				return true;
			}
		}
		return false;
	}
	return false;
}

unsigned char ParserUNI::GetFlag()
{
	return _flag;
}

void ParserUNI::SetFlag(Flag flag)
{
	_flag ^= flag;
}

void ParserUNI::OffFlag(Flag flag)
{
	_flag &= ~flag;
}

bool ParserUNI::IsComment()
{
	return _flag & (LINECOMMENT | BLOCKCOMMENT);
}

bool ParserUNI::IsString()
{
	return _flag & (STRINGMODE);
}
