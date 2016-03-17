#include "CmdLoarder.h"
#include <Stream.h>
#include <Arduino.h>
#include <ctype.h>

CmdLoarder Command;

CmdLoarder::CmdLoarder()
: LoarderDefined(false)
, Enable(true)
, cmdLoarder(nullptr)
, MatchEnable(true)
{

}
CmdLoarder::CmdLoarder(Stream& s)
: LoarderDefined(false)
, Enable(true)
, cmdLoarder(nullptr)
, MatchEnable(true)
{
    setLoadFrom(s);
}
void CmdLoarder::setLoadFrom(Stream& s)
{
    if(&s)
    {
        cmdLoarder = &s;
        LoarderDefined = true;
    }
    else
    {
        LoarderDefined = false;
    }
}
void CmdLoarder::setDefaultLoarder(void)
{
    Serial.begin(9600);
    setLoadFrom(Serial);
}
void CmdLoarder::removeLoarder()
{
    cmdLoarder = NULL;
    LoarderDefined = false;
}


int CmdLoarder::available(void)
{
    if(Enable && LoarderDefined)
        return cmdLoarder->available();
    else
        return 0;
}
int CmdLoarder::peek(void)
{
    if(Enable && LoarderDefined)
        return cmdLoarder->peek();
    else
        return 0;
}
int CmdLoarder::read(void)
{
    int val = cmdLoarder->read();
    if(MatchEnable)
    {
        for(int i = 0; i<_matchList.size(); i++)
        {
            _matchList[i].Getchar((char)val);
        }
    }
    return (Enable && LoarderDefined)? val : 0;
}
void CmdLoarder::flush(void)
{
    if(Enable && LoarderDefined)
        cmdLoarder->flush();
}
size_t CmdLoarder::write(uint8_t b)
{
    if(Enable && LoarderDefined)
        return cmdLoarder->write(b);
    else
        return 0;
}

void CmdLoarder::addMatchKey(String key, MATCHHANDLE handle, bool ignoreCase)
{
    Match newMatch(key, handle, ignoreCase);
    _matchList.push_back(newMatch);
}

void CmdLoarder::delMatchKey(String key)
{
    for(MATCHLIST::iterator it=_matchList.begin(); it!= _matchList.end(); )
    {
        if((*it).Key == key)
            it = _matchList.erase(it);
        else
            ++it;
    }
}


void CmdLoarder::fresh()
{
    int n = available();
    if(n)
    {
        char buf[n];
        readBytes(buf, n);

        for(int i =0; i<_matchList.size(); i++)
            _matchList[i].CallEvent();
    }
}

/*****************************************************************************/


Match::Match()
{
    Set("", NULL, false);
}
Match::Match(String key, MATCHHANDLE handle, bool ignoreCase)
{
    Set(key, handle, ignoreCase);
}
void Match::Set(String key, MATCHHANDLE handle, bool ignoreCase)
{
    Key = key;
    _Handle = handle;
    keyLength = Key.length();
    _IgnoreCase = ignoreCase;
    curIndex = 0;
    Matched = false;
}
bool charMatch(char a, char b, bool ignoreCase)
{
    char a1 = a;
    char b1 = b;
    if(ignoreCase)
    {
        a1 = tolower(a);
        b1 = tolower(b);
    }
    return (a1 == b1);
}
void Match::Getchar(char revChar)
{
    if(!Matched)
    {
        char curMachingChar = Key.charAt(curIndex);
        curIndex = charMatch(revChar, curMachingChar, _IgnoreCase)? curIndex+1 : 0;
        Matched = (curIndex >= keyLength)? true : false;
    }
}

void Match::Reset()
{
    Matched = false;
    curIndex = 0;
}
void Match::CallEvent()
{
    if(Matched && (_Handle!= NULL))
    {
        (*_Handle)(Key);
        Reset();
    }
}
