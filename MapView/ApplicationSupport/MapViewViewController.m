//
//  MapViewViewController.m
//  MapView
//
//  Created by Joseph Gentle on 17/09/08.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

#import "MapViewViewController.h"

#import "RMMapView.h"
#import "RMMapContents.h"
#import "RMFoundation.h"
#import "RMMarker.h"

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
	
	RMMercatorRect loc = [[(RMMapView*)[self view] contents] mercatorBounds];
	loc.origin.x += loc.size.width / 2;
	loc.origin.y += loc.size.height / 2;

	marker.location = loc.origin;
	[[[(RMMapView*)[self view] contents] overlay] addSublayer:marker];
	NSLog(@"marker added to %f %f", loc.origin.x, loc.origin.y);*/
	
	RMMapView *view = (RMMapView*)[self view];
	[(RMMapView*)view addDefaultMarkerAt:[[(RMMapView*)view contents] mapCenter]];
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
