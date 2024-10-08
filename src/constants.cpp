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

#include "constants.hpp"
#include "reader.hpp"
#include "game.hpp" // TODO: We should move Common somewhere else

#include <iostream>

#include "configHelper.hpp"

std::string valueConstantsNames[] =
{
	"NRInitialLength",
	"NRAttachLength",

	"MinBounceUp",
	"MinBounceDown",
	"MinBounceLeft",
	"MinBounceRight",
	"WormGravity",
	"WalkVelLeft",
	"MaxVelLeft",
	"WalkVelRight",
	"MaxVelRight",
	"JumpForce",
	"MaxAimVelLeft",
	"AimAccLeft",
	"MaxAimVelRight",
	"AimAccRight",
	"NinjaropeGravity",
	"NRMinLength",
	"NRMaxLength",
	"BonusGravity",

	"WormFricMult",
	"WormFricDiv",
	"WormMinSpawnDistLast",
	"WormMinSpawnDistEnemy",
	"WormSpawnRectX",
	"WormSpawnRectY",
	"WormSpawnRectW",
	"WormSpawnRectH",
	"AimFricMult",
	"AimFricDiv",
	"NRThrowVelX",
	"NRThrowVelY",
	"NRForceShlX",
	"NRForceDivX",
	"NRForceShlY",
	"NRForceDivY",
	"NRForceLenShl",
	"BonusBounceMul",
	"BonusBounceDiv",
	"BonusFlickerTime",


	"AimMaxRight",
	"AimMinRight",
	"AimMaxLeft",
	"AimMinLeft",

	"NRPullVel",
	"NRReleaseVel",

	"NRColourBegin",
	"NRColourEnd",
	"BonusExplodeRisk",
	"BonusHealthVar",
	"BonusMinHealth",
	"LaserWeapon",
	"FirstBloodColour",
	"NumBloodColours",

	"BObjGravity",

	"BonusDropChance",
	"SplinterLarpaVelDiv",
	"SplinterCracklerVelDiv",

	"BloodStepUp",
	"BloodStepDown",
	"BloodLimit",

	// FallDamage hack
	"FallDamageRight",
	"FallDamageLeft",
	"FallDamageDown",
	"FallDamageUp",

	// WormFloat hack
	"WormFloatLevel",
	"WormFloatPower",

	// BonusSpawn hack
	"BonusSpawnRectX",
	"BonusSpawnRectY",
	"BonusSpawnRectW", // This is used even when the hack isn't enabled
	"BonusSpawnRectH", // -==-

	// RemExp hack
	"RemExpObject"
};

std::string stringConstantsNames[] =
{
	"InitSound",
	"LoadingSounds",
	"LoadingAndThinking",
	"OK",
	"OK2",
	"PressAnyKey",
	"CommittedSuicideMsg",
	"KilledMsg",
	"YoureIt",

	"Init_BaseIO",
	"Init_IRQ",
	"Init_DMA8",
	"Init_DMA16",

	"Init_DSPVersion",
	"Init_Colon",
	"Init_16bit",
	"Init_Autoinit",

	"Init_XMSSucc",

	"Init_FreeXMS",
	"Init_k"
};

std::string hackConstantsNames[] =
{
	"HFallDamage",
	"HBonusReloadOnly",
	"HBonusSpawnRect",
	"HWormFloat",
	"HBonusOnlyHealth",
	"HBonusOnlyWeapon",
	"HBonusDisable",
	"HRemExp",
	"HSignedRecoil",

	"HAirJump",
	"HMultiJump"
};

int CSint32desc[][3] =
{
	{NRInitialLength, 0x32D7, 0x32DD},
	{NRAttachLength, 0xA679, 0xA67F},

	{0, -1, -1}
};

