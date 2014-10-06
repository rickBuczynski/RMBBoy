//
//  ViewController.m
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import "ViewController.h"
#import "Z80.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *gameView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    self.gameView.contentMode = UIViewContentModeScaleAspectFit;
    UIImage *gameImage = [self imageWidth:15 height:17];
    self.gameView.image = gameImage;
    
    
    
    Z80_doStuff();
    
}

-(UIImage *)imageWidth:(NSUInteger)width height:(NSUInteger)height {
    /*
     Assuming pixel color values are 8 bit unsigned
     
     You need to create an array that is in the format BGRA (blue,green,red,alpha).
     You can achieve this by implementing a for-loop that sets the values at each index.
     I have not included a for-loop in this example because it depends on how the values are stored in your input 2D array.
     You can set the alpha value to 255.
     */
    unsigned char pixelData[width * height];
    for (int i=0; i<width*height; i++) {
        pixelData[i]=i;
    }
    
    // This is where the for-loop would be
    
    void *baseAddress = &pixelData;
    
    size_t bytesPerRow = width;
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();
    CGContextRef context = CGBitmapContextCreate(baseAddress, width, height, 8, bytesPerRow, colorSpace, kCGBitmapByteOrderDefault);
    CGImageRef cgImage = CGBitmapContextCreateImage(context);
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    return [UIImage imageWithCGImage:cgImage];
}

@end
