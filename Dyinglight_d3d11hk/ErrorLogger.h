#pragma once

static void LogError(std::string str) 
{
	const char* cstr = str.c_str();
	MessageBox(NULL, cstr, "DEBUG INFO", MB_OK);
}