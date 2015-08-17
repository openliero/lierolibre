// #include "configCompat.hpp"

#include <string>

#include "configHelper.hpp"
#include "common.hpp"

using namespace std;
using namespace libconfig;

string valueConstantsNamesCFGVer0[] =
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
	"BObjGravity",

	// WormFloat hack
	"WormFloatPower",

	"BloodLimit",

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

	"BonusDropChance",
	"SplinterLarpaVelDiv",
	"SplinterCracklerVelDiv",


	// WormFloat hack
	"WormFloatLevel",

	// BonusSpawnRect hack
	"BonusSpawnRectX",
	"BonusSpawnRectY",
	"BonusSpawnRectW",
	"BonusSpawnRectH",

	"AimMaxRight",
	"AimMinRight",
	"AimMaxLeft",
	"AimMinLeft",
	"NRColourBegin",
	"NRColourEnd",
	"BonusExplodeRisk",
	"BonusHealthVar",
	"BonusMinHealth",
	"LaserWeapon",

	"FirstBloodColour",
	"NumBloodColours",

	"RemExpObject",

	"NRPullVel",
	"NRReleaseVel",

	// FallDamage hack
	"FallDamageRight",
	"FallDamageLeft",
	"FallDamageDown",
	"FallDamageUp",

	"BloodStepUp",
	"BloodStepDown"

};

string stringConstantsNamesCFGVer0[] =
{
	"InitSound",
	"LoadingSounds",

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
	"Init_k",

	"LoadingAndThinking",
	"OK",
	"OK2",
	"PressAnyKey",

	"CommittedSuicideMsg",
	"KilledMsg",
	"YoureIt"
};

std::string hackConstantsNamesVer0[] =
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

void Common::loadConstantsFromCFGVer0(string cfgFilePath)
{
	Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const Setting &constants = cfg.lookup("Constants");

	const Setting &vconstants = constants["Values"];
	for(int i = 0; i < MaxC; ++i)
	{
		C[i] = (int)vconstants[valueConstantsNamesCFGVer0[i].c_str()];
	}

	const Setting &sconstants = constants["Strings"];
	for(int i = 0; i < MaxS; ++i)
	{
		S[i]= (char const*)sconstants[stringConstantsNamesCFGVer0[i].c_str()];
	}

	const Setting &hconstants = constants["Hacks"];
	for(int i = 0; i < MaxH; ++i)
	{
		H[i] = (bool)hconstants[hackConstantsNamesVer0[i].c_str()];
	}
}