int CSint24desc[][3] =
{
	{MinBounceUp, 0x3B7D, 0x3B74},
	{MinBounceDown, 0x3B00, 0x3AF7},
	{MinBounceLeft, 0x3A83, 0x3A7A},
	{MinBounceRight, 0x3A06, 0x39FD},
	{WormGravity, 0x3BDE, 0x3BD7},
	{WalkVelLeft, 0x3F97, 0x3F9D},
	{MaxVelLeft, 0x3F8C, 0x3F83},
	{WalkVelRight, 0x4018, 0x401E},
	{MaxVelRight, 0x400D, 0x4004},
	{JumpForce, 0x3327, 0x332D},
	{MaxAimVelLeft, 0x30F2, 0x30E9},
	{AimAccLeft, 0x30FD, 0x3103},
	{MaxAimVelRight, 0x311A, 0x3111},
	{AimAccRight, 0x3125, 0x312B},
	{NinjaropeGravity, 0xA895, 0xA89B},
	{NRMinLength, 0x3206, 0x31FD},
	{NRMaxLength, 0x3229, 0x3220},

	{BonusGravity, 0x72C3, 0x72C9},
	{BObjGravity, 0x744A, 0x7450},



	// WormFloat hack
	{WormFloatPower, 0x29DB, 0x29E1},

	{0, -1, -1}
};

int CUint16desc[][2] =
{
	{BloodLimit, 0xE686},

	{0, -1}
};

int CSint16desc[][2] =
{
	{WormFricMult, 0x39BD},
	{WormFricDiv, 0x39C7},
	{WormMinSpawnDistLast, 0x242E},
	{WormMinSpawnDistEnemy, 0x244B},
	{WormSpawnRectX, 0x4913},
	{WormSpawnRectY, 0x4925},
	{WormSpawnRectW, 0x490B},
	{WormSpawnRectH, 0x491D},
	{AimFricMult, 0x3003},
	{AimFricDiv, 0x300D},

	{NRThrowVelX, 0x329B},
	{NRThrowVelY, 0x32BF},
	{NRForceShlX, 0xA8AD},
	{NRForceDivX, 0xA8B7},
	{NRForceShlY, 0xA8DA},
	{NRForceDivY, 0xA8E4},
	{NRForceLenShl, 0xA91E},

	{BonusBounceMul, 0x731F},
	{BonusBounceDiv, 0x7329},
	{BonusFlickerTime, 0x87B8},

	{BonusDropChance, 0xBECA},
	{SplinterLarpaVelDiv, 0x677D},
	{SplinterCracklerVelDiv, 0x67D0},


	// WormFloat hack
	{WormFloatLevel, 0x29D3},

	// BonusSpawnRect hack
	{BonusSpawnRectX, 0x2319},
	{BonusSpawnRectY, 0x2327},
	{BonusSpawnRectW, 0x2311}, // This is used even when the hack isn't enabled
	{BonusSpawnRectH, 0x231F}, // -==-

	{0, -1}
};

int CUint8desc[][2] =
{
	{AimMaxRight, 0x3030},
	{AimMinRight, 0x304A},
	{AimMaxLeft, 0x3066},
	{AimMinLeft, 0x3080},
	{NRColourBegin, 0x10FD2},
	{NRColourEnd, 0x11069},
	{BonusExplodeRisk, 0x2DB2},
	{BonusHealthVar, 0x2D56},
	{BonusMinHealth, 0x2D5D},
	{LaserWeapon, 0x7255},

	{FirstBloodColour, 0x2388},
	{NumBloodColours, 0x2381},

	{RemExpObject, 0x8F8B},

	{0, -1}
};

int CSint8desc[][2] =
{
	{NRPullVel, 0x31D0},
	{NRReleaseVel, 0x31F0},

	// FallDamage hack
	{FallDamageRight, 0x3A0E},
	{FallDamageLeft, 0x3A8B},
	{FallDamageDown, 0x3B08},
	{FallDamageUp, 0x3B85},

	{BloodStepUp, 0xE67B},
	{BloodStepDown, 0xE68E},

	{0, -1}
};

