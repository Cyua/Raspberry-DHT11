#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <map>
#include <vector>
using namespace std;
class Account{
private:
	string rootPasswd;
	map<string,string> accountList;
	string fileName;
	string filePath;

public:
	//If the following functions perform correctly, then return true. Otherwise false.
	bool add(string id, string passwd);		//add a new account, id: the account name, passwd: the account password
	bool drop(string id);					//delete an account
	bool check(string id, string passwd);	//check if the password fits the account
	bool modify(string id, string passwd);	//modify an account, passwd: the new account password

	//The following function is for account class itself
	bool loadRoot(string fileName="", string filePath="");	//Load the password of root
	bool readFile(string fileName="", string filePath="");	//Load the account list
	bool writeFile();										//write the data back to the file
 	void split(string s, string delim, vector<string>& ret);
 	string encode(const char* src, int size);
 	string decode(const char* src, int size);
	Account();
	~Account();
};
#endif