#include ProcessControl.h

ProcessController::ProcessController(boost::program_options::variables_map vm) :
	_vm(vm), _launched(false) {
}

BPatch_addressSpace * ProcessController::LaunchProcess() {
	BPatch_addressSpace * handle = NULL;
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();

	// Setup arguments
	char ** argv = (char**)malloc(progName.size() * sizeof(char *));
	for (int i = 0; i < progName.size(); i++) 
		argv[i] = strdup(progName[i].c_str());

	// Create the bpatch process
	handle = bpatch.processCreate(argv[0],argv);
	assert(handle != NULL);

	// Free temporary argv
	for (int i = 0; i < progName.size(); i++)
		free(argv[i]);
	free(argv);

	_addrSpace = handle;
	_launched = true;
	return handle;
}

BPatch * ProcessController::GetBPatch() {
	return &bpatch;
}