//
//  TileImageSet.m
//  RouteMe
//
//  Created by Joseph Gentle on 9/09/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "RMTileImageSet.h"
#import "RMTileImage.h"
#import "RMMathUtils.h"

@implementation RMTileImageSet

@synthesize delegate, nudgeTileSize;

-(id) initWithDelegate: (id<RMTileImageSetDelegate>) _delegate
{
	if (![super init])
		return nil;
	
	self.delegate = _delegate;
	images = [[NSCountedSet alloc] init];
	nudgeTileSize = YES;
	return self;
}

-(void) dealloc
{
	[images release];
	[super dealloc];
}

-(void) removeTile: (RMTile) tile
{
	RMTileImage *dummyTile = [RMTileImage dummyTile:tile];
	if ([images countForObject:dummyTile] == 1)
	{
		if ([delegate respondsToSelector: @selector(tileRemoved:)])
		{
			[delegate tileRemoved:tile];
		}
	}

	[images removeObject:dummyTile];
}

-(void) removeTiles: (RMTileRect)rect
{	
	RMTileRect roundedRect = RMTileRectRound(rect);
	// The number of tiles we'll load in the vertical and horizontal directions
	int tileRegionWidth = (int)roundedRect.size.width;
	int tileRegionHeight =  (int)roundedRect.size.height;
	
	RMTile t;
	t.zoom = rect.origin.tile.zoom;
	
	for (t.x = roundedRect.origin.tile.x; t.x < roundedRect.origin.tile.x + tileRegionWidth; t.x++)
	{
		for (t.y = (roundedRect.origin.tile.y); t.y <= roundedRect.origin.tile.y + tileRegionHeight; t.y++)
		{
			[self removeTile:t];
		}
	}
}

/* Untested.
 -(BOOL) hasTile: (Tile) tile
 {
 NSEnumerator *enumerator = [images objectEnumerator];
 TileImage *object;
 
 while ((object = [enumerator nextObject])) {
 if (TilesEqual(tile, [object tile]))
 return YES;
 }
 
 return NO;
 }*/

-(void) addTile: (RMTile) tile WithImage: (RMTileImage *)image At: (CGRect) screenLocation
{
	image.screenLocation = screenLocation;
	[images addObject:image];
	
	if (!RMTileIsDummy(image.tile) && [delegate respondsToSelector:@selector(tileAdded:WithImage:)])
	{
		[delegate tileAdded:tile WithImage:image];
	}
}

-(void) addTile: (RMTile) tile At: (CGRect) screenLocation
{
	//	NSLog(@"addTile: %d %d", tile.x, tile.y);
	
	RMTileImage *dummyTile = [RMTileImage dummyTile:tile];
	if ([images containsObject:dummyTile])
	{
		[images addObject:dummyTile];
	}
	else
	{
		if (delegate != nil)
		{
			RMTileImage *image = [delegate makeTileImageFor:tile];
			if (image != nil)
				[self addTile:tile WithImage:image At:screenLocation];		
		}
	}
}

// Add tiles inside rect protected to bounds. Return rectangle containing bounds
// extended to full tile loading area
-(CGRect) addTiles: (RMTileRect)rect ToDisplayIn:(CGRect)bounds
{
	//	NSLog(@"addTiles: %d %d - %f %f", rect.origin.tile.x, rect.origin.tile.y, rect.size.width, rect.size.height);
	
	RMTile t;
	t.zoom = rect.origin.tile.zoom;
	
	// ... Should be the same as equivalent calculation for height.
	float pixelsPerTile = bounds.size.width / rect.size.width;
	
	CGRect screenLocation;
	screenLocation.size.width = pixelsPerTile;
	screenLocation.size.height = pixelsPerTile;
	
	// Corrects a bug in quartz's resizing code
	if (nudgeTileSize)
	{
		screenLocation.size.width += 0.5;
		screenLocation.size.height += 0.5;
	}
	
	RMTileRect roundedRect = RMTileRectRound(rect);
	// The number of tiles we'll load in the vertical and horizontal directions
	int tileRegionWidth = (int)roundedRect.size.width;
	int tileRegionHeight =  (int)roundedRect.size.height;
	
	for (t.x = roundedRect.origin.tile.x; t.x < roundedRect.origin.tile.x + tileRegionWidth; t.x++)
	{
		for (t.y = (roundedRect.origin.tile.y); t.y <= roundedRect.origin.tile.y + tileRegionHeight; t.y++)
		{
			screenLocation.origin.x = bounds.origin.x + (t.x - (rect.origin.offset.x + rect.origin.tile.x)) * pixelsPerTile;
			screenLocation.origin.y = bounds.origin.y + (t.y - (rect.origin.offset.y + rect.origin.tile.y)) * pixelsPerTile;
			
			[self addTile:t At:screenLocation];
		}
	}
	
	// Now we translate the loaded region back into screen space for loadedBounds.
	CGRect newLoadedBounds;
	newLoadedBounds.origin.x = bounds.origin.x - (rect.origin.offset.x * pixelsPerTile);
	newLoadedBounds.origin.y = bounds.origin.y - (rect.origin.offset.y * pixelsPerTile);	
	newLoadedBounds.size.width = tileRegionWidth * pixelsPerTile;
	newLoadedBounds.size.height = tileRegionHeight * pixelsPerTile;
	return newLoadedBounds;
}

-(RMTileImage*) imageWithTile: (RMTile) tile
{
	NSEnumerator *enumerator = [images objectEnumerator];
	RMTileImage *object;
	
	while ((object = [enumerator nextObject])) {
		if (RMTilesEqual(tile, [object tile]))
			return object;
	}
	
	return nil;
}

-(NSUInteger) count
{
	return [images count];
	
}

- (void)moveBy: (CGSize) delta
{
	for (RMTileImage *image in images)
	{
		[image moveBy: delta];
	}
}

- (void)zoomByFactor: (float) zoomFactor Near:(CGPoint) center
{
	for (RMTileImage *image in images)
	{
		[image zoomByFactor:zoomFactor Near:center];
	}
}

- (void) draw
{
	for (RMTileImage *image in images)
	{
		[image draw];
	}
}

@end
