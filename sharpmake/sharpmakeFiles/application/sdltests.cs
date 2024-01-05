namespace Puma
{
    [Sharpmake.Generate]
    class SDLTest : Puma.SharpmakeBase.IApplication
    {
        public SDLTest()
            : base("SDLTest", @"sdlests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Export.SDL>(target);
            conf.AddPublicDependency<Export.SDLgfx>(target);
            conf.AddPublicDependency<Export.SDLImage>(target);
            conf.AddPublicDependency<Export.SDLTtf>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}