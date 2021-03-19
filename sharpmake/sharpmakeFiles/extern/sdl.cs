namespace Extern
{
    [Sharpmake.Generate]
    class SDLgfx : Puma.Common.IExternLib
    {
        public SDLgfx()
            : base("SDLgfx", @"SDL2_gfx-1.0.1")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.IncludePaths.Add(@"\include");
            conf.AddPrivateDependency<Export.SDL>(target);
        }
    }
}

namespace Export
{
    [Sharpmake.Export]
    class SDLgfx : Puma.Common.IExternBinaries
    {
        public SDLgfx()
            : base("SDLgfx", @"SDL2_gfx-1.0.1")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib");

            if(target.Optimization == Sharpmake.Optimization.Debug)
            {
                conf.LibraryFiles.Add(@"sdlgfx_d.lib");

            }
            else
            {
                conf.LibraryFiles.Add(@"sdlgfx_r.lib");
            }
        }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.IncludePaths.Add(@"\include");
            conf.AddPrivateDependency<Export.SDL>(target);
        }
    }

    [Sharpmake.Export]
    class SDL : Puma.Common.IExternBinaries
    {
        public SDL()
            : base("ExternSDL", @"SDL2-2.0.10")
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
        }
    }

    [Sharpmake.Export]
    class SDLImage : Puma.Common.IExternBinaries
    {
        public SDLImage()
            : base("ExternSDLImage", @"SDL2_image-2.0.5")
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
        }
    }

    [Sharpmake.Export]
    class SDLTtf : Puma.Common.IExternBinaries
    {
        public SDLTtf()
            : base("ExternSDLImage", @"SDL2_ttf-2.0.15")
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
        }
    }
}

