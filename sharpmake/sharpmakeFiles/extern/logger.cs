namespace Puma
{
    [Sharpmake.Generate]
    class Logger : Puma.SharpmakeBase.IStaticLibrary
    {
        public Logger()
            : base("Logger", @"extern/logger\source\logger")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Utils>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Submodules";
        }
    }
}