#include <GL/gl.h>

const char* const timeWarpChromaticVertexProgramGLSL =
	"#version " GLSL_VERSION "\n"
	"uniform highp mat4x4 TimeWarpStartTransform;\n"
	"uniform highp mat4x4 TimeWarpEndTransform;\n"
	"in highp vec3 vertexPosition;\n"
	"in highp vec2 vertexUv0;\n"
	"in highp vec2 vertexUv1;\n"
	"in highp vec2 vertexUv2;\n"
	"out mediump vec2 fragmentUv0;\n"
	"out mediump vec2 fragmentUv1;\n"
	"out mediump vec2 fragmentUv2;\n"
	"out gl_PerVertex { vec4 gl_Position; };\n"
	"void main( void )\n"
	"{\n"
	"	gl_Position = vec4( vertexPosition, 1.0 );\n"
	"\n"
	"	float displayFraction = vertexPosition.x * 0.5 + 0.5;\n"	// landscape left-to-right
	"\n"
	"	vec3 startUv0 = (TimeWarpStartTransform * vec4( vertexUv0, -1, 1 )).xyz;\n"
	"	vec3 startUv1 = (TimeWarpStartTransform * vec4( vertexUv1, -1, 1 )).xyz;\n"
	"	vec3 startUv2 = (TimeWarpStartTransform * vec4( vertexUv2, -1, 1 )).xyz;\n"
	"\n"
	"	vec3 endUv0 = (TimeWarpEndTransform * vec4( vertexUv0, -1, 1 )).xyz;\n"
	"	vec3 endUv1 = (TimeWarpEndTransform * vec4( vertexUv1, -1, 1 )).xyz;\n"
	"	vec3 endUv2 = (TimeWarpEndTransform * vec4( vertexUv2, -1, 1 )).xyz;\n"
	"\n"
	"	vec3 curUv0 = mix( startUv0, endUv0, displayFraction );\n"
	"	vec3 curUv1 = mix( startUv1, endUv1, displayFraction );\n"
	"	vec3 curUv2 = mix( startUv2, endUv2, displayFraction );\n"
	"\n"
	"	fragmentUv0 = curUv0.xy * ( 1.0 / max( curUv0.z, 0.00001 ) );\n"
	"	fragmentUv1 = curUv1.xy * ( 1.0 / max( curUv1.z, 0.00001 ) );\n"
	"	fragmentUv2 = curUv2.xy * ( 1.0 / max( curUv2.z, 0.00001 ) );\n"
	"}\n";

const char* const timeWarpChromaticFragmentProgramGLSL =
	"#version " GLSL_VERSION "\n"
	"uniform int ArrayLayer;\n"
	"uniform highp sampler2DArray Texture;\n"
	"in mediump vec2 fragmentUv0;\n"
	"in mediump vec2 fragmentUv1;\n"
	"in mediump vec2 fragmentUv2;\n"
	"out lowp vec4 outColor;\n"
	"void main()\n"
	"{\n"
	"	outColor.r = texture( Texture, vec3( fragmentUv0, ArrayLayer ) ).r;\n"
	"	outColor.g = texture( Texture, vec3( fragmentUv1, ArrayLayer ) ).g;\n"
	"	outColor.b = texture( Texture, vec3( fragmentUv2, ArrayLayer ) ).b;\n"
	"	outColor.a = 1.0;\n"
	"}\n";

const char* const timeWarpChromaticFragmentProgramGLSL_Alternative =
	"#version " GLSL_VERSION "\n"
	"uniform int ArrayLayer;\n"
	"uniform highp sampler2D Texture;\n"
	"in mediump vec2 fragmentUv0;\n"
	"in mediump vec2 fragmentUv1;\n"
	"in mediump vec2 fragmentUv2;\n"
	"out lowp vec4 outColor;\n"
	"void main()\n"
	"{\n"
	"	outColor.r = texture( Texture, fragmentUv0 ).r;\n"
	"	outColor.g = texture( Texture, fragmentUv1 ).g;\n"
	"	outColor.b = texture( Texture, fragmentUv2 ).b;\n"
	"	outColor.a = 1.0;\n"
	"}\n";
