
using UnrealBuildTool;

public class MYPJ3 : ModuleRules
{
	public MYPJ3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		
	}
}
