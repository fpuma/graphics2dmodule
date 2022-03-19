using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class Gfx2dAppSolution : Puma.Common.IMySolution
    {
        public Gfx2dAppSolution()
            : base("Gfx2dApp")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.Nina>( target );
            conf.AddProject<Puma.GraphicsTest>(target);
            conf.AddProject<Puma.SDLTest>(target);
            conf.AddProject<Puma.InputTests>(target);
        }
    }


    [Sharpmake.Generate]
    public class ExternSolution : Puma.Common.IMySolution
    {
        public ExternSolution()
            : base("ExternLibs")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Extern.SDLgfx>(target);
        }
    }

}