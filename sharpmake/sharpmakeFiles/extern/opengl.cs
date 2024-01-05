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

}