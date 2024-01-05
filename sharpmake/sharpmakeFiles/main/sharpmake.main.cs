using System.IO;

[module: Sharpmake.Include(@"..\..\sharpmakeutils\utils\*")]

[module: Sharpmake.Include(@"..\extern\*")]
[module: Sharpmake.Include(@"..\application\*")]

public static class SharpmakeMainClass
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments sharpmakeArgs)
    {
        sharpmakeArgs.Generate<Puma.NinaSolution>();
    }
}

