typedef std::map<uint64_t, StackRecord> StackRecMap;


class ReadStackRecs {
public:
	ReadStackKeys(std::string key, std::string bin); 	
	void GetStackRecords(StackRecMap & ret);
	void ExtractLineInfo(StackRecMap & rec);

private:
	std::string _key;
	std::string _bin;
};

ReadStackKeys::ReadStackKeys(std::string key, std::string bin) : _key(key), _bin(bin) {}


void ReadStackKeys::ExtractLineInfo(StackRecMap & rec) {
	SymbolMap symbolInfo;
	// Open all symtabs for functions found on the stack. 
	for (auto i : rec) {
		std::vector<std::string> lnames = i.second.GetLibNames();
		for (auto z : lnames){
			if (symbolInfo.find(z) == symbolInfo.end())
				symbolInfo[z] = std::shared_ptr<SymbolLookup>(new SymbolLookup(z));
		}	
	}
	for (auto & i : rec)
		i.second.GetStackSymbols(symbolInfo);
}

void ReadStackKeys::

void ReadStackKeys::GetStackRecords(StackRecMap & ret, std::function<void()>) {
	std::cerr << "[ReadStackKeys::GetStackRecords] Reading stack file: " << _bin << std::endl;
	std::cerr << "[ReadStackKeys::GetStackRecords] Reading key file: " << _key << std::endl;

	FILE * inFile = fopen(_bin.c_str(), "rb");
	assert(inFile != NULL);

	FILE * keyFile = fopen(_key.c_str(), "rb");
	assert(keyFile != NULL);

	StackKeyReader reader(keyFile);
	std::map<uint64_t, std::vector<StackPoint> > ret = reader.ReadStacks();

	for (auto & i : ret)
		ret[i.first] = StackRecord(i.first, i.second);

	ExtractLineInfo(ret);

	for (auto i : ret) {
		std::cerr << "Adding " << i.second.GetFirstCudaCall().funcName << " with hash id " << i.first << std::endl;
		_callMapper.InsertStackID(i.second.GetFirstCudaCall().funcName, i.first);
	}


	fseek(inFile, 0, SEEK_END);
	uint64_t elementCount = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);
	elementCount = elementCount / 8;
	// Typically have ~7 calls to low level synchronization
	_orderingInfo.reserve(elementCount / 7);

	std::vector<StackPoint> e;
	// Insert an empty element at 0 for unidentified synchronizations.
	ret[0] = StackRecord(0, e);
	uint64_t hash = 0;
	uint64_t pos = 0;
	uint64_t syncCount = 0;
	bool start = true;
	bool found = false;
	while (fread(&hash, 1, sizeof(uint64_t), inFile) > 0){
		syncCount++;
		found = false;
		//std::cerr << "My Hash: " << hash << std::endl;
		if (start != true) {
			if (_orderingInfo.back().stackId == hash){
				_orderingInfo.back().count++;
				found = true;
			}
		}
		if (start == true || found == false){
			TF_SyncRecord tmp;
			tmp.stackId = hash;
			tmp.dynId = _callMapper.StackIDToGeneral(hash);
			tmp.count = 1;
			_orderingInfo.push_back(tmp);
			start = false;
		}
		if (feof(inFile))
			break;
	}
	_capturedSyncs = syncCount;
	fclose(inFile);


}