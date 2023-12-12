#version 330 core

in vec2 UVpos;
uniform sampler2D sampler;
uniform bool per_pixel;
uniform bool kernel;

out vec4 fragColor;

void main()
{    
    vec4 color = texture(sampler, UVpos);

    if(kernel){
        float offset = 1.0 / textureSize(sampler, 0).x; // Assuming a square texture
        vec4 blurColor = vec4(0.0);

        for(int i = -2; i <= 2; i++) {
            for(int j = -2; j <= 2; j++) {
                vec2 texOffset = vec2(float(i) * offset, float(j) * offset);
                blurColor += texture(sampler, UVpos + texOffset);
            }
        }
        color = blurColor / 25.0;
    }
    if(per_pixel){
        color[0] = 1 - color[0];
        color[1] = 1 - color[1];
        color[2] = 1 - color[2];
    }

    fragColor = color;
}
