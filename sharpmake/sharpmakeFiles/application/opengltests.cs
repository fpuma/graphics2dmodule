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

            conf.AddPublicDependency<Export.SDL>(target);
            conf.AddPublicDependency<Export.OpenGL>(target);
            conf.AddPublicDependency<Export.GLEW>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}