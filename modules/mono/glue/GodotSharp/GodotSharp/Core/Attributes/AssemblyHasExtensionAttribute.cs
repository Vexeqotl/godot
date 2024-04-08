using System;

#nullable enable

namespace Godot
{
    [AttributeUsage(AttributeTargets.Assembly)]
    public sealed class AssemblyHasExtensionAttribute : Attribute
    {
        public string[] AssemblyNames { get; }

        public AssemblyHasExtensionAttribute(string[] assemblyNames)
        {
            AssemblyNames = assemblyNames;
        }
    }
}

#nullable restore
