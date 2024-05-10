using Sharpmake;

namespace Puma
{
    [Sharpmake.Generate]
    class InputTests : Puma.SharpmakeBase.IApplication
    {
        public InputTests()
            : base ("InputTests", @"tests\inputtests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Nina>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Tests";
        }
    }
}
