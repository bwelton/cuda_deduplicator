#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <boost/thread/recursive_mutex.hpp>

// Lock to ensure single entry output
extern boost::recursive_mutex _log_mtx;
class LogInfo {
private:
	
	FILE * _fd;
	
public:
	LogInfo(FILE * fd = stderr) {
		_fd = fd; 
	}

	~LogInfo() {
		fflush(_fd);
	}

	void Write(char * fmt, ...) {
		boost::recursive_mutex::scoped_lock lock(_log_mtx);
	    va_list ap;
	    va_start(ap, fmt);
	    vfprintf(_fd, fmt, ap);
	    va_end(ap);
	}
	void Write(char * fmt, va_list args) {
		boost::recursive_mutex::scoped_lock lock(_log_mtx);
	    vfprintf(_fd, fmt, args);
	}
};
