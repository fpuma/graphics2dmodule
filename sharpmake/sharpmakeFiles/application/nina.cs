namespace Puma
{
    [Sharpmake.Generate]
    class Nina : Puma.SharpmakeBase.IStaticLibrary
    {
        public Nina()
            : base("Nina", @"nina")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Extern.SDL>(target);
            conf.AddPrivateDependency<Extern.SDLImage>(target);
            conf.AddPrivateDependency<Extern.SDLTtf>(target);
            conf.AddPrivateDependency<Extern.SDLgfx>(target);
            conf.AddPublicDependency<Puma.Utils>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");
            conf.IncludePaths.Add(@"\shared");

            conf.PrecompHeader = @"precompiledapplication.h";
            conf.PrecompSource = @"precompiledapplication.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}