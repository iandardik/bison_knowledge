#ifndef _H_DATABASE
#define _H_DATABASE

#include <string>
#include <map>

typedef std::map< std::string, std::string > map_t;

class Database {
public:
	void AddNoun(const std::string& n);
	void AddNoun(const std::string& n, const std::string& v);
	bool LookUp(const std::string& n, const std::string& v);

private:
	map_t m_db;
};

#endif /* _H_DATABASE */
