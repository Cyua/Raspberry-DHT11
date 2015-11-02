#include "fileReader.h"
#include <iostream>
#include <string>
#include <map>
FileReader::FileReader(string name):file_name(name)
{
}

bool FileReader::ReadFile()
{
	ifstream file(file_name);
	vector<string> dest;
	int count=-1;
	if(!file.is_open()){
		cout<<"Can't open file "<<file_name<<" !"<<endl;
		return false;
	}
	else{
		cout<<"Open the file successfully!"<<endl;
	}
	while(!file.eof())
	{
		string raw;
		file>>raw;
		if(raw.substr(0,1)=="["){
			count++;
			Split(raw.substr(1),"]",dest);
			index[dest[0]]=count;
			continue;
		}
		else{
			Split(raw,"=",dest);
			data[count][dest[0]]=dest[1];
		}
	}
	file.close();
	return true;
}

void FileReader::Split(string src, string separator, vector<string>& dest)
{
	dest.clear();
    string str = src;
    string substring;
    string::size_type start = 0, index;

    do
    {
        index = str.find_first_of(separator,start);
        if (index != string::npos)
        {    
            substring = str.substr(start,index-start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == string::npos) return;
        }
    }while(index != string::npos);
    
    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
}

void FileReader::GetConfigInfo(string i, string name, string& info){
	info = data[index[i]][name];
}