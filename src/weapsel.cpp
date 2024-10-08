/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
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

#include "weapsel.hpp"
#include "gfx.hpp"
#include "game.hpp"
#include "worm.hpp"
#include "text.hpp"
#include "menu/menu.hpp"
#include "sfx.hpp"
#include "viewport.hpp"
#include <SDL/SDL.h>

WeaponSelection::WeaponSelection(Game& game)
: game(game)
, enabledWeaps(0)
, isReady(game.viewports.size())
, menus(game.viewports.size())
, cachedBackground(false)
, focused(true)
{
	Common& common = *game.common;
	
	for(int i = 0; i < 40; ++i)
	{
		if(game.settings->weapTable[i] == 0)
			++enabledWeaps;
	}
	
	for(std::size_t i = 0; i < menus.size(); ++i)
	{
		bool weapUsed[256] = {};
		
		Viewport& vp = *game.viewports[i];
		
		Worm& worm = *vp.worm;
		WormSettings& ws = *worm.settings;
		
		menus[i].items.push_back(MenuItem(60, 60, common.texts.randomize));
		
		{
			int x = vp.rect.center_x() - 31;
			int y = vp.rect.center_y() - 51;
			menus[i].place(x, y);
		}	
		
		for(int j = 0; j < Settings::selectableWeapons; ++j)
		{
			if(ws.weapons[j] == 0)
			{
				ws.weapons[j] = gfx.rand(1, 41);
			}
			
			bool enoughWeapons = (enabledWeaps >= Settings::selectableWeapons);
			
			while(true)
			{
				int w = common.weapOrder[ws.weapons[j]];
				
				if((!enoughWeapons || !weapUsed[w])
				&& game.settings->weapTable[w] <= 0)
					break;
					
				ws.weapons[j] = gfx.rand(1, 41);
			}
			
			int w = common.weapOrder[ws.weapons[j]];
			
			weapUsed[w] = true;
			
			WormWeapon& ww = worm.weapons[j];
			
			ww.ammo = 0;
			ww.id = w;
			
			menus[i].items.push_back(MenuItem(48, 48, common.weapons[w].name));
		}
		
		menus[i].items.push_back(MenuItem(10, 10, common.texts.done));
		
		worm.currentWeapon = 0;
		
		menus[i].moveToFirstVisible();
		isReady[i] = (ws.controller != 0); // AIs are ready immediately
	}
}
	
void WeaponSelection::draw()
{
	Common& common = *game.common;
	
	if(!cachedBackground)
	{
		game.draw();
		
			
		if(game.settings->levelFile.empty())
		{
			common.font.drawText(common.texts.levelRandom, 0, 162, 50);
		}
		else
		{
			common.font.drawText((common.texts.levelIs1 + game.settings->levelFile + common.texts.levelIs2), 0, 162, 50);
		}
		
		std::memcpy(&gfx.frozenScreen[0], gfx.screen->pixels, gfx.frozenScreen.size());
		cachedBackground = true;
	}
	
	std::memcpy(gfx.screen->pixels, &gfx.frozenScreen[0], gfx.frozenScreen.size());

	if(!focused)
		return;
		

	drawRoundedBox(114, 2, 0, 7, common.font.getDims(common.texts.selWeap));
	
	common.font.drawText(common.texts.selWeap, 116, 3, 50);
		
	for(std::size_t i = 0; i < menus.size(); ++i)
	{
		Menu& weaponMenu = menus[i];
		
		Viewport& vp = *game.viewports[i];
		
		Worm& worm = *vp.worm;
		WormSettings& ws = *worm.settings;
		
		int width = common.font.getDims(ws.name);
		drawRoundedBox(weaponMenu.x + 29 - width/2, weaponMenu.y - 11, 0, 7, width);
		common.font.drawText(ws.name, weaponMenu.x + 31 - width/2, weaponMenu.y - 10, ws.color + 1);
		
		if(!isReady[i])
		{
			menus[i].draw(common, false);
		}
	}
	
	// TODO: This just uses the currently activated palette, which might well be wrong.
	gfx.origpal.rotate(168, 174);
	gfx.pal = gfx.origpal;
	gfx.pal.fade(gfx.fadeValue);
}
	
