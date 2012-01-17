#import "CalcController.h"

#include "Parser.h"
#include "Utility.h"

@implementation CalcController
@synthesize root;

-(id)init
{
	if(self = [super init])
	{
		root =  [[NSMutableArray alloc] init];
		[root setArray:[[NSFileManager defaultManager] contentsOfDirectoryAtPath:@"./" error:nil]];
		
		helpRoot =  [[NSMutableArray alloc] init];

		helpRoot = [[NSMutableArray alloc] init];
		
		[helpRoot addObject:@"•Basic Math•"];	
		[helpRoot addObject:@"+  (add)"];
		[helpRoot addObject:@"-   (subtract)"];
		[helpRoot addObject:@"*   (multiply)"];
		[helpRoot addObject:@"/   (divide)"];
		[helpRoot addObject:@"^     (to the power of)"];
		[helpRoot addObject:@"\\    (square root)"];
		[helpRoot addObject:@"%     (mod)"];						
		
		[helpRoot addObject:@"="];
		
		
		[helpRoot addObject:@""];
		
		
		
		[helpRoot addObject:@"•Math•"];	
		[helpRoot addObject:@"log[ number ] (natural log)"];
		[helpRoot addObject:@"rand[] (random 0-1)"];
		[helpRoot addObject:@"rand[ num ] (random 0-num)"];
		[helpRoot addObject:@"floor[ number ]"];
		[helpRoot addObject:@"round[ number ]"];
		[helpRoot addObject:@"round[ number, place ] (round to place)"];
		
		[helpRoot addObject:@"(Trig)"];
		[helpRoot addObject:@"sin[ degrees ]"];
		[helpRoot addObject:@"cos[ degrees ]"];
		[helpRoot addObject:@"tan[ degrees ]"];
		[helpRoot addObject:@"asin[ degrees ]"];
		[helpRoot addObject:@"acos[ degrees ]"];
		[helpRoot addObject:@"atan[ degrees ]"];
		
		[helpRoot addObject:@""];
		
		[helpRoot addObject:@"•Comparisons•"];
		[helpRoot addObject:@">"];
		[helpRoot addObject:@">= (greater or equal)"];
		[helpRoot addObject:@"<"];
		[helpRoot addObject:@"<= (less or equal)"];	
		[helpRoot addObject:@"&    (and)"];
		[helpRoot addObject:@"|     (or)"];
		[helpRoot addObject:@"!     (invert)"];
		[helpRoot addObject:@"<> (is equal to)"];		
		
		[helpRoot addObject:@""];		
		[helpRoot addObject:@"•Constants•"];
		[helpRoot addObject:@"pi (3.14159265...)"];
		[helpRoot addObject:@"e (2.71828183)"];
		[helpRoot addObject:@"i (0 + 1i)"];
		[helpRoot addObject:@"deg (180/pi)"];
		[helpRoot addObject:@"rad (pi/180)"];
		
		
		[helpRoot addObject:@"false (0)"];
		[helpRoot addObject:@"true  (1)"];
		
		[helpRoot addObject:@""];
		[helpRoot addObject:@"•Bracket Types•"];
		
		[helpRoot addObject:@"(order of operation)"];
		[helpRoot addObject:@"[function inputs]"];
		[helpRoot addObject:@"{list contents}"];
		
		[helpRoot addObject:@""];
		[helpRoot addObject:@"•Statements•"];
		[helpRoot addObject:@"if"];
		[helpRoot addObject:@"else"];
		[helpRoot addObject:@"end"];
		[helpRoot addObject:@"out (end and return a value)"];
		[helpRoot addObject:@""];

		[helpRoot addObject:@"loop (loop i < 5)"];
		[helpRoot addObject:@"next (iterates loop)"];	
		[helpRoot addObject:@""];
		
		[helpRoot addObject:@"; (suppresses output of line)"];
		
		[helpRoot addObject:@""];		
		[helpRoot addObject:@""];
		
		[helpRoot addObject:@"•Lists•"];
		[helpRoot addObject:@"size[list] (size of list)"];
		[helpRoot addObject:@"add[list, new] (add new to element)"];
		[helpRoot addObject:@"add[list, new, index] (add @ index)"];
		[helpRoot addObject:@"remove[list] (remove last element)"];
		[helpRoot addObject:@"remove[list, index] (remove @ index)"];
		[helpRoot addObject:@"list[#] (list with dimensions)"];
		[helpRoot addObject:@"avg[list] (mean of a list)"];		
		[helpRoot addObject:@""];		
		[helpRoot addObject:@"myList[#,#,#] (list access)"];
		
		
		
		[helpRoot addObject:@""];
		[helpRoot addObject:@""];
				
		
		[helpRoot addObject:@"•Complex Numbers•"];
		[helpRoot addObject:@"(real + (i)complex)"];
		[helpRoot addObject:@"real[complex] (get real component)"];
		[helpRoot addObject:@"imag[complex] (get imaginary component)"];
	}
	
	return self;
}

-(void)dealloc
{
	[helpRoot release];
	[root release];
	[super dealloc];
}

-(void)run
{	
	utility.evaluationCounter = 0;
	
	utility.output = "";
	
	string in = [[inputTextView string] UTF8String];
	
	Parser parser;
	
	Function function = parser.parse(utility.simple_split(in, "\n"));
	
	function.evaluate();
	
	[outputTextView setString:[NSString stringWithUTF8String:utility.output.c_str()]];
}

- (IBAction)runAction:(id)sender
{
	[self run];
}

- (IBAction)helpAction:(id)sender
{
	[helpWindow makeKeyAndOrderFront:nil];
//	[mainWindow addChildWindow:helpWindow ordered:NSWindowAbove];
//	[helpWindow becomeMainWindow];
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
	if(outlineView == functionsOutlineView)
	{
		id parentObject = [outlineView parentForItem:item] ? [outlineView parentForItem:item] : root;

		
		if ([parentObject isKindOfClass:[NSArray class]]) 
		{
			return [root objectAtIndex:[parentObject indexOfObject:item]];
		}
	}
	else if(outlineView == helpOutlineView)
	{
		id parentObject = [outlineView parentForItem:item] ? [outlineView parentForItem:item] : helpRoot;
		
		
		if ([parentObject isKindOfClass:[NSArray class]]) 
		{
			return [helpRoot objectAtIndex:[parentObject indexOfObject:item]];
		}
	}

    return nil;
}

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{

	if(outlineView == functionsOutlineView)
	{
		if (item == nil)
		{
			return [root count];
		}
		
	}
	else if(outlineView == helpOutlineView)
	{
		if (item == nil)
		{
			return [helpRoot count];
		}
	}	
	
	return 0;
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item
{
	if(outlineView == functionsOutlineView)
	{
		if(item == nil)
		{
			item = root;
		}
		
		if([item isKindOfClass:[NSArray class]]) 
		{
			return [item objectAtIndex:index];
		}
	}
	else if(outlineView == helpOutlineView)
	{
		if(item == nil)
		{
			item = helpRoot;
		}
		
		if([item isKindOfClass:[NSArray class]]) 
		{
			return [item objectAtIndex:index];
		}
	}	
	

	
    return nil;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
	return NO;
	
    if ([item isKindOfClass:[NSArray class]] || [item isKindOfClass:[NSDictionary class]])
    {
        if ([item count] > 0)
            return YES;
    }
	return NO;
}

@end
