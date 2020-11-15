namespace Puma
{
    [Sharpmake.Generate]
    class Graphics : Puma.Common.IMyLib
    {
        public Graphics()
            : base("Graphics", @"graphics")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Export.SDL>(target);
            conf.AddPrivateDependency<Export.SDLImage>(target);
            conf.AddPrivateDependency<Export.SDLTtf>(target);
            conf.AddPrivateDependency<Export.SDLgfx>(target);
            conf.AddPublicDependency<Puma.Utils>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.PrecompHeader = @"precompiledgraphics.h";
            conf.PrecompSource = @"precompiledgraphics.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}