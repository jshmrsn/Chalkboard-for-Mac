#import <Cocoa/Cocoa.h>
#import <OSAKit/OSAKit.h>

@interface CalcController : NSObjectController <NSOutlineViewDataSource>
{
	NSMutableArray         *root;
	NSMutableArray         *helpRoot;

	IBOutlet NSTextView* inputTextView;
	IBOutlet NSTextView* outputTextView;
	IBOutlet NSOutlineView* functionsOutlineView;
	IBOutlet NSOutlineView* helpOutlineView;
	
	IBOutlet NSWindow* helpWindow;		
	IBOutlet NSWindow* mainWindow;			
}

- (IBAction)runAction:(id)sender;
- (IBAction)helpAction:(id)sender;

@property (assign,readonly) NSMutableArray *root;
@end