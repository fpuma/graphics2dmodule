using Sharpmake;

namespace Puma
{
    [Sharpmake.Generate]
    class InputTests : Puma.Common.IMyApplication
    {
        public InputTests()
            : base ("InputTests", @"inputtests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Gfx2dApp>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

        }
    }
}
