// Copyright  By Devin


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
// CharacterBase 要继承该接口, 但是CharacterBase 其实并不需要该接口 GetCharacterLevel 的功能, 真正需要的是 Enemy
// 因而, 为了避免 CharacterBase 需要实现, 在这里简单实现一下
uint8 ICombatInterface::GetCharacterLevel() const{
	return 0;
}
