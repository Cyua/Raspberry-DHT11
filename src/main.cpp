#include <iostream>
#include "dht11.h"
#include <fstream>
int main(void)
{
	std::ofstream file("out");
	DHT11 sensor;
	for(long i=0;i<100000000;i++){
		data the_data=sensor.dht11_read();
		file<<"T:"<<the_data.temperature<<" H:"<<the_data.humidity<<std::endl;
		std::cout<<i<<"- T:"<<the_data.temperature<<" H:"<<the_data.humidity<<std::endl;
	}
	file.close();
	return 0;
}
