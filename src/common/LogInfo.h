#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <boost/thread/recursive_mutex.hpp>
#include <string>

// Lock to ensure single entry output
class LogInfo {
private:
	mutable boost::recursive_mutex _log_mtx;
	FILE * _fd;	
	std::string _header;
public:
	LogInfo(FILE * fd = stderr) {
		_header = std::string("");
		if (fd < 0){
			_fd = stderr;
			fprintf(stderr, "%s\n", "[LOGINFO] Could not open output file, using stderr");
		}
		else {
			_fd = fd; 
		}
	}

	LogInfo(std::string filename, std::string header) {
		_fd = fopen(filename.c_str(), "w");
		if (_fd == NULL)  {
			fprintf(stderr, "%s %s\n", "[LOGINFO] Could not open output file, defaulting to stdout: ", filename.c_str());
			_fd = stdout;
		}
		_header = std::string("[") + header + std::string("]");
	}

	~LogInfo() {
		fflush(_fd);
		fclose(_fd);
	}

	void Flush() {
		fflush(_fd);
	}
	void Write(std::string & out) {
		{
			boost::recursive_mutex::scoped_lock lock(_log_mtx);
			fprintf(_fd, "%s %s", _header.c_str(), out.c_str());
		}
	}
	void Write(char * fmt, ...) {
		{
			boost::recursive_mutex::scoped_lock lock(_log_mtx);
		    va_list ap;
		    va_start(ap, fmt);
		    vfprintf(_fd, fmt, ap);
		    va_end(ap);
		}
	}
	void Write(char * fmt, va_list args) {
		{
			boost::recursive_mutex::scoped_lock lock(_log_mtx);
		    vfprintf(_fd, fmt, args);
		}
	}
};
