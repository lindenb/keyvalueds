#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP

#include <db.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <unistd.h>
#include <cerrno>
#include <getopt.h>
#include <sys/types.h>



struct option_desc:public option
	{
	const char* desc;
	};

#define ADD_OPTION(NAME,HAS_ARG,FLAG,VAL,DESC) \
	do{struct option_desc optx; optx.name=NAME; optx.has_arg=HAS_ARG;optx.flag=FLAG;optx.val=VAL;optx.desc=DESC; this->options.push_back(optx);} while(0)


class AbstractApplication
	{
	public:
		std::vector<option_desc> options;
		AbstractApplication* parent;
		AbstractApplication(AbstractApplication* parent);
		virtual void usage(std::ostream& out);
		virtual ~AbstractApplication();
		virtual int instanceMain(int,char**)=0;
	};



class Main:public AbstractApplication
	{
	public:
		Main();
		virtual ~Main();
		virtual int instanceMain(int,char**);
	};

class AbstractOneDatabaseApplication:AbstractApplication
	{
	protected:
		DB *dbp;
		std::string db_filename;
	public:
		AbstractOneDatabaseApplication(AbstractApplication* parent);
		virtual ~AbstractOneDatabaseApplication();
		virtual int instanceMain(int,char**)=0;
		virtual int openDatabase();
		virtual int closeDatabase();
	};

class PutApplication: AbstractOneDatabaseApplication
	{
	public:
		PutApplication(Main* owner);
		virtual ~PutApplication();
		virtual int instanceMain(int,char**);
	};


#endif

