#version 150

#define PI 3.14159
#define FACTOR 1.5

const float reflection_factor = 1;
const int alpha = 30;

uniform float AmbientIntensity;
uniform float LightIntensity;
uniform vec3 CameraPosition;
uniform vec3 PlanetColor;
uniform vec3 AmbientColor;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform bool Cel;

in vec3 Position;
in vec3 Normal;
out vec4 out_Color;

void main() {
  vec3 light_direction = LightPosition - Position; //calculates direction from surface pt to light source
  
  // Ambient
  vec3 ambient = AmbientIntensity * AmbientColor;
  
  // Diffuse
  float diffuse_strength = max(dot(normalize(light_direction), normalize(Normal)), 0.0); //max for +ve
  vec3 diffuse = PlanetColor * diffuse_strength;
  
  // Blinn-Phong local illumination
  vec3 view_direction = normalize(CameraPosition - Position);
  vec3 halfway_vector = normalize(light_direction + view_direction); //halfway vec
  float specular_strength = pow(max(dot(normalize(Normal), halfway_vector), 0.0), 4 * alpha);
  vec3 specular = reflection_factor * AmbientColor * specular_strength;


  vec3 lighting = ambient + LightIntensity * (diffuse + specular);
  out_Color = vec4(lighting, 1.0);
}
