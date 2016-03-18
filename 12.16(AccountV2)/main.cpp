#include "account.h"
#include <iostream>
using namespace std;

// int main(void){
// 	Account manager;
// 	manager.loadRoot("root");
// 	manager.readFile("accountList");
// 	manager.add("hhhh","111111");
// 	manager.writeFile();
// 	return 0;
// }

int main(int argc, char const *argv[])
{
	if(argc <= 1){
		cout<<"Please enter the command! "<<endl;
		cout<<"For example: -a means add"<<endl;
		return 0;
	}

	string command(argv[1]);
	Account manager;
	

	if(command == "-a"){				//add the account
		if(argc != 4){
			cout<<"The format of the command is wrong!"<<endl;
			cout<<"Try ./account -a username password"<<endl;
			return 0;
		}
		string username(argv[2]);
		string password(argv[3]);
		if(manager.add(username, password)){
			cout<<"Successfully add the account!"<<endl;
		}
		else{
			cout<<"The username is already exist!"<<endl;
		}
	}

	else if(command == "-h"){	//help
		cout<<"***********        ************"<<endl;
		cout<<"Hint: "<<endl;
		cout<<"add an new account:  ./account -a username password"<<endl;
		cout<<"delete an account:   ./account -d username"<<endl;
		cout<<"check the password:  ./account -c username password"<<endl;
		cout<<"modify the password: ./account -m username password"<<endl;
		cout<<"list all the users:  ./account -l"<<endl;
		cout<<"***********        ************"<<endl;
	}

	else if(command == "-l"){	//list all the username
		manager.listAllUser();
		return 0;
	}

	else if(command == "-d"){	//delete the account
		if(argc != 3){
			cout<<"The format of the command is wrong!"<<endl;
			cout<<"Try ./account -d username"<<endl;
			return 0;
		}
		string username(argv[2]);
		if(manager.drop(username)){
			cout<<"Successfully delete the account!"<<endl;
		}
		else{
			cout<<"Doesn't find the account!"<<endl;
		}
	}

	else if(command == "-c"){	//check the account
		if(argc != 4){
			cout<<"The format of the command is wrong!"<<endl;
			cout<<"Try ./account -c username password"<<endl;
			return 0;
		}
		string username(argv[2]);
		string password(argv[3]);
		if(manager.check(username,password)){
			cout<<"Check successfully!"<<endl;
		}
		else{
			cout<<"Doesn't find the account or the password isn't right!"<<endl;
		}
	}

	else if(command == "-m"){	//modify the password
		if(argc != 4){
			cout<<"The format of the command is wrong!"<<endl;
			cout<<"Try ./account -m username password"<<endl;
			return 0;
		}
		string username(argv[2]);
		string password(argv[3]);
		if(manager.modify(username,password)){
			cout<<"Modify the password successfully!"<<endl;
		}
		else{
			cout<<"Can't find the account"<<endl;
		}
	}
	else{
		cout<<"command not found!"<<endl;
		cout<<"Hint: "<<endl;
		cout<<"add an new account:  ./account -a username password"<<endl;
		cout<<"delete an account:   ./account -d username"<<endl;
		cout<<"check the password:  ./account -c username password"<<endl;
		cout<<"modify the password: ./account -m username password"<<endl;
		cout<<"list all the users:  ./account -l"<<endl;
	}
	manager.writeFile();
	return 0;
}