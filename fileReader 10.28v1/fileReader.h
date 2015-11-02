#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef FILEREADER_H_
#define FILEREADER_H_
class FileReader {
private:
	string file_name;
	map<string,int> index;
	map<string,string> data[4];

public:
	FileReader(string file_name="ini"); //open file "ini"
	bool ReadFile();
	void GetConfigInfo(string index, string name, string& info);
	void Split(string src, string separator, vector<string>& dest);
};
#endif