#ifndef HighScore_H
#define HighScore_H
/*
-----------------------------------------------------------------------------
 Class: HighScore

 Desc: Player data that persists between sessions.  Can be stored on a local
	disk or on a memory card.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "Grade.h"

struct XNode;
struct HighScore
{
	CString	sName;	// name that shows in the machine's ranking screen
	Grade grade;
	int iScore;
	float fPercentDP;
	float fSurviveSeconds;
	CString	sModifiers;
	time_t time;		// return value of time() when screenshot was taken
	CString sPlayerGuid;	// who made this high score
	CString sMachineGuid;	// where this high score was made


	HighScore() { Unset(); }
	void Unset()
	{
		sName = "";
		grade = GRADE_NO_DATA;
		iScore = 0;
		fPercentDP = 0;
		fSurviveSeconds = 0;
		sModifiers = "";
		time = 0;
		sPlayerGuid = "";
		sMachineGuid = "";
	}

	bool operator>=( const HighScore& other ) const;
	bool operator==( const HighScore& other ) const 
	{
#define COMPARE(x)	if( x!=other.x )	return false;
		COMPARE( sName );
		COMPARE( grade );
		COMPARE( iScore );
		COMPARE( fPercentDP );
		COMPARE( fSurviveSeconds );
		COMPARE( sModifiers );
		COMPARE( time );
		COMPARE( sPlayerGuid );
		COMPARE( sMachineGuid );
#undef COMPARE
		return true;
	}

	XNode* CreateNode() const;
	void LoadFromNode( const XNode* pNode );

	CString GetDisplayName() const;
};

struct HighScoreList
{
	int iNumTimesPlayed;
	vector<HighScore> vHighScores;

	
	HighScoreList()
	{
		iNumTimesPlayed = 0;
	}
	
	void Init();

	void AddHighScore( HighScore hs, int &iIndexOut );

	const HighScore& GetTopScore() const;

	XNode* CreateNode() const;
	void LoadFromNode( const XNode* pNode );
};


#endif
