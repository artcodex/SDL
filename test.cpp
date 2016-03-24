#include "precomp.h"
#include "shapelib.h"

b2Vec2 gravity(0.0f, -9.8f);
b2World world(gravity);

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertexShaderCode;
  std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);

  if (vertexShaderStream.is_open()) {
    std::string line = "";
    while(getline(vertexShaderStream, line)) {
      vertexShaderCode += "\n" + line;
    }

    vertexShaderStream.close();
  } else {
    printf("Unable to open vertex shader %s\n", vertex_file_path);
    getchar();
  }

  std::string fragmentShaderCode;
  std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);

  if (fragmentShaderStream.is_open()) {
    std::string line = "";
    while(getline(fragmentShaderStream, line)) {
      fragmentShaderCode += "\n" + line;
    }

    fragmentShaderStream.close();
  } else {
    printf("Unable to open fragment shader %s\n", fragment_file_path);
    getchar();
  }

  GLint result = GL_FALSE;
  int infoLogLength;

  printf("Compiling shader %s\n", vertex_file_path);
  char const *vertexCodePtr = vertexShaderCode.c_str();
  glShaderSource(vertexShaderID, 1, &vertexCodePtr, NULL);
  glCompileShader(vertexShaderID);

  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> vertexShaderMsg(infoLogLength+1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderMsg[0]);
    printf("%s\n", &vertexShaderMsg[0]);
  }

  printf("Compiling shader %s\n", fragment_file_path);
  char const *fragmentCodePtr = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentCodePtr, NULL);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> fragmentShaderMsg(infoLogLength+1);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderMsg[0]);
    printf("%s\n", &fragmentShaderMsg[0]);
  }
  
  //Link shaders
  printf("Linking program\n");
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

  if (infoLogLength > 0) {
    std::vector<char> linkMsg(infoLogLength+1);
    glGetProgramInfoLog(programID, infoLogLength, NULL, &linkMsg[0]);
    printf("%s\n", &linkMsg[0]);
  }
  
  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

   return programID;
}

SDL_Joystick *joystick = NULL;

void InitializeJoysticks() {
  printf ("%i joysticks were found.\n\n", SDL_NumJoysticks());
  printf ("Names of joysticks are: \n");

  for (int i=0; i < SDL_NumJoysticks(); i++) {
    SDL_Joystick *current = SDL_JoystickOpen(i);
    if (current) {
      printf("    %s\n", SDL_JoystickName(current));
      SDL_JoystickClose(current);
    }
    else {
      printf("    Error opening joystick %d: %s\n", i, SDL_GetError());
    }
  }

  if (SDL_NumJoysticks() > 0) {
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);
  }
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
    printf("Unable to initialize SDL properly: %s\n", SDL_GetError());
    exit(1);
  }

  InitializeJoysticks();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window *window = SDL_CreateWindow("Hello World", 100, 100, 1024, 768, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	//SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//SDL_Surface *temp = SDL_LoadBMP("sdl_logo.bmp");
	//SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	GLint majorVersion = 0;
	GLint minorVersion = 0;
	const GLubyte* pszGLversion = glGetString(GL_VERSION);

	if (pszGLversion) {
	  printf("version = %s\n", pszGLversion);
	}
	
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	printf("OpenGL version %d.%d\n", majorVersion, minorVersion);

  CoordinateHelper::InitializeWorld();

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

  GLuint texID = glGetUniformLocation(programID, "myTextureSampler");
  GLuint matID = glGetUniformLocation(programID, "MVP");

  CoordinateHelper::setShaderMatrix(matID);

	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f };

	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  CoordinateHelper::SetGameDimensions(1024.0f, 768.0f);
  std::string filename2 = "BumpTexture.bmp";
  std::string filename1 = "wood.bmp";
  TexturedRectangle rectangle(10.0f, -0.0f, 15.0f, 10.0f, 7.0f, filename1, texID);
  rectangle.Initialize();
  TexturedRectangle rectangle2(300.0f, -500.0f, 245.0f, 60.0f, 10.0f, filename1, texID);
  rectangle2.Initialize();
  TexturedRectangle rectangle3(50.0f, -200.0f, 140.0f, 40.0f, 2.0f, filename2, texID);
  rectangle3.Initialize();
  TexturedRectangle rectangle4(200.0f, 0.0f, 60.0f, 60.0f, 20.0f, filename2, texID);
  rectangle4.Initialize();
  // SDL_FreeSurface(temp);
	SDL_Event event;
	int gameover = 0;
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

	while (!gameover)
	{
		if (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
        case SDL_MOUSEBUTTONDOWN:
          rectangle.AddForce(b2Vec2(50.0f,50.0f));
          rectangle2.AddForce(b2Vec2(50.0f,50.0f));
          rectangle3.AddForce(b2Vec2(50.0f,50.0f));
          rectangle4.AddForce(b2Vec2(50.0f,50.0f));
          break;
				case SDL_QUIT:
					gameover = 1;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;
					}
					break;
      case SDL_JOYBUTTONDOWN:
        if (event.jbutton.button == 0)
          {
            gameover = 1;
            break;
          }
			}
		}

		glClearColor(60,10,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		/*glVertexAttribPointer(
				    0,
				    3,
				    GL_FLOAT,
				    GL_FALSE,
				    0,
				    (void*)0
				    );*/

		//glDrawArrays(GL_TRIANGLES, 0, 6);
    world.Step(timeStep, velocityIterations, positionIterations);
    rectangle.Update();
    rectangle2.Update();
    rectangle3.Update();
    rectangle4.Update();
    
    rectangle.Draw();
    rectangle2.Draw();
    rectangle3.Draw();
    rectangle4.Draw();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
		//SDL_RenderClear(renderer);
		//SDL_RenderCopy(renderer, texture, NULL, NULL);
		

		SDL_GL_SwapWindow(window);
		//SDL_RenderPresent(renderer);i
	}

  if (joystick) {
    SDL_JoystickClose(joystick);
  }
  
	//SDL_DestroyTexture(texture);
	//SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);

	SDL_Quit();
}