int Sstringdesc[][2] =
{
	{InitSound, 0x177F},
	{LoadingSounds, 0x18F2},

	{Init_BaseIO, 0x17DD},
	{Init_IRQ, 0x17E5},
	{Init_DMA8, 0x17EE},
	{Init_DMA16, 0x17F8},

	{Init_DSPVersion, 0x181E},
	{Init_Colon, 0x182B},
	{Init_16bit, 0x182F},
	{Init_Autoinit, 0x1840},

	{Init_XMSSucc, 0x189D},

	{Init_FreeXMS, 0x18C5},
	{Init_k, 0x18D8},

	{LoadingAndThinking, 0xFB92},
	{OK, 0xFBA8},
	{OK2, 0x190E},
	{PressAnyKey, 0xFBAB},

	{CommittedSuicideMsg, 0xE70C},
	{KilledMsg, 0xE71F},
	{YoureIt, 0x75C5},

	{0, -1}
};

struct HackDesc
{
	int which;
	int (*indicators)[2];
};

int hFallDamageInd[][2] =
{
	{0x3A0A, 0x26},
	{0x3A87, 0x26},
	{0x3B04, 0x26},
	{0x3B81, 0x26},

	{-1, 0}
};

int hBonusReloadOnlyInd[][2] =
{
	{0x2DB1, 0xEB}, // We check one byte only, because ProMode has a silly jump destination

	{-1, 0}
};

int hBonusSpawnRectInd[][2] =
{
	{0x2318, 0x05}, // These are the first bytes of the add instructions that offset the spawn
	{0x2323, 0x05},

	{-1, 0}
};

int hBonusOnlyHealthInd[][2] =
{
	{0x228B, 0xB0},
	{0x228C, 0x02},

	{-1, 0}
};

int hBonusOnlyWeaponInd[][2] =
{
	{0x228B, 0xB0},
	{0x228C, 0x01},

	{-1, 0}
};

int hBonusDisableInd[][2] =
{
	{0xBED3, 0xEB},

	{-1, 0}
};

int hWormFloatInd[][2] =
{
	{0x29D7, 0x26}, // 0x26 is the first byte of the sub instruction
	{0x29DA, 0x34}, // 0x34 is the offset to part of velY of the worm

	{-1, 0}
};

int hRemExpInd[][2] =
{
	// Start of the mov instruction that zeroes the timeout counter
	{0x8fc9, 0x26},
	{0x8fca, 0xc7},
	{-1, 0}
};

int hSignedRecoilInd[][2] =
{
	{0x38AC, 0x98},
	{0x38EC, 0x98},
	{-1, 0}
};

int hAirJumpInd[][2] =
{
	{0x3313, 0xEB},
	{0x3314, 0x06},
	{-1, 0}
};

int hMultiJumpInd[][2] =
{
	{0x331B, 0xEB},
	{0x331C, 0x06},
	{-1, 0}
};

HackDesc Hhackdesc[] =
{
	{HFallDamage, hFallDamageInd},
	{HBonusReloadOnly, hBonusReloadOnlyInd},
	{HBonusSpawnRect, hBonusSpawnRectInd},
	{HWormFloat, hWormFloatInd},
	{HBonusOnlyHealth, hBonusOnlyHealthInd},
	{HBonusOnlyWeapon, hBonusOnlyWeaponInd},
	{HBonusDisable, hBonusDisableInd},
	{HRemExp, hRemExpInd},
	{HSignedRecoil, hSignedRecoilInd},
	{HAirJump, hAirJumpInd},
	{HMultiJump, hMultiJumpInd},
	{0, 0}
};

