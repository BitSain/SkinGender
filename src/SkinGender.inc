/**
 * @file SkinGender.inc
 * @brief A highly optimized and customizable system for skin gender identification in SA-MP.
 *
 * @author BitSain (Leonardo)
 * @contact bitsaindeveloper@gmail.com
 * @license Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
 *         - See the LICENSE file for full details.
 *
 * Copyright (c) 2025 BitSain (Leonardo)
 *
 * This program is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
 * You may modify, distribute, and create derivative works of this software under the following conditions:
 * 
 * 1. Attribution: You must give appropriate credit to the original author (BitSain/Leonardo), provide a link to the original project,
 *    and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the author
 *    endorses you or your use.
 * 2. ShareAlike: If you modify the software and distribute it, you must distribute your contributions under the same license (CC BY-SA 4.0).
 * 
 * For more details, see the full license at https://creativecommons.org/licenses/by-sa/4.0/
 *
 * License: CC BY-SA 4.0 International
 * Copyright © 2025 BitSain (Leonardo)
 *
 * Language: Pawn
 * Dependencies:
 * - Requires `open.mp` or `a_samp` to be included first.
 * - Optionally supports YSI hooks if available.
 *
 * Features:
 * - **O(1)** time complexity for skin gender checks.
 * - Easily customizable gender text outputs through defines.
 * - Clear, concise, and reusable API.
 * - Validates skin IDs to avoid errors.
 *
 * Macros:
 * - `MAX_SKINS`: Maximum number of skins in the system.
 * - `MALE_GENDER_TEXT`: Customizable text for male skins.
 * - `FEMALE_GENDER_TEXT`: Customizable text for female skins.
 * - `INVALID_GENDER_TEXT`: Customizable text for invalid skins.
 *
 * Functions:
 * - `IsValidSkinID(skinid)`: Checks if the provided skin ID is valid.
 * - `IsMaleSkinID(skinid)`: Checks if the provided skin ID is male.
 * - `IsFemaleSkinID(skinid)`: Checks if the provided skin ID is female.
 * - `GetSkinGenderText(skinid)`: Returns the gender of the skin as a string (customizable).
 *
 * Example Usage:
 * ```
 *		if(IsMaleSkinID(22)) {
 *     		printf("Skin 22 is male.");
 * 		} else if(IsFemaleSkinID(9)) {
 *     		printf("Skin 9 is female.");
 * 		} else if(!IsValidSkinID(555)) {
 *     		printf("Skin 555 is invalid.");
 * 		}
 *
 * 		printf("Skin 10 gender: %s", GetSkinGenderText(10));
 * ```
 *
 * Version: 1.0.0
 */

// Protection of Author and License
#define AUTHOR "BitSain (Leonardo)"
#define LICENSE "CC BY-SA 4.0 International - See the LICENSE file for full details"
#define PROJECT_URL "https://github.com/BitSain/SkinGender"

#if !defined AUTHOR
    #error "This code must include the author's name and license."
#endif

#if defined _INC_SKIN_GENDER
    #endinput
#endif
#define _INC_SKIN_GENDER

// Importing necessary dependencies
#tryinclude <open.mp>
#if !defined _INC_open_mp
    #tryinclude <a_samp>
    #if !defined _INC_a_samp
        #error "Please include <open.mp> or <a_samp> before <SkinGender>."
    #endif
#endif

// HOOKS --- Optional YSI hooks support && Gamemode or filterscript initialization
#if !defined SKG_NO_Y_HOOKS 
	#tryinclude <YSI_Coding\y_hooks>

	#if defined _INC_y_hooks
		#if defined FILTERSCRIPT
	 		hook OnFilterScriptInit() {
	 			return CallLocalFunction("OnIncludeInit", "");
	 		}
	 	#else
	 		hook OnGameModeInit() {
	 			return CallLocalFunction("OnIncludeInit", "");
	 		}
		#endif
	#else
	 		#error Include <YSI_Coding\y_hooks> not found.
	#endif
#else
	#if defined FILTERSCRIPT
 		public OnFilterScriptInit() {
 			CallLocalFunction("OnIncludeInit", "");

 			#if defined SKG_OnFilterScriptInit
 				return SKG_OnFilterScriptInit();
 			#else
 				return 1;
 			#endif
 		}
 	#else
 		public OnGameModeInit() {
 			CallLocalFunction("OnIncludeInit", "");

 			#if defined SKG_OnGameModeInit
 				return SKG_OnGameModeInit();
 			#else
 				return 1;
 			#endif
 		}
	#endif
#endif

// Constants
#define MAX_SKINS 311

// Default Gender Texts (can be overridden externally)
#if !defined MALE_GENDER_TEXT
    #define MALE_GENDER_TEXT "male"
#endif
#if !defined FEMALE_GENDER_TEXT
    #define FEMALE_GENDER_TEXT "female"
#endif
#if !defined INVALID_GENDER_TEXT
    #define INVALID_GENDER_TEXT "invalid"
#endif

// Gender lookup array (true = male, false = female)
static bool:GenderArray[MAX_SKINS] = {true, ...}; /**< Array storing the gender of skins */

/** 
 * @brief Initializes the SkinGender system and marks skins as male or female.
 */
forward OnIncludeInit();
public OnIncludeInit() {
    static const __femaleSkins[] = {
        9, 10, 11, 12, 13, 31, 38, 39, 40, 41, 53, 54, 55, 56, 63, 64, 69, 75, 76, 77, 85, 87, 88, 89, 90, 
        91, 92, 93, 129, 130, 131, 138, 139, 140, 141, 145, 148, 150, 151, 152, 157, 169, 172, 178, 190, 191, 
        192, 193, 194, 195, 196, 197, 198, 199, 201, 205, 207, 211, 214, 215, 216, 218, 219, 224, 225, 226, 
        231, 232, 233, 237, 238, 243, 244, 245, 246, 251, 256, 257, 263, 298, 304
    };
    for(new i = 0; i < sizeof(__femaleSkins); i++) {
        GenderArray[__femaleSkins[i]] = false; // Mark female skins
    }
    return true;
}

// Stock functions for checking skin gender
stock bool:IsValidSkinID(skinid) {
    return 0 <= skinid <= (MAX_SKINS - 1); // Check if the skin ID is within valid range
}

stock bool:IsMaleSkinID(skinid) {
    if(!IsValidSkinID(skinid)) return false;
    return GenderArray[skinid];
}

stock bool:IsFemaleSkinID(skinid) {
    if(!IsValidSkinID(skinid)) return false;
    return !GenderArray[skinid];
}

// Function to return gender as text
stock GetSkinGenderText(skinid) {
    if(!IsValidSkinID(skinid)) return INVALID_GENDER_TEXT;
    return (GenderArray[skinid] ? MALE_GENDER_TEXT : FEMALE_GENDER_TEXT);
}

// ALS
#if defined SKG_NO_Y_HOOKS
	#if !defined FILTERSCRIPT
		#if defined _ALS_OnGameModeInit
			#undef OnGameModeInit
		#else
			#define _ALS_OnGameModeInit
		#endif
		
		#define OnGameModeInit SKG_OnGameModeInit
		#if defined SKG_OnGameModeInit
			forward SKG_OnGameModeInit();
		#endif
	#else
		#if defined _ALS_OnFilterScriptInit
			#undef OnFilterScriptInit
		#else
			#define _ALS_OnFilterScriptInit
		#endif
		
		#define OnFilterScriptInit SKG_OnFilterScriptInit
		#if defined SKG_OnFilterScriptInit
			forward SKG_OnFilterScriptInit();
		#endif
	#endif
#endif