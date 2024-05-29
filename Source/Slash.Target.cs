// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SlashTarget : TargetRules
{
	public SlashTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		// IncludeOrderVersion = EngineIncludeOrderVersion.Latest; // Set to the latest include order version

		ExtraModuleNames.AddRange(new string[] { "Slash" });
	}
}