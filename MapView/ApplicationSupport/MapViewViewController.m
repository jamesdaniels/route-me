//
//  MapViewViewController.m
//  MapView
//
//  Created by Joseph Gentle on 17/09/08.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

#import "MapViewViewController.h"

#import "RMMapContents.h"
#import "RMFoundation.h"
#import "RMMarker.h"

#import "RMMarkerManager.h"

@implementation MapViewViewController

/*
// Override initWithNibName:bundle: to load the view using a nib file then perform additional customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view.
- (void)viewDidLoad {
    [super viewDidLoad];

	
/*	RMMarker *marker = [[RMMarker alloc] initWithKey:RMMarkerBlueKey];
	
	RMMercatorRect loc = [[mapView contents] mercatorBounds];
	loc.origin.x += loc.size.width / 2;
	loc.origin.y += loc.size.height / 2;

	marker.location = loc.origin;
	[[[mapView contents] overlay] addSublayer:marker];
	NSLog(@"marker added to %f %f", loc.origin.x, loc.origin.y);*/
	
		
	RMMarkerManager *markerManager = [mapView markerManager];
	
	[markerManager addDefaultMarkerAt:[[mapView contents] mapCenter]];

	
	NSArray *markers = [markerManager getMarkers];
	
	NSLog(@"Nb markers %d", [markers count]);
	
	NSEnumerator *markerEnumerator = [markers objectEnumerator];
	RMMarker *aMarker;
	
	while (aMarker = (RMMarker *)[markerEnumerator nextObject])
		
	{
		RMXYPoint point = [aMarker location];
		NSLog(@"Marker mercator location: X:%lf, Y:%lf", point.x, point.y);
		CGPoint screenPoint = [markerManager getMarkerScreenCoordinate: aMarker];
		NSLog(@"Marker screen location: X:%lf, Y:%lf", screenPoint.x, screenPoint.y);
		CLLocationCoordinate2D coordinates =  [markerManager getMarkerCoordinate2D: aMarker];
		NSLog(@"Marker Lat/Lon location: Lat:%lf, Lon:%lf", coordinates.latitude, coordinates.longitude);
		
		[markerManager removeMarker:aMarker];
	}
	
	// Put the marker back
	[markerManager addDefaultMarkerAt:[[mapView contents] mapCenter]];
	
	markers  = [markerManager getMarkersForScreenBounds];
	
	NSLog(@"Nb Markers in Screen: %d", [markers count]);
	
	[mapView setZoomBounds:0.0 maxZoom:17.0];
	
	[mapView getScreenCoordinateBounds];
	
	

	
}



- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}


- (void)dealloc {
    [super dealloc];
}

@end
