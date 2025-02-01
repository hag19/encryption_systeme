void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = fragCoord / iResolution.xy;//0-1
    uv = 2.0 * uv - 1.0;//(-1)-1
    float cosA = cos(iTime);
    float sinA = sin(iTime);
    mat2 matrix_rot = mat2(cosA, -sinA, sinA, cosA);
    vec2 c = matrix_rot * uv;//center to which we are rotation
    vec2 z = vec2(0.0);
    int imax=50;// iterations
    int i;// so we can access it later
    for (i = 0; i < imax; i++) {
        if (dot(z,z) > 2.0) break; // optimisation of the code by verifaying directly in the loop
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;// fractal
    }
    if (i == imax) {// its in
        vec2 coord = (uv + vec2(1.0)) * 0.5;
        fragColor = texture(iChannel1, coord);
    } else {// its not
        vec2 coord = (uv + vec2(1.0)) * 0.5;
        fragColor = texture(iChannel0, coord);   
       
       }
   }