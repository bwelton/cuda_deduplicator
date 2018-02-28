#include "SymbolLookup.h"
#define DEBUG_SYMBOLLOOKUP 1
SymbolLookup::SymbolLookup(std::string filename) {
	bool err = Symtab::openFile(_obj, filename);
	if (err == false){
		std::cerr << "Could not open file - " << filename << std::endl;
		_obj = NULL;
	}
	//assert(err != false);
}

SymbolLookup::~SymbolLookup() {
	if (_obj != NULL)
		Symtab::closeSymtab(_obj);
}

bool SymbolLookup::GetInfoAtLocation(uint64_t offset, std::pair<std::string, LineInfo> & lines) {
	if (_obj == NULL) {
		LineInfo tmp;
		tmp.filename = std::string("UNKNOWN");
		tmp.lineNum = 0;
		lines = std::make_pair(std::string("UNKNOWN"), tmp);
		return false;
	}
	std::vector<Symbol *> ret = _obj->findSymbolByOffset(offset);
	if (ret.size() == 0) {
#ifdef DEBUG_SYMBOLLOOKUP
		std::cerr << "Did not return a symbol" << std::cerr;
#endif
		return false;
	}
	if (ret[0]->isFunction() == false){
		return false;
	}
	lines.first = ret[0]->getPrettyName();
	std::vector<Dyninst::SymtabAPI::Statement::Ptr> lineNumbers;
	_obj->getSourceLines(lineNumbers, offset);
	if (lineNumbers.size() > 0) {
		lines.second.filename = lineNumbers[0]->getFile();
		lines.second.lineNum = lineNumbers[0]->getLine();
	}
	return true;
}