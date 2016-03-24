#include "precomp.h"
#include "CoordinateHelper.h"
#include "Rectangle.h"


Rectangle::Rectangle(GLfloat left, GLfloat top, GLfloat width, GLfloat height, float32 density)
{
  this->SetBounds(left, top, width, height);
  _density = density;
}

Rectangle::~Rectangle()
{
  _body = nullptr;
}

void Rectangle::SetBounds(GLfloat left, GLfloat top, GLfloat width, GLfloat height)
{
  _left = left;
  //_top = CoordinateHelper::getGameHeight() - top; // Invert the y-coodinate
  _top = top;
  _width = width;
  _height = height; 
}

bool Rectangle::Update() 
{
  //if (_density > 5.0) {
  //std::cout << "Applying a force" << std::endl;
    //_body->ApplyForce(b2Vec2(50, 50), _body->GetWorldCenter(), true);
    //}

  if (_body) {
    b2Vec2 pos = _body->GetPosition();
    _left = pos.x;
    _top = -pos.y;
    //std::cout << "Top = " << _top << std::endl;
    }

  _numVertices = RECTANGLE_VERTICES_COUNT;
  _bufferSize = _numVertices * 3;

  _model = glm::mat4(1);
  glm::mat4 rot(1.0f);

  if (_density > 15.0f) {
    float32 angle = _body->GetAngle();
    float32 degrees = glm::degrees(angle);

    while (degrees < 0.0f)
      degrees += 360;

    while (degrees > 360.0f)
      degrees -= 360;

    //std::cout << "degrees = " << degrees << std::endl;
    //std::cout << "angular = " << _body->GetAngularVelocity() << std::endl;
    rot = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(0.0f, 0.0f, 1.0f));
  }

  GLfloat fLeft   = CoordinateHelper::TranslateXToOpenGL(_left);
  GLfloat fTop    = CoordinateHelper::TranslateYToOpenGL(_top);

  _trans = glm::translate(glm::mat4(1.0f), glm::vec3(fLeft, fTop, 0.0f));

  //std::cout << glm::to_string(_trans) << std::endl;
  _model = _trans * rot;

  return true;
}

void Rectangle::AddForce(b2Vec2 force) {
  if (_body) {
    std::cout << "Applying impulse ..." << std::endl;
    //_body->ApplyForce(force, _body->GetWorldCenter(), false);
    _body->SetLinearVelocity(force);
  }
}

bool Rectangle::Initialize()
{
  //Initialize the model matrix to identity
  _model = glm::mat4(1.0f);
  //_model = glm::rotate(_model, 30.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  //Initialize the physics geometry
  b2BodyDef bodyDef;
  if (_density > 11.0f) {
    bodyDef.type = b2_dynamicBody;
  }

  bodyDef.position.Set(_left, _top);

  _body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(_width, _height);

  std::cout << "Density = " << _density << std::endl;
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f; //_density;
  fixtureDef.friction = 0.3f; //1 / _density;
  fixtureDef.restitution = 0.2f;

  b2MassData mass;
  mass.mass = _density * 10.0;
  mass.center = b2Vec2(0.0f, 0.0f);
  mass.I = 0;

  //_body->SetMassData(&mass);

  if (_body) {
    _body->CreateFixture(&fixtureDef);
  }
  else {
    std::cout << "Error creating box2d body" << std::endl;
  }

  if (_density > 11.0) {
  //std::cout << "Applying a force" << std::endl;
    //_body->SetLinearVelocity(b2Vec2(_density, -10*_density));
  }

  GLfloat fLeft   = CoordinateHelper::TranslateXToOpenGL(_left);
  GLfloat fWidth  = CoordinateHelper::TranslateXToOpenGL(_width, true);
  GLfloat fTop    = CoordinateHelper::TranslateYToOpenGL(_top);
  GLfloat fHeight = CoordinateHelper::TranslateYToOpenGL(_height, true);

  _trans = glm::translate(glm::mat4(1.0f), glm::vec3(fLeft, fTop, 0.0f));

  _numVertices = RECTANGLE_VERTICES_COUNT;
  _bufferSize = RECTANGLE_DISTINCT_VERTICES * 3;
  std::cout << _bufferSize << std::endl;

 	glGenBuffers(1, &_vertexBuffer);

  _buffer = new GLfloat[_bufferSize] {
    -(fWidth / 2.0f), (fHeight / 2.0f), 0.0f,
    -(fWidth / 2.0f), -(fHeight / 2.0f), 0.0f,
    (fWidth / 2.0f), -(fHeight / 2.0f), 0.0f,
    (fWidth / 2.0f), (fHeight / 2.0f), 0.0f,
  };

  glGenBuffers(1, &_indexBuffer);

  _indices = new GLuint[_numVertices] {
    0,
    1,
    2,
    2,
    3,
    0
  };


  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _bufferSize * sizeof(GLfloat), _buffer, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numVertices * sizeof(GLuint), _indices, GL_STATIC_DRAW);

	return true;
}
