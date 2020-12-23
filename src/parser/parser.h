#ifndef GALAXYCMT_PARSER_H
#define GALAXYCMT_PARSER_H

#include <string>
#include <memory>

namespace galaxycmt
{

class IWalker;

class IParser
{
public:
	IParser(const std::shared_ptr<IWalker>& walker = nullptr)
		: walker_(walker){}
	~IParser() = default;

	virtual bool Parse() = 0;
	virtual bool Parse(const std::string& pathToFile) = 0;

protected:
	std::shared_ptr<IWalker> walker_;
};

} // galaxycmt

#endif //GALAXYCMT_PARSER_H