void Common::loadConstantsFromEXE()
{
	FILE* exe = openLieroEXE();

	for(int i = 0; CSint32desc[i][1] >= 0; ++i)
	{
		fseek(exe, CSint32desc[i][1], SEEK_SET);
		int a = readUint16(exe);
		fseek(exe, CSint32desc[i][2], SEEK_SET);
		int b = readSint16(exe);
		C[CSint32desc[i][0]] = a + (b << 16);

		//std::cout << C[CSint32desc[i][0]] << std::endl;
	}

	for(int i = 0; CSint24desc[i][1] >= 0; ++i)
	{
		fseek(exe, CSint24desc[i][1], SEEK_SET);
		int a = readUint16(exe);
		fseek(exe, CSint24desc[i][2], SEEK_SET);
		int b = readSint8(exe);
		C[CSint24desc[i][0]] = a + (b << 16);

		//std::cout << C[CSint24desc[i][0]] << std::endl;
	}

	for(int i = 0; CSint16desc[i][1] >= 0; ++i)
	{
		fseek(exe, CSint16desc[i][1], SEEK_SET);
		C[CSint16desc[i][0]] = readSint16(exe);

		//std::cout << C[CSint16desc[i][0]] << std::endl;
	}

	for(int i = 0; CUint16desc[i][1] >= 0; ++i)
	{
		fseek(exe, CUint16desc[i][1], SEEK_SET);
		C[CUint16desc[i][0]] = readUint16(exe);

		//std::cout << C[CUint16desc[i][0]] << std::endl;
	}

	for(int i = 0; CSint8desc[i][1] >= 0; ++i)
	{
		fseek(exe, CSint8desc[i][1], SEEK_SET);
		C[CSint8desc[i][0]] = readSint8(exe);
	}

	for(int i = 0; CUint8desc[i][1] >= 0; ++i)
	{
		fseek(exe, CUint8desc[i][1], SEEK_SET);
		C[CUint8desc[i][0]] = readUint8(exe);

		//std::cout << C[CUint8desc[i][0]] << std::endl;
	}

	for(int i = 0; Sstringdesc[i][1] >= 0; ++i)
	{
		S[Sstringdesc[i][0]] = readPascalStringAt(exe, Sstringdesc[i][1]);
	}

	for(int i = 0; Hhackdesc[i].indicators; ++i)
	{
		int (*ind)[2] = Hhackdesc[i].indicators;
		bool active = true;
		for(; (*ind)[0] >= 0; ++ind)
		{
			std::fseek(exe, (*ind)[0], SEEK_SET);
			int b = std::fgetc(exe);
			if(b != (*ind)[1])
			{
				active = false;
				break;
			}
		}

		H[Hhackdesc[i].which] = active;
	}
}

void Common::loadConstantsFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &constants = cfg.lookup("Constants");

	const libconfig::Setting &vconstants = constants["Values"];
	for(int i = 0; i < MaxC; ++i)
	{
		C[i] = (int)vconstants[valueConstantsNames[i].c_str()];
	}

	const libconfig::Setting &sconstants = constants["Strings"];
	for(int i = 0; i < MaxS; ++i)
	{
		S[i]= (char const*)sconstants[stringConstantsNames[i].c_str()];
	}

	const libconfig::Setting &hconstants = constants["Hacks"];
	for(int i = 0; i < MaxH; ++i)
	{
		H[i] = (bool)hconstants[hackConstantsNames[i].c_str()];
	}
}

void Common::writeConstantsToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelper;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &constants = cfgHelper.getSubgroup(root, "Constants");

	libconfig::Setting &vconstants = cfgHelper.getSubgroup(constants, "Values");
	for(int i = 0; i < MaxC; ++i)
	{
		cfgHelper.put(vconstants, valueConstantsNames[i], C[i]);
	}

	libconfig::Setting &sconstants = cfgHelper.getSubgroup(constants, "Strings");
	for(int i = 0; i < MaxS; ++i)
	{
		cfgHelper.put(sconstants, stringConstantsNames[i], S[i]);
	}

	libconfig::Setting &hconstants = cfgHelper.getSubgroup(constants, "Hacks");
	for(int i = 0; i < MaxH; ++i)
	{
		cfgHelper.put(hconstants, hackConstantsNames[i], H[i]);
	}

	cfg.writeFile(cfgFilePath.c_str());
}

