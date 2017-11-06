#pragma once
#include <vector>
#include <tuple>

class ParameterBase {
	int _callId;
public:
	const char * GetName();
	ParameterBase(int callid);
	virtual void * GetParameter(int pos) = 0;

	virtual ~ParameterBase() = 0;
};

template<typename T>
class ParameterImpl : public ParameterBase {
private:
	T _params;
public:
	ParameterImpl(int callid, T params);
	void * GetParameter(int pos);
	~ParameterImpl();
};
