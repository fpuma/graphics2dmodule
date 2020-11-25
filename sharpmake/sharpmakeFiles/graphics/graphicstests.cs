namespace Puma
{
    [Sharpmake.Generate]
    class GraphicsTest : Puma.Common.IMyApplication
    {
        public GraphicsTest()
            : base("GraphicsTest", @"graphicstests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Gfx2dApp>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}