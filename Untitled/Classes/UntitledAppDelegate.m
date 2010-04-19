//
//  UntitledAppDelegate.m
//  Untitled
//
//  Created by Alexey Streltsow on 4/5/10.
//  Copyright Zila Networks LLC 2010. All rights reserved.
//

#import "UntitledAppDelegate.h"
#import "RootViewController.h"


@implementation UntitledAppDelegate

@synthesize window;
@synthesize navigationController;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    // Override point for customization after app launch    
	
	[window addSubview:[navigationController view]];
    [window makeKeyAndVisible];
	return YES;
}


- (void)applicationWillTerminate:(UIApplication *)application {
	// Save data if appropriate
}


#pragma mark -
#pragma mark Memory management

- (void)dealloc {
	[navigationController release];
	[window release];
	[super dealloc];
}


@end

