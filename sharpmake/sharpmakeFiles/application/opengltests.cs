namespace Puma
{
    [Sharpmake.Generate]
    class OpenGlTest : Puma.SharpmakeBase.IApplication
    {
        public OpenGlTest()
            : base("OpenGlTest", @"opengltests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Extern.SDL>(target);
            conf.AddPublicDependency<Extern.OpenGL>(target);
            conf.AddPublicDependency<Extern.GLEW>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Tests";
        }
    }
}