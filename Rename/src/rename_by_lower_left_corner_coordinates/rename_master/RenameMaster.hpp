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

		// 前四位，前三位，y, x, 2556.0-560.0
		int RenameByLowerLeftCornerCoordinate2(const std::string & directory, int boundary);

	protected:
		void init_defualt_value();

		bool img_ext_satisfied( const std::string & ext );

	protected:
		std::vector<std::string> _expected_img_exts;

	};
}

