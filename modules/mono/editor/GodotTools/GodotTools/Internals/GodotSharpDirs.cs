using System.Diagnostics.CodeAnalysis;
using System.IO;
using Godot;
using Godot.NativeInterop;
using GodotTools.Core;
using static GodotTools.Internals.Globals;

namespace GodotTools.Internals
{
    public static class GodotSharpDirs
    {
        public static string ResMetadataDir
        {
            get
            {
                Internal.godot_icall_GodotSharpDirs_ResMetadataDir(out godot_string dest);
                using (dest)
                    return Marshaling.ConvertStringToManaged(dest);
            }
        }

        public static string MonoUserDir
        {
            get
            {
                Internal.godot_icall_GodotSharpDirs_MonoUserDir(out godot_string dest);
                using (dest)
                    return Marshaling.ConvertStringToManaged(dest);
            }
        }

        public static string BuildLogsDirs
        {
            get
            {
                Internal.godot_icall_GodotSharpDirs_BuildLogsDirs(out godot_string dest);
                using (dest)
                    return Marshaling.ConvertStringToManaged(dest);
            }
        }

        public static string DataEditorToolsDir
        {
            get
            {
                Internal.godot_icall_GodotSharpDirs_DataEditorToolsDir(out godot_string dest);
                using (dest)
                    return Marshaling.ConvertStringToManaged(dest);
            }
        }


        public static string CSharpProjectName
        {
            get
            {
                Internal.godot_icall_GodotSharpDirs_CSharpProjectName(out godot_string dest);
                using (dest)
                    return Marshaling.ConvertStringToManaged(dest);
            }
        }

        [MemberNotNull("_projectAssemblyName", "_projectSlnPath")]
        public static void DetermineProjectLocation()
        {
            _projectAssemblyName = (string?)ProjectSettings.GetSetting("dotnet/project/assembly_name");
            if (string.IsNullOrEmpty(_projectAssemblyName))
            {
                _projectAssemblyName = CSharpProjectName;
                ProjectSettings.SetSetting("dotnet/project/assembly_name", _projectAssemblyName);
            }

            string? slnParentDir = (string?)ProjectSettings.GetSetting("dotnet/project/solution_directory");
            if (string.IsNullOrEmpty(slnParentDir))
                slnParentDir = "res://";
            else if (!slnParentDir.StartsWith("res://", System.StringComparison.Ordinal))
                slnParentDir = "res://" + slnParentDir;

            _projectSlnPath = Path.Combine(ProjectSettings.GlobalizePath(slnParentDir),
                string.Concat(_projectAssemblyName, ".sln"));
        }

        private static string? _projectAssemblyName;
        private static string? _projectSlnPath;

        public static string ProjectAssemblyName
        {
            get
            {
                if (_projectAssemblyName == null)
                    DetermineProjectLocation();
                return _projectAssemblyName;
            }
        }

        public static string ProjectSlnPath
        {
            get
            {
                if (_projectSlnPath == null)
                    DetermineProjectLocation();
                return _projectSlnPath;
            }
        }

        public static string ProjectBaseOutputPath
        {
            get
            {
                if (_projectSlnPath == null)
                    DetermineProjectLocation();
                return Path.Combine(Path.GetDirectoryName(_projectSlnPath)!, ".godot", "mono", "temp", "bin");
            }
        }

        public static string LogsDirPathFor(string solution, string configuration)
            => Path.Combine(BuildLogsDirs, $"{solution.Md5Text()}_{configuration}");

        public static string LogsDirPathFor(string configuration)
            => LogsDirPathFor(ProjectSlnPath, configuration);
    }
}
