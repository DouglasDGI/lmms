/*
 * Microwave.h - declaration of class Microwave (a wavetable synthesizer)
 *
 * Copyright (c) 2019 Robert Black AKA DouglasDGI AKA Lost Robot <r94231/at/gmail/dot/com>
 * 
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef Microwave_H
#define Microwave_H

#include "Instrument.h"
#include "InstrumentView.h"
#include "Graph.h"
#include "Knob.h"
#include "PixmapButton.h"
#include "LedCheckbox.h"
#include "MemoryManager.h"
#include "LcdSpinBox.h"
#include "SampleBuffer.h"
#include "ComboBox.h"
#include "stdshims.h"
#include <QScrollBar>
#include <QLabel>
#include <QPlainTextEdit>


class oscillator;
class MicrowaveView;

class Microwave : public Instrument
{
	Q_OBJECT

#define setwavemodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Pulse Width" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Weird 1" ), make_unique<PluginPixmapLoader>( "noise" ) );\
		name ->addItem( tr( "Weird 2" ), make_unique<PluginPixmapLoader>( "noise" ) );\
		name ->addItem( tr( "Asym To Right" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Asym To Left" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Stretch From Center" ), make_unique<PluginPixmapLoader>( "sinabs" ) );\
		name ->addItem( tr( "Squish To Center" ), make_unique<PluginPixmapLoader>( "exp" ) );\
		name ->addItem( tr( "Stretch And Squish" ), make_unique<PluginPixmapLoader>( "tri" ) );\
		name ->addItem( tr( "Cut Off Right" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Cut Off Left" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Squarify" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Pulsify" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Flip" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Clip" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Inverse Clip" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Sine" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Atan" ), make_unique<PluginPixmapLoader>( "tri" ) );

#define modsectionsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Main OSC" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Sub OSC" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Sample OSC" ), make_unique<PluginPixmapLoader>( "noise" ) );\
		name ->addItem( tr( "Matrix" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Filter Input" ), make_unique<PluginPixmapLoader>( "moog" ) );\
		name ->addItem( tr( "Filter Parameters" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Macro" ), make_unique<PluginPixmapLoader>( "letter_m" ) );

#define mainoscsignalsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Morph" ), make_unique<PluginPixmapLoader>( "tri" ) );\
		name ->addItem( tr( "Range" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Modify" ), make_unique<PluginPixmapLoader>( "moog" ) );\
		name ->addItem( tr( "Detune" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Phase" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Volume" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Panning" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Unison Number" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Unison Detune" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Unison Morph" ), make_unique<PluginPixmapLoader>( "tri" ) );\
		name ->addItem( tr( "Unison Modify" ), make_unique<PluginPixmapLoader>( "moog" ) );

#define subsignalsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Detune" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Phase" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Volume" ), make_unique<PluginPixmapLoader>( "ramp" ) );

#define samplesignalsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Detune" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Phase" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Volume" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Panning" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Length" ), make_unique<PluginPixmapLoader>( "sin" ) );

#define matrixsignalsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Amount" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Curve" ), make_unique<PluginPixmapLoader>( "moog" ) );\
		name ->addItem( tr( "Secondary Amount" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Secondary Curve" ), make_unique<PluginPixmapLoader>( "moog" ) );

#define filtersignalsmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Cutoff Frequency" ), make_unique<PluginPixmapLoader>( "moog" ) );\
		name ->addItem( tr( "Resonance" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "db Gain" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Filter Type" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Slope" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Input Volume" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Output Volume" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Wet/Dry" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Balance/Panning" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Saturation" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Feedback" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Detune" ), make_unique<PluginPixmapLoader>( "ramp" ) );

#define modinmodel( name )\
		name ->addItem( tr( "None" ), make_unique<PluginPixmapLoader>( "none" ) );\
		name ->addItem( tr( "Main OSC" ), make_unique<PluginPixmapLoader>( "sqr" ) );\
		name ->addItem( tr( "Sub OSC" ), make_unique<PluginPixmapLoader>( "sin" ) );\
		name ->addItem( tr( "Sample OSC" ), make_unique<PluginPixmapLoader>( "noise" ) );\
		name ->addItem( tr( "Filter Output" ), make_unique<PluginPixmapLoader>( "moog" ) );\
		name ->addItem( tr( "Velocity" ), make_unique<PluginPixmapLoader>( "saw" ) );\
		name ->addItem( tr( "Panning" ), make_unique<PluginPixmapLoader>( "ramp" ) );\
		name ->addItem( tr( "Humanizer" ), make_unique<PluginPixmapLoader>( "sinabs" ) );\
		name ->addItem( tr( "Macro" ), make_unique<PluginPixmapLoader>( "letter_m" ) );

#define mod8model( name )\
		name ->addItem( tr( "1" ), make_unique<PluginPixmapLoader>( "number_1" ) );\
		name ->addItem( tr( "2" ), make_unique<PluginPixmapLoader>( "number_2" ) );\
		name ->addItem( tr( "3" ), make_unique<PluginPixmapLoader>( "number_3" ) );\
		name ->addItem( tr( "4" ), make_unique<PluginPixmapLoader>( "number_4" ) );\
		name ->addItem( tr( "5" ), make_unique<PluginPixmapLoader>( "number_5" ) );\
		name ->addItem( tr( "6" ), make_unique<PluginPixmapLoader>( "number_6" ) );\
		name ->addItem( tr( "7" ), make_unique<PluginPixmapLoader>( "number_7" ) );\
		name ->addItem( tr( "8" ), make_unique<PluginPixmapLoader>( "number_8" ) );

#define filtertypesmodel( name )\
		name ->addItem( tr( "Lowpass" ), make_unique<PluginPixmapLoader>( "filter_lowpass" ) );\
		name ->addItem( tr( "Highpass" ), make_unique<PluginPixmapLoader>( "filter_highpass" ) );\
		name ->addItem( tr( "Bandpass" ), make_unique<PluginPixmapLoader>( "filter_bandpass" ) );\
		name ->addItem( tr( "Low Shelf" ), make_unique<PluginPixmapLoader>( "filter_lowshelf" ) );\
		name ->addItem( tr( "High Shelf" ), make_unique<PluginPixmapLoader>( "filter_highshelf" ) );\
		name ->addItem( tr( "Peak" ), make_unique<PluginPixmapLoader>( "filter_peak" ) );\
		name ->addItem( tr( "Notch" ), make_unique<PluginPixmapLoader>( "filter_notch" ) );\
		name ->addItem( tr( "Allpass" ), make_unique<PluginPixmapLoader>( "filter_allpass" ) );\
		name ->addItem( tr( "Moog Lowpass (Note: Slope is doubled)" ), make_unique<PluginPixmapLoader>( "filter_moog" ) );

#define filterslopesmodel( name )\
		name ->addItem( tr( "12 db" ), make_unique<PluginPixmapLoader>( "number_1" ) );\
		name ->addItem( tr( "24 db" ), make_unique<PluginPixmapLoader>( "number_2" ) );\
		name ->addItem( tr( "36 db" ), make_unique<PluginPixmapLoader>( "number_3" ) );\
		name ->addItem( tr( "48 db" ), make_unique<PluginPixmapLoader>( "number_4" ) );\
		name ->addItem( tr( "60 db" ), make_unique<PluginPixmapLoader>( "number_5" ) );\
		name ->addItem( tr( "72 db" ), make_unique<PluginPixmapLoader>( "number_6" ) );\
		name ->addItem( tr( "84 db" ), make_unique<PluginPixmapLoader>( "number_7" ) );\
		name ->addItem( tr( "96 db" ), make_unique<PluginPixmapLoader>( "number_8" ) );

#define modcombinetypemodel( name )\
		name ->addItem( tr( "Add Bidirectional" ), make_unique<PluginPixmapLoader>( "number_1" ) );\
		name ->addItem( tr( "Multiply Bidirectional" ), make_unique<PluginPixmapLoader>( "number_2" ) );\
		name ->addItem( tr( "Add Unidirectional" ), make_unique<PluginPixmapLoader>( "number_3" ) );\
		name ->addItem( tr( "Multiply Unidirectional" ), make_unique<PluginPixmapLoader>( "number_4" ) );

#define oversamplemodel( name )\
		name.addItem( tr( "1x" ), make_unique<PluginPixmapLoader>( "number_1" ) );\
		name.addItem( tr( "2x" ), make_unique<PluginPixmapLoader>( "number_2" ) );\
		name.addItem( tr( "3x" ), make_unique<PluginPixmapLoader>( "number_3" ) );\
		name.addItem( tr( "4x" ), make_unique<PluginPixmapLoader>( "number_4" ) );\
		name.addItem( tr( "5x" ), make_unique<PluginPixmapLoader>( "number_5" ) );\
		name.addItem( tr( "6x" ), make_unique<PluginPixmapLoader>( "number_6" ) );\
		name.addItem( tr( "7x" ), make_unique<PluginPixmapLoader>( "number_7" ) );\
		name.addItem( tr( "8x" ), make_unique<PluginPixmapLoader>( "number_8" ) );

#define loadmodemodel( name )\
		name.addItem( tr( "Load sample without changes" ) );\
		name.addItem( tr( "Load wavetable file" ) );\
		name.addItem( tr( "Autocorrelation method" ) );\
		name.addItem( tr( "Choose waveform length" ) );\
		name.addItem( tr( "Similarity Test Method" ) );\
		name.addItem( tr( "6x" ) );\
		name.addItem( tr( "7x" ) );\
		name.addItem( tr( "8x" ) );

public:
	Microwave(InstrumentTrack * _instrument_track );
	virtual ~Microwave();
	virtual PluginView * instantiateView( QWidget * _parent );
	virtual QString nodeName() const;
	virtual void saveSettings( QDomDocument & _doc, QDomElement & _parent );
	virtual void loadSettings( const QDomElement & _this );
	virtual void playNote( NotePlayHandle * _n, sampleFrame * _working_buffer );
	virtual void deleteNotePluginData( NotePlayHandle * _n );

	virtual f_cnt_t desiredReleaseFrames() const
	{
		return( 64 );
	}

	void switchMatrixSections( int source, int destination );

protected slots:
	void valueChanged( int, int );
	void morphMaxChanged();
	void sampLenChanged();
	void subSampLenChanged( int );
	void mainEnabledChanged( int );
	void subEnabledChanged( int );
	void modEnabledChanged( int );
	void filtEnabledChanged( int );
	void sampleEnabledChanged( int );
	void samplesChanged( int, int );

private:
	FloatModel  * morph[8];
	FloatModel  * range[8];
	FloatModel  * sampLen[8];
	FloatModel  visvol;
	FloatModel  * morphMax[8];
	ComboBoxModel * modifyMode[8];
	FloatModel  * modify[8];
	ComboBoxModel * modOutSec[64];
	ComboBoxModel * modOutSig[64];
	IntModel * modOutSecNum[64];
	ComboBoxModel * modIn[64];
	IntModel * modInNum[64];
	IntModel * modInOtherNum[64];
	FloatModel * modInAmnt[64];
	FloatModel * modInCurve[64];
	ComboBoxModel * modIn2[64];
	IntModel * modInNum2[64];
	IntModel * modInOtherNum2[64];
	FloatModel * modInAmnt2[64];
	FloatModel * modInCurve2[64];
	BoolModel * modEnabled[64];
	ComboBoxModel * modCombineType[64];
	BoolModel * modType[64];
	IntModel  modNum;
	FloatModel  * unisonVoices[8];
	FloatModel  * unisonDetune[8];
	FloatModel  * unisonMorph[8];
	FloatModel  * unisonModify[8];
	FloatModel  * detune[8];
	FloatModel  loadAlg;
	FloatModel  loadChnl;
	FloatModel  * phase[8];
	FloatModel  * phaseRand[8];
	FloatModel  * vol[8];
	BoolModel * enabled[8];
	BoolModel * muted[8];
	FloatModel  scroll;
	IntModel  subNum;
	IntModel  sampNum;
	IntModel  mainNum;
	ComboBoxModel  oversample;
	ComboBoxModel  loadMode;

	FloatModel  * pan[8];

	FloatModel  * filtInVol[8];
	ComboBoxModel  * filtType[8];
	ComboBoxModel  * filtSlope[8];
	FloatModel  * filtCutoff[8];
	FloatModel  * filtReso[8];
	FloatModel  * filtGain[8];
	FloatModel  * filtSatu[8];
	FloatModel  * filtWetDry[8];
	FloatModel  * filtBal[8];
	FloatModel  * filtOutVol[8];
	BoolModel  * filtEnabled[8];
	FloatModel  * filtFeedback[8];
	FloatModel  * filtDetune[8];// This changes the feedback delay time to change the pitch
	BoolModel  * filtKeytracking[8];
	BoolModel  * filtMuted[8];
	
	graphModel  graph;
	
	
	BoolModel visualize;
	BoolModel * subEnabled[64];
	FloatModel * subVol[64];
	FloatModel * subPhase[64];
	FloatModel * subPhaseRand[64];
	BoolModel * subMuted[64];
	BoolModel * subKeytrack[64];
	FloatModel * subDetune[64];
	FloatModel * subSampLen[64];
	BoolModel * subNoise[64];
	FloatModel * subPanning[64];
	FloatModel * subTempo[64];

	
	float sample_realindex[8][32] = {{0}};
	float sample_subindex[64] = {0};
	float waveforms[8][524288] = {{0}};
	int currentTab = 0;
	float subs[131072] = {0};
	float sampGraphs[1024] = {0};
	std::vector<float> samples[8][2];

	BoolModel * sampleEnabled[8];
	BoolModel * sampleGraphEnabled[8];
	BoolModel * sampleMuted[8];
	BoolModel * sampleKeytracking[8];
	BoolModel * sampleLoop[8];

	FloatModel * sampleVolume[8];
	FloatModel * samplePanning[8];
	FloatModel * sampleDetune[8];
	FloatModel * samplePhase[8];
	FloatModel * samplePhaseRand[8];
	FloatModel * sampleStart[8];
	FloatModel * sampleEnd[8];

	FloatModel  wtLoad1;
	FloatModel  wtLoad2;
	FloatModel  wtLoad3;
	FloatModel  wtLoad4;

	BoolModel  mainFlipped;
	BoolModel  subFlipped;

	FloatModel  * macro[8];

	SampleBuffer sampleBuffer;

	//Below is for passing to mSynth initialization
	int modifyModeArr[8] = {0};
	float modifyArr[8] = {0};
	float morphArr[8] = {0};
	float rangeArr[8] = {0};
	float unisonVoicesArr[8] = {0};
	float unisonDetuneArr[8] = {0};
	float unisonMorphArr[8] = {0};
	float unisonModifyArr[8] = {0};
	float morphMaxArr[8] = {0};
	float detuneArr[8] = {0};
	int sampLenArr[8] = {0};
	int modInArr[64] = {0};
	int modInNumArr[64] = {0};
	int modInOtherNumArr[64] = {0};
	float modInAmntArr[64] = {0};
	float modInCurveArr[64] = {0};
	int modIn2Arr[64] = {0};
	int modInNum2Arr[64] = {0};
	int modInOtherNum2Arr[64] = {0};
	float modInAmnt2Arr[64] = {0};
	float modInCurve2Arr[64] = {0};
	int modOutSecArr[64] = {0};
	int modOutSigArr[64] = {0};
	int modOutSecNumArr[64] = {0};
	bool modEnabledArr[64] = {false};
	int modCombineTypeArr[64] = {0};
	bool modTypeArr[64] = {0};
	float phaseArr[8] = {0};
	float phaseRandArr[8] = {0};
	float volArr[8] = {0};
	bool enabledArr[8] = {false};
	bool mutedArr[8] = {false};

	float panArr[8] = {0};
	
	bool subEnabledArr[64] = {false};
	float subVolArr[64] = {0};
	float subPhaseArr[64] = {0};
	float subPhaseRandArr[64] = {0};
	float subDetuneArr[64] = {0};
	bool subMutedArr[64] = {false};
	bool subKeytrackArr[64] = {false};
	float subSampLenArr[64] = {0};
	bool subNoiseArr[64] = {false};
	float subPanningArr[64] = {0};
	float subTempoArr[64] = {0};
	
	float filtInVolArr[8] = {0};
	int filtTypeArr[8] = {0};
	int filtSlopeArr[8] = {0};
	float filtCutoffArr[8] = {0};
	float filtResoArr[8] = {0};
	float filtGainArr[8] = {0};
	float filtSatuArr[8] = {0};
	float filtWetDryArr[8] = {0};
	float filtBalArr[8] = {0};
	float filtOutVolArr[8] = {0};
	bool filtEnabledArr[8] = {false};
	float filtFeedbackArr[8] = {0};
	float filtDetuneArr[8] = {0};
	bool filtKeytrackingArr[8] = {false};
	bool filtMutedArr[8] = {false};

	bool sampleEnabledArr[8] = {false};
	bool sampleGraphEnabledArr[8] = {false};
	bool sampleMutedArr[8] = {false};
	bool sampleKeytrackingArr[8] = {false};
	bool sampleLoopArr[8] = {false};

	float sampleVolumeArr[8] = {0};
	float samplePanningArr[8] = {0};
	float sampleDetuneArr[8] = {0};
	float samplePhaseArr[8] = {0};
	float samplePhaseRandArr[8] = {0};
	float sampleStartArr[8] = {0};
	float sampleEndArr[8] = {1, 1, 1, 1, 1, 1, 1, 1};

	float macroArr[8] = {0};
	//Above is for passing to mSynth initialization

	int maxMainEnabled = 0;// The highest number of main oscillator sections that must be looped through
	int maxModEnabled = 0;// The highest number of matrix sections that must be looped through
	int maxSubEnabled = 0;// The highest number of sub oscillator sections that must be looped through
	int maxSampleEnabled = 0;// The highest number of sample sections that must be looped through
	int maxFiltEnabled = 0;// The highest number of filter sections that must be looped through

	InstrumentTrack * microwaveTrack = this->instrumentTrack();
	
	friend class MicrowaveView;
	friend class mSynth;
};



class MicrowaveView : public InstrumentView
{
	Q_OBJECT
public:
	MicrowaveView( Instrument * _instrument,
					QWidget * _parent );

	virtual ~MicrowaveView() {};

protected slots:
	void updateScroll();
	void scrollReleased();
	void mainNumChanged();
	void subNumChanged();
	void sampNumChanged();
	void modOutSecChanged( int i );
	void modInChanged( int i );
	void tabChanged( int tabnum );
	void visualizeToggled( bool value );
	void sinWaveClicked();
	void triangleWaveClicked();
	void sqrWaveClicked();
	void sawWaveClicked();
	void noiseWaveClicked();
	void usrWaveClicked();
	void smoothClicked( void  );
	void chooseWavetableFile( );
	void openWavetableFile( QString fileName = "" );
	void openWavetableFileBtnClicked();
	void openSampleFile();
	void openSampleFileBtnClicked();

	void modUpClicked( int );
	void modDownClicked( int );

	void confirmWavetableLoadClicked();

	void tabBtnClicked( int );

	void manualBtnClicked();

	void updateBackground();

	void flipperClicked();

	void XBtnClicked();

private:
	virtual void modelChanged();

	void mouseMoveEvent( QMouseEvent * _me );
	void wheelEvent( QWheelEvent * _me );
	virtual void dropEvent( QDropEvent * _de );
	virtual void dragEnterEvent( QDragEnterEvent * _dee );

	PixmapButton * sinWaveBtn;
	PixmapButton * triangleWaveBtn;
	PixmapButton * sqrWaveBtn;
	PixmapButton * sawWaveBtn;
	PixmapButton * whiteNoiseWaveBtn;
	PixmapButton * smoothBtn;
	PixmapButton * usrWaveBtn;

	PixmapButton * sinWave2Btn;
	PixmapButton * triangleWave2Btn;
	PixmapButton * sqrWave2Btn;
	PixmapButton * sawWave2Btn;
	PixmapButton * whiteNoiseWave2Btn;
	PixmapButton * smooth2Btn;
	PixmapButton * usrWave2Btn;

	PixmapButton * XBtn;// For leaving wavetable loading section

	PixmapButton * openWavetableButton;
	PixmapButton * confirmLoadButton;
	PixmapButton * openSampleButton;

	PixmapButton * modUpArrow[64];
	PixmapButton * modDownArrow[64];

	PixmapButton * tab1Btn;
	PixmapButton * tab2Btn;
	PixmapButton * tab3Btn;
	PixmapButton * tab4Btn;
	PixmapButton * tab5Btn;
	PixmapButton * tab6Btn;

	PixmapButton * mainFlipBtn;
	PixmapButton * subFlipBtn;

	PixmapButton * manualBtn;

	Knob * morphKnob[8];
	Knob * rangeKnob[8];
	Knob * visvolKnob;
	Knob * sampLenKnob[8];
	Knob * morphMaxKnob[8];
	Knob * unisonVoicesKnob[8];
	Knob * unisonDetuneKnob[8];
	Knob * unisonMorphKnob[8];
	Knob * unisonModifyKnob[8];
	Knob * detuneKnob[8];
	Knob * loadAlgKnob;
	Knob * loadChnlKnob;
	Knob * phaseKnob[8];
	Knob * phaseRandKnob[8];
	Knob * volKnob[8];
	LedCheckBox * enabledToggle[8];
	LedCheckBox * mutedToggle[8];
	Knob * scrollKnob;
	Knob * panKnob[8];

	Knob * filtInVolKnob[8];
	ComboBox * filtTypeBox[8];
	ComboBox * filtSlopeBox[8];
	Knob * filtCutoffKnob[8];
	Knob * filtResoKnob[8];
	Knob * filtGainKnob[8];
	Knob * filtSatuKnob[8];
	Knob * filtWetDryKnob[8];
	Knob * filtBalKnob[8];
	Knob * filtOutVolKnob[8];
	LedCheckBox * filtEnabledToggle[8];
	Knob * filtFeedbackKnob[8];
	Knob * filtDetuneKnob[8];
	LedCheckBox * filtKeytrackingToggle[8];
	LedCheckBox * filtMutedToggle[8];

	LcdSpinBox * subNumBox;
	LcdSpinBox * sampNumBox;
	LcdSpinBox * mainNumBox;

	ComboBox * oversampleBox;
	ComboBox * loadModeBox;

	ComboBox * modifyModeBox[8];
	Knob * modifyKnob[8];
	ComboBox * modOutSecBox[64];
	ComboBox * modOutSigBox[64];
	LcdSpinBox * modOutSecNumBox[64];
	ComboBox * modInBox[64];
	LcdSpinBox * modInNumBox[64];
	LcdSpinBox * modInOtherNumBox[64];
	Knob * modInAmntKnob[64];
	Knob * modInCurveKnob[64];
	ComboBox * modInBox2[64];
	LcdSpinBox * modInNumBox2[64];
	LcdSpinBox * modInOtherNumBox2[64];
	Knob * modInAmntKnob2[64];
	Knob * modInCurveKnob2[64];
	LedCheckBox * modEnabledToggle[64];
	ComboBox * modCombineTypeBox[64];
	LedCheckBox * modTypeToggle[64];

	LcdSpinBox * modNumBox;
	
	static QPixmap * s_artwork;

	Graph * graph;
	LedCheckBox * visualizeToggle;
	LedCheckBox * subEnabledToggle[64];
	Knob * subVolKnob[64];
	Knob * subPhaseKnob[64];
	Knob * subPhaseRandKnob[64];
	Knob * subDetuneKnob[64];
	LedCheckBox * subMutedToggle[64];
	LedCheckBox * subKeytrackToggle[64];
	Knob * subSampLenKnob[64];
	LedCheckBox * subNoiseToggle[64];
	Knob * subPanningKnob[64];
	Knob * subTempoKnob[64];

	LedCheckBox * sampleEnabledToggle[8];
	LedCheckBox * sampleGraphEnabledToggle[8];
	LedCheckBox * sampleMutedToggle[8];
	LedCheckBox * sampleKeytrackingToggle[8];
	LedCheckBox * sampleLoopToggle[8];

	Knob * sampleVolumeKnob[8];
	Knob * samplePanningKnob[8];
	Knob * sampleDetuneKnob[8];
	Knob * samplePhaseKnob[8];
	Knob * samplePhaseRandKnob[8];
	Knob * sampleStartKnob[8];
	Knob * sampleEndKnob[8];

	Knob * wtLoad1Knob;
	Knob * wtLoad2Knob;
	Knob * wtLoad3Knob;
	Knob * wtLoad4Knob;

	Knob * macroKnob[8];

	QScrollBar * effectScrollBar;
	QScrollBar * matrixScrollBar;

	QLabel * filtForegroundLabel;
	QLabel * filtBoxesLabel;
	QLabel * matrixForegroundLabel;
	QLabel * matrixBoxesLabel;

	QPalette pal = QPalette();
	QPixmap tab1ArtworkImg = PLUGIN_NAME::getIconPixmap("tab1_artwork");
	QPixmap tab1FlippedArtworkImg = PLUGIN_NAME::getIconPixmap("tab1_artwork_flipped");
	QPixmap tab2ArtworkImg = PLUGIN_NAME::getIconPixmap("tab2_artwork");
	QPixmap tab2FlippedArtworkImg = PLUGIN_NAME::getIconPixmap("tab2_artwork_flipped");
	QPixmap tab3ArtworkImg = PLUGIN_NAME::getIconPixmap("tab3_artwork");
	QPixmap tab4ArtworkImg = PLUGIN_NAME::getIconPixmap("tab4_artwork");
	QPixmap tab5ArtworkImg = PLUGIN_NAME::getIconPixmap("tab5_artwork");
	QPixmap tab6ArtworkImg = PLUGIN_NAME::getIconPixmap("tab6_artwork");
	QPixmap tab7ArtworkImg = PLUGIN_NAME::getIconPixmap("tab7_artwork");

	QString wavetableFileName = "";

	Microwave * microwave;

	float temp1;
	float temp2;

	friend class mSynth;
};


class mSynth
{
	MM_OPERATORS
public:
	mSynth( NotePlayHandle * _nph,
			const sample_rate_t _sample_rate,
			float * phaseRand,
			int * modifyModeVal, float * modifyVal, float * morphVal, float * rangeVal, float * unisonVoices, float * unisonDetune, float * unisonMorph, float * unisonModify, float * morphMaxVal, float * detuneVal, float waveforms[8][524288], float * subs, bool * subEnabled, float * subVol, float * subPhase, float * subPhaseRand, float * subDetune, bool * subMuted, bool * subKeytrack, float * subSampLen, bool * subNoise, int * sampLen, int * modIn, int * modInNum, int * modInOtherNum, float * modInAmnt, float * modInCurve, int * modIn2, int * modInNum2, int * modInOtherNum2, float * modInAmnt2, float * modInCurve2, int * modOutSec, int * modOutSig, int * modOutSecNum, int * modCombineType, bool * modType, float * phase, float * vol, float * filtInVol, int * filtType, int * filtSlope, float * filtCutoff, float * filtReso, float * filtGain, float * filtSatu, float * filtWetDry, float * filtBal, float * filtOutVol, bool * filtEnabled, bool * enabled, bool * modEnabled, float * sampGraphs, bool * muted, bool * sampleEnabled, bool * sampleGraphEnabled, bool * sampleMuted, bool * sampleKeytracking, bool * sampleLoop, float * sampleVolume, float * samplePanning, float * sampleDetune, float * samplePhase, float * samplePhaseRand, std::vector<float> (&samples)[8][2], float * filtFeedback, float * filtDetune, bool * filtKeytracking, float * subPanning, float * sampleStart, float * sampleEnd, float * pan, float * subTempo, float * macro, bool * filtMuted );
	virtual ~mSynth();
	
	std::vector<float> nextStringSample( float (&waveforms)[8][524288], float * subs, float * sampGraphs, std::vector<float> (&samples)[8][2], int maxFiltEnabled, int maxModEnabled, int maxSubEnabled, int maxSampleEnabled, int maxMainEnabled, int sample_rate );

	inline float detuneWithCents( float pitchValue, float detuneValue );

	void refreshValue( int which, int num );

private:
	float sample_realindex[8][32] = {(0)};
	float sample_subindex[64] = {0};
	float sample_sampleindex[8] = {0};
	NotePlayHandle* nph;
	const sample_rate_t sample_rate;

	int noteDuration;
	float noteFreq = 0;

	float lastMainOscVal[8][2] = {{0}};
	float lastSubVal[64][2] = {{0}};
	float sample_step_sub = 0;
	float noiseSampRand = 0;
	float lastSampleVal[8][2] = {{0}};
	float sample_step_sample = 0;

	float lastMainOscEnvVal[8][2] = {{0}};
	float lastSubEnvVal[64][2] = {{0}};
	float lastSampleEnvVal[8][2] = {{0}};

	bool lastMainOscEnvDone[8] = {false};
	bool lastSubEnvDone[64] = {false};
	bool lastSampleEnvDone[8] = {false};

	int loopStart = 0;
	int loopEnd = 0;
	float currentRangeValInvert = 0;
	int currentSampLen = 0;
	int currentIndex = 0;

	float filtInputs[8][2] = {{0}};// [filter number][channel]
	float filtOutputs[8][2] = {{0}};// [filter number][channel]
	float filtPrevSampIn[8][8][5][2] = {{{{0}}}};// [filter number][slope][samples back in time][channel]
	float filtPrevSampOut[8][8][5][2] = {{{{0}}}};// [filter number][slope][samples back in time][channel]
	float filtModOutputs[8][2] = {{0}};// [filter number][channel]

	std::vector<float> filtDelayBuf[8][2];// [filter number][channel]

	float filty1[2] = {0};
	float filty2[2] = {0};
	float filty3[2] = {0};
	float filty4[2] = {0};
	float filtoldx[2] = {0};
	float filtoldy1[2] = {0};
	float filtoldy2[2] = {0};
	float filtoldy3[2] = {0};
	float filtx[2] = {0};

	std::vector<int> modValType;
	std::vector<int> modValNum;



	int modifyModeVal[8];
	float modifyVal[8];
	float morphVal[8];
	float rangeVal[8];
	float unisonVoices[8];
	float unisonDetune[8];
	float unisonMorph[8];
	float unisonModify[8];
	float morphMaxVal[8];
	float detuneVal[8];
	int sampLen[8];
	int modIn[64];
	int modInNum[64];
	int modInOtherNum[64];
	float modInAmnt[64];
	float modInCurve[64];
	int modIn2[64];
	int modInNum2[64];
	int modInOtherNum2[64];
	float modInAmnt2[64];
	float modInCurve2[64];
	int modOutSec[64];
	int modOutSig[64];
	int modOutSecNum[64];
	bool modEnabled[64];
	int modCombineType[64];
	bool modType[64];
	float phase[8];
	float phaseRand[8];
	float vol[8];
	bool enabled[8];
	bool muted[8];
	float pan[8];
	
	bool subEnabled[64];
	float subVol[64];
	float subPhase[64];
	float subPhaseRand[64];
	float subDetune[64];
	bool subMuted[64];
	bool subKeytrack[64];
	float subSampLen[64];
	bool subNoise[64];
	float subPanning[64];
	float subTempo[64];
	
	float filtInVol[8];
	int filtType[8];
	int filtSlope[8];
	float filtCutoff[8];
	float filtReso[8];
	float filtGain[8];
	float filtSatu[8];
	float filtWetDry[8];
	float filtBal[8];
	float filtOutVol[8];
	bool filtEnabled[8];
	float filtFeedback[8];
	float filtDetune[8];
	bool filtKeytracking[8];
	bool filtMuted[8];

	bool sampleEnabled[8];
	bool sampleGraphEnabled[8];
	bool sampleMuted[8];
	bool sampleKeytracking[8];
	bool sampleLoop[8];

	float sampleVolume[8];
	float samplePanning[8];
	float sampleDetune[8];
	float samplePhase[8];
	float samplePhaseRand[8];
	float sampleStart[8];
	float sampleEnd[8];

	float cutoff;
	int mode;
	float reso;
	float dbgain;
	float Fs;
	float a0;
	float a1;
	float a2;
	float b0;
	float b1;
	float b2;
	float alpha;
	float w0;
	float A;
	float f;
	float k;
	float p;
	float scale;
	float r;

	float humanizer[8] = {0};

	float unisonDetuneAmounts[8][32] = {{0}};

	float temp1;
	float temp2;
	float temp3;

	float curModVal[2] = {0};
	float curModVal2[2] = {0};
	float curModValCurve[2] = {0};
	float curModVal2Curve[2] = {0};
	float comboModVal[2] = {0};
	float comboModValMono = 0;

	float sample_morerealindex[8][32] = {{0}};
	float sample_step[8][32] = {{0}};
	float sample_length_modify[8][32] = {{0}};

	float unisonVoicesMinusOne = 0;

	bool updateFrequency = 0;

	float macro[8];

	friend class Microwave;
	
};


class MicrowaveManualView: public QTextEdit
{
	Q_OBJECT
public:
	static MicrowaveManualView* getInstance()
	{
		static MicrowaveManualView instance;
		return &instance;
	}
	static void finalize()
	{
	}

private:
	MicrowaveManualView();
	static QString s_manualText;
};




#endif
