//
//  RMMapContents.h
//  MapView
//
//  Created by Joseph Gentle on 24/09/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "RMFoundation.h"
#import "RMLatLong.h"
#import "RMTile.h"

// constants for boundingMask
enum {
	// Map can be zoomed out past view limits
	RMMapNoMinBound			= 0,
	// Minimum map height when zooming out restricted to view height
	RMMapMinHeightBound		= 1,
	// Minimum map width when zooming out restricted to view width ( default )
	RMMapMinWidthBound		= 2
};

@class RMProjection;
@class RMMercatorToScreenProjection;
@class RMTileImageSet;
@class RMTileLoader;
@class RMMapRenderer;
@class RMMapLayer;
@class RMLayerSet;
@class RMMarker;
@protocol RMMercatorToTileProjection;
@protocol RMTileSource;

@interface RMMapContents : NSObject
{
	// TODO: Also support NSView.
	
	// This is the underlying UIView's layer.
	CALayer *layer;
	
	RMMapLayer *background;
	RMLayerSet *overlay;
	
	// Latlong is calculated dynamically from mercatorBounds.
	RMProjection *projection;
	
	id<RMMercatorToTileProjection> mercatorToTileProjection;
//	RMTileRect tileBounds;
	
	RMMercatorToScreenProjection *mercatorToScreenProjection;
	
	id<RMTileSource> tileSource;
	
	RMTileImageSet *imagesOnScreen;
	RMTileLoader *tileLoader;
	
	RMMapRenderer *renderer;
	NSUInteger		boundingMask;
}

@property (readwrite) CLLocationCoordinate2D mapCenter;
@property (readwrite) RMXYRect XYBounds;
@property (readonly)  RMTileRect tileBounds;
@property (readonly)  CGRect screenBounds;
@property (readwrite) float scale;
@property (readwrite) float zoom;

@property (readonly)  RMTileImageSet *imagesOnScreen;

@property (readonly)  RMProjection *projection;
@property (readonly)  id<RMMercatorToTileProjection> mercatorToTileProjection;
@property (readonly)  RMMercatorToScreenProjection *mercatorToScreenProjection;

@property (retain, readwrite) id<RMTileSource> tileSource;
@property (retain, readwrite) RMMapRenderer *renderer;

@property (readonly)  CALayer *layer;

@property (retain, readwrite) RMMapLayer *background;
@property (retain, readwrite) RMLayerSet *overlay;
@property (readwrite) NSUInteger boundingMask;

- (id) initForView: (UIView*) view;

// Designated initialiser
- (id)initForView:(UIView*)view WithTileSource:(id<RMTileSource>)tileSource WithRenderer:(RMMapRenderer*)renderer LookingAt:(CLLocationCoordinate2D)latlong;

- (void)moveToLatLong: (CLLocationCoordinate2D)latlong;
- (void)moveToXYPoint: (RMXYPoint)aPoint;

- (void)moveBy: (CGSize) delta;
- (void)zoomByFactor: (float) zoomFactor near:(CGPoint) center;
- (float)adjustZoomForBoundingMask:(float)zoomFactor;
- (void)adjustMapPlacementWithScale:(float)aScale;

- (void) drawRect: (CGRect) rect;

//-(void)addLayer: (id<RMMapLayer>) layer above: (id<RMMapLayer>) other;
//-(void)addLayer: (id<RMMapLayer>) layer below: (id<RMMapLayer>) other;
//-(void)removeLayer: (id<RMMapLayer>) layer;

// During touch and move operations on the iphone its good practice to
// hold off on any particularly expensive operations so the user's 
+ (BOOL) performExpensiveOperations;
+ (void) setPerformExpensiveOperations: (BOOL)p;

- (CGPoint)latLongToPixel:(CLLocationCoordinate2D)latlong;
- (CGPoint)latLongToPixel:(CLLocationCoordinate2D)latlong withScale:(float)aScale;
- (CLLocationCoordinate2D)pixelToLatLong:(CGPoint)aPixel;
- (CLLocationCoordinate2D)pixelToLatLong:(CGPoint)aPixel withScale:(float)aScale;

- (void)zoomWithLatLngBoundsNorthEast:(CLLocationCoordinate2D)ne SouthWest:(CLLocationCoordinate2D)se;
- (void)zoomWithRMMercatorRectBounds:(RMXYRect)bounds;

- (void) addMarker: (RMMarker*)marker;
- (void) addMarker: (RMMarker*)marker AtLatLong:(CLLocationCoordinate2D)point;
- (void) addDefaultMarkerAt: (CLLocationCoordinate2D)point;
- (void) removeMarkers;
- (NSArray *)getMarkers;
- (void) removeMarker:(RMMarker *)marker;

@end
