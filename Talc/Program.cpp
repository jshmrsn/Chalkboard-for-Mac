#include "Program.h"
#include "Utility.h"

#import "Parser.h"

//
//#import "Organizer.h"
//#import "TalcSource.h"

using namespace std;

Program program;

Function* Program::getFunction(string in)
{
//	for(int i = 0; i < [utility.organizer.sourceList count]; i++)
//		if(utility.equalsNoCase( [[[utility.organizer.sourceList objectAtIndex:i] name] UTF8String], in))
//		{
//			Parser parser;
//			TalcSource* source = [utility.organizer.sourceList objectAtIndex:i];
//			if(utility.equalsNoCase( source.function->name, [[[utility.organizer.sourceList objectAtIndex:i] name] UTF8String]) )
//			{
//			}
//			else
//			{
//				string xtext = [[source text] UTF8String];
//
//				vector<string> xcontents = utility.simple_split(xtext, "\n");
//				
//				*source.function = parser.parse(xcontents);				
//			}
//			
//			return source.function;
//		}
	
	return 0;
}

Function* Program::getFunction(string in, int inputs)
{
//	for(int i = 0; i < [utility.organizer.sourceList count]; i++)
//	{
//		if(utility.equalsNoCase( [[[utility.organizer.sourceList objectAtIndex:i] name] UTF8String], in))
//		{
//			Parser parser;
//			TalcSource* source = [utility.organizer.sourceList objectAtIndex:i];
//
//			if(utility.equalsNoCase( source.function->name, [[[utility.organizer.sourceList objectAtIndex:i] name] UTF8String]) )
//			{
//			}
//			else
//			{
//
//			
//				string xtext = [[source text] UTF8String];
//
//				vector<string> xcontents = utility.simple_split(xtext, "\n");
//				
//				*source.function = parser.parse(xcontents);				
//			}
//			
//			return source.function;
//		}
//		
//	}
	return 0;
}

