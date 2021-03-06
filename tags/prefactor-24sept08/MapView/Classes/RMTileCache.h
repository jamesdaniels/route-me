//
//  TileImageCache.h
//  Images
//
//  Created by Joseph Gentle on 30/08/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RMTile.h"
#import "RMTileSource.h"

@class RMTileImage;

@protocol RMTileCache<NSObject>

// Returns the cached image if it exists. nil otherwise.
-(RMTileImage*) cachedImage:(RMTile)tile;

@optional

-(void)addTile: (RMTile)tile WithImage: (RMTileImage*)image;

@end


@interface RMTileCache : NSObject<RMTileCache>
{
	NSMutableArray *caches;
}

+(RMTileCache*)sharedCache;

+(NSNumber*) tileHash: (RMTile)tile;

// Add tile to cache
-(void)addTile: (RMTile)tile WithImage: (RMTileImage*)image;

-(void)addCache: (id<RMTileCache>)cache;

@end