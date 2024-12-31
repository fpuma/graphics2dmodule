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

    //[Sharpmake.Generate]
    //class GLEW : Puma.SharpmakeBase.IBinaries
    //{
    //    public GLEW()
    //        : base("GLEW", @"extern\glew-2.2.0") { }

    //    public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
    //    {
    //        conf.IncludePaths.Add(@"\include");
    //    }

    //    public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
    //    {
    //        conf.LibraryPaths.Add(SourceRootPath + @"\lib");
    //        conf.LibraryFiles.Add(@"glew32.lib");

    //        conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\glew32.dll");

    //        conf.SolutionFolder = "Extern";
    //    }
    //}

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

}