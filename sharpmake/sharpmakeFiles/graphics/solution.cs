using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class GraphicsSolution : Puma.Common.IMySolution
    {
        public GraphicsSolution()
            : base("Graphics")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.Graphics>( target );
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