//
//  RMTiledLayerController.h
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

#import <Foundation/Foundation.h>
#import "RMFoundation.h"
#import <QuartzCore/QuartzCore.h>

@protocol RMTileSource;

/// ////////////////////////// NOT COMPLETE. DO NOT USE
@interface RMTiledLayerController : NSObject
{
	CATiledLayer *layer;
	
//	MercatorPoint topLeft;
	
	// Size in pixels
//	CGSize viewSize;
	
	/*! \brief "scale" as of version 0.4/0.5 actually doesn't mean cartographic scale; it means meters per pixel.
	 
	 Scale is how many meters in 1 pixel. Larger scale means bigger things are smaller on the screen.
	 Scale of 1 means 1 pixel == 1 meter.
	 Scale of 10 means 1 pixel == 10 meters.
	 */
	float scale;
	
	id tileSource;
}

-(id) initWithTileSource: (id <RMTileSource>) tileSource;

-(void) setScale: (float) scale;

-(void) centerXYPoint: (RMXYPoint) aPoint animate: (BOOL) animate;
-(void) centerLatLong: (CLLocationCoordinate2D) point animate: (BOOL) animate;
-(void) dragBy: (CGSize) delta;
-(void) zoomByFactor: (float) zoomFactor near:(CGPoint) center;

/*
-(CGPoint) projectMercatorPoint: (MercatorPoint) point;
-(CGRect) projectMercatorRect: (MercatorRect) rect;

-(MercatorPoint) projectInversePoint: (CGPoint) point;
-(MercatorRect) projectInverseRect: (CGRect) rect;

-(MercatorRect) bounds;
*/
@property (assign, readwrite, nonatomic) float scale;
@property (readonly, nonatomic) CATiledLayer *layer;

@end
