#pragma once
#include "Domain.h"
#include "FileRepository.h"
#include <string>

class HtmlRepository : public FileRepository
{
public:
	void  setSaveListPath(std::string path) override;
	void setSaveList(std::string type) override;
	std::vector<TElems> getfromfile() const override;
	void writeTofile(std::vector<TElems> whattowrite) override;
	std::string StatuetoHTML(TElems statue) const;
	TElems HTMLtoStatue(std::string line) const;
	void openInApp() override;
	Type type() { return HtmlRepo; }
};

