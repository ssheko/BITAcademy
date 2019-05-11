#pragma once
#pragma comment(lib,"thirdparty/mysql-c/lib/vs14/mysqlclient.lib")

#include <Windows.h>
#include <strsafe.h>
#include "Logger.h"
#include "Parser.h"
#include "CrashDump.h"
#include "thirdparty/mysql-c/include/mysql.h"
#include "thirdparty/mysql-c/include/errmsg.h"

class DBConnector
{
public:
	enum en_DB_CONNECTOR
	{
		eQUERY_MAX_LEN = 2048
	};

private:
	//-------------------------------------------------------------
	// MySQL ���ᰴü ��ü
	//-------------------------------------------------------------
	MYSQL		_MySQL;

	//-------------------------------------------------------------
	// MySQL ���ᰴü ������. �� ������ ��������. 
	// �� �������� null ���η� ������� Ȯ��.
	//-------------------------------------------------------------
	MYSQL *		_MySQLPointer;

	//-------------------------------------------------------------
	// ������ ���� �� Result �����.
	//
	//-------------------------------------------------------------
	MYSQL_RES *	_SQLResult;

	WCHAR		_DBIP[16];
	WCHAR		_DBUser[64];
	WCHAR		_DBPassword[64];
	WCHAR		_DBName[64];
	int			_DBPort;


	WCHAR		_Query[eQUERY_MAX_LEN];
	char		_QueryUTF8[eQUERY_MAX_LEN];

	int			_LastError;
	WCHAR		_LastErrorMsg[128];

	//////////////////////////////////////////////////////////////////////
	// mysql �� LastError �� �ɹ������� �����Ѵ�.
	//////////////////////////////////////////////////////////////////////
	void		SaveLastError(void);
protected:
	Parser		_configParser;

public:
	DBConnector(const char * config);
	DBConnector(WCHAR * DBIP, WCHAR * User, WCHAR * Password, WCHAR * DBName, int DBPort);
	virtual		~DBConnector();

	//////////////////////////////////////////////////////////////////////
	// MySQL DB ����
	//////////////////////////////////////////////////////////////////////
	bool		Connect(void);

	//////////////////////////////////////////////////////////////////////
	// MySQL DB ����
	//////////////////////////////////////////////////////////////////////
	bool		Disconnect(void);


	//////////////////////////////////////////////////////////////////////
	// ���� ������ ����� �ӽ� ����
	//
	//////////////////////////////////////////////////////////////////////
	bool		Query(const WCHAR * StringFormat, va_list args);
	bool		Query(const WCHAR * StringFormat, ...);
	bool		Query_Save(const WCHAR *szStringFormat, ...);	// DBWriter �������� Save ���� ����
															// ������� �������� ����.

	//////////////////////////////////////////////////////////////////////
	// ������ ���� �ڿ� ��� �̾ƿ���.
	//
	// ����� ���ٸ� NULL ����.
	//////////////////////////////////////////////////////////////////////
	MYSQL_ROW	FetchRow(void);

	//////////////////////////////////////////////////////////////////////
	// �� ������ ���� ��� ��� ��� �� ����.
	//////////////////////////////////////////////////////////////////////
	void		FreeResult(void);


	//////////////////////////////////////////////////////////////////////
	// Error ���.�� ������ ���� ��� ��� ��� �� ����.
	//////////////////////////////////////////////////////////////////////
	int			GetLastError(void) { return _LastError; };
	WCHAR *		GetLastErrorMsg(void) { return _LastErrorMsg; }

	friend class DBConnectorTLS;
};


// TLS ver
constexpr int DBConnectorArray = 20;
class DBConnectorTLS
{
	DWORD		_tlsIndex;
	WCHAR		_DBIP[16];
	WCHAR		_DBUser[64];
	WCHAR		_DBPassword[64];
	WCHAR		_DBName[64];
	int			_DBPort;

	int			_arrayIndex;
	DBConnector *	_DBConnectorPointerArray[DBConnectorArray];
	Parser		_configParser;

	void		SaveLastError(void);

public:
	DBConnectorTLS(const char * config);
	DBConnectorTLS(WCHAR * DBIP, WCHAR * User, WCHAR * Password, WCHAR * DBName, int DBPort);
	~DBConnectorTLS();

	bool		Connect(void);

	bool		Disconnect(void);

	bool		Query(const WCHAR *szStringFormat, ...);
	bool		Query_Save(const WCHAR *szStringFormat, ...);

	MYSQL_ROW	FetchRow(void);

	void		FreeResult(void);

	int			GetLastError(void);
	WCHAR *		GetLastErrorMsg(void);
};