class CUPTIEventHandler : public InstrumentBase {
private: 


public: 
	void bufferRequested(uint8_t **buffer, size_t *size, size_t *maxNumRecords);
	void bufferCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize);
	