//
//  ScreenProjection.m
//  Images
//
//  Created by Joseph Gentle on 28/08/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "RMScreenProjection.h"


@implementation RMScreenProjection

@synthesize scale, topLeft;

-(id) initWithBounds: (CGRect) _bounds
{
	if (![super init])
		return nil;
	bounds = _bounds;
	topLeft.x = 0;
	topLeft.y = 0;
	scale = 1;
	return self;
}

-(void) moveToMercator: (RMMercatorPoint) point
{
	topLeft = point;
	topLeft.x -= bounds.size.width * scale / 2;
	topLeft.y -= bounds.size.height * scale / 2;
}

-(void) moveToLatLong: (CLLocationCoordinate2D) point;
{
	[self moveToMercator:[RMMercator toMercator:point]];
}

-(void) moveBy: (CGSize) delta
{
	topLeft.x -= delta.width * scale;
	topLeft.y += delta.height * scale;
}

-(void) zoomByFactor: (float) zoomFactor Near:(CGPoint) center
{
//	NSLog(@"zoomBy: %f", zoomFactor);
	topLeft.x += center.x * scale;
	topLeft.y += (bounds.size.height - center.y) * scale;
	scale /= zoomFactor;
	topLeft.x -= center.x * scale;
	topLeft.y -= (bounds.size.height - center.y) * scale;
}

- (void)zoomBy: (float) factor
{
	scale *= factor;
}

-(CGPoint) projectMercatorPoint: (RMMercatorPoint) mercator
{
	CGPoint point;
	point.x = (mercator.x - topLeft.x) / scale;
	point.y = -(mercator.y - topLeft.y) / scale;
	return point;
}

-(CGRect) projectMercatorRect: (RMMercatorRect) mercator
{
	CGRect rect;
	rect.origin = [self projectMercatorPoint: mercator.origin];
	mercator.size.width = rect.size.width / scale;
	mercator.size.height = rect.size.height / scale;
	return rect;
}

-(RMMercatorPoint) projectInversePoint: (CGPoint) point
{
	RMMercatorPoint mercator;
	mercator.x = (scale * point.x) + topLeft.x;
	mercator.y = -(scale * point.y) + topLeft.y;
	return mercator;
}

-(RMMercatorRect) projectInverseRect: (CGRect) rect
{
	RMMercatorRect mercator;
	mercator.origin = [self projectInversePoint: rect.origin];
	mercator.size.width = rect.size.width * scale;
	mercator.size.height = rect.size.height * scale;
	return mercator;
}

-(CGRect) screenBounds
{
	return bounds;
}

-(RMMercatorRect) mercatorBounds
{
	RMMercatorRect rect;
	rect.origin = topLeft;
	rect.size.width = bounds.size.width * scale;
	rect.size.height = bounds.size.height * scale;
	return rect;
}

@end
