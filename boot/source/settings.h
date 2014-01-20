#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>

class Settings {

private:
	Settings();
	~Settings();
	/*mem table object*/

public:
	int loadIni(std::string f);
	int saveIni(std::string f);
	std::string getValue(std::string i);
	std::string setValue(std::string i, std::string v);

protected:
	
};

#endif