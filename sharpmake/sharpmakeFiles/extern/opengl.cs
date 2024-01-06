namespace Export
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
        }
    }

    [Sharpmake.Export]
    class GLEW : Puma.SharpmakeBase.IBinaries
    {
        public GLEW()
            : base("GLEW", @"extern\glew-2.2.0") { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib");
            conf.LibraryFiles.Add(@"glew32.lib");
        }
    }


}