bool WeaponSelection::processFrame()
{
	Common& common = *game.common;
	
	bool allReady = true;
	
	for(std::size_t i = 0; i < menus.size(); ++i)
	{
		int weapID = menus[i].selection() - 1;
		
		Viewport& vp = *game.viewports[i];
		Worm& worm = *vp.worm;
		
		WormSettings& ws = *worm.settings;
		
		if(!isReady[i])
		{
			//menus[i].draw(common, ws.selWeapX - 2, 28, false, curSel[i]);

			if(weapID >= 0 && weapID < Settings::selectableWeapons)
			{
				if(worm.pressed(Worm::Left))
				{
					worm.release(Worm::Left);
					
					game.soundPlayer->play(25);
					
					do
					{
						--ws.weapons[weapID];
						if(ws.weapons[weapID] < 1)
							ws.weapons[weapID] = 40; // TODO: Unhardcode
					}
					while(game.settings->weapTable[common.weapOrder[ws.weapons[weapID]]] != 0);
					
					int w = common.weapOrder[ws.weapons[weapID]];
					worm.weapons[weapID].id = w;
					menus[i].items[menus[i].selection()].string = common.weapons[w].name;
				}
				
				if(worm.pressed(Worm::Right))
				{
					worm.release(Worm::Right);
					
					game.soundPlayer->play(26);
					
					do
					{
						++ws.weapons[weapID];
						if(ws.weapons[weapID] > 40)
							ws.weapons[weapID] = 1; // TODO: Unhardcode
					}
					while(game.settings->weapTable[common.weapOrder[ws.weapons[weapID]]] != 0);
					
					int w = common.weapOrder[ws.weapons[weapID]];
					worm.weapons[weapID].id = w;
					menus[i].items[menus[i].selection()].string = common.weapons[w].name;
				}
			}
			
			if(worm.pressedOnce(Worm::Up))
			{
				game.soundPlayer->play(26);
				/*
				int s = int(menus[i].items.size());
				curSel[i] = (curSel[i] - 1 + s) % s;*/
				menus[i].movement(-1);
			}
			
			if(worm.pressedOnce(Worm::Down))
			{
				game.soundPlayer->play(25);
				/*
				int s = int(menus[i].items.size());
				curSel[i] = (curSel[i] + 1 + s) % s;
				*/
				menus[i].movement(1);
			}
			
			if(worm.pressed(Worm::Fire))
			{
				if(menus[i].selection() == 0)
				{
					bool weapUsed[256] = {};
					
					bool enoughWeapons = (enabledWeaps >= Settings::selectableWeapons);
					
					for(int j = 0; j < Settings::selectableWeapons; ++j)
					{
						while(true)
						{
							ws.weapons[j] = gfx.rand(1, 41);
							
							int w = common.weapOrder[ws.weapons[j]];
							
							if((!enoughWeapons || !weapUsed[w])
							&& game.settings->weapTable[w] <= 0)
								break;
						}
						
						int w = common.weapOrder[ws.weapons[j]];
						
						weapUsed[w] = true;
						
						//WormWeapon& ww = worm.weapons[j];
						
						menus[i].items[j + 1].string = common.weapons[w].name;
					}
				}
				else if(menus[i].selection() == 6) // TODO: Unhardcode
				{
					game.soundPlayer->play(27);
					isReady[i] = true;
				}
			}
		}
		
		allReady = allReady && isReady[i];
	}
	
	return allReady;
}


	
void WeaponSelection::finalize()
{
	for(std::size_t i = 0; i < game.worms.size(); ++i)
	{
		Worm& worm = *game.worms[i];
		
		worm.initWeapons();
		/*
		for(int j = 0; j < 6; ++j)
		{
			gfx.releaseKey(worm.settings->controls[j]);
		}*/
	}
	game.releaseControls();
	
	// TODO: Make sure the weapon selection is transfered back to Gfx to be saved
}

void WeaponSelection::focus()
{
	focused = true;
}

void WeaponSelection::unfocus()
{
	focused = false;
}

#if 0
void selectWeapons(Game& game)
{
	WeaponSelection ws(game);
	
	while(!ws.processFrame())
	{
		ws.draw();
		gfx.flip();
		gfx.process(&game);
	}
	
	ws.finalize();
	// Important that escape isn't released here
}
#endif
	
