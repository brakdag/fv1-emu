#include "stdafx.h"
#include "SCLog.h"
#include <iostream>
#include <string>
#include <cstdarg>
#include <fstream>
#include <time.h>

#ifdef _DEBUG
#define DEFAULT_LOG_LEVEL SCLogLevelVerbose
#else
#define DEFAULT_LOG_LEVEL SCLogLevelWarning
#endif

using namespace std;

SCLog* SCLog::_instance = 0;

SCLog::SCLog()
{
}

SCLog* SCLog::mainInstance()
{
	if(_instance == 0)
		_instance = new SCLog();

	return _instance;
}

const char* SCLog::rollingLogFile()
{
	return "logs\\SCLog.txt";
}

void SCLog::setupLogging()
{
	setupLoggingLevel(DEFAULT_LOG_LEVEL);
	file = rollingLogFile();
}

void SCLog::setupLoggingLevel(int level)
{
	logLevel = level;
}

void SCLog::log(int severity, const char* fmt, ... )
{
    va_list args;
    va_start(args, fmt);

	stringstream stream;

	if(severity >= this->logLevel)
	{
		while (*fmt != '\0') 
		{
			if(*fmt == '%')
			{
				if (*(fmt+1) == 'd') 
				{	
					int i = va_arg(args, int);
					stream << i;

					++fmt;
				}
				else if(*(fmt+1) == 'f')
				{
					double d = va_arg(args, double);
					stream << d;
					++fmt;
				}
				else if (*(fmt+1) == 's') 
				{
					char * s = va_arg(args, char*);
					if(s != 0)
					{
						stream << s;
					}
					else
					{
						stream << "null";
					}

					++fmt;
				}
			}
			else
			{
				stream << fmt[0];
			}
			++fmt;
		}

	
		std::cout << stream.str() << endl;
	
		std::ofstream outfile;
		outfile.open (this->rollingLogFile(), std::ofstream::out | std::ofstream::app);
		time_t rawtime;
		struct tm timeinfo;
		char buffer [80];

		time (&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime (buffer, 80,"[%Y-%m-%d %H:%M:%S]", &timeinfo);
		outfile << buffer << " " << stream.str() << endl;
		outfile.close();
	}
    va_end(args);
}