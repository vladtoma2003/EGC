#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform int light_type;


uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

vec3 point_light_contribution(vec3 light_pos, vec3 light_color);

void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    
    vec3 L = normalize(light_position - world_position);
    float diffuse_light = material_kd * max(dot(world_normal, L), 0.0);
    
    //vec3 L2 = normalize(light_position[1] - world_position);
    //float diffuse_light2 = material_kd * max(dot(world_normal, L2), 0.0);
    
    //float diffuse_light = diffuse_light1 + diffuse_light2;
    
   // vec3 L2 = normalize(light_position2 - world_position);
    //float diffuse_light2 = material_kd * max(dot(world_normal, L2), 0.0);
    
    //vec3 L = normalize(L1 + L2);
    
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        vec3 R = normalize(reflect(-L, world_normal));
        specular_light = material_ks * pow(max(dot(R, V), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    
    float total_light;
    
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    //float distance = length(light_position - world_position);
    float distance = length(light_position - world_position);
    //float distance2 = length(light_position[1] - world_position);
    
    float attenuation = 1 / (0.1+distance*distance);
    //float attenuation = 1 / (0.1+distance1*distance1);
    //float attenuation2 = 1 / (0.1+distance2*distance2);
    
    if(light_type == 1) {
        float cut_off = radians(30.f);
        float spot_light = dot(normalize(light_direction), -L);
        float spot_light_limit = cos(cut_off);  
        if(spot_light > spot_light_limit){
            float linear_att = (spot_light - spot_light_limit) / (1.f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);
            total_light = ambient_light +  ( diffuse_light + specular_light) * light_att_factor;
        } else {
            total_light = ambient_light;
        }
    } else {
        total_light = ambient_light + attenuation * ( diffuse_light + specular_light);
        //total_light = ambient_light + attenuation1 * ( diffuse_light1 + specular_light);
    }
    // TODO(student): Write pixel out color
    out_color = vec4(object_color * total_light, 1);

}
