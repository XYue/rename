#include <iostream>

#include "rename_master/RenameMaster.hpp"

void main(int argc, char ** argv)
{
	do 
	{
		if (argc != 2)
		{
			std::cout<<"Error: Invalid input."<<std::endl;
			std::cout<<"usage: exe_name directory"<<std::endl;
			break;
		}

		rename_util::RenameMaster re_master;
		if(re_master.RenameByLowerLeftCornerCoordinate(argv[1]))
		{
			std::cout<<"Error: RenameByLowerLeftCornerCoordinate failed."<<std::endl;
			break;
		}

	} while (0);

	std::cout<<"rename done."<<std::endl;
}