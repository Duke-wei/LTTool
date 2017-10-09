/*************************************************************************
    > File Name: mylog4cxx.h
    > Author: Duke-wei
    > Mail: 13540639584@163.com 
    > Created Time: 2016年12月27日 星期二 14时00分46秒
 ************************************************************************/

#ifndef _MYLOG4CXX_H_
#define _MYLOG4CXX_H_

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <string>
using namespace std;
using namespace log4cxx;
class mylog{
	public:
		mylog();
		~mylog();
		void mydebug(std::string m);
		log4cxx::LoggerPtr logger;
};
#endif
