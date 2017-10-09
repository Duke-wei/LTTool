/*************************************************************************
    > File Name: mylog4cxx.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 14时07分10秒
 ************************************************************************/
#include "mylog4cxx.h"
#include<iostream>
using namespace std;
mylog::mylog(){
	log4cxx::PropertyConfigurator::configureAndWatch("log4cxx.properties");
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("lib"));
}
mylog::~mylog(){

}
void mylog::mydebug(std::string m){
	LOG4CXX_DEBUG(logger,m);
}
