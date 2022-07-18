# Filters

The following images show the effect of different filters on mipmap quality. The source image was a 128x128 TGA image. For each filter the 32x32 generated mipmap is shown. Differences are more apparent in a [side by side comparison](https://roy-t.nl/mipmap_filters/). 


|   |   |   |   |   |
|---|---|---|---|---|
| <image src="assets/Bell-32x32.png" width=32/> | <image src="assets/Blackman-32x32.png" width=32/> | <image src="assets/Box-32x32.png" width=32/> | <image src="assets/BSpline-32x32.png" width=32/> | Bell, Blackman, Box B-spline |
| <image src="assets/Catmullrom-32x32.png" width=32/> | <image src="assets/Gaussian-32x32.png" width=32/> | <image src="assets/Kaiser-32x32.png" width=32/> | <image src="assets/Lanczos3-32x32.png" width=32/> | Catmull-Rom, Gaussian, Kaiser, Lanczos3 |
| <image src="assets/Lanczos4-32x32.png" width=32/> | <image src="assets/Lanczos6-32x32.png" width=32/> | <image src="assets/Lanczos12-32x32.png" width=32/> | <image src="assets/Mitchell-32x32.png" width=32/> | Lanczos4, Lanczos6, Lanczos12, Mitchell |
| <image src="assets/QuadraticApproximation-32x32.png" width=32/> | <image src="assets/QuadraticInterpolation-32x32.png" width=32/> | <image src="assets/QuadraticMix-32x32.png" width=32/> | <image src="assets/Tent-32x32.png" width=32/> | Quadratic approximation, Quadratic interpolation, Quadratic mix, Tent


For reference, the original image

|<image src="assets/original.png" width=128/>