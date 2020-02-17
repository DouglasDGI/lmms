/*
 * PhaserControls.cpp
 *
 * Copyright (c) 2019 Lost Robot <r94231@gmail.com>
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


#include <QDomElement>

#include "PhaserControls.h"
#include "PhaserEffect.h"
#include "Engine.h"
#include "Song.h"
#include "GuiApplication.h"
#include "MainWindow.h"


const int PHA_DOT_SLIDER_LENGTH = 338;
const float PHA_MIN_FREQ = 20;
const float PHA_MAX_FREQ = 20000;


PhaserControls::PhaserControls( PhaserEffect* effect ) :
	EffectControls( effect ),
	m_effect( effect ),
	m_cutoffModel( 640.0f, 20.0f, 20000.0f, 0.01f, this, tr( "Cutoff" ) ),
	m_resonanceModel( 0.05f, 0.05f, 2.0f, 0.001f, this, tr( "Resonance" ) ),
	m_feedbackModel( 0.0f, -100.0f, 100.0f, 0.01f, this, tr( "Feedback" ) ),
	m_orderModel(8, 1, 32, this, tr("Order")),
	m_delayModel( 1.0f, 1.0f, 50.0f, 1.0f, this, tr( "Delay" ) ),
	m_rateModel( 10.0f, 0.01f, 60.0f, 0.001f, 60000.0, this, tr( "Rate" ) ),
	m_amountModel( 5.0f, 0.f, 5.0f, 0.01f, this, tr( "Amount" ) ),
	m_enableLFOModel( true , this, tr( "Enable LFO" ) ),
	m_phaseModel( 180.0f, 0.f, 360.0f, 0.1f, this, tr( "Phase" ) ),
	m_wetDryModel( 0.5f, 0.f, 1.0f, 0.01f, this, tr( "Wet/Dry" ) ),
	m_inFollowModel( 0.f, -15.f, 15.0f, 0.01f, this, tr( "Input Follow" ) ),
	m_attackModel( 500.0f, 0.0f, 2000.0f, 1.0f, this, tr( "Attack" ) ),
	m_releaseModel( 500.0f, 0.0f, 2000.0f, 1.0f, this, tr( "Release" ) ),
	m_outGainModel( 0.0, -60.0, 20.0, 0.01, this, tr( "Output gain" ) ),
	m_inGainModel( 0.0, -60.0, 20.0, 0.01, this, tr( "Input gain" ) )
{
	m_cutoffModel.setScaleLogarithmic(true);
	m_resonanceModel.setScaleLogarithmic(true);
	m_delayModel.setScaleLogarithmic(true);

	connect( Engine::mixer(), SIGNAL( sampleRateChanged() ), this, SLOT( changedSampleRate() ) );
	connect( Engine::getSong(), SIGNAL( playbackStateChanged() ), this, SLOT( changedPlaybackState() ) );

	connect( &m_phaseModel, SIGNAL( dataChanged() ), this, SLOT( updatePhase() ) );

	m_outPeakL = 0.0;
	m_outPeakR = 0.0;
}


PhaserControls::~PhaserControls()
{
}


void PhaserControls::saveSettings( QDomDocument& doc, QDomElement& _this )
{
	m_cutoffModel.saveSettings( doc, _this, "cutoff" );
	m_resonanceModel.saveSettings( doc, _this, "resonance" );
	m_feedbackModel.saveSettings( doc, _this, "feedback" );
	m_orderModel.saveSettings( doc, _this, "order" );
	m_delayModel.saveSettings( doc, _this, "delay" );
	m_rateModel.saveSettings( doc, _this, "rate" );
	m_enableLFOModel.saveSettings( doc, _this, "enableLFO" );
	m_amountModel.saveSettings( doc, _this, "amount" );
	m_phaseModel.saveSettings( doc, _this, "phase" );
	m_wetDryModel.saveSettings( doc, _this, "wetDry" );
	m_inFollowModel.saveSettings( doc, _this, "inFollow" );
	m_attackModel.saveSettings( doc, _this, "attack" );
	m_releaseModel.saveSettings( doc, _this, "release" );
	m_outGainModel.saveSettings( doc, _this, "outGain" );
	m_inGainModel.saveSettings( doc, _this, "inGain" );
}



void PhaserControls::loadSettings( const QDomElement& _this )
{
	m_cutoffModel.loadSettings( _this, "cutoff" );
	m_resonanceModel.loadSettings( _this, "resonance" );
	m_feedbackModel.loadSettings( _this, "feedback" );
	m_orderModel.loadSettings( _this, "order" );
	m_delayModel.loadSettings( _this, "delay" );
	m_rateModel.loadSettings( _this, "rate" );
	m_amountModel.loadSettings( _this, "amount" );
	m_enableLFOModel.loadSettings( _this, "enableLFO" );
	m_phaseModel.loadSettings( _this, "phase" );
	m_wetDryModel.loadSettings( _this, "wetDry" );
	m_inFollowModel.loadSettings( _this, "inFollow" );
	m_attackModel.loadSettings( _this, "attack" );
	m_releaseModel.loadSettings( _this, "release" );
	m_outGainModel.loadSettings( _this, "outGain" );
	m_inGainModel.loadSettings( _this, "inGain" );
}


void PhaserControls::changedSampleRate()
{
	m_effect->changeSampleRate();
}



void PhaserControls::changedPlaybackState()
{
	m_effect->restartLFO();
}


void PhaserControls::updatePhase()
{
	m_effect->m_lfo->setOffset(m_phaseModel.value() / 180 * D_PI);
}


