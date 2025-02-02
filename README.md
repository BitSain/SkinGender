# SkinGender - SA-MP Skin Gender Identification
Optimized system to identify skin gender (male/female) in SA-MP with **O(1)** time complexity.

## Features
- **O(1)** performance.
- Easily customizable gender texts.
- Works in both **gamemodes** and **filterscripts**.
- Validates skin IDs to prevent errors.

## Installation
1. Place `SkinGender.inc` in the `includes` folder.
2. Include it in your script:
```pawn
#include <SkinGender>
```
3. Customize gender texts (optional) before including:
```pawn
#define MALE_GENDER_TEXT "Male"
#define FEMALE_GENDER_TEXT "Female"
#define INVALID_GENDER_TEXT "Unknown"
#include <SkinGender>
```
4. If you don't want to use y_hooks, use this before the inclusion:
```pawn
#define SKG_NO_Y_HOOKS
#include <SkinGender>
```

## Functions
- **IsMaleSkinID(skinid)**: Returns `true` if the skin is male.
- **IsFemaleSkinID(skinid)**: Returns `true` if the skin is female.
- **GetSkinGenderText(skinid)**: Returns gender text (`"male"`, `"female"`, or `"invalid"`).
- **IsValidSkinID(skinid)**: Returns `true` if the skin is valid.

## Example
```pawn
if(IsMaleSkinID(22)) {
    printf("Skin 22 is male.");
} else if(IsFemaleSkinID(9)) {
    printf("Skin 9 is female.");
} else if(!IsValidSkinID(555)) {
    printf("Skin 555 is invalid.");
}

printf("Skin 10 gender: %s", GetSkinGenderText(10));
```

## Credit
- **Author**: BitSain (Leonardo)  
- **Contact**: bitsaindeveloper@gmail.com  
- **Project**: [Link](https://github.com/BitSain/SkinGender)

## License
This project is licensed under the **Creative Commons Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0)**.  
For more details, visit [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) / [LICENSE](LICENCE.md).