/*
void SelectWeapons()
{
 //At this point, cEnabledWeaps contains the number of weapons that are selectable from the menu




 memcpy(cGFX::pScrTemp, cGFX::pScr, cGFX::iScrSize);

	fadevalue = 0;

 do
 {
  for(w = 0; w <= 1; w++)
  {
   if(isready[w] == 0)
   {
    BYTE color;

    for(o = 1; o <= SELECTABLE_WEAPONS; o++)
    {
     long weapid = o - 1;
     long ypos = (o<<3);
     if(o == cursel[w])
     {
      wid = GetTextWidth(cSettings::sWeapNames.m_bData[cGame::cWorm[w].m_sWeapons[weapid].m_iID]);
      DrawRoundedBox(cSettings::iSelWeapX[w]-2, ypos+28, 0, 7, wid);
     } else // AE58
     {
      DrawTextMW(cSettings::sWeapNames.m_bData[cGame::cWorm[w].m_sWeapons[weapid].id], cSettings::iSelWeapX[w]+1, ypos+30, 0);
     } // AE9D

     
     if(o == cursel[w])
     {
      color = 168;
     } else
     {
      color = 48;
     }
     DrawTextMW(cSettings::sWeapNames.m_bData[cGame::cWorm[w].m_sWeapons[weapid].m_iID], cSettings::iSelWeapX[w], ypos+29, color);
    } // AF01

    wid = GetTextWidth(txt_done);
    if(cursel[w] == 6)
    {
     DrawRoundedBox(cSettings::iSelWeapX[w]-2, 76, 0, 7, wid);
    } else // AF3E
    {
     DrawTextMW(txt_done, cSettings::iSelWeapX[w]+1, 78, 0);
    } // AF64

    if(cursel[w] == 6) //NOTE! The table is a bit strange here!
    {
     color = 168;
    } else
    {
     color = 10;
    }

    DrawTextMW(cMenus::bTxtDone, cSettings::iSelWeapX[w], 77, color);

    wid = GetTextWidth(cMenus::bTxtRandomize);
    if(cursel[w] == 0)
    {
     DrawRoundedBox(cSettings::iSelWeapX[w]-2, 28, 0, 7, wid);
    } else // AFDB
    {
     DrawTextMW(cMenus::bTxtRandomize, cSettings::iSelWeapX[w]+1, 30, 0);
    } // B001

    if(cursel[w] == 0)
    {
     color = 168;
    } else
    {
     color = 13;
    }
    DrawTextMW(cMenus::bTxtRandomize, cSettings::iSelWeapX[w], 29, color);

    if(cGame::cWorm[w].m_bKeyleft)
    {
     long weapid = cursel[w]-1;
     if(weapid >= 0 && weapid < SELECTABLE_WEAPONS)
     {
						cLOSP::bDisKeyBuffer[cSettings::sSettings.m_iControls[w][KEY_LEFT]] = true;
      if(cLOSP::bSoundEnabled)
      {
       playsound(0, 0, cLOSP::pSoundPointers[26]);
      } // B07A
      do
      {
       cSettings::sSettings.m_iWeapons[w][weapid]--;
       if(cSettings::sSettings.m_iWeapons[w][weapid] < 0)
       {
        cSettings::sSettings.m_iWeapons[w][weapid] = 39;
       } // B0C9
      } while(cSettings::sSettings.m_iWeapTable[cSettings::sWeap.order[cSettings::sSettings.m_iWeapons[w][weapid]]] != 0);

      cGame::cWorm[w].m_sWeapons[weapid].m_iID = cSettings::sWeap.order[cSettings::sSettings.m_iWeapons[w][weapid]];
     }
    } // B137

    if(cGame::cWorm[w].m_bKeyright)
    {
     long weapid = cursel[w]-1;
     if(weapid >= 0 && weapid < SELECTABLE_WEAPONS)
     {
      cLOSP::bDisKeyBuffer[cSettings::sSettings.m_iControls[w][KEY_RIGHT]] = true;
      if(cLOSP::bSoundEnabled)
      {
       playsound(0, 0, cLOSP::pSoundPointers[27]);
      } // B176
      do
      {
       cSettings::sSettings.m_iWeapons[w][weapid]++;
       if(cSettings::sSettings.m_iWeapons[w][weapid] > 39)
       {
        cSettings::sSettings.m_iWeapons[w][weapid] = 0;
       } // B1C5
      } while(cSettings::sSettings.m_iWeapTable[cSettings::sWeap.m_iOrder[cSettings::sSettings.m_iWeapons[w][weapid]]] != 0);

      cGame::cWorm[w].m_iWeapons[weapid].id = cSettings::sWeap.m_iOrder[cSettings::sSettings.m_iWeapons[w][weapid]];
     }
    } // B233

    if(cGame::cWorm[w].m_bKeyup)
    {
     cLOSP::bDisKeyBuffer[cSettings::sSettings.m_iControls[w][KEY_UP]] = true;
     if(cLOSP::bSoundEnabled)
     {
      playsound(0, 0, cLOSP::pSoundPointers[27]);
     } // B26F
     cursel[w]--;
     if(cursel[w] < 0)
     {
      cursel[w] = 6;
     }
    } // B28C

    if(cGame::cWorm[w].m_bKeydown)
    {
					cLOSP::bDisKeyBuffer[cSettings::sSettings.m_iControls[w][KEY_DOWN]] = true;
     if(cLOSP::bSoundEnabled)
     {
      playsound(0, 0, cLOSP::pSoundPointers[26]);
     } // B2C8
     cursel[w]++;
     if(cursel[w] > 6)
     {
      cursel[w] = 0;
     }
    } // B2E5

    if(cGame::cWorm[w].m_bKeyfire)
    {
     if(cursel[w] == 0)
     {
      memset(bWeapUsed, 0, 256);

      for(o = 0; o < SELECTABLE_WEAPONS; o++)
      {
       cSettings::sSettings.m_iWeapons[w][o] = random(40);

       if(cEnabledWeaps < SELECTABLE_WEAPONS)
       {
        while(1)
        {
         if(cSettings::sSettings.m_iWeapTable[cSettings::sWeap.m_iOrder[cSettings::sSettings.m_iWeapons[w][o]]] == 0)
          break;

         cSettings::sSettings.m_iWeapons[w][o] = random(40);
        }
       } else // B398
       {
        while(1)
        {
         if(!bWeapUsed[cSettings::sSettings.m_iWeapons[w][o]]) //Avoid choosing the same weapon twice
         {
          if(cSettings::sSettings.weaptable[cSettings::sWeap.m_iOrder[cSettings::sSettings.m_iWeapons[w][o]]] <= 0) break;
         } // B3E4
         cSettings::sSettings.weapons[w][o] = random(40);
        }
       } // B404
       bWeapUsed[cSettings::sSettings.weapons[w][o]] = true;

       cGame::cWorm[w].m_sWeapons[o].m_iAmmo = 0;
       cGame::cWorm[w].m_sWeapons[o].m_iID = cSettings::sWeap.m_iOrder[cSettings::sSettings.m_iWeapons[w][o]];
      } // B4A7
     } else if(cursel[w] == 6)
     {
      //NOTE! Disable the key here. Do we really need to?
      if(cLOSP::bSoundEnabled)
      {
       playsound(0, 0, cLOSP::pSoundPointers[28]);
      } // B4DB
      isready[w] = 1;
     } // B4E2
    }
   }
  } // B4EB

  AnimateOrigPal(168, 174);
  GetOrigPal();

  if(fadevalue < 256)
  {
   FadePalette(fadevalue);
   fadevalue += 8;
  } // B506

  Flip();
  
  memcpy(cGFX::pScr, cGFX::pScrTemp, cGFX::pScrSize); //Restore the original screen
 } while((isready[0] == 0 || isready[1] == 0) && !cLOSP::bKeyBuffer[DIK_ESCAPE]);

//l_B53F:
 for(w = 0; w < 2; w++)
 {
  cGame::cWorm[w].m_iCurrentWeapon = 1;
  for(o = 0; o < SELECTABLE_WEAPONS; o++) //Fill up ammo!
  {
   cGame::cWorm[w].m_sWeapons[o].m_iAmmo = cSettings::sWeap.m_iAmmo[cGame::cWorm[w].m_sWeapons[o].m_iID];
  } // B5A2
 } // B5A8

 for(w = 0; w; w++)
 {
  for(wid = 0; wid <= 6; wid++)
  {
			cLOSP::bDisKeyBuffer[cSettings::sSettings.m_iControls[w][wid]] = true;
  }
 } // B5DE

}
*/
