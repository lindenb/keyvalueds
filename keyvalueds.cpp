#include "keyvalueds.hpp"


using namespace std;


AbstractApplication::AbstractApplication(AbstractApplication* p):parent(p)
	{
	ADD_OPTION("help",no_argument,0,'h',"Get Help. This screen");
	}

AbstractApplication::~AbstractApplication()
	{
	}
	
void AbstractApplication::usage(std::ostream& out)
	{
	
	}


AbstractOneDatabaseApplication::AbstractOneDatabaseApplication(AbstractApplication* parent):AbstractApplication(parent)
	{
	
	}

AbstractOneDatabaseApplication::~AbstractOneDatabaseApplication()
	{
	closeDatabase();
	}

int AbstractOneDatabaseApplication::openDatabase()
	{
	int ret;
	if( dbp !=NULL) return 0;

	if ((ret = db_create(&dbp, NULL, 0)) != 0)
		{
		cerr <<  "db_create:" << db_strerror(ret) << endl;
		return -1;
		}
	if ((ret = dbp->open(dbp,  NULL, db_filename.c_str(), NULL, DB_BTREE, DB_CREATE, 0664)) != 0) {
		dbp->err(dbp, ret, "%s", db_filename.c_str());
		return -1;
		}
	return 0;
	}

int AbstractOneDatabaseApplication::closeDatabase()
	{
	int ret;
	if( dbp ==NULL) return 0;

	ret = dbp->close(dbp, 0);
	dbp=NULL;
	return ret;
	}

PutApplication::PutApplication(Main* owner):AbstractOneDatabaseApplication(owner)
	{
	
	}

PutApplication::~PutApplication()
	{
	}

int PutApplication::instanceMain(int argc,char** argv)
	{
	DBT key, data;
	openDatabase();
	memset(&key, 0, sizeof(key));
	memset(&data, 0, sizeof(data));
	dbp->put(dbp, NULL, &key, &data, 0);
	closeDatabase();
	return 0;
	}

Main::Main():AbstractApplication(0)
	{
	}



Main::~Main()
	{
	}




int Main::instanceMain(int argc,char** argv)
	{
	if(optind==argc)
		{
		usage(cerr);
		return EXIT_FAILURE;
		}
	if(strcmp(argv[optind],"put")==0)
		{
		PutApplication sub(this);
		return sub.instanceMain(argc-optind,&argv[optind]);
		}
	else
		{
		cerr << "unknown sub-program "<< argv[optind] << endl;
		usage(cerr);
		return EXIT_FAILURE;
		}
	return EXIT_SUCCESS;
	}
	
int main(int argc,char** argv)
	{
	Main app;
	int ret = app.instanceMain(argc,argv);
	return ret;
	}

