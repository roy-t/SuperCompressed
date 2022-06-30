using System.Runtime.InteropServices;

namespace SuperCompressed
{
    public static class NativeMethods
    {
        [DllImport("SuperCompressed.Native.dll", EntryPoint = "FortyTwo")]
        public static extern int FortyTwo();
    }
}
