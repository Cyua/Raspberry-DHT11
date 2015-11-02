#include <iostream>
#include "fileReader.h"
using namespace std;
int main(void)
{
	FileReader obj;
	obj.ReadFile();
	string index="",name="",info="";
	while(true){
		cout<<"Input the index : ";
		cin>>index;
		cout<<"Input the name: ";
		cin>>name;
		obj.GetConfigInfo(index, name, info);
		cout<<info<<endl;
	}
	return 0;
}