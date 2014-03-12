# CCTextScroller

CCTextScroller is a simple, extendable class to help with showing characters in a label sequentially like in RPGs, etc.

Written for cocos2d-x 2.2.2 api.
Just copy over the header and cpp to use. If you know how to make a CCLabelBMFont, you know how to use this.

## Usage

```
// Create standard cocos2d-x CCLabelBMFont.
CCLabelBMFont* const MY_FONT = CCLabelBMFont::create("This is a text string.", "fonts/myFont.fnt");

// Pass it into an instance of CCTextScroller.
CCTextScroller* const TEXT_SCROLLER = CCTextScroller::create(MY_FONT);

// You can define more settings to override defaults.
// Changing the character reveal interval changes how long it takes for a character 
// to fade in (default is 0 seconds).
TEXT_SCROLLER->setCharacterRevealInterval(0.5f);

See the header and implementation for more detail (it's really simple).
```

## License
Copyright 2014 Justin Godesky.
Released under the MIT License.