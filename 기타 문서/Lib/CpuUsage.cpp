#include "pch.h"
#include "CpuUsage.h"

CpuUsage::CpuUsage(HANDLE process)
{
	// �ڵ��� ���ٸ� �ڱ��ڽ��� ���
	if (process == INVALID_HANDLE_VALUE)
	{
		_process = GetCurrentProcess();
	}

	// ���μ��� ���� Ȯ��
	SYSTEM_INFO systemInfo;

	GetSystemInfo(&systemInfo);
	_numberOfProcessors = systemInfo.dwNumberOfProcessors;

	_processorTotal = 0;
	_processorUser = 0;
	_processorKernel = 0;

	_processTotal = 0;
	_processUser = 0;
	_processKernel = 0;

	_processor_LastKernel.QuadPart = 0;
	_processor_LastUser.QuadPart = 0;
	_processor_LastIdle.QuadPart = 0;

	_process_LastKernel.QuadPart = 0;
	_process_LastUser.QuadPart = 0;
	_process_LastTime.QuadPart = 0;

	UpdateCpuTime();
}

void CpuUsage::UpdateCpuTime()
{
	// CPU���� ����
	ULARGE_INTEGER kernel;
	ULARGE_INTEGER user;
	ULARGE_INTEGER idle;

	if (GetSystemTimes((PFILETIME)&idle, (PFILETIME)&kernel, (PFILETIME)&user) == false)
		return;

	// Ŀ��Ÿ�ӿ��� ���̵� Ÿ�� ����, ó����� �̻���
	ULONGLONG kernelDiff = kernel.QuadPart - _processor_LastKernel.QuadPart;
	ULONGLONG userDiff = user.QuadPart - _processor_LastUser.QuadPart;
	ULONGLONG idleDiff = idle.QuadPart - _processor_LastIdle.QuadPart;

	ULONGLONG Total = kernelDiff + userDiff;

	if (Total == 0)
	{
		_processUser = 0.0f;
		_processKernel = 0.0f;
		_processTotal = 0.0f;
	}
	else
	{
		// Ŀ�ο��� ���̵黩�� ���
		_processorTotal = (float)((double)(Total - idleDiff) / Total * 100.0f);
		_processorUser = (float)((double)userDiff / Total * 100.0f);
		_processorKernel = (float)((double)(kernelDiff - idleDiff) / Total * 100.0f);

		_processor_LastKernel = kernel;
		_processor_LastUser = user;
		_processor_LastIdle = idle;
	}

	// ������ ���μ��� ������ �����Ѵ�
	ULARGE_INTEGER none;
	ULARGE_INTEGER nowTime;

	GetSystemTimeAsFileTime((LPFILETIME)&nowTime);
	GetProcessTimes(_process, (LPFILETIME)&none, (LPFILETIME)&none, (LPFILETIME)&kernel, (LPFILETIME)&user);

	// ������ �ð��� ���ؼ� �����ð� Ȯ��
	ULONGLONG TimeDiff = nowTime.QuadPart - _process_LastTime.QuadPart;
	userDiff = user.QuadPart - _process_LastUser.QuadPart;
	kernelDiff = kernel.QuadPart - _process_LastKernel.QuadPart;

	Total = kernelDiff + userDiff;

	_processTotal = (float)(Total / (double)_numberOfProcessors / (double)TimeDiff * 100.0f);
	_processKernel = (float)(kernelDiff / (double)_numberOfProcessors / (double)TimeDiff * 100.0f);
	_processUser = (float)(userDiff / (double)_numberOfProcessors / (double)TimeDiff * 100.0f);

	_process_LastTime = nowTime;
	_process_LastKernel = kernel;
	_process_LastUser = user;
}

