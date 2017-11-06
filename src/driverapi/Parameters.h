#pragma once
#include <vector>
#include <tuple>

class ParameterBase {
private:
	int _callId;
public:
	const char * GetName();
	ParameterBase(int callid);
	virtual void * GetParameter(int pos) = 0;
	virtual size_t GetLen() = 0;
	virtual ~ParameterBase() = 0;
};

class ParameterImpl : public ParameterBase {
private:
	std::vector<void *> * _params;
public:
	ParameterImpl(int callid, std::vector<void *> * params);
	size_t GetLen();
	void * GetParameter(int pos);
	~ParameterImpl();
};
