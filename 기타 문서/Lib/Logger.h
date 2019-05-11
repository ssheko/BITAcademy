#pragma once
#define LOGGER			Logger::GetInstance()
#define LOG_DEBUG		Logger::LOG_LEVEL_DEBUG
#define LOG_WARNING		Logger::LOG_LEVEL_WARNING
#define LOG_ERROR		Logger::LOG_LEVEL_ERROR
#define LOG(filename, logLevel, fmt, ...)		LOGGER.Log(filename, logLevel, fmt, __VA_ARGS__)
#define LOGHEX(filename, logLevel, log, size)	LOGGER.LogHex(filename, logLevel, log, size)


#include <string>
#include <Windows.h>
#include <time.h>
#include <direct.h>
#include <strsafe.h>
#include <locale.h>

#include "Clock.h"
using namespace std;
// �α� Ŭ����
class Logger
{
public:
	enum LOG_LEVEL
	{
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_ERROR
	};
private:
	int _logLevel;					// �α� ����
	bool _fileSaveFlag;				// �������� �÷���
	wstring _logDir;				// �α����� ����̸�
	unsigned int _logCount;			// �α� ī��Ʈ
	static Logger * _instance;		// �̱���
	Logger();
	~Logger() {};
public:
	static Logger & GetInstance() 
	{
		if (_instance == nullptr)
			_instance = new Logger;
		return *_instance;
	}
	// �α��ۼ� ��� �Լ�
	void Log(const WCHAR * filename, LOG_LEVEL logLevel, const WCHAR * fmt, ...);
	void Log(const WCHAR * filename, const WCHAR *fmt, va_list args);
	// 16������ �α��ۼ�
	void LogHex(const WCHAR * filename, LOG_LEVEL logLevel, const CHAR * loghex, int hexSize);
	// �α׷��� ����
	void SetLogLevel(LOG_LEVEL level);
	// �α׵��丮
	void SetLogDir(wstring * fileName);
	// �¿���
	void OnOff(bool onoff);
};