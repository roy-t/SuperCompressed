namespace SuperCompressed
{
    public enum MipMapGeneration : byte
    {
        Disabled,
        Default,
        Box,
        Tent,
        Bell,
        BSpline,
        Mitchell,
        Blackman,
        Lanczos3,
        Lanczos4,
        Lanczos6,
        Lanczos12,
        Kaiser,
        Gaussian,
        Catmullrom,
        QuadraticInterpolation,
        QuadraticApproximation,
        QuadraticMix
    };
}
