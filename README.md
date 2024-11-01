# Overview

This is a simple project created by me (Xyuan Xiao), based on Epic Games' Third Person Smple project, with the purpose of showing my C++ and BP skills for both gameplay and UI on UE5.

This project implements a new player ability, with an interatable object and required UI, and a quickly built level demonstration to test that new ability.
The player can also Pause (ENTER/ESC) the game with the options to "resume" or "restart".

* Link to Youtube video showing a quick playtest of the project: [https://youtu.be/fJ0jPrLUp1E](https://youtu.be/fJ0jPrLUp1E)

![image](https://github.com/user-attachments/assets/e967ec15-3039-4c18-a0ca-081e7ae70116)


# Air Platform Ability (MOUSE LEFT CLICK)

In this project there's a new collectable which are the orange boxes spread around the level. Each of those boxes gives the player a charge to use the ability.
The ability consists on the player putting one of those boxes under his foot while in the air, by pressing the *Left Mouse Button*. Said box will remain static in the air for a set period of time (1 second as default), before it starts falling and can be collected once again.
 ![image](https://github.com/user-attachments/assets/854bec32-c44c-47d3-9a3e-0b30d559984c)

The idea was to develop something that is more complex than a simple double jump, making it into a puzzle that demands more thought and skill from the player, while also enabling designers to be creative in creating puzzles that involve aquiring and managing those boxes through each level.

# Implementation

The gameplay implementation consists mostly of C++ programming over the files `XyuanTestCharacter.h/.cpp`, `AirPlatform.h/.cpp`, `AbilityHud.h/.cpp` and `PauseMenu.h/.cpp`.

`XyuanTestCharacter.h/.cpp` has some default implementation from the Epic's Third Person Sample, but also includes my implementation for:
- Ability input and triggering (restrictions like being in the air and having ability charges)
- Spawning the Air Platform under the character
- Ability HUD creation and control
- Pause menu triggering

`AirPlatform.h/.cpp` implements everything that happens to the Air Platform after it is spawned:
- Staying static mid-air during a set period of time
- Start falling using physics after that time
- Collection by the player once it's not static anymore

`AbilityHud.h/.cpp` deals with the HUD to show the player how many platforms is in the inventory by showing orange squares by the left of the screen and also the current objective on the top-left:
![image](https://github.com/user-attachments/assets/407ee850-2909-49eb-a635-b6acbc4dc058)


And finally, `PauseMenu.h/.cpp` implements the pause options "Resume" (unpause and dismiss menu) and "Restart" (reset the game).
![image](https://github.com/user-attachments/assets/19d6fee4-1433-404f-8d8c-b39636009477)


# Final Considerations

All C++ classes where created following Epic's recommended code standards. Header files are organized by properties first and then methods, ordered by public, protected and private.
I tried including as many comments as necessary, and logs in case of errors. Unbinding of delegates on object destruction were also applied for safety.
Null safety checks were also used extensively throughout the code.

Worth mentioning that even though most of the implementation is done on code, it still gives designers flexibility by exposing some variables for them to tweak and experiment with the implementation, without having to touch the code.
For instance, a designer can change how long it takes for the platforms to start falling by just adjusting the value `Delay To Fall` at *BP_AirPlatform*.
![image](https://github.com/user-attachments/assets/ab1bdc86-1769-4df0-8776-84bcdf65ed91)


Or, to give a more drastic example, a designer could open *BP_ThirdPersonCharacter* and choose a different `Air Platform Class` to spawn another blueprint instead of the one I've set, or choose a different `Ability Hud Class` to experiment with a different HUD for the abilities.
![image](https://github.com/user-attachments/assets/7371b0e5-64a7-48b5-8c2f-9d8f59cb54f4)


The main unreal engine assets created/modified for this test are:
- *Content/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.uasset* (created to inherit my `XyuanTestCharacter` C++ class)
- *Content/ThirdPerson/Blueprints/BP_AirPlatform.uasset* (created to inherit my `AirPlatform` C++ class)
- *Content/ThirdPerson/Blueprints/WBP_PlayerAbilityHUD.uasset* (created to inherit my `AbilityHud` C++ class)
- *Content/ThirdPerson/Blueprints/WBP_AirPlatformSlot.uasset* (created square widget, with animation to simulate collection of 3D cube into 2D icon)
- *Content/ThirdPerson/Blueprints/WBP_PauseMenu.uasset* (created to inherit my `PauseMenu` C++ class, with some visual design implementation)
- *Content/ThirdPerson/Blueprints/WBP_PauseOption.uasset* (created button widget, to be used for each pause menu widget option)
- *Content/ThirdPerson/Input/IMC_Default.uasset* (modified to include the Mouse Left Click input for my new ability)
- *Content/ThirdPerson/Input/Actions/IA_AirPlatform.uasset* (created input action for the new ability)
- *Content/ThirdPerson/Input/Actions/IA_Pause.uasset* (created input action for the pause menu)
- *Content/ThirdPerson/Maps/ThirdPersonMap.umap* (modified to demonstrate a simple case of a puzzle using my new Air Platform ability, with multiple solutions)

Thanks for your time and I hope you enjoy my quickly created prototype!

Xyuan Xiao



