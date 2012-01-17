#include "Utility.h"
#import "Math.h"

using namespace std;

Utility::Utility()
{
	evaluationCounter = 0;
	keyboardOffset = 0;
	maxEvals = 999999;
	isTutorial = false;
	isAssign = false;
	isFirstRun = false;
}

string Utility::strip(string in, string delim)
{
	string out = "";
	bool protect = false;
	for(int i = 0; i < in.length(); i++)
	{
		bool isBad = false;
		for(int j = 0; j < delim.length() && !isBad; j++)
			isBad = in[i] == delim[j];

		string temp = "";
		temp += in[i];

		if(temp == "\"")
			protect = !protect;
		
		if(isBad)
		{
			if(protect && temp != "\"")
			{
				out += in[i];
			}
		}
		else
		{
			out += in[i];
		}
	}
	return out;
}

bool Utility::contains(string in, string check)
{
	for(int i = 0; i < in.length(); i++)
	{
		for(int j = 0; j < check.length(); j++)
		{
			if(in[i + j] == check[j])
			{
				
			}
			else
			{
				break;
			}
			if(j == check.size() - 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool Utility::contains(vector<string> in, string check)
{
	for(int i = 0; i < in.size(); i++)
	{
		if(utility.lowerOf(in[i]) == utility.lowerOf(check))
			return true;
	}
	return false;
}

vector<string> Utility::simple_split(string in, string delim)
{
	vector<string> out; 
	string word = "";
		for(int i = 0; i< in.length(); i++)
		{
			bool splitting = false;
			for(int j = 0; j < delim.length() && !splitting; j++)
				splitting = in[i] == delim[j];
				
				
				if(splitting)
				{
					out.push_back(word);
					word = "";
				}
				else
				{
					word += in[i];
				}
		}
			out.push_back(word);
	return out;
}

vector<string> Utility::split(string in, string delim)
{
	bool canSplit = true;
	vector<string> out;                       
	string word = "";
		for(int i = 0; i< in.length(); i++)
		{
			bool splitting = false;
			for(int j = 0; j < delim.length() && !splitting; j++)
				splitting = in[i] == delim[j];
			
			string temp = "";
			temp += in[i];
			if(temp == "\"")
				canSplit = !canSplit;

				if(splitting && canSplit)
				{
					if(word != "")
					{	
						out.push_back(word);
					}
					word = "";
					string temp = "";

					temp += in[i];

					bool appending = false;	
					if( (i+1) < in.size())
					{
						if(in[i] == '+' && in[i+1] == '+')
						{
							appending = true;
						}
						else if(in[i] == '-' && in[i+1] == '-')
						{
							appending = true;
						}
						else if(in[i] == '<' && in[i+1] == '>')
						{
							appending = true;
						}
						else if(in[i] == '+' && in[i+1] == '=')
						{
							appending = true;
						}
						else if(in[i] == '-' && in[i+1] == '=')
						{
							appending = true;
						}
						else if(in[i] == '*' && in[i+1] == '=')
						{
							appending = true;
						}
						else if(in[i] == '/' && in[i+1] == '=')
						{
							appending = true;
						}
						else if(in[i] == '<' && in[i+1] == '=')
						{
							appending = true;
						}
						else if(in[i] == '>' && in[i+1] == '=')
						{
							appending = true;
						}

						if(appending)
						{
							temp += in[i+1];
							i++;
						}
					}
					out.push_back(temp);

				}
				else
				{
					word += in[i];
				}
		}
		if(word != "")
			out.push_back(word);
			
	return out;
}

string Utility::extensionOf(string in)
{
	string out = "";
	for(int i = in.length() - 1; i >= 0; i--)
	{
		if(in[i] == '.')
		{
			for(int j = i + 1; j < in.length(); j++)
			{
				out += in[j];
			}
			break;
		}
	}
	return out;
}

string Utility::stripExtension(string in)
{
	string out = "";
	
	for(int i = in.length() - 1; i >= 0; i--)
	{
		if(in[i] == '.')
		{
			for(int j = 0; j < i && j < in.length(); j++)
			{
				out += in[j];
			}
			break;
		}
	}	

	return out;
}

bool Utility::isDir(string inPath, string inItem)
{
	#ifdef OSX
		DIR *pdir = opendir( inPath.c_str() );	
		if(pdir)
		{
			bool done = false; 
				while (!done)
				{
					dirent *item = readdir(pdir);
						if (item != 0)
						{ 	
							if(item->d_name == inItem)
							{
								switch(item->d_type)
								{
									case DT_REG:
										closedir(pdir);
										return false;
									break;
									
									default: 
										closedir(pdir);
										return true; 
									break;
								}
								
							}
						}
						else 
						{
							done = true;
						}
				}			
		}			
		else
		{
			return false;
		}
	#endif
	
	#ifdef WIN
		string path = inPath + inItem;
			DIR* pdir = opendir( path.c_str() );
			if(pdir)
			{
				closedir(pdir);
				return true; 
			}
			else
			{
				closedir(pdir);
				return false;
			}	
		return false;
	#endif 
	return false;
}

bool Utility::fileExists(const string& fileName) 
{   
fstream fin;   
     fin.open(fileName.c_str(),ios::in);  
     if( fin.is_open() )   
     {     
          fin.close();     
          return true;   
     }   
     fin.close();   
return false;
}

string Utility::lowerOf(string in)
{
	for(int i = 0; i < in.length(); i++)
		if(in[i] >= 'A' && in[i] <= 'Z')
			in[i] = in[i] + 32;
			
	return in;
}

bool Utility::equalsNoCase(string a, string b)
{
	return lowerOf(a) == lowerOf(b);
}

string Utility::double2string(double in)
{
	if(in == 0)
	{
		return "0";
	}

	vector<int> digits;
	
	
	string out = "";

	if(in < 0)
		out = "-";

	in = math.abs(in);

	int exponent = floor(log10(in));
	double magnitude = pow((double)10.0, exponent);
	double scaled = in/magnitude;
	
	

	for(int i = 0; i < 16; i++)
	{
		int digit = floor(scaled);
		digits.push_back(digit);
		scaled -= digit;
		scaled *= 10;
	}


	int numZ = 0;

	for(int i = digits.size()-3; i >= 0; i--)
	{
		if(digits[i] == 0)
		{
			numZ++;
		}
		else
			break;
	}
	
	if(numZ > 5)
	{
		digits.erase(digits.end() - (numZ+2), digits.end());	
	}

	
	if(!digits.size())
		return "0";

	int numNines = 0;

	for(int i = digits.size()-3; i >= 0; i--)
	{
		if(digits[i] == 9)
		{
			numNines++;
		}
		else
			break;
	}

	if(numNines >= 5)
	{
		digits.erase(digits.end() - (numNines+2), digits.end());
		if(digits.size())
		{
			digits[digits.size()-1]++;
		}
		else
		{
			digits.push_back(1);
			exponent++;
		}
	}


	

	if(in < 10e-10 || in > 10e+10)
	{
		for(int i = 0; i < digits.size(); i++)
		{
			out += (char)(48 + digits[i]);
			if(i == 0 && digits.size() > 1)
				out += ".";
		} 
		out += "e" + utility.stringOf(exponent);	
	}
	else if(in >= 1)
	{
		int s = digits.size();
		int expon = exponent + 1;
		while(s < expon)
		{
			digits.push_back(0);
			s = digits.size();
		}
		for(int i = 0; i < digits.size(); i++)
		{
			out += (char)(48 + digits[i]);
			if(i == exponent && i != digits.size()-1)
				out += ".";
		}
	}
	else if(in < 1)
	{
		int s = digits.size();
		int expon = exponent + 1;
		while(s < expon)
		{
			digits.push_back(0);
			s = digits.size();
		}


		out += "0.";
		
		for(int i = 0; i < math.abs(exponent)-1; i++)
		{
			out += "0";
		}
		
		for(int i = 0; i < digits.size(); i++)
		{
			out += (char)(48 + digits[i]);
		}		
	}
	return out;
}

string Utility::stringOf(int in)
{
	ostringstream oss;
	oss << in;
	return oss.str();
}

string Utility::stringOf(double in)
{
	ostringstream oss;
	oss << in;
	return oss.str();
}

IOPath::IOPath()
{
}

IOPath::IOPath(string initial)
{
   set(initial);
}

          
string IOPath::get()
{
   string out;

   for(int i = 0; i < path.size(); i++)
   {
      out += path[i] + "/";
   } 

   return out;  
}

bool IOPath::set(string in)
{
	path = utility.split(in, "/");   
	for(int i = 0; i < path.size(); i++)
		path[i] = utility.strip(path[i], "/");   	
	return true;
}

bool IOPath::add(string in)
{
	path.push_back(in);   
	return true;
}

bool IOPath::up()
{
	if(path.size() > 1)
	{
		path.pop_back();     
		return true;
	}
	else
	{
		return false;
	}
}

vector<IOItem> IOPath::getContents()
{
	vector<IOItem> out; 
	string dot = ".";

		string currentPath = get();
		DIR *pdir = opendir( currentPath.c_str() );
			if(pdir)
			{
				bool done = false; 
					while (!done)
					{
						dirent *item = readdir(pdir);
							if (item != 0)
							{ 	
								IOItem ioItem;
								ioItem.name = item->d_name;
									if( (int)ioItem.name[0] != (int)dot[0] )
									{
										out.push_back(ioItem);
									}
							}
							else 
							{
								done = true;
							}
					} 
			}
		closedir(pdir);      
	
	for(int i = 0; i < out.size(); i++)
	{
		out[i].type = utility.isDir(get(), out[i].name);
	}	
		
	return out;            
}





Utility utility;
