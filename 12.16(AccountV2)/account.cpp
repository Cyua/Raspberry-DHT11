#include "account.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <map>
using namespace std;

Account::Account(){
	accountList.clear();
	fileName="";
	filePath="";
}

Account::~Account(){
	if(fileName!="")
		writeFile();
}

bool Account::add(string id, string passwd){
	if(accountList.count(id)>0)
		return false;
	accountList[id]=passwd;
	return true;
}

bool Account::drop(string id){
	if(accountList.count(id)<=0)
		return false;
	accountList.erase(id);
	return true;
}

bool Account::check(string id, string passwd){
	if(accountList.count(id)<=0)
		return false;
	if(accountList[id]!=passwd)
		return false;
	return true;
}

bool Account::modify(string id, string passwd){
	if(accountList.count(id)<=0)
		return false;
	accountList[id]=passwd;
	return true;
}

bool Account::loadRoot(string fileName, string filePath){
	ifstream fin(fileName.c_str());
	if(!fin.is_open()){
		cout<<"The file "<<fileName<<" does not exist!"<<endl;
		return false;
	}
	getline(fin,rootPasswd);
	if(rootPasswd=="")
		return false;
	fin.close();
	return true;
}

bool Account::readFile(string file, string filePath){
	fileName = filePath + file;
	ifstream fin(fileName.c_str());
	if(!fin.is_open()){
		// cout<<"The file "<<fileName<<" does not exist!"<<endl;
		fin.close();
		return false;
	}
	vector<string> data;
	while(!fin.eof()){
		string raw;
		getline(fin,raw);
		if(raw=="")
			break;
		split(raw, " ", data);
		string id = decode(data[0].c_str(), data[0].size());
		string passwd = decode(data[1].c_str(), data[1].size());
		accountList[id]=passwd;
	}	
	fin.close();
	return true;
}

bool Account::writeFile(){
	ofstream fout(fileName.c_str());
	if(!fout.is_open()){
		cout<<"Can't open the file: "<<fileName<<" !"<<endl;
		return false;
	}
	map<string,string>::iterator it;
	for(it = accountList.begin(); it!=accountList.end(); ++it){
		string id = encode(it->first.c_str(), it->first.size());
		string passwd = encode(it->second.c_str(),it->second.size());
		fout<<id<<" "<<passwd<<endl;
	}
	fout.close();
	return true;
}

string Account::encode(const char* src, int size){
	char* temp = new char[size+1];
	memset(temp, 0, sizeof(char)*(size+1));
	
	for(int i = 0; i < size; i++){
		char x;
		if(src[i]>='a' && src[i]<='z'){
			int d = (src[i]-'a'+3) % 26;
			x = 'a'+d;
			temp[i] = x;
		}
		else if(src[i]>='A' && src[i]<='Z'){
			int d = (src[i]-'A'+4) % 26;
			x = 'A'+d;
			temp[i] = x;
		}
		else if(src[i]>='1' && src[i]<='9'){
			int d = (src[i]-'1'+5) % 10;
			x = '1'+d;
			temp[i] = x;
		}
		else
			temp[i] = src[i];

	}
	string s(temp);
	delete[] temp;
	return s;
}

string Account::decode(const char* src, int size){
	char* temp = new char[size+1];
	memset(temp,0,sizeof(char)*(size+1));
	for(int i = 0; i < size; i++){
		char x;
		if(src[i]>='a' && src[i]<='z'){
			int d = (src[i]-'a'+23) % 26;
			x = 'a'+d;
			temp[i] = x;
			continue;
		}
		else if(src[i]>='A' && src[i]<='Z'){
			int d = (src[i]-'A'+22) % 26;
			x = 'A'+d;
			temp[i] = x;
			continue;
		}
		else if(src[i]>='1' && src[i]<='9'){
			int d = (src[i]-'1'+5) % 10;
			x = '1'+d;
			temp[i] = x;
			continue;
		}
		else
			temp[i] = src[i];
	}
	string s(temp);
	delete[] temp;
	return s;
}
void Account::split(string s, string delim,vector<string>& ret)
{
	ret.clear();
	size_t last = 0;
	size_t index=s.find_first_of(delim,last);
	while (index!=std::string::npos)
	{
		ret.push_back(s.substr(last,index-last));
		last=index+1;
		index=s.find_first_of(delim,last);
	}
	if (index-last>0)
	{
		ret.push_back(s.substr(last,index-last));
	}
}

void Account::listAllUser(){
	map<string,string>::iterator it;
	for(it = accountList.begin(); it!=accountList.end(); ++it){
		cout<<it->first<<endl;
	}
}