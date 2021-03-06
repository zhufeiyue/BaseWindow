#pragma once
#include <Windows.h>

class ISyncVideo
{
public:
	enum {
		DontShowThisFrameNow,
		DoShowThisFrameNow,
		SkipThisFrame_ShowNext
	};
	ISyncVideo() { m_bPausePlay = false; }
	virtual ~ISyncVideo() {}
	virtual int IsSwitchToNextFrame(void*) = 0;
	void PausePlay(bool b) { m_bPausePlay = b; }
protected:
	bool m_bPausePlay;
};

class CSyncVideoByFrameRate : public ISyncVideo
{
public:
	CSyncVideoByFrameRate(LARGE_INTEGER frameInterval);
	int IsSwitchToNextFrame(void*);
protected:
	LARGE_INTEGER m_liMaxDisplay;
	LARGE_INTEGER m_liMinDisplay;
	LARGE_INTEGER m_liLast;
	LARGE_INTEGER m_liError;
	LARGE_INTEGER m_liFrameInterval;
};

class CSyncVideoByAudioTime : public ISyncVideo
{
public:
	CSyncVideoByAudioTime(double fr, double gap);
	int IsSwitchToNextFrame(void*);
protected:
	double m_dFrameRate;
	double m_dDisplayGap;
	// video to audio
	int m_iCountAdvance;
	int m_iCountFallBehind;
};