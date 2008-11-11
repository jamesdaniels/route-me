/*
 *  RMFoundation.h
 *  MapView
 *
 *  Created by David Bainbridge on 10/28/08.
 *
 */



#define RMLatLong					CLLocationCoordinate2D

typedef struct {
	double x, y;
} RMXYPoint;

typedef struct {
	double width, height;
} RMXYSize;

typedef struct {
	RMXYPoint origin;
	RMXYSize size;
} RMXYRect;

typedef struct {
	CLLocationCoordinate2D northWest;
	CLLocationCoordinate2D southEast;
} RMLatLongBounds;

RMXYPoint RMScaleXYPointAboutPoint(RMXYPoint point, float factor, RMXYPoint pivot);
RMXYRect  RMScaleXYRectAboutPoint (RMXYRect rect,   float factor, RMXYPoint pivot);
RMXYPoint RMTranslateXYPointBy    (RMXYPoint point, RMXYSize delta);
RMXYRect  RMTranslateXYRectBy     (RMXYRect rect,   RMXYSize delta);

RMXYPoint  RMXYMakePoint (double x, double y);
RMXYRect  RMXYMakeRect (double x, double y, double width, double height);

