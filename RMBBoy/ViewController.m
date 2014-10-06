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
    
    [[NSNotificationCenter defaultCenter] addObserverForName:@"display gameboy screen" object:nil queue:nil usingBlock:^(NSNotification *note) {
        NSArray *pixels = note.userInfo[@"pixels"];
        UIImage *gameImage = [self imageWithPixels:pixels];
        self.gameView.image = gameImage;
    }];
    
    Z80_doStuff();
}

-(UIImage *)imageWithPixels:(NSArray *)pixels
{
    int width = 160;
    int height = 144;

    unsigned char pixelData[width*height];
    for (int i = 0; i < width*height; i++) {
        pixelData[i] = [pixels[i] integerValue];
    }
    
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
