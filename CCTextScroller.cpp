//  CCTextScroller.cpp
//  Created by Justin Godesky on 3/11/14.

#include "CCTextScroller.h"

CCTextScroller::CCTextScroller() :
currentCharacter(0),
normalUpdateInterval(0.05f),
breakUpdateInterval(0.1f),
characterRevealInterval(0),
label(NULL)
{}

CCTextScroller::~CCTextScroller(){}
CCTextScroller* const CCTextScroller::create(CCLabelBMFont* const newLabel,
                                             const bool startShowingNow)
{
  CCTextScroller* const MESSAGE = CCTextScroller::create();
  MESSAGE->setLabel(newLabel);
  if (startShowingNow) {MESSAGE->startShowing();}
  return MESSAGE;
}

void CCTextScroller::onExit()
{
  this->stopAllActions();
  this->unscheduleAllSelectors();
  this->removeAllChildren();
}

void CCTextScroller::startShowing()
{
  if (!label) {reset();}
  
  this->addChild(label);
  label->setOpacity(0);
  this->schedule(schedule_selector(CCTextScroller::showNextCharacter));
}

// Any time something goes wrong, we can call this internally to reset the state.
void CCTextScroller::reset()
{
  this->unscheduleAllSelectors();
  
  if (label)
  {
    label->stopAllActions();
    label->setOpacity(0);
  }
  
  currentCharacter = 0;
}

void CCTextScroller::showNextCharacter()
{
  if (!label) {reset();}
  
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
    this->unschedule(schedule_selector(CCTextScroller::showNextCharacter));
  }
}

// Getters and setters
void CCTextScroller::setLabel(CCLabelBMFont* const newLabel) {label = newLabel;}
void CCTextScroller::setNormalUpdateInterval(const float newUpdateInterval) {normalUpdateInterval = newUpdateInterval;}
void CCTextScroller::setBreakUpdateInterval(const float newBreakUpdateInterval) {breakUpdateInterval = newBreakUpdateInterval;}
void CCTextScroller::setCharacterRevealInterval(const float newCharacterRevealInterval) {characterRevealInterval = newCharacterRevealInterval;}