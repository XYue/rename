#pragma once

#include <vector>
#include <string>

namespace rename_util
{
	class RenameMaster
	{

	public:
		RenameMaster();
		~RenameMaster(){};

		int RenameByLowerLeftCornerCoordinate(const std::string & directory);

	protected:
		void init_defualt_value();

		bool img_ext_satisfied( const std::string & ext );

	protected:
		std::vector<std::string> _expected_img_exts;

	};
}

