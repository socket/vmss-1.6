//
//  UntitledAppDelegate.h
//  Untitled
//
//  Created by Alexey Streltsow on 4/5/10.
//  Copyright Zila Networks LLC 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UntitledAppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UINavigationController *navigationController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end

