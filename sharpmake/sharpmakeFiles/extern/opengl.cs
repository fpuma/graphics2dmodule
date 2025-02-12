namespace Extern
{
    [Sharpmake.Export]
    class OpenGL : Puma.SharpmakeBase.IBinaries
    {
        public OpenGL()
            : base("OpenGLBin", @"")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryFiles.Add(@"opengl32.lib");
            
            conf.SolutionFolder = "Extern";
        }
    }

    [Sharpmake.Generate]
    class GLAD : Puma.SharpmakeBase.IStaticLibrary
    {
        public GLAD()
            : base("glad", @"extern/glad")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.IncludePaths.Add(@"\include");

            conf.SolutionFolder = "Extern";
        }
    }

    [Sharpmake.Export]
    class GLM : Puma.SharpmakeBase.IHeaderOnly
    {
        public GLM()
            : base("glm", @"extern/glm")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"");
            conf.SolutionFolder = "Extern";
        }
    }

}