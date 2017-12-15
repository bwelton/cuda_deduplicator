#pragma once
#include <vector>
#include <tuple>
#include "PluginCommon.h"
class Parameters{
private:
	void * _func;
	CallID _callId;
	bool _called;
	int _ret;
public:
	std::vector<void **> values;
	const char * GetName();
	CallID GetID();
	Parameters(CallID id, void * func, std::vector<void**> v);
	~Parameters();
	size_t GetLen();
	void * GetParameter(int pos);
	int Call();
	int GetReturn();
	int CallUnderlying();
};


// class ParameterBase {
// private:
// 	int _callId;
// public:
// 	const char * GetName();
// 	int GetID();
// 	ParameterBase(int callid);
// 	virtual void * GetParameter(int pos) = 0;
// 	virtual size_t GetLen() = 0;
// 	virtual ~ParameterBase() = 0;
// };

// class ParameterImpl : public ParameterBase {
// private:
// 	std::vector<void *> * _params;
// public:
// 	ParameterImpl(int callid, std::vector<void *> * params);
// 	size_t GetLen();
// 	void * GetParameter(int pos);
// 	~ParameterImpl();
// };
