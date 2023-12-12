#version 330 core
in vec3 world_pos_out;
in vec3 world_norm_out;

out vec4 fragColor;

uniform float k_a;
uniform float k_d;
uniform float k_s;

uniform vec4 dir_light_dir[8];
uniform vec4 dir_light_color[8];

uniform vec4 point_light_dir[8];
uniform vec4 point_light_color[8];
uniform vec3 point_light_pos[8];
uniform vec3 point_light_func[8];

uniform vec4 spot_light_dir[8];
uniform vec4 spot_light_color[8];
uniform vec3 spot_light_pos[8];
uniform vec3 spot_light_func[8];
uniform float penumbra[8];
uniform float angle[8];


uniform int num_dir_lights;
uniform int num_point_lights;
uniform int num_spot_lights;

uniform vec4 cA;
uniform vec4 cD;
uniform vec4 cS;
uniform float shine;
uniform vec4 cam_pos;

void main() {
    vec4 normfinal = normalize(vec4(world_norm_out,0.0f));
    vec4 E = normalize(cam_pos - vec4(world_pos_out,1.0f));
    fragColor += k_a*cA;

    for(int i = 0; i < num_dir_lights; i++){
        vec4 interToLight =-normalize(dir_light_dir[i]);
        vec4 reflectLight = 2.0f * dot(normfinal, interToLight)*normfinal-interToLight;
        vec4 color = dir_light_color[i];
        fragColor += color*k_d*cD*clamp(dot(normfinal,interToLight),0.0f,1.0f);
        if(shine > 0.0f){fragColor += color*k_s*cS*pow(clamp(dot(normalize(reflectLight),E),0.0f,1.0f),shine);}
    }
    for(int i = 0; i < num_point_lights; i++){
        vec3 func = point_light_func[i];
        float distance = length(point_light_pos[i] - world_pos_out);
        float att = min(1.0f, 1.0f/(func[0] + distance*func[1]+ pow(distance, 2.0f)*func[2]));
        vec4 interToLight = vec4(normalize(point_light_pos[i] - world_pos_out), 0.0f);
        vec4 reflectLight = 2.0f * dot(normfinal, interToLight)*normfinal-interToLight;
        vec4 color = point_light_color[i];
        fragColor += att*color*k_d*cD*clamp(dot(normfinal,interToLight),0.0f,1.0f);
        if(shine > 0.0f){fragColor += color*k_s*cS*pow(clamp(dot(normalize(reflectLight),E),0.0f,1.0f),shine);}
    }
    for(int i = 0; i < num_spot_lights; i++){
        vec3 func = spot_light_func[i];
        vec4 lightDir = normalize(spot_light_dir[i]);
        float distance = length(spot_light_pos[i] - world_pos_out);
        float att = min(1.0f, 1.0f/(func[0] + distance*func[1]+ pow(distance, 2.0f)*func[2]));
        vec4 interToLight = vec4(normalize(spot_light_pos[i] - world_pos_out), 0.0f);
        vec4 reflectLight = 2.0f * dot(normfinal, interToLight)*normfinal-interToLight;
        float x = acos((dot(interToLight,-lightDir) / (length(interToLight) * length(lightDir))));
        float inner = angle[i] - penumbra[i];
        float outer = angle[i];
        float fade = 1.0f;
        if(x <= inner){
            fade = 1.0f;
        }
        else if(inner < x && x <= outer){
            fade = 1.0f + 2.0f*pow((x - inner)/(outer - inner),3.0f) - 3*pow((x - inner)/(outer - inner),2.0f);
        }
        else{
            fade = 0.0f;
        }
        vec4 color = spot_light_color[i];
        fragColor += fade*att*color*k_d*cD*clamp(dot(normfinal,interToLight),0.0f,1.0f);
        if(shine > 0.0f){fragColor += color*k_s*cS*pow(clamp(dot(normalize(reflectLight),E),0.0f,1.0f),shine);}
    }

}
