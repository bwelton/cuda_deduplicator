#pragma once
#include <vector>
#include <tuple>
#include <set>
#include "PluginCommon.h"

class Parameters{
private:
	void * _func;
	CallID _callId;
	bool _called;
	int _ret;
	size_t _instId;
	uint32_t _hash;
public:
	std::vector<void **> values;
	const char * GetName();
	uint32_t GetHash();
	void SetHash(uint32_t hash);
	CallID GetID();
	void SetInstID(size_t i);
	size_t GetInstID();

	Parameters(CallID id, void * func, std::vector<void**> v);
	~Parameters();
	size_t GetLen();
	void * GetParameter(int pos);
	bool Called();
	int Call();
	int GetReturn();
	int CallUnderlying();
};

extern "C" void InitParameterData();

#define TRANSFER_CALLS {ID_cuMemcpy, ID_cuMemcpyAtoH, ID_cuMemcpyAtoA, ID_cuMemcpyAtoD_v2, ID_cuMemcpyAtoHAsync_v2, ID_cuMemcpyAtoH_v2, ID_cuMemcpyAtoA_v2, ID_cuMemcpyAtoD, ID_cuMemcpyAtoHAsync, ID_cuMemcpyDtoA, ID_cuMemcpyDtoA_v2, ID_cuMemcpyHtoA_v2, ID_cuMemcpyHtoA, ID_cuMemcpyHtoAAsync, ID_cuMemcpyHtoAAsync_v2, ID_cuMemcpyHtoD, ID_cuMemcpyDtoH, ID_cuMemcpyDtoD, ID_cuMemcpyDtoH_v2, ID_cuMemcpyDtoD_v2, ID_cuMemcpyAsync, ID_cuMemcpyHtoDAsync, ID_cuMemcpyDtoHAsync, ID_cuMemcpyDtoDAsync, ID_cuMemcpyHtoD_v2, ID_cuMemcpyHtoDAsync_v2, ID_cuMemcpyDtoHAsync_v2, ID_cuMemcpyDtoDAsync_v2, ID_cuMemcpyPeer, ID_cuMemcpyPeerAsync, ID_cuMemcpy2D_v2, ID_cuMemcpy2DUnaligned_v2, ID_cuMemcpy3D_v2, ID_cuMemcpy2DAsync, ID_cuMemcpy3DAsync, ID_cuMemcpy3DPeerAsync, ID_cuMemcpy2DAsync_v2, ID_cuMemcpy3DAsync_v2, ID_cuMemcpy2D, ID_cuMemcpy2DUnaligned, ID_cuMemcpy3D, ID_cuMemcpy3DPeer};

// Transfers that are not captured
#define UNSUPPORTED_TRANSFERS {ID_cuMemcpyAtoA, ID_cuMemcpyPeer, ID_cuMemcpyPeerAsync, ID_cuMemcpy2D_v2, ID_cuMemcpy2DUnaligned_v2, ID_cuMemcpy3D_v2, ID_cuMemcpy2DAsync, ID_cuMemcpy3DAsync, ID_cuMemcpy3DPeerAsync, ID_cuMemcpy2DAsync_v2, ID_cuMemcpy3DAsync_v2, ID_cuMemcpy2D, ID_cuMemcpy2DUnaligned, ID_cuMemcpy3D, ID_cuMemcpy3DPeer};

// Standard copies in the form of dst, src, count...
#define STANDARD_COPIES {ID_cuMemcpy, ID_cuMemcpyHtoD, ID_cuMemcpyDtoH, ID_cuMemcpyDtoD, ID_cuMemcpyDtoH_v2, ID_cuMemcpyDtoD_v2, ID_cuMemcpyAsync, ID_cuMemcpyHtoDAsync, ID_cuMemcpyDtoHAsync, ID_cuMemcpyDtoDAsync, ID_cuMemcpyHtoD_v2, ID_cuMemcpyHtoDAsync_v2, ID_cuMemcpyDtoHAsync_v2, ID_cuMemcpyDtoDAsync_v2};

// Array copies which must be handled in a special way...
#define ARRAY_COPIES {ID_cuMemcpyAtoH, ID_cuMemcpyAtoD_v2, ID_cuMemcpyAtoHAsync_v2, ID_cuMemcpyAtoH_v2, ID_cuMemcpyAtoA_v2, ID_cuMemcpyAtoD, ID_cuMemcpyAtoHAsync, ID_cuMemcpyDtoA, ID_cuMemcpyDtoA_v2, ID_cuMemcpyHtoA_v2, ID_cuMemcpyHtoA, ID_cuMemcpyHtoAAsync, ID_cuMemcpyHtoAAsync_v2};


extern std::set<CallID> * TransferCallIDs;
extern std::set<CallID> * StandardCopies;
extern std::set<CallID> * ArrayCopies;
extern std::set<CallID> * UnsupportedCopies;




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
