#ifndef __CMDLOARDER__
#define __CMDLOARDER__

#include "Stream.h"
#include <String.h>
#include <vector>

using namespace std;

typedef void (*MATCHHANDLE)(String key);

struct Match
{
    private:
        int curIndex;
        int keyLength;
        MATCHHANDLE _Handle;
        bool _IgnoreCase;

    public:
        String Key;
        bool Matched;

        Match();
        Match(String key, MATCHHANDLE handle = NULL, bool ignoreCase = false);
        void Set(String key, MATCHHANDLE handle = NULL, bool ignoreCase = false);
        void Getchar(char revChar);
        void Reset();
        void CallEvent();
};

typedef vector<Match> MATCHLIST;

class CmdLoarder : public Stream
{
    private:
        MATCHLIST _matchList;
        Stream *cmdLoarder;

    public:
        bool LoarderDefined;
        bool Enable;
        bool MatchEnable;

        CmdLoarder();
        CmdLoarder(Stream& s);
        void setLoadFrom(Stream& s);
        void setDefaultLoarder(void);
        void removeLoarder();

        int available(void) override;
        int peek(void) override;
        int read(void) override;
        void flush(void) override;
		size_t write(uint8_t) override;

		void addMatchKey(String key, MATCHHANDLE handle = NULL, bool ignoreCase = false);
        void delMatchKey(String key);
        void fresh();
};


extern CmdLoarder Command;

#endif
