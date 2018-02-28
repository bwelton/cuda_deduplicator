#include "SymbolLookup.h"

SymbolLookup::SymbolLookup(std::string filename) {
	bool err = Symtab::openFile(_obj, filename);
	assert(err != true);
}

SymbolLookup::~SymbolLookup() {
	Symtab::closeSymtab(_obj);
}

bool SymbolLookup::GetInfoAtLocation(uint64_t offset, std::pair<std::string, LineInfo> & lines) {
	std::vector<Symbol *> ret = _obj->findSymbolByOffset(offset);
	if (ret.size() == 0) {
		return false;
	}
	if (ret[0]->isFunction() == false)
		return false;
	lines.first = ret[0]->getPrettyName();
	std::vector<Dyninst::SymtabAPI::Statement::Ptr> lineNumbers;
	_obj->getSourceLines(lineNumbers, offset);
	if (lineNumbers.size() > 0) {
		lines.second.filename = lineNumbers[0]->getFile();
		lines.second.lineNum = lineNumbers[0]->getLine();
	}
	return true;
}