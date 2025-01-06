using System;

namespace Godot
{
    /// <summary>
    /// Informs Godot to not register the annotated member as a property, field, or method.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property | AttributeTargets.Method)]
    public sealed class IgnoreAttribute : Attribute
    {
        /// <summary>
        /// Constructs a new IgnoreAttribute Instance.
        /// </summary>
        public IgnoreAttribute()
        {
        }
    }
}
