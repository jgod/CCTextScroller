# CCTextScroller

CCTextScroller is a simple, extendable class to help with showing characters in a label sequentially like in RPGs, etc.

Written for cocos2d-x 2.2.x api and C++03.
 
##__This is no longer maintained. It's left as an example.__

## Usage

### Basic 

Once you have setup a CCTextScroller (see below for more detail), starting it is simple.

```
textScroller->start()
```

A more flexible way is to use the `print` helper function. It assumes a bunch of sane defaults.

It returns true if it's started printing, and takes an optional callback (CCAction).

```
if (textScroller->print("Have fun!",   CCCallFunc::create(this, callfunc_selector(MyLayer::myCallbackFunction)))) 
{
// Play a sound if starting the text scroller was successful.
  sounds->play(Sound::MESSAGE);
}
```

### Setup

The first step is to have a CCLabelBMFont (that isn't a child of anything) ready. 

CCTextScroller will add it as a child and handle it internally.

```
CCLabelBMFont* const MY_LABEL = CCLabelBMFont::create("This is a text string.", "fonts/myFont.fnt");
```

#### Eager

Pass the label into a new instance of CCTextScroller. It will start showing showing text with the default settings immediately (optional; default: true).

```
CCTextScroller* const TEXT_SCROLLER = CCTextScroller::create(MY_LABEL, true);
this->addChild(TEXT_SCROLLER);
```

#### Lazy

The label can be set later, doesn't have to be known at creation time.

```
textScroller = CCTextScroller::create();
this->addChild(textScroller);

// Some time later
textScroller->setLabel(MY_LABEL);
```

This allows for reuse of the same CCTextScroller over and over. Use case: storing one on your scene alongside your other objects.

### Customizing

#### Character Reveal Interval

How long it takes for a character to show (default is 0 seconds).

```
textScroller->setCharacterRevealInterval(0.5f);
```

#### Callbacks

Callback to run when all characters are done revealing.

```
textScroller->setOnDoneAction(CCSequence::create(CCDelayTime::create(3.0f),
                                                 CCFadeOut::create(3.0f),
                                                 NULL));
```

### Extra

See the header and implementation for more detail (it's really simple).

## License

Copyright Justin Godesky.
Released under the AGPLv3 License.
