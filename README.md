# CCTextScroller

CCTextScroller is a simple, extendable class to help with showing characters in a label sequentially like in RPGs, etc.

Written for cocos2d-x 2.2.2 api.
Just copy over the header and cpp to use. If you know how to make a CCLabelBMFont, you know how to use this.

## Usage

Give CCTextScroller a CCLabelBMFont that hasn't been added as a child to anything:
CCTextScroller will add it as a child and handle it internally.

### One-off's

```
// Create standard cocos2d-x CCLabelBMFont.
CCLabelBMFont* const MY_FONT = CCLabelBMFont::create("This is a text string.", "fonts/myFont.fnt");

// Pass it into an instance of CCTextScroller. It will start showing showing text with the default settings.
CCTextScroller* const TEXT_SCROLLER = CCTextScroller::create(MY_FONT);
this->addChild(TEXT_SCROLLER);
```

### Customizing and reusing the same instance

You can define more settings to override default behavior.


```
// The label can be set later, doesn't have to be instantiated at creation time.
// This allows for reuse of the same CCTextScroller over and over.
textScroller = CCTextScroller::create();
this->addChild(TEXT_SCROLLER);

// Some time later...
textScroller->setLabel(MY_FONT);

// Changing the character reveal interval changes how long it takes for a character 
// to fade in (default is 0 seconds).
textScroller->setCharacterRevealInterval(0.5f);

// An action to be run on the label once it's done triggering all it's characters.
textScroller->setOnDoneAction(CCSequence::create(CCDelayTime::create(3.0f),
                                                 CCFadeOut::create(3.0f),
                                                 NULL));

// When the label has changed or reset() has been called, you need to call start() manually.
textScroller->start();
```


See the header and implementation for more detail (it's really simple).
If anything seems off, submit a pull request and I'll probably put it through.
If not, you can directly override by subclassing to extend easily.

## License
Copyright 2014 Justin Godesky.
Released under the MIT License.