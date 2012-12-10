/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
 * This software is released under the The BSD-2-Clause License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LIERO_CONSTANTS_HPP
#define LIERO_CONSTANTS_HPP

#include <string>

enum
{
	NRInitialLength,
	NRAttachLength,

	MinBounceUp,
	MinBounceDown,
	MinBounceLeft,
	MinBounceRight,
	WormGravity,
	WalkVelLeft,
	MaxVelLeft,
	WalkVelRight,
	MaxVelRight,
	JumpForce,
	MaxAimVelLeft,
	AimAccLeft,
	MaxAimVelRight,
	AimAccRight,
	NinjaropeGravity,
	NRMinLength,
	NRMaxLength,
	BonusGravity,

	WormFricMult,
	WormFricDiv,
	WormMinSpawnDistLast,
	WormMinSpawnDistEnemy,
	WormSpawnRectX,
	WormSpawnRectY,
	WormSpawnRectW,
	WormSpawnRectH,
	AimFricMult,
	AimFricDiv,
	NRThrowVelX,
	NRThrowVelY,
	NRForceShlX,
	NRForceDivX,
	NRForceShlY,
	NRForceDivY,
	NRForceLenShl,
	BonusBounceMul,
	BonusBounceDiv,
	BonusFlickerTime,

	AimMaxRight,
	AimMinRight,
	AimMaxLeft,
	AimMinLeft,

	NRPullVel,
	NRReleaseVel,

	NRColourBegin,
	NRColourEnd,
	BonusExplodeRisk,
	BonusHealthVar,
	BonusMinHealth,
	LaserWeapon,
	FirstBloodColour,
	NumBloodColours,

	BObjGravity,

	BonusDropChance,
	SplinterLarpaVelDiv,
	SplinterCracklerVelDiv,

	BloodStepUp,
	BloodStepDown,
	BloodLimit,

	// FallDamage hack
	FallDamageRight,
	FallDamageLeft,
	FallDamageDown,
	FallDamageUp,

	// WormFloat hack
	WormFloatLevel,
	WormFloatPower,

	// BonusSpawn hack
	BonusSpawnRectX,
	BonusSpawnRectY,
	BonusSpawnRectW, // This is used even when the hack isn't enabled
	BonusSpawnRectH, // -==-

	// RemExp hack
	RemExpObject,

	MaxC
};

enum
{
	InitSound,
	LoadingSounds,
	LoadingAndThinking,
	OK,
	OK2,
	PressAnyKey,
	CommittedSuicideMsg,
	KilledMsg,
	YoureIt,

	Init_BaseIO,
	Init_IRQ,
	Init_DMA8,
	Init_DMA16,

	Init_DSPVersion,
	Init_Colon,
	Init_16bit,
	Init_Autoinit,

	Init_XMSSucc,

	Init_FreeXMS,
	Init_k,

	MaxS
};

enum
{
	HFallDamage,
	HBonusReloadOnly,
	HBonusSpawnRect,
	HBonusOnlyHealth,
	HBonusOnlyWeapon,
	HBonusDisable,
	HWormFloat,
	HRemExp,
	HSignedRecoil,

	HAirJump,
	HMultiJump,

	MaxH
};

// TODO: Move these to Common

#endif // LIERO_CONSTANTS_HPP
