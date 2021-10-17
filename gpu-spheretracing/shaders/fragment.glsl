#version 330 core
vec2 texcoord;
in vec3 view_ray;
out vec4 fragColor;

uniform vec3 cameraPos;

float dSphere(vec3 p, float rad) {
    return length(p) - rad;
}

vec3 normal(vec3 p){
    float eps = 0.0001;
    float x = dSphere(p + vec3(eps,0,0),0.5) - dSphere(p-vec3(eps,0,0),0.5);
    float y = dSphere(p + vec3(0,eps,0),0.5) - dSphere(p-vec3(0,eps,0),0.5);
    float z = dSphere(p + vec3(0,0,eps),0.5) - dSphere(p-vec3(0,0,eps),0.5);
    return normalize(vec3(x, y, z));
}

void main()
{
    vec3 viewRay = normalize(view_ray);
    vec3 color = vec3(0.5);
    for (float t = 0.1; t < 5.0;){
        vec3 p = cameraPos + t * viewRay;
        float d =dSphere(p, 0.5);
        if ( d < 0.0001){
            vec3 n = normal(p);
            float nDotL = clamp(dot(n, vec3(0,0,1)),0,1);
            color = vec3(nDotL,0,0);
            break;
        }
        t += d;        
    }

    fragColor = vec4(color,1);
}