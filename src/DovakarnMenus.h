#pragma once

// Dovakarn fork of Community Shaders 1.8.3 (GPL-3.0): its menus are closed in Dovakarn's game.
// Modified by the Dovakarn team, 2026-10-19. Every change in this fork is listed in DOVAKARN_CHANGES.txt.
//
// Dovakarn is an online game: no player may turn its shaders' features off or edit weather, fog and lighting to see
// further than everyone else, and no Skyrim or mod settings window is reachable while playing (19/10/2026).
// So, always, with no switch (a switch in a file on the player's PC would be one every player could flip):
//   - the Community Shaders menu never opens: not on its menu key (ToggleKey), not on the built-in Shift+Enter;
//   - the CS Editor (weather, lighting and fog editor) never opens: not on its key (CSEditorToggleKey), nor from
//     anywhere else;
//   - the first-start dialog (it asks for a menu key and holds the keyboard and mouse) never shows;
//   - its Remote Control tools are never registered with a devbench host, so no outside program changes its settings.
// What stays: the effects key (all effects on or off, the same as the launcher's Community Shaders switch) and the
// performance overlay (FPS and frame times; it takes no input while the menu is closed).
// To use the menu or the editor for development, load the official Community Shaders DLL instead of this one.

namespace DovakarnMenus
{
	// Always true; nothing writes it. Volatile so the compiler reads it where it is asked rather than folding the closed
	// paths away (a constant here trips C4127 and C4702, fatal under /W4 /WX).
	inline volatile bool closed = true;
}
