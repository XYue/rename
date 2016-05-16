#include "rename_master/RenameMaster.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include <boost/filesystem/operations.hpp>
#include <gdal_priv.h>

namespace rename_util
{


	RenameMaster::RenameMaster()
	{
		init_defualt_value();
	}

	void RenameMaster::init_defualt_value()
	{
		_expected_img_exts.push_back("jpg");
		_expected_img_exts.push_back("jpeg");
		_expected_img_exts.push_back("tif");
		_expected_img_exts.push_back("tiff");
		_expected_img_exts.push_back("img");
	}

	bool RenameMaster::img_ext_satisfied( const std::string & ext )
	{
		std::string suffix = ext;
		std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
		int num_expected_ext = _expected_img_exts.size();
		for (int i_e = 0; i_e < num_expected_ext; ++i_e)
		{
			if (!suffix.compare(_expected_img_exts[i_e]))
				return true;
		}

		return false;
	}

	int RenameMaster::RenameByLowerLeftCornerCoordinate( const std::string & directory )
	{
		int ret = -1;

		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
		GDALAllRegister();

		do 
		{
			boost::filesystem::directory_iterator end_iter;
			for (boost::filesystem::directory_iterator dir_iter(directory);
				dir_iter != end_iter; ++dir_iter)
			{
				if (boost::filesystem::is_regular_file(dir_iter->status()) &&
					img_ext_satisfied(dir_iter->path().extension().string().substr(1)))
				{
					//img_files.push_back(dir_iter->path().string());
					std::string img_filename = dir_iter->path().string();

					GDALDataset * ds = 
						(GDALDataset *)GDALOpen(img_filename.c_str(), GA_ReadOnly);
					if(ds == NULL){
						std::cout<<"Error: Can not read "<<img_filename<<std::endl;
						continue;
					} else {
						// read the lower left corner
						double	geo_transform[6];
						ds->GetGeoTransform(geo_transform);
						int height = ds->GetRasterYSize();
						GDALClose(ds);

						double lower_left_x = geo_transform[0] + geo_transform[2] * height;
						double lower_left_y = geo_transform[3] + geo_transform[5] * height;

						std::cout<<std::setprecision(10)<<lower_left_x<<" "<<lower_left_y<<std::endl;

						// construct filename
						std::stringstream sstr;
						sstr << std::setiosflags(std::ios::fixed)<<std::setprecision(1)
							<<lower_left_x<<"-"<<lower_left_y;
						std::string new_filename = directory+"\\"+sstr.str()+dir_iter->path().extension().string();
						std::cout<<new_filename<<std::endl;

						if (rename(img_filename.c_str(), new_filename.c_str()))
						{
							std::cout<<"rename failed. "<<img_filename<<"-->"<<new_filename<<std::endl;
							continue;
						}

						std::cout<<std::endl;
					}			
				}
			}

			ret = 0;
		} while (0);

		GDALDestroyDriverManager();
		CPLFreeConfig();

		return ret;
	}

	int RenameMaster::RenameByLowerLeftCornerCoordinate2( 
		const std::string & directory, int boundary )
	{
		int ret = -1;

		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
		GDALAllRegister();

		do 
		{
			boost::filesystem::directory_iterator end_iter;
			for (boost::filesystem::directory_iterator dir_iter(directory);
				dir_iter != end_iter; ++dir_iter)
			{
				if (boost::filesystem::is_regular_file(dir_iter->status()) &&
					img_ext_satisfied(dir_iter->path().extension().string().substr(1)))
				{
					//img_files.push_back(dir_iter->path().string());
					std::string img_filename = dir_iter->path().string();

					GDALDataset * ds = 
						(GDALDataset *)GDALOpen(img_filename.c_str(), GA_ReadOnly);
					if(ds == NULL){
						std::cout<<"Error: Can not read "<<img_filename<<std::endl;
						continue;
					} else {
						// read the lower left corner
						double	geo_transform[6];
						ds->GetGeoTransform(geo_transform);
						int height = ds->GetRasterYSize();
						GDALClose(ds);


						double lower_left_x = geo_transform[0] + geo_transform[2] * height + boundary * geo_transform[1];
						double lower_left_y = geo_transform[3] + geo_transform[5] * height - boundary * geo_transform[5];
						lower_left_x /= 1000.;
						lower_left_y /= 1000.;

						//std::cout<<std::setprecision(10)<<lower_left_x<<" "<<lower_left_y<<std::endl;

						// construct filename
						std::stringstream sstr;
						sstr << std::setiosflags(std::ios::fixed)<<std::setprecision(1)
							<<lower_left_y<<"-"<<lower_left_x;
						std::string new_filename = directory+"\\"+sstr.str()+dir_iter->path().extension().string();
						std::cout<<new_filename<<std::endl;

						if (rename(img_filename.c_str(), new_filename.c_str()))
						{
							std::cout<<"rename failed. "<<img_filename<<"-->"<<new_filename<<std::endl;
							continue;
						}

						std::cout<<std::endl;
					}			
				}
			}

			ret = 0;
		} while (0);

		GDALDestroyDriverManager();
		CPLFreeConfig();

		return ret;
	}

}
