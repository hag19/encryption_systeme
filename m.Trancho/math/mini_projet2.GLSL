void mainImage(out vec4 fragcolor, in vec2 fragcoord)
{
    // Normaliz 0-1
    vec2 uv = fragcoord / iResolution.xy;
    uv = uv * 2.0 - 1.0; // to have full image (-1)-1
    uv.x *= iResolution.x / iResolution.y; // Adjust for aspect ratio

    float angle = iTime * 0.5; // Rotation speed
    mat2 rotation = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));// rotation matrix
    uv = rotation * uv;
    vec3 backgroundcolor = mix(// color changing
        vec3(sin(iTime) * 0.5 + 0.5, cos(iTime * 1.2) * 0.5 + 0.5, 1.0),
        vec3(0.0, cos(iTime) * 0.5 + 0.5, sin(iTime * 1.5) * 0.5 + 0.5),
        uv.x + 0.5
    );

    // Sphere properties
    vec3 spherecenter = vec3(0.0, 0.0, 1.0); // Sphere center in 3D space
    float sphereradius = 2.; 

    // Ray direction
    vec3 rayorigin = vec3(uv, -1.0); // Ray origin from screen to scene
    vec3 raydir = normalize(vec3(uv, 1.0)); // Normalized ray direction

    // Ray-sphere intersection
    vec3 oc = rayorigin - spherecenter;
    float b = dot(oc, raydir);
    float c = dot(oc, oc) - sphereradius * sphereradius;
    float discriminant = b * b - c;

    if (discriminant > 0.0)
    {
        float t = -b - sqrt(discriminant); // Closest intersection
        vec3 hitpoint = rayorigin + t * raydir; // Point of intersection
        vec3 normal = normalize(hitpoint - spherecenter); // Surface normal

        // Lighting calculations
        vec3 lightdir = normalize(vec3(1.0, 1.0, -1.0)); // Directional light
        float diff = max(dot(normal, lightdir), 0.0); // Diffuse lighting
        vec3 spherecolor = vec3(0.2, 0.4, 0.8) + vec3(sin(iTime) * 0.5 + 0.5); // Dynamic color
        vec3 lighting = spherecolor * diff + vec3(0.1); // Ambient lighting

        // Specular highlight
        vec3 viewdir = normalize(-raydir);
        vec3 reflectdir = reflect(-lightdir, normal);
        float spec = pow(max(dot(viewdir, reflectdir), 0.0), 32.0); // Shininess factor
        lighting += vec3(1.0) * spec; // Add specular highlight

        fragcolor = vec4(lighting, 1.0); // Set pixel color
    }
    else
    {
        fragcolor = vec4(backgroundcolor, 1.0); // Background color
    }
}
