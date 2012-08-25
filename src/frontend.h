#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDecimalNumber.h>
#import <curses.h>


@interface Channel: NSObject {
    @private
        int my;
        WINDOW *win;
        NSNumber* level;
        BOOL mute;
}

-(Channel*) initWithIndex: (int) i
                 andLevel: (NSNumber*) level_
                  andMute: (NSNumber*) mute_ // it's BOOL, but we need a pointer
                andParent: (WINDOW*) parent;
-(void) dealloc;
-(void) setMute: (BOOL) mute_;
-(void) setLevel: (NSNumber*) level_;
@end


@interface Channels: NSObject {
    @private
        WINDOW *win;
        NSMutableArray *channels;
}

-(Channels*) initWithChannels: (int) channels_
                    andParent: (WINDOW*) parent;
-(void) dealloc;
@end


@interface Widget: NSObject {
    @private
        WINDOW *win;
        int position;
        int height;
        int width;
        NSString *name;
        NSMutableArray *controls;
}

-(Widget*) initWithPosition: (int) p
                    andName: (NSString*) name_
                andChannels: (int) channels;
-(void) dealloc;
-(int) endPosition;
@end


@interface Top: NSObject {
    @private
        WINDOW *win;
        NSAutoreleasePool *pool;
}

-(Top*) init;
-(void) dealloc;
@end


@interface Bottom: NSObject {
    @private
        WINDOW *win;
        NSAutoreleasePool *pool;
}

-(Bottom*) init;
-(void) dealloc;
@end


@interface TUI: NSObject {
    @private
        NSMutableArray *widgets;
        Top *top;
        Bottom *bottom;
}

-(TUI*) init;
-(void) dealloc;
-(void) addWidgetWithChannels: (int) channels;
@end