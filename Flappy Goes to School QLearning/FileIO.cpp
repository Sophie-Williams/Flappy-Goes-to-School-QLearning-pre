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

void FileIO::saveValue(int value, string path, string fileName)
{
	ofstream file(path + fileName, ios::app);
	file << value << " ";
	file.close();
}

FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}
