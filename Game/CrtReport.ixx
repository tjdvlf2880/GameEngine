module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
export module CrtReport;

export enum DumpMode
{
	Conosle,
	VsOutput
};

export class CrtReport
{
	_CrtMemState initialState;
	void SetMode(DumpMode mode);
public:
	void MemCheckPoint();
	void Check(DumpMode mode = DumpMode::Conosle);
	void FinalCheck(DumpMode mode = DumpMode::VsOutput);
	CrtReport();
};

