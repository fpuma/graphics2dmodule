namespace Puma
{
    [Sharpmake.Generate]
    class GraphicsTest : Puma.SharpmakeBase.IApplication
    {
        public GraphicsTest()
            : base("GraphicsTest", @"graphicstests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Nina>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}