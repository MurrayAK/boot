#include "settings.h"

Settings::Settings() {  }

Settings::~Settings() {  }

stringmap &Settings::operator[](std::string table)
{
	return database[table];
}

//opens file with name filename
//function tests operation and outputs filestream
//
std::ifstream openFile(std::string filename) 
{
	std::ifstream instream;
	instream.open(filename, std::ifstream::in);

	if (instream.fail()) std::cerr << "File Error: " << strerror(errno) << std::endl;
	
	if (instream.is_open()) 
		std::cout << "File "+filename+" is open\n";

	return instream;
}

//indentifies if line refers to a section or key value pair or newline
//function receives line and outputs 1 or 2 or 0 respectively
// 
int Settings::checkLine(std::string line) 
{
	std::regex a ("^\\[[a-zA-Z]+\\.?[a-zA-Z]+\\]+");
	std::regex b (".*=.*");

	if (std::regex_match(line, a)) return 1;

	if (std::regex_match(line, b)) return 2;

	return 0;
}

//gets ini filename
//function receives filename and outputs file contents to hashtable
//
std::vector<std::string> Settings::splitLine(std::string lineTosplit) 
{
	char *s = new char[lineTosplit.length() + 1];
	std::strcpy(s, lineTosplit.c_str());
	std::vector<std::string> auxVec;
	char *p = std::strtok(s, "=");

	while (p != 0) {
		auxVec.push_back(p);
		p = strtok(NULL, "=");
	}
	//std::cout<<auxVec[0]<<"here\n";
	//std::cout<<auxVec[1]<<"datavalue\n";

	delete[] s;
	
	return auxVec;
}

int Settings::LoadIni(std::string filename) 
{
	std::ifstream instream = openFile(filename);
	std::string line;
	std::map< std::string, std::string > section;
	std::vector<std::string> auxVec;
	std::pair< std::string, std::string> sectionEntry;
	stringmap table;

	if (instream == NULL) return 1;
	
	while (std::getline(instream, line)) 
	{
		switch (checkLine(line)) 
		{
			case 1:
				std::cout << "Section: "+line+'\n';
				database[line] = table;
				break;

			case 2:
				//std::cout<<"Key value: "+line+'\n';
				auxVec = splitLine(line);
				section[auxVec[0]] = auxVec[1];

				table[auxVec[0]] = auxVec[1];

				std::cout << auxVec[0] << '=' << section[auxVec[0]] << '\n';
				break;
 
			default: 
				table.clear();
				std::cout << "finished section?\n";
				break;
		}
	}

	instream.close();

	return 0;
}

//gets section from ini file with filename
//function receives filename and section to look in file for and outputs hashtable(section)
//
int Settings::LoadIni(std::string filename, std::string section) 
{
	std::ifstream instream = openFile(filename);
	std::string line;
 
	if (instream != NULL) 
	{
		while (std::getline(instream, line)) 
			std::cout<<line+'\n';
	 }
	
	instream.close();
	
	return 1;
}

int Settings::SaveIni(std::string filename) {

	//loop through each section and through items in memory
	//write section > item > value to file

	return 0;
}