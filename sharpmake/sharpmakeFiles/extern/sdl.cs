namespace Extern
{
    [Sharpmake.Generate]
    class SDLgfx : Puma.SharpmakeBase.IStaticLibrary
    {
        public SDLgfx()
            : base("SDLgfx", @"extern/SDL2_gfx-1.0.4")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.IncludePaths.Add(@"\include");
            conf.AddPrivateDependency<Extern.SDL>(target);

            conf.SolutionFolder = "Extern";
        }
    }

    [Sharpmake.Generate]
    class SDL : Puma.SharpmakeBase.IBinaries
    {
        public SDL()
            : base("SDL", @"extern/SDL2-2.0.10")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib\x64");

            conf.LibraryFiles.Add(@"SDL2.lib");
            conf.LibraryFiles.Add(@"SDL2main.lib");

            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\SDL2.dll");

            conf.SolutionFolder = "Extern";
        }
    }

    [Sharpmake.Generate]
    class SDLImage : Puma.SharpmakeBase.IBinaries
    {
        public SDLImage()
            : base("ExternSDLImage", @"extern/SDL2_image-2.0.5")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib\x64");

            conf.LibraryFiles.Add(@"SDL2_image.lib");

            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\SDL2_image.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\libjpeg-9.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\libpng16-16.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\libtiff-5.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\libwebp-7.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\zlib1.dll");

            conf.SolutionFolder = "Extern";
        }
    }

    [Sharpmake.Generate]
    class SDLTtf : Puma.SharpmakeBase.IBinaries
    {
        public SDLTtf()
            : base("SDLttf", @"extern/SDL2_ttf-2.0.15")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib\x64");

            conf.LibraryFiles.Add(@"SDL2_ttf.lib");

            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\SDL2_ttf.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\libfreetype-6.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\lib\x64\zlib1.dll");

            conf.SolutionFolder = "Extern";
        }
    }
}