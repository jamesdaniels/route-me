//
//  Tile.h
//  Images
//
//  Created by Joseph Gentle on 13/08/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import "Tile.h"

@class TileImage;
@protocol TileImageLoadingDelegate

- (void)tileDidFinishLoading: (TileImage *)image;

@end


@interface TileImage : NSObject {
	Tile tile;
	UIImage *image;
	
	// I know this is a bit nasty.
	CGRect screenLocation;
	
	int loadingPriorityCount;
}

- (id) initWithTile: (Tile)tile;

- (id) increaseLoadingPriority;
- (id) decreaseLoadingPriority;

+ (TileImage*)imageWithTile: (Tile) tile FromURL: (NSString*)url;
+ (TileImage*)imageWithTile: (Tile) tile FromFile: (NSString*)filename;

- (void)drawInRect:(CGRect)rect;
- (void)draw;

- (void)setDelegate:(id) delegate;
-(void) cancelLoading;

- (void)setImageToData: (NSData*) data;

@property (readwrite, assign) CGRect screenLocation;

@end
