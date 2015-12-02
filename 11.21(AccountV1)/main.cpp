#include "account.h"
#include <iostream>
using namespace std;

int main(void){
	Account manager;
	manager.loadRoot("root");
	manager.readFile("accountList");
	manager.add("hhhh","111111");
	manager.writeFile();
	return 0;
}
