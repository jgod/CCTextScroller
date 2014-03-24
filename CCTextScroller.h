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
                                      const bool startNow = true);
  virtual void onExit();
  
  /**
   * Starts scheduling updates to trigger showing characters.
   */
  virtual void start();
  
  /**
   * Hides all characters, keeping the same label. Sets current character to 0.
   */
  virtual void reset();
  
  /**
   * Uses current configuration to print string, taking care of the "magic".
   * Optional callback to be called when it's done printing.
   */
  const bool print(const std::string string,
                   CCAction* const extraCallback = NULL);
  
  // Getters and setters
  /**
   * Gets the label whose characters need to be shown.
   */
  CCLabelBMFont* const getLabel() const;
  
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
  
  /**
   * Sets an action to be run on the label when all the letters are done triggering.
   */
  void setOnDoneAction(CCAction* const newOnDoneAction);
  
protected:
  int currentCharacter;
  float normalUpdateInterval;
  float breakUpdateInterval;
  float characterRevealInterval;
  
  CCLabelBMFont *label;
  CCAction *onDone;
  virtual void showNextCharacter();
};
#endif /* defined(__CCTextScroller__) */