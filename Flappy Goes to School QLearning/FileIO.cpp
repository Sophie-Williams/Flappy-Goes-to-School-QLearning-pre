#include "FileIO.h"



void FileIO::saveImage(Mat image, string path, string fileName)
{
	string file = path + fileName + ".jpg";
	imwrite(file, image);
}

Mat FileIO::getImage(string path, string fileName)
{
	string file = path + fileName + ".jpg";
	return imread(file);
}

FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}
