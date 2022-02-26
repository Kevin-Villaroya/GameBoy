#ifndef __STARTUP_EXCEPTION_H__
#define __STARTUP_EXCEPTION_H__

#include <stdexcept>

class StartupException : public std::runtime_error{
    public:
        StartupException() : runtime_error("startup failed to boot"){}
};

#endif