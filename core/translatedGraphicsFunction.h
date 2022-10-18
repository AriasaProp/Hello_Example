#ifndef Included_TGF
#define Included_TGF

namespace TGF {
	const unsigned int GL_DEPTH_BUFFER_BIT = 0x00000100;
	const unsigned int GL_STENCIL_BUFFER_BIT = 0x00000400;
	const unsigned int GL_COLOR_BUFFER_BIT = 0x00004000;
	const unsigned int GL_FALSE = 0;
	const unsigned int GL_TRUE = 1;
	const unsigned int GL_POINTS = 0x0000;
	const unsigned int GL_LINES = 0x0001;
	const unsigned int GL_LINE_LOOP = 0x0002;
	const unsigned int GL_LINE_STRIP = 0x0003;
	const unsigned int GL_TRIANGLES = 0x0004;
	const unsigned int GL_TRIANGLE_STRIP = 0x0005;
	const unsigned int GL_TRIANGLE_FAN = 0x0006;
	const unsigned int GL_ZERO = 0;
	const unsigned int GL_ONE = 1;
	const unsigned int GL_SRC_COLOR = 0x0300;
	const unsigned int GL_ONE_MINUS_SRC_COLOR = 0x0301;
	const unsigned int GL_SRC_ALPHA = 0x0302;
	const unsigned int GL_ONE_MINUS_SRC_ALPHA = 0x0303;
	const unsigned int GL_DST_ALPHA = 0x0304;
	const unsigned int GL_ONE_MINUS_DST_ALPHA = 0x0305;
	const unsigned int GL_DST_COLOR = 0x0306;
	const unsigned int GL_ONE_MINUS_DST_COLOR = 0x0307;
	const unsigned int GL_SRC_ALPHA_SATURATE = 0x0308;
	const unsigned int GL_FUNC_ADD = 0x8006;
	const unsigned int GL_BLEND_EQUATION = 0x8009;
	const unsigned int GL_BLEND_EQUATION_RGB = 0x8009;
	const unsigned int GL_BLEND_EQUATION_ALPHA = 0x883D;
	const unsigned int GL_FUNC_SUBTRACT = 0x800A;
	const unsigned int GL_FUNC_REVERSE_SUBTRACT = 0x800B;
	const unsigned int GL_BLEND_DST_RGB = 0x80C8;
	const unsigned int GL_BLEND_SRC_RGB = 0x80C9;
	const unsigned int GL_BLEND_DST_ALPHA = 0x80CA;
	const unsigned int GL_BLEND_SRC_ALPHA = 0x80CB;
	const unsigned int GL_CONSTANT_COLOR = 0x8001;
	const unsigned int GL_ONE_MINUS_CONSTANT_COLOR = 0x8002;
	const unsigned int GL_CONSTANT_ALPHA = 0x8003;
	const unsigned int GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004;
	const unsigned int GL_BLEND_COLOR = 0x8005;
	const unsigned int GL_ARRAY_BUFFER = 0x8892;
	const unsigned int GL_ELEMENT_ARRAY_BUFFER = 0x8893;
	const unsigned int GL_ARRAY_BUFFER_BINDING = 0x8894;
	const unsigned int GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
	const unsigned int GL_STREAM_DRAW = 0x88E0;
	const unsigned int GL_STATIC_DRAW = 0x88E4;
	const unsigned int GL_DYNAMIC_DRAW = 0x88E8;
	const unsigned int GL_BUFFER_SIZE = 0x8764;
	const unsigned int GL_BUFFER_USAGE = 0x8765;
	const unsigned int GL_CURRENT_VERTEX_ATTRIB = 0x8626;
	const unsigned int GL_FRONT = 0x0404;
	const unsigned int GL_BACK = 0x0405;
	const unsigned int GL_FRONT_AND_BACK = 0x0408;
	const unsigned int GL_TEXTURE_2D = 0x0DE1;
	const unsigned int GL_CULL_FACE = 0x0B44;
	const unsigned int GL_BLEND = 0x0BE2;
	const unsigned int GL_DITHER = 0x0BD0;
	const unsigned int GL_STENCIL_TEST = 0x0B90;
	const unsigned int GL_DEPTH_TEST = 0x0B71;
	const unsigned int GL_SCISSOR_TEST = 0x0C11;
	const unsigned int GL_POLYGON_OFFSET_FILL = 0x8037;
	const unsigned int GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
	const unsigned int GL_SAMPLE_COVERAGE = 0x80A0;
	const unsigned int GL_NO_ERROR = 0;
	const unsigned int GL_INVALID_ENUM = 0x0500;
	const unsigned int GL_INVALID_VALUE = 0x0501;
	const unsigned int GL_INVALID_OPERATION = 0x0502;
	const unsigned int GL_OUT_OF_MEMORY = 0x0505;
	const unsigned int GL_CW = 0x0900;
	const unsigned int GL_CCW = 0x0901;
	const unsigned int GL_LINE_WIDTH = 0x0B21;
	const unsigned int GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
	const unsigned int GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
	const unsigned int GL_CULL_FACE_MODE = 0x0B45;
	const unsigned int GL_FRONT_FACE = 0x0B46;
	const unsigned int GL_DEPTH_RANGE = 0x0B70;
	const unsigned int GL_DEPTH_WRITEMASK = 0x0B72;
	const unsigned int GL_DEPTH_CLEAR_VALUE = 0x0B73;
	const unsigned int GL_DEPTH_FUNC = 0x0B74;
	const unsigned int GL_STENCIL_CLEAR_VALUE = 0x0B91;
	const unsigned int GL_STENCIL_FUNC = 0x0B92;
	const unsigned int GL_STENCIL_FAIL = 0x0B94;
	const unsigned int GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
	const unsigned int GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
	const unsigned int GL_STENCIL_REF = 0x0B97;
	const unsigned int GL_STENCIL_VALUE_MASK = 0x0B93;
	const unsigned int GL_STENCIL_WRITEMASK = 0x0B98;
	const unsigned int GL_STENCIL_BACK_FUNC = 0x8800;
	const unsigned int GL_STENCIL_BACK_FAIL = 0x8801;
	const unsigned int GL_STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802;
	const unsigned int GL_STENCIL_BACK_PASS_DEPTH_PASS = 0x8803;
	const unsigned int GL_STENCIL_BACK_REF = 0x8CA3;
	const unsigned int GL_STENCIL_BACK_VALUE_MASK = 0x8CA4;
	const unsigned int GL_STENCIL_BACK_WRITEMASK = 0x8CA5;
	const unsigned int GL_VIEWPORT = 0x0BA2;
	const unsigned int GL_SCISSOR_BOX = 0x0C10;
	const unsigned int GL_COLOR_CLEAR_VALUE = 0x0C22;
	const unsigned int GL_COLOR_WRITEMASK = 0x0C23;
	const unsigned int GL_UNPACK_ALIGNMENT = 0x0CF5;
	const unsigned int GL_PACK_ALIGNMENT = 0x0D05;
	const unsigned int GL_MAX_TEXTURE_SIZE = 0x0D33;
	const unsigned int GL_MAX_TEXTURE_UNITS = 0x84E2;
	const unsigned int GL_MAX_VIEWPORT_DIMS = 0x0D3A;
	const unsigned int GL_SUBPIXEL_BITS = 0x0D50;
	const unsigned int GL_RED_BITS = 0x0D52;
	const unsigned int GL_GREEN_BITS = 0x0D53;
	const unsigned int GL_BLUE_BITS = 0x0D54;
	const unsigned int GL_ALPHA_BITS = 0x0D55;
	const unsigned int GL_DEPTH_BITS = 0x0D56;
	const unsigned int GL_STENCIL_BITS = 0x0D57;
	const unsigned int GL_POLYGON_OFFSET_UNITS = 0x2A00;
	const unsigned int GL_POLYGON_OFFSET_FACTOR = 0x8038;
	const unsigned int GL_TEXTURE_BINDING_2D = 0x8069;
	const unsigned int GL_SAMPLE_BUFFERS = 0x80A8;
	const unsigned int GL_SAMPLES = 0x80A9;
	const unsigned int GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
	const unsigned int GL_SAMPLE_COVERAGE_INVERT = 0x80AB;
	const unsigned int GL_DONT_CARE = 0x1100;
	const unsigned int GL_FASTEST = 0x1101;
	const unsigned int GL_NICEST = 0x1102;
	const unsigned int GL_GENERATE_MIPMAP = 0x8191;
	const unsigned int GL_GENERATE_MIPMAP_HINT = 0x8192;
	const unsigned int GL_BYTE = 0x1400;
	const unsigned int GL_UNSIGNED_BYTE = 0x1401;
	const unsigned int GL_SHORT = 0x1402;
	const unsigned int GL_UNSIGNED_SHORT = 0x1403;
	const unsigned int GL_INT = 0x1404;
	const unsigned int GL_UNSIGNED_INT = 0x1405;
	const unsigned int GL_FLOAT = 0x1406;
	const unsigned int GL_FIXED = 0x140C;
	const unsigned int GL_DEPTH_COMPONENT = 0x1902;
	const unsigned int GL_ALPHA = 0x1906;
	const unsigned int GL_RGB = 0x1907;
	const unsigned int GL_RGBA = 0x1908;
	const unsigned int GL_LUMINANCE = 0x1909;
	const unsigned int GL_LUMINANCE_ALPHA = 0x190A;
	const unsigned int GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
	const unsigned int GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
	const unsigned int GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
	const unsigned int GL_FRAGMENT_SHADER = 0x8B30;
	const unsigned int GL_MAX_VERTEX_ATTRIBS = 0x8869;
	const unsigned int GL_MAX_VERTEX_UNIFORM_VECTORS = 0x8DFB;
	const unsigned int GL_MAX_VARYING_VECTORS = 0x8DFC;
	const unsigned int GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
	const unsigned int GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
	const unsigned int GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872;
	const unsigned int GL_MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD;
	const unsigned int GL_SHADER_TYPE = 0x8B4F;
	const unsigned int GL_DELETE_STATUS = 0x8B80;
	const unsigned int GL_LINK_STATUS = 0x8B82;
	const unsigned int GL_VALIDATE_STATUS = 0x8B83;
	const unsigned int GL_ATTACHED_SHADERS = 0x8B85;
	const unsigned int GL_ACTIVE_UNIFORMS = 0x8B86;
	const unsigned int GL_ACTIVE_UNIFORM_MAX_LENGTH = 0x8B87;
	const unsigned int GL_ACTIVE_ATTRIBUTES = 0x8B89;
	const unsigned int GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A;
	const unsigned int GL_SHADING_LANGUAGE_VERSION = 0x8B8C;
	const unsigned int GL_CURRENT_PROGRAM = 0x8B8D;
	const unsigned int GL_NEVER = 0x0200;
	const unsigned int GL_LESS = 0x0201;
	const unsigned int GL_EQUAL = 0x0202;
	const unsigned int GL_LEQUAL = 0x0203;
	const unsigned int GL_GREATER = 0x0204;
	const unsigned int GL_NOTEQUAL = 0x0205;
	const unsigned int GL_GEQUAL = 0x0206;
	const unsigned int GL_ALWAYS = 0x0207;
	const unsigned int GL_KEEP = 0x1E00;
	const unsigned int GL_REPLACE = 0x1E01;
	const unsigned int GL_INCR = 0x1E02;
	const unsigned int GL_DECR = 0x1E03;
	const unsigned int GL_INVERT = 0x150A;
	const unsigned int GL_INCR_WRAP = 0x8507;
	const unsigned int GL_DECR_WRAP = 0x8508;
	const unsigned int GL_VENDOR = 0x1F00;
	const unsigned int GL_RENDERER = 0x1F01;
	const unsigned int GL_VERSION = 0x1F02;
	const unsigned int GL_EXTENSIONS = 0x1F03;
	const unsigned int GL_NEAREST = 0x2600;
	const unsigned int GL_LINEAR = 0x2601;
	const unsigned int GL_NEAREST_MIPMAP_NEAREST = 0x2700;
	const unsigned int GL_LINEAR_MIPMAP_NEAREST = 0x2701;
	const unsigned int GL_NEAREST_MIPMAP_LINEAR = 0x2702;
	const unsigned int GL_LINEAR_MIPMAP_LINEAR = 0x2703;
	const unsigned int GL_TEXTURE_MAG_FILTER = 0x2800;
	const unsigned int GL_TEXTURE_MIN_FILTER = 0x2801;
	const unsigned int GL_TEXTURE_WRAP_S = 0x2802;
	const unsigned int GL_TEXTURE_WRAP_T = 0x2803;
	const unsigned int GL_TEXTURE = 0x1702;
	const unsigned int GL_TEXTURE_CUBE_MAP = 0x8513;
	const unsigned int GL_TEXTURE_BINDING_CUBE_MAP = 0x8514;
	const unsigned int GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
	const unsigned int GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
	const unsigned int GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
	const unsigned int GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
	const unsigned int GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
	const unsigned int GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
	const unsigned int GL_MAX_CUBE_MAP_TEXTURE_SIZE = 0x851C;
	const unsigned int GL_ACTIVE_TEXTURE = 0x84E0;
	const unsigned int GL_REPEAT = 0x2901;
	const unsigned int GL_CLAMP_TO_EDGE = 0x812F;
	const unsigned int GL_MIRRORED_REPEAT = 0x8370;
	const unsigned int GL_FLOAT_VEC2 = 0x8B50;
	const unsigned int GL_FLOAT_VEC3 = 0x8B51;
	const unsigned int GL_FLOAT_VEC4 = 0x8B52;
	const unsigned int GL_INT_VEC2 = 0x8B53;
	const unsigned int GL_INT_VEC3 = 0x8B54;
	const unsigned int GL_INT_VEC4 = 0x8B55;
	const unsigned int GL_BOOL = 0x8B56;
	const unsigned int GL_BOOL_VEC2 = 0x8B57;
	const unsigned int GL_BOOL_VEC3 = 0x8B58;
	const unsigned int GL_BOOL_VEC4 = 0x8B59;
	const unsigned int GL_FLOAT_MAT2 = 0x8B5A;
	const unsigned int GL_FLOAT_MAT3 = 0x8B5B;
	const unsigned int GL_FLOAT_MAT4 = 0x8B5C;
	const unsigned int GL_SAMPLER_2D = 0x8B5E;
	const unsigned int GL_SAMPLER_CUBE = 0x8B60;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_POINTER = 0x8645;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
	const unsigned int GL_IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A;
	const unsigned int GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;
	const unsigned int GL_COMPILE_STATUS = 0x8B81;
	const unsigned int GL_INFO_LOG_LENGTH = 0x8B84;
	const unsigned int GL_SHADER_SOURCE_LENGTH = 0x8B88;
	const unsigned int GL_SHADER_COMPILER = 0x8DFA;
	const unsigned int GL_SHADER_BINARY_FORMATS = 0x8DF8;
	const unsigned int GL_NUM_SHADER_BINARY_FORMATS = 0x8DF9;
	const unsigned int GL_LOW_FLOAT = 0x8DF0;
	const unsigned int GL_MEDIUM_FLOAT = 0x8DF1;
	const unsigned int GL_HIGH_FLOAT = 0x8DF2;
	const unsigned int GL_LOW_INT = 0x8DF3;
	const unsigned int GL_MEDIUM_INT = 0x8DF4;
	const unsigned int GL_HIGH_INT = 0x8DF5;
	const unsigned int GL_FRAMEBUFFER = 0x8D40;
	const unsigned int GL_RENDERBUFFER = 0x8D41;
	const unsigned int GL_RGBA4 = 0x8056;
	const unsigned int GL_RGB5_A1 = 0x8057;
	const unsigned int GL_RGB565 = 0x8D62;
	const unsigned int GL_DEPTH_COMPONENT16 = 0x81A5;
	const unsigned int GL_STENCIL_INDEX = 0x1901;
	const unsigned int GL_STENCIL_INDEX8 = 0x8D48;
	const unsigned int GL_RENDERBUFFER_WIDTH = 0x8D42;
	const unsigned int GL_RENDERBUFFER_HEIGHT = 0x8D43;
	const unsigned int GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;
	const unsigned int GL_RENDERBUFFER_RED_SIZE = 0x8D50;
	const unsigned int GL_RENDERBUFFER_GREEN_SIZE = 0x8D51;
	const unsigned int GL_RENDERBUFFER_BLUE_SIZE = 0x8D52;
	const unsigned int GL_RENDERBUFFER_ALPHA_SIZE = 0x8D53;
	const unsigned int GL_RENDERBUFFER_DEPTH_SIZE = 0x8D54;
	const unsigned int GL_RENDERBUFFER_STENCIL_SIZE = 0x8D55;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;
	const unsigned int GL_COLOR_ATTACHMENT0 = 0x8CE0;
	const unsigned int GL_DEPTH_ATTACHMENT = 0x8D00;
	const unsigned int GL_STENCIL_ATTACHMENT = 0x8D20;
	const unsigned int GL_NONE = 0;
	const unsigned int GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
	const unsigned int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
	const unsigned int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
	const unsigned int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS = 0x8CD9;
	const unsigned int GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD;
	const unsigned int GL_FRAMEBUFFER_BINDING = 0x8CA6;
	const unsigned int GL_RENDERBUFFER_BINDING = 0x8CA7;
	const unsigned int GL_MAX_RENDERBUFFER_SIZE = 0x84E8;
	const unsigned int GL_INVALID_FRAMEBUFFER_OPERATION = 0x0506;
	const unsigned int GL_VERTEX_PROGRAM_POINT_SIZE = 0x8642;
	const unsigned int GL_READ_BUFFER = 0x0C02;
	const unsigned int GL_UNPACK_ROW_LENGTH = 0x0CF2;
	const unsigned int GL_UNPACK_SKIP_ROWS = 0x0CF3;
	const unsigned int GL_UNPACK_SKIP_PIXELS = 0x0CF4;
	const unsigned int GL_PACK_ROW_LENGTH = 0x0D02;
	const unsigned int GL_PACK_SKIP_ROWS = 0x0D03;
	const unsigned int GL_PACK_SKIP_PIXELS = 0x0D04;
	const unsigned int GL_COLOR = 0x1800;
	const unsigned int GL_DEPTH = 0x1801;
	const unsigned int GL_STENCIL = 0x1802;
	const unsigned int GL_RED = 0x1903;
	const unsigned int GL_RGB8 = 0x8051;
	const unsigned int GL_RGBA8 = 0x8058;
	const unsigned int GL_RGB10_A2 = 0x8059;
	const unsigned int GL_TEXTURE_BINDING_3D = 0x806A;
	const unsigned int GL_UNPACK_SKIP_IMAGES = 0x806D;
	const unsigned int GL_UNPACK_IMAGE_HEIGHT = 0x806E;
	const unsigned int GL_TEXTURE_3D = 0x806F;
	const unsigned int GL_TEXTURE_WRAP_R = 0x8072;
	const unsigned int GL_MAX_3D_TEXTURE_SIZE = 0x8073;
	const unsigned int GL_UNSIGNED_INT_2_10_10_10_REV = 0x8368;
	const unsigned int GL_MAX_ELEMENTS_VERTICES = 0x80E8;
	const unsigned int GL_MAX_ELEMENTS_INDICES = 0x80E9;
	const unsigned int GL_TEXTURE_MIN_LOD = 0x813A;
	const unsigned int GL_TEXTURE_MAX_LOD = 0x813B;
	const unsigned int GL_TEXTURE_BASE_LEVEL = 0x813C;
	const unsigned int GL_TEXTURE_MAX_LEVEL = 0x813D;
	const unsigned int GL_MIN = 0x8007;
	const unsigned int GL_MAX = 0x8008;
	const unsigned int GL_DEPTH_COMPONENT24 = 0x81A6;
	const unsigned int GL_MAX_TEXTURE_LOD_BIAS = 0x84FD;
	const unsigned int GL_TEXTURE_COMPARE_MODE = 0x884C;
	const unsigned int GL_TEXTURE_COMPARE_FUNC = 0x884D;
	const unsigned int GL_CURRENT_QUERY = 0x8865;
	const unsigned int GL_QUERY_RESULT = 0x8866;
	const unsigned int GL_QUERY_RESULT_AVAILABLE = 0x8867;
	const unsigned int GL_BUFFER_MAPPED = 0x88BC;
	const unsigned int GL_BUFFER_MAP_POINTER = 0x88BD;
	const unsigned int GL_STREAM_READ = 0x88E1;
	const unsigned int GL_STREAM_COPY = 0x88E2;
	const unsigned int GL_STATIC_READ = 0x88E5;
	const unsigned int GL_STATIC_COPY = 0x88E6;
	const unsigned int GL_DYNAMIC_READ = 0x88E9;
	const unsigned int GL_DYNAMIC_COPY = 0x88EA;
	const unsigned int GL_MAX_DRAW_BUFFERS = 0x8824;
	const unsigned int GL_DRAW_BUFFER0 = 0x8825;
	const unsigned int GL_DRAW_BUFFER1 = 0x8826;
	const unsigned int GL_DRAW_BUFFER2 = 0x8827;
	const unsigned int GL_DRAW_BUFFER3 = 0x8828;
	const unsigned int GL_DRAW_BUFFER4 = 0x8829;
	const unsigned int GL_DRAW_BUFFER5 = 0x882A;
	const unsigned int GL_DRAW_BUFFER6 = 0x882B;
	const unsigned int GL_DRAW_BUFFER7 = 0x882C;
	const unsigned int GL_DRAW_BUFFER8 = 0x882D;
	const unsigned int GL_DRAW_BUFFER9 = 0x882E;
	const unsigned int GL_DRAW_BUFFER10 = 0x882F;
	const unsigned int GL_DRAW_BUFFER11 = 0x8830;
	const unsigned int GL_DRAW_BUFFER12 = 0x8831;
	const unsigned int GL_DRAW_BUFFER13 = 0x8832;
	const unsigned int GL_DRAW_BUFFER14 = 0x8833;
	const unsigned int GL_DRAW_BUFFER15 = 0x8834;
	const unsigned int GL_MAX_FRAGMENT_UNIFORM_COMPONENTS = 0x8B49;
	const unsigned int GL_MAX_VERTEX_UNIFORM_COMPONENTS = 0x8B4A;
	const unsigned int GL_SAMPLER_3D = 0x8B5F;
	const unsigned int GL_SAMPLER_2D_SHADOW = 0x8B62;
	const unsigned int GL_FRAGMENT_SHADER_DERIVATIVE_HINT = 0x8B8B;
	const unsigned int GL_PIXEL_PACK_BUFFER = 0x88EB;
	const unsigned int GL_PIXEL_UNPACK_BUFFER = 0x88EC;
	const unsigned int GL_PIXEL_PACK_BUFFER_BINDING = 0x88ED;
	const unsigned int GL_PIXEL_UNPACK_BUFFER_BINDING = 0x88EF;
	const unsigned int GL_FLOAT_MAT2x3 = 0x8B65;
	const unsigned int GL_FLOAT_MAT2x4 = 0x8B66;
	const unsigned int GL_FLOAT_MAT3x2 = 0x8B67;
	const unsigned int GL_FLOAT_MAT3x4 = 0x8B68;
	const unsigned int GL_FLOAT_MAT4x2 = 0x8B69;
	const unsigned int GL_FLOAT_MAT4x3 = 0x8B6A;
	const unsigned int GL_SRGB = 0x8C40;
	const unsigned int GL_SRGB8 = 0x8C41;
	const unsigned int GL_SRGB8_ALPHA8 = 0x8C43;
	const unsigned int GL_COMPARE_REF_TO_TEXTURE = 0x884E;
	const unsigned int GL_MAJOR_VERSION = 0x821B;
	const unsigned int GL_MINOR_VERSION = 0x821C;
	const unsigned int GL_NUM_EXTENSIONS = 0x821D;
	const unsigned int GL_RGBA32F = 0x8814;
	const unsigned int GL_RGB32F = 0x8815;
	const unsigned int GL_RGBA16F = 0x881A;
	const unsigned int GL_RGB16F = 0x881B;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_INTEGER = 0x88FD;
	const unsigned int GL_MAX_ARRAY_TEXTURE_LAYERS = 0x88FF;
	const unsigned int GL_MIN_PROGRAM_TEXEL_OFFSET = 0x8904;
	const unsigned int GL_MAX_PROGRAM_TEXEL_OFFSET = 0x8905;
	const unsigned int GL_MAX_VARYING_COMPONENTS = 0x8B4B;
	const unsigned int GL_TEXTURE_2D_ARRAY = 0x8C1A;
	const unsigned int GL_TEXTURE_BINDING_2D_ARRAY = 0x8C1D;
	const unsigned int GL_R11F_G11F_B10F = 0x8C3A;
	const unsigned int GL_UNSIGNED_INT_10F_11F_11F_REV = 0x8C3B;
	const unsigned int GL_RGB9_E5 = 0x8C3D;
	const unsigned int GL_UNSIGNED_INT_5_9_9_9_REV = 0x8C3E;
	const unsigned int GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76;
	const unsigned int GL_TRANSFORM_FEEDBACK_BUFFER_MODE = 0x8C7F;
	const unsigned int GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80;
	const unsigned int GL_TRANSFORM_FEEDBACK_VARYINGS = 0x8C83;
	const unsigned int GL_TRANSFORM_FEEDBACK_BUFFER_START = 0x8C84;
	const unsigned int GL_TRANSFORM_FEEDBACK_BUFFER_SIZE = 0x8C85;
	const unsigned int GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88;
	const unsigned int GL_RASTERIZER_DISCARD = 0x8C89;
	const unsigned int GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A;
	const unsigned int GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B;
	const unsigned int GL_INTERLEAVED_ATTRIBS = 0x8C8C;
	const unsigned int GL_SEPARATE_ATTRIBS = 0x8C8D;
	const unsigned int GL_TRANSFORM_FEEDBACK_BUFFER = 0x8C8E;
	const unsigned int GL_TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F;
	const unsigned int GL_RGBA32UI = 0x8D70;
	const unsigned int GL_RGB32UI = 0x8D71;
	const unsigned int GL_RGBA16UI = 0x8D76;
	const unsigned int GL_RGB16UI = 0x8D77;
	const unsigned int GL_RGBA8UI = 0x8D7C;
	const unsigned int GL_RGB8UI = 0x8D7D;
	const unsigned int GL_RGBA32I = 0x8D82;
	const unsigned int GL_RGB32I = 0x8D83;
	const unsigned int GL_RGBA16I = 0x8D88;
	const unsigned int GL_RGB16I = 0x8D89;
	const unsigned int GL_RGBA8I = 0x8D8E;
	const unsigned int GL_RGB8I = 0x8D8F;
	const unsigned int GL_RED_INTEGER = 0x8D94;
	const unsigned int GL_RGB_INTEGER = 0x8D98;
	const unsigned int GL_RGBA_INTEGER = 0x8D99;
	const unsigned int GL_SAMPLER_2D_ARRAY = 0x8DC1;
	const unsigned int GL_SAMPLER_2D_ARRAY_SHADOW = 0x8DC4;
	const unsigned int GL_SAMPLER_CUBE_SHADOW = 0x8DC5;
	const unsigned int GL_UNSIGNED_INT_VEC2 = 0x8DC6;
	const unsigned int GL_UNSIGNED_INT_VEC3 = 0x8DC7;
	const unsigned int GL_UNSIGNED_INT_VEC4 = 0x8DC8;
	const unsigned int GL_INT_SAMPLER_2D = 0x8DCA;
	const unsigned int GL_INT_SAMPLER_3D = 0x8DCB;
	const unsigned int GL_INT_SAMPLER_CUBE = 0x8DCC;
	const unsigned int GL_INT_SAMPLER_2D_ARRAY = 0x8DCF;
	const unsigned int GL_UNSIGNED_INT_SAMPLER_2D = 0x8DD2;
	const unsigned int GL_UNSIGNED_INT_SAMPLER_3D = 0x8DD3;
	const unsigned int GL_UNSIGNED_INT_SAMPLER_CUBE = 0x8DD4;
	const unsigned int GL_UNSIGNED_INT_SAMPLER_2D_ARRAY = 0x8DD7;
	const unsigned int GL_BUFFER_ACCESS_FLAGS = 0x911F;
	const unsigned int GL_BUFFER_MAP_LENGTH = 0x9120;
	const unsigned int GL_BUFFER_MAP_OFFSET = 0x9121;
	const unsigned int GL_DEPTH_COMPONENT32F = 0x8CAC;
	const unsigned int GL_DEPTH32F_STENCIL8 = 0x8CAD;
	const unsigned int GL_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE = 0x8212;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217;
	const unsigned int GL_FRAMEBUFFER_DEFAULT = 0x8218;
	const unsigned int GL_FRAMEBUFFER_UNDEFINED = 0x8219;
	const unsigned int GL_DEPTH_STENCIL_ATTACHMENT = 0x821A;
	const unsigned int GL_DEPTH_STENCIL = 0x84F9;
	const unsigned int GL_UNSIGNED_INT_24_8 = 0x84FA;
	const unsigned int GL_DEPTH24_STENCIL8 = 0x88F0;
	const unsigned int GL_UNSIGNED_NORMALIZED = 0x8C17;
	const unsigned int GL_DRAW_FRAMEBUFFER_BINDING = GL_FRAMEBUFFER_BINDING;
	const unsigned int GL_READ_FRAMEBUFFER = 0x8CA8;
	const unsigned int GL_DRAW_FRAMEBUFFER = 0x8CA9;
	const unsigned int GL_READ_FRAMEBUFFER_BINDING = 0x8CAA;
	const unsigned int GL_RENDERBUFFER_SAMPLES = 0x8CAB;
	const unsigned int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = 0x8CD4;
	const unsigned int GL_MAX_COLOR_ATTACHMENTS = 0x8CDF;
	const unsigned int GL_COLOR_ATTACHMENT1 = 0x8CE1;
	const unsigned int GL_COLOR_ATTACHMENT2 = 0x8CE2;
	const unsigned int GL_COLOR_ATTACHMENT3 = 0x8CE3;
	const unsigned int GL_COLOR_ATTACHMENT4 = 0x8CE4;
	const unsigned int GL_COLOR_ATTACHMENT5 = 0x8CE5;
	const unsigned int GL_COLOR_ATTACHMENT6 = 0x8CE6;
	const unsigned int GL_COLOR_ATTACHMENT7 = 0x8CE7;
	const unsigned int GL_COLOR_ATTACHMENT8 = 0x8CE8;
	const unsigned int GL_COLOR_ATTACHMENT9 = 0x8CE9;
	const unsigned int GL_COLOR_ATTACHMENT10 = 0x8CEA;
	const unsigned int GL_COLOR_ATTACHMENT11 = 0x8CEB;
	const unsigned int GL_COLOR_ATTACHMENT12 = 0x8CEC;
	const unsigned int GL_COLOR_ATTACHMENT13 = 0x8CED;
	const unsigned int GL_COLOR_ATTACHMENT14 = 0x8CEE;
	const unsigned int GL_COLOR_ATTACHMENT15 = 0x8CEF;
	const unsigned int GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56;
	const unsigned int GL_MAX_SAMPLES = 0x8D57;
	const unsigned int GL_HALF_FLOAT = 0x140B;
	const unsigned int GL_MAP_READ_BIT = 0x0001;
	const unsigned int GL_MAP_WRITE_BIT = 0x0002;
	const unsigned int GL_MAP_INVALIDATE_RANGE_BIT = 0x0004;
	const unsigned int GL_MAP_INVALIDATE_BUFFER_BIT = 0x0008;
	const unsigned int GL_MAP_FLUSH_EXPLICIT_BIT = 0x0010;
	const unsigned int GL_MAP_UNSYNCHRONIZED_BIT = 0x0020;
	const unsigned int GL_RG = 0x8227;
	const unsigned int GL_RG_INTEGER = 0x8228;
	const unsigned int GL_R8 = 0x8229;
	const unsigned int GL_RG8 = 0x822B;
	const unsigned int GL_R16F = 0x822D;
	const unsigned int GL_R32F = 0x822E;
	const unsigned int GL_RG16F = 0x822F;
	const unsigned int GL_RG32F = 0x8230;
	const unsigned int GL_R8I = 0x8231;
	const unsigned int GL_R8UI = 0x8232;
	const unsigned int GL_R16I = 0x8233;
	const unsigned int GL_R16UI = 0x8234;
	const unsigned int GL_R32I = 0x8235;
	const unsigned int GL_R32UI = 0x8236;
	const unsigned int GL_RG8I = 0x8237;
	const unsigned int GL_RG8UI = 0x8238;
	const unsigned int GL_RG16I = 0x8239;
	const unsigned int GL_RG16UI = 0x823A;
	const unsigned int GL_RG32I = 0x823B;
	const unsigned int GL_RG32UI = 0x823C;
	const unsigned int GL_VERTEX_ARRAY_BINDING = 0x85B5;
	const unsigned int GL_R8_SNORM = 0x8F94;
	const unsigned int GL_RG8_SNORM = 0x8F95;
	const unsigned int GL_RGB8_SNORM = 0x8F96;
	const unsigned int GL_RGBA8_SNORM = 0x8F97;
	const unsigned int GL_SIGNED_NORMALIZED = 0x8F9C;
	const unsigned int GL_PRIMITIVE_RESTART_FIXED_INDEX = 0x8D69;
	const unsigned int GL_COPY_READ_BUFFER = 0x8F36;
	const unsigned int GL_COPY_WRITE_BUFFER = 0x8F37;
	const unsigned int GL_COPY_READ_BUFFER_BINDING = GL_COPY_READ_BUFFER;
	const unsigned int GL_COPY_WRITE_BUFFER_BINDING = GL_COPY_WRITE_BUFFER;
	const unsigned int GL_UNIFORM_BUFFER = 0x8A11;
	const unsigned int GL_UNIFORM_BUFFER_BINDING = 0x8A28;
	const unsigned int GL_UNIFORM_BUFFER_START = 0x8A29;
	const unsigned int GL_UNIFORM_BUFFER_SIZE = 0x8A2A;
	const unsigned int GL_MAX_VERTEX_UNIFORM_BLOCKS = 0x8A2B;
	const unsigned int GL_MAX_FRAGMENT_UNIFORM_BLOCKS = 0x8A2D;
	const unsigned int GL_MAX_COMBINED_UNIFORM_BLOCKS = 0x8A2E;
	const unsigned int GL_MAX_UNIFORM_BUFFER_BINDINGS = 0x8A2F;
	const unsigned int GL_MAX_UNIFORM_BLOCK_SIZE = 0x8A30;
	const unsigned int GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31;
	const unsigned int GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33;
	const unsigned int GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT = 0x8A34;
	const unsigned int GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35;
	const unsigned int GL_ACTIVE_UNIFORM_BLOCKS = 0x8A36;
	const unsigned int GL_UNIFORM_TYPE = 0x8A37;
	const unsigned int GL_UNIFORM_SIZE = 0x8A38;
	const unsigned int GL_UNIFORM_NAME_LENGTH = 0x8A39;
	const unsigned int GL_UNIFORM_BLOCK_INDEX = 0x8A3A;
	const unsigned int GL_UNIFORM_OFFSET = 0x8A3B;
	const unsigned int GL_UNIFORM_ARRAY_STRIDE = 0x8A3C;
	const unsigned int GL_UNIFORM_MATRIX_STRIDE = 0x8A3D;
	const unsigned int GL_UNIFORM_IS_ROW_MAJOR = 0x8A3E;
	const unsigned int GL_UNIFORM_BLOCK_BINDING = 0x8A3F;
	const unsigned int GL_UNIFORM_BLOCK_DATA_SIZE = 0x8A40;
	const unsigned int GL_UNIFORM_BLOCK_NAME_LENGTH = 0x8A41;
	const unsigned int GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS = 0x8A42;
	const unsigned int GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43;
	const unsigned int GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44;
	const unsigned int GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46;
	const unsigned int GL_INVALID_INDEX = 0xFFFFFFFF;
	const unsigned int GL_MAX_VERTEX_OUTPUT_COMPONENTS = 0x9122;
	const unsigned int GL_MAX_FRAGMENT_INPUT_COMPONENTS = 0x9125;
	const unsigned int GL_MAX_SERVER_WAIT_TIMEOUT = 0x9111;
	const unsigned int GL_OBJECT_TYPE = 0x9112;
	const unsigned int GL_SYNC_CONDITION = 0x9113;
	const unsigned int GL_SYNC_STATUS = 0x9114;
	const unsigned int GL_SYNC_FLAGS = 0x9115;
	const unsigned int GL_SYNC_FENCE = 0x9116;
	const unsigned int GL_SYNC_GPU_COMMANDS_COMPLETE = 0x9117;
	const unsigned int GL_UNSIGNALED = 0x9118;
	const unsigned int GL_SIGNALED = 0x9119;
	const unsigned int GL_ALREADY_SIGNALED = 0x911A;
	const unsigned int GL_TIMEOUT_EXPIRED = 0x911B;
	const unsigned int GL_CONDITION_SATISFIED = 0x911C;
	const unsigned int GL_WAIT_FAILED = 0x911D;
	const unsigned int GL_SYNC_FLUSH_COMMANDS_BIT = 0x00000001;
	const unsigned int GL_VERTEX_ATTRIB_ARRAY_DIVISOR = 0x88FE;
	const unsigned int GL_ANY_SAMPLES_PASSED = 0x8C2F;
	const unsigned int GL_ANY_SAMPLES_PASSED_CONSERVATIVE = 0x8D6A;
	const unsigned int GL_SAMPLER_BINDING = 0x8919;
	const unsigned int GL_RGB10_A2UI = 0x906F;
	const unsigned int GL_TEXTURE_SWIZZLE_R = 0x8E42;
	const unsigned int GL_TEXTURE_SWIZZLE_G = 0x8E43;
	const unsigned int GL_TEXTURE_SWIZZLE_B = 0x8E44;
	const unsigned int GL_TEXTURE_SWIZZLE_A = 0x8E45;
	const unsigned int GL_GREEN = 0x1904;
	const unsigned int GL_BLUE = 0x1905;
	const unsigned int GL_INT_2_10_10_10_REV = 0x8D9F;
	const unsigned int GL_TRANSFORM_FEEDBACK = 0x8E22;
	const unsigned int GL_TRANSFORM_FEEDBACK_PAUSED = 0x8E23;
	const unsigned int GL_TRANSFORM_FEEDBACK_ACTIVE = 0x8E24;
	const unsigned int GL_TRANSFORM_FEEDBACK_BINDING = 0x8E25;
	const unsigned int GL_PROGRAM_BINARY_RETRIEVABLE_HINT = 0x8257;
	const unsigned int GL_PROGRAM_BINARY_LENGTH = 0x8741;
	const unsigned int GL_NUM_PROGRAM_BINARY_FORMATS = 0x87FE;
	const unsigned int GL_PROGRAM_BINARY_FORMATS = 0x87FF;
	const unsigned int GL_TEXTURE_IMMUTABLE_FORMAT = 0x912F;
	const unsigned int GL_MAX_ELEMENT_INDEX = 0x8D6B;
	const unsigned int GL_NUM_SAMPLE_COUNTS = 0x9380;
	const unsigned int GL_TEXTURE_IMMUTABLE_LEVELS = 0x82DF;
	// GL_TIMEOUT_IGNORED is defined as 0xFFFFFFFFFFFFFFFFull in C.
	const unsigned long GL_TIMEOUT_IGNORED = (unsigned long)-1;
	// Extensions
	const unsigned int GL_COVERAGE_BUFFER_BIT_NV = 0x8000;
}

class TranslatedGraphicsFunction {
public:
	virtual ~TranslatedGraphicsFunction() {};
	virtual void clearcolormask(unsigned int, float, float, float, float) = 0;
	virtual void viewport(unsigned int, unsigned int, unsigned int, unsigned int) = 0;
};

#endif //Included_TGF