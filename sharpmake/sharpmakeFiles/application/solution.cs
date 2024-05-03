using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class NinaSolution : Puma.SharpmakeBase.ISolution
    {
        public NinaSolution()
            : base("Nina")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.Nina>( target );
            conf.AddProject<Puma.GraphicsTest>(target);
            conf.AddProject<Puma.SDLTest>(target);
            conf.AddProject<Puma.InputTests>(target);
            conf.AddProject<Puma.OpenGlTest>(target);
        }
    }
}