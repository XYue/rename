#include <iostream>

#include <gflags/gflags.h>

#include "rename_master/RenameMaster.hpp"

DEFINE_string(dir,     "",       "* image directory");
DEFINE_int32(b, 0,      "(optional) boundary in pixel");

void main(int argc, char ** argv)
{
	google::ParseCommandLineFlags(&argc, &argv, true);

	do 
	{	
		if (FLAGS_dir.empty())
		{
			std::cout<<"error: invalid directory"<<std::endl;
			break;
		}

		if (FLAGS_b < 0)
		{
			std::cout<<"error: invalid boundary"<<std::endl;
			break;
		}

		rename_util::RenameMaster re_master;
		if(re_master.RenameByLowerLeftCornerCoordinate2(FLAGS_dir, FLAGS_b))
		{
			std::cout<<"Error: RenameByLowerLeftCornerCoordinate failed."<<std::endl;
			break;
		}

	} while (0);

	google::ShutDownCommandLineFlags();

	std::cout<<"rename done."<<std::endl;
}