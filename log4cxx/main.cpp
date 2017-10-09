/*************************************************************************
    > File Name: main.cpp
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月26日 星期一 19时23分36秒
 ************************************************************************/
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include<iostream>
using namespace std;

int main(){
	log4cxx::PropertyConfigurator::configureAndWatch("log4cxx.properties");
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("lib"));
	LOG4CXX_DEBUG(logger,"this is log4cxx test");
	return 0;
}


//#include "log4cxx/logger.h"
//#include "log4cxx/basicconfigurator.h"
//#include "log4cxx/propertyconfigurator.h"
//#include "log4cxx/helpers/exception.h"
//#include "log4cxx/xml/domconfigurator.h" 
//
//using namespace std;
//using namespace log4cxx;
//using namespace log4cxx::helpers;
//using namespace log4cxx::xml;
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//    DOMConfigurator.configure("E:/study/log4j/log4j.xml");//加载.xml文件
//    Logger log=Logger.getLogger("system");
//    log.info("测试");
//}
