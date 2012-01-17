#ifndef _Utility_h_included_
#define _Utility_h_included_



#ifdef WIN32
	#define WIN //Define when compiling on Windows
#else //if defined(__APPLE__) || defined(__APPLE_CC__)
	#define OSX  //Define when compiling on MacOSX or Linux
#endif

#include <time.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <sstream> 

using namespace std;

/* Conveniently makes utility functions available */


class Utility
{
private:
	
public:

	Utility();
	
	string stringOf(int in); //Returns a string of the input integer
	string stringOf(double in); // '' double
	
	string strip(string in, string delim);
	vector<string> split(string in, string delim);
	vector<string> simple_split(string in, string delim);

	string extensionOf(string in); // get the text following the last '.' of a string. return "" if none
	string stripExtension(string in); // return string in, with out the text including and following the last '.'
	string lowerOf(string in);
	bool equalsNoCase(string a, string b);
	bool contains(string in, string check);			
	bool contains(vector<string> in, string check);																									
    bool isDir(string inPath, string inItem); //Is this item in this path a directory?
	bool fileExists(const string& fileName) ;	// Does this file exist?
	int evaluationCounter;
	int maxEvals;
	bool isTutorial;
	int listingIndexInGraph;
	int keyboardOffset;
	
	bool isFirstRun;
	
	bool isAssign;
	
	string double2string(double in);
	
	vector<string> getCodeOf(vector<string> contents)
	{
		for(int i = 0; i < contents.size(); i++)
		{
			if(contents[i].length() && contents[i][0] == '$')
			{
				contents.erase(contents.begin() + i);
				i--;
			}
		}
		return contents;
	}
	
	string getPropertyOf(string property, vector<string> contents, string def)
	{
		for(int i = 0; i < contents.size(); i++)
			if(contents[i].length() && contents[i][0] == '$')
			{
				vector<string> result = simple_split(contents[i], ":");
				if(result.size() == 2 && result[0] == ("$" + property))
				{
					return result[1];
					
				}
			}
		return def;
	}
	
	string output;
};

extern Utility utility;

class IOItem // A file or directory 
{
public:
       int type; // 0 = file, 1 = directory
       string name; 
};

class IOPath 
{
public:
		vector<string> path; //Vector than when put together forms the file path 
		IOPath();  
		IOPath(string initial); //Initial path
		string get(); //Stitch together the vector into a single file path string
		bool set(string in); //Split 'in' into the path vector
		bool add(string in); //Add 'in' to the path vector
		bool up(); //Remove the last element of the the path vector (back)
		vector<IOItem> getContents(); // Get files and directories in the current path
};

extern ofstream idl; // Physical log (/.Log/IdentityEngineLog.txt)

#endif

