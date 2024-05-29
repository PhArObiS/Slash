// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SlashEditorTarget : TargetRules
{
	public SlashEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		// IncludeOrderVersion = EngineIncludeOrderVersion.Latest; // Set to the latest include order version

		ExtraModuleNames.AddRange(new string[] { "Slash" });
	}
}