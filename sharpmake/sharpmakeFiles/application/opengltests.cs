namespace Puma
{
    [Sharpmake.Generate]
    class OpenGlTest : Puma.SharpmakeBase.IApplication
    {
        public OpenGlTest()
            : base("OpenGlTest", @"tests\opengltests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Extern.SDL>(target);
            conf.AddPublicDependency<Extern.OpenGL>(target);
            conf.AddPublicDependency<Extern.GLAD>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Tests";
        }
    }
}