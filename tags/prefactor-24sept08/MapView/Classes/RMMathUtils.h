/*
 *  MathUtils.h
 *  RouteMe
 *
 *  Created by Joseph Gentle on 8/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

#include <CoreGraphics/CGGeometry.h>

CGRect RMScaleCGRectAboutPoint(CGRect rect, float factor, CGPoint point);
CGRect RMTranslateCGRectBy(CGRect rect, CGSize delta);
CGPoint RMTranslateCGPointBy(CGPoint point, CGSize delta);

#endif