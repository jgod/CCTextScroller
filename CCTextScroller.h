//  CCTextScroller.h
//  Created by Justin Godesky on 3/11/14.

#ifndef __CCTextScroller__
#define __CCTextScroller__

#include "cocos2d.h"
using namespace cocos2d;

class CCTextScroller : public CCNode
{
public:
  CREATE_FUNC(CCTextScroller);
  CCTextScroller();
  virtual ~CCTextScroller();
  
  static CCTextScroller* const create(CCLabelBMFont* const newLabel,
                                      const bool startShowingNow = true);
  virtual void onExit();
  
  /**
   * Starts scheduling updates to trigger showing characters.
   */
  virtual void startShowing();
  
  /**
   * Hides all characters, keeping the same label. Sets current character to 0.
   */
  virtual void reset();
  
  // Getters and setters
  /**
   * Sets the label whose characters need to be shown.
   */
  void setLabel(CCLabelBMFont* const newLabel);
  
  /**
   * Sets how long it takes for a character to trigger showing.
   */
  void setNormalUpdateInterval(const float newUpdateInterval);
  
  /**
   * Sets how long it takes for a space to trigger showing.
   */
  void setBreakUpdateInterval(const float newBreakUpdateInterval);
  
  /**
   * Sets how long it takes for a character to show once it's been triggered.
   */
  void setCharacterRevealInterval(const float newCharacterRevealInterval);
  
protected:
  int currentCharacter;
  float normalUpdateInterval;
  float breakUpdateInterval;
  float characterRevealInterval;
  
  CCLabelBMFont *label;
  virtual void showNextCharacter();
};
#endif /* defined(__CCTextScroller__) */