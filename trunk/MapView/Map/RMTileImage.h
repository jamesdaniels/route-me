//
//  RMTileImage.h
//
// Copyright (c) 2008, Route-Me Contributors
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#import <TargetConditionals.h>
#if TARGET_OS_IPHONE
	#import <UIKit/UIKit.h>
#else
	#import <Cocoa/Cocoa.h>
typedef NSImage UIImage;
#endif

#import "RMFoundation.h"
#import "RMTile.h"

@class RMTileImage;
@class NSData;

extern NSString * const RMMapImageLoadedNotification;
extern NSString * const RMMapImageLoadingCancelledNotification;

@interface RMTileImage : NSObject {
	UIImage *image;

//	CGImageRef image;
	
	NSData* dataPending;
	
	// I know this is a bit nasty.
	RMTile tile;
	CGRect screenLocation;
	
	int loadingPriorityCount;
	
	// Used by cache
	NSDate *lastUsedTime;
	
	// Only used when appropriate
	CALayer *layer;
}

- (id) initWithTile: (RMTile)tile;

+ (RMTileImage*) dummyTile: (RMTile)tile;

//- (id) increaseLoadingPriority;
//- (id) decreaseLoadingPriority;

+ (RMTileImage*)imageWithTile: (RMTile) tile FromURL: (NSString*)url;
+ (RMTileImage*)imageWithTile: (RMTile) tile FromFile: (NSString*)filename;
+ (RMTileImage*)imageWithTile: (RMTile) tile FromData: (NSData*)data;

- (void)drawInRect:(CGRect)rect;
- (void)draw;

- (void)moveBy: (CGSize) delta;
- (void)zoomByFactor: (float) zoomFactor near:(CGPoint) center;

- (void)makeLayer;

- (void)cancelLoading;

- (void)setImageToData: (NSData*) data;

- (void)touch;

- (BOOL)isLoaded;

@property (readwrite, assign) CGRect screenLocation;
@property (readonly, assign) RMTile tile;
@property (readonly) CALayer *layer;
@property (readonly) UIImage *image;
@property (readonly) NSDate *lastUsedTime;

@end
