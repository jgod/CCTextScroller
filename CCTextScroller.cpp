//  CCTextScroller.cpp
//  Created by Justin Godesky on 3/11/14.

#include "CCTextScroller.h"

CCTextScroller::CCTextScroller() :
currentCharacter(0),
normalUpdateInterval(0.05f),
breakUpdateInterval(0.1f),
characterRevealInterval(0),
label(NULL),
onDone(NULL)
{}

CCTextScroller::~CCTextScroller(){}
CCTextScroller* const CCTextScroller::create(CCLabelBMFont* const newLabel,
                                             const bool startNow)
{
  CCTextScroller* const MESSAGE = CCTextScroller::create();
  
  if (newLabel)
  {
    MESSAGE->setLabel(newLabel);
    if (startNow) {MESSAGE->start();}
  }
  
  return MESSAGE;
}

void CCTextScroller::onExit()
{
  this->stopAllActions();
  this->unscheduleAllSelectors();
  this->removeAllChildren();
  
  // Clear out members in case things are still operating on them while CCTextScroller
  // is still being destroyed.
  label = NULL;
  onDone = NULL;
}

void CCTextScroller::start()
{
  if (label)
  {
    reset();
    this->schedule(schedule_selector(CCTextScroller::showNextCharacter));
  }
}

// Any time something goes wrong, we can call this internally to reset the state.
void CCTextScroller::reset()
{
  // Reset the label if it exists.
  if (label)
  {
    label->stopAllActions();
    label->setOpacity(0);
  }
  
  // Reset CCTextScroller.
  currentCharacter = 0;
  this->unscheduleAllSelectors();
}

void CCTextScroller::showNextCharacter()
{
  // Don't let an update happen if the label stopped existing.
  if (!label)
  {
    reset();
    return;
  }
  
  const std::string STRING = label->getString();
  if (currentCharacter < STRING.size())
  {
    CCSprite* const CURRENT_CHAR = dynamic_cast<CCSprite*>(label->getChildByTag(currentCharacter));
    if (CURRENT_CHAR)
    {
      CURRENT_CHAR->runAction(CCFadeIn::create(characterRevealInterval));
    }
    currentCharacter++;
    
    // Extra pauses for the next character when it's a space.
    const float UPDATE_INTERVAL = isspace(STRING.at(currentCharacter - 1)) ?
    breakUpdateInterval : normalUpdateInterval;
    this->schedule(schedule_selector(CCTextScroller::showNextCharacter), UPDATE_INTERVAL);
  }
  else
  {
    if (label && onDone)
    {
      label->stopAllActions();
      label->runAction(onDone);
      onDone->release();
      onDone = NULL;
    }
    this->unschedule(schedule_selector(CCTextScroller::showNextCharacter));
  }
}

CCLabelBMFont* const CCTextScroller::getLabel() const {return label;}
void CCTextScroller::setLabel(CCLabelBMFont* const newLabel)
{
  // Remove any already existing labels.
  if (label) {label->removeFromParent();}
  
  label = newLabel;
  this->addChild(label);
  
  // In case the label has changed while schedulers are still running, reset everything.
  reset();
}

void CCTextScroller::setNormalUpdateInterval(const float newUpdateInterval) {normalUpdateInterval = newUpdateInterval;}
void CCTextScroller::setBreakUpdateInterval(const float newBreakUpdateInterval) {breakUpdateInterval = newBreakUpdateInterval;}
void CCTextScroller::setCharacterRevealInterval(const float newCharacterRevealInterval) {characterRevealInterval = newCharacterRevealInterval;}
void CCTextScroller::setOnDoneAction(CCAction* const newOnDoneAction)
{
  // If an action has already been stored, clear it out.
  if (onDone)
  {
    onDone->release();
    onDone = NULL;
  }
  
  onDone = newOnDoneAction;
  onDone->retain();
}