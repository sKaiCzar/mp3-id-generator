
#include <iostream>
#include <fstream>  
#include <string> 
using namespace std;
//Create a Structure to store MP3s tagged info
struct MP3Tag
{
	string Artist;
	string Title;
	string Album;
	string Year;
	string Comment;
};

int getsize(FILE *file)
{
	//returns the size of the file as an int
	int loc = ftell(file);
	fseek(file,0,SEEK_END);
	int size = ftell(file);
	fseek(file, loc, SEEK_SET);
	return size;
}

bool checkMP3(string filename)
{
	//Checks if the file extension is mp3
	int filetype = filename.length() - 4;
	string filetipe = filename.substr(filetype, 4);
	if (filetipe == ".mp3")
	{
		return true;
	}
	else
	{
		return false;
	}
}

string Header(FILE *file, int readloc)
{
	char magic[4];
	fseek(file , readloc, SEEK_SET);
	fread(magic, 1, 4, file);
	string str(magic);
	string mag = str.substr(0,3);
	return mag;
}
string Year(FILE *file, int readloc)
{
	//Reads Year Of Track...4bytes long
	char magic[4];
	fseek(file , readloc, SEEK_SET);
	fread(magic, 1, 4, file);
	string str(magic);
	return str;
}
string ReadThirty(FILE *file, int readloc)
{
	//Used to read Title, Artist, Album, Comment
	//Each is 30 bytes long
	char magic[30];
	fseek(file , readloc, SEEK_SET);
	fread(magic, 1, 30, file);
	string str(magic);
	return str;
}
void ReadMP3(FILE *file, MP3Tag tag)
{
	//The following code reads the information for x bytes and then increases the readlocation x spaces
	//so the next information can be read
	int readloc = getsize(file)-125;
	tag.Title = ReadThirty(file, readloc);
	readloc+=30;
	tag.Artist = ReadThirty(file, readloc);
	readloc+=30;
	tag.Album = ReadThirty(file, readloc);
	readloc+=30;
	tag.Year = Year(file, readloc);
	readloc+=4;
	tag.Comment = ReadThirty(file, readloc);
}

