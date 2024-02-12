#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <miniz.h>
#include <iostream>
using std::filesystem::directory_iterator;

class Backup {
public:
	Backup(const std::string& players, const std::string& worlds);
	~Backup() { remove(m_last_backup.c_str()), m_files.clear(); }
	void Zip();
	void create_name();
	std::string get_backup() { return m_backup; }
	std::string get_files();
private:
	std::vector<std::string> m_files;
	std::string m_last_backup;
	std::string m_backup;
	size_t m_worlds = 0, m_players = 0;
};