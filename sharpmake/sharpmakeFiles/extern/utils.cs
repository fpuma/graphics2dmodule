namespace Puma
{
    [Sharpmake.Generate]
    class Utils : Puma.SharpmakeBase.IHeaderOnly
    {
        public Utils()
            : base("Utils", @"extern\utilslibrary\source\utils")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");

            conf.SolutionFolder = "Submodules";
        }
    }
}