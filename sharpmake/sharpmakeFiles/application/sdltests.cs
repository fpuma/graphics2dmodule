namespace Puma
{
    [Sharpmake.Generate]
    class SDLTest : Puma.SharpmakeBase.IApplication
    {
        public SDLTest()
            : base("SDLTest", @"tests\sdlests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Extern.SDL>(target);
            conf.AddPublicDependency<Extern.SDLgfx>(target);
            conf.AddPublicDependency<Extern.SDLImage>(target);
            conf.AddPublicDependency<Extern.SDLTtf>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
            
            conf.SolutionFolder = "Tests";
        }
    }
}