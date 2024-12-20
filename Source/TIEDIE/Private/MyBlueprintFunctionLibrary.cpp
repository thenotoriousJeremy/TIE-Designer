// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericApplication.h"
#include "Framework/Application/SlateApplication.h"

bool UMyBlueprintFunctionLibrary::AreCapsLocked()
{
	return FSlateApplication::Get().GetModifierKeys().AreCapsLocked();
